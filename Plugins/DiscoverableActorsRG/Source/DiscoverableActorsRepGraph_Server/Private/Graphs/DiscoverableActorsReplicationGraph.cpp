// Fill out your copyright notice in the Description page of Project Settings.


#include "Graphs/DiscoverableActorsReplicationGraph.h"

#include "Nodes/ReplicationGraphNode_PlayerSharedActors.h"
#include "Subsystems/ActorsDiscoverySubsystem_Server.h"


void UDiscoverableActorsReplicationGraph::InitForNetDriver(UNetDriver* InNetDriver)
{
	Super::InitForNetDriver(InNetDriver);
	GetWorld()->GetSubsystem<UActorsDiscoverySubsystem_Server>()->SetReplicationGraph(this);
}

void UDiscoverableActorsReplicationGraph::InitGlobalActorClassSettings()
{
	Super::InitGlobalActorClassSettings();

	// ReplicationGraph stores internal associative data for actor classes. 
	// We build this data here based on actor CDO values.
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;
		const AActor* ActorCDO = Cast<AActor>(Class->GetDefaultObject());
		if (!ActorCDO || !ActorCDO->GetIsReplicated())
		{
			continue;
		}

		// Skip SKEL and REINST classes.
		if (Class->GetName().StartsWith(TEXT("SKEL_")) || Class->GetName().StartsWith(TEXT("REINST_")))
		{
			continue;
		}

		FClassReplicationInfo ClassInfo;

		// Replication Graph is frame based. Convert NetUpdateFrequency to ReplicationPeriodFrame based on Server MaxTickRate.
		ClassInfo.ReplicationPeriodFrame = GetReplicationPeriodFrameForFrequency(ActorCDO->NetUpdateFrequency);

		if (ActorCDO->bAlwaysRelevant || ActorCDO->bOnlyRelevantToOwner)
		{
			ClassInfo.SetCullDistanceSquared(1.f);
		}
		else
		{
			ClassInfo.SetCullDistanceSquared(ActorCDO->NetCullDistanceSquared);
		}

		GlobalActorReplicationInfoMap.SetClassInfo(Class, ClassInfo);
	}
}

void UDiscoverableActorsReplicationGraph::InitGlobalGraphNodes()
{
	// -----------------------------------------------
	//	Spatial Actors
	// -----------------------------------------------

	/*GridNode = CreateNewNode<UReplicationGraphNode_GridSpatialization2D>();
	GridNode->CellSize = 10000.f;
	GridNode->SpatialBias = FVector2D(-UE_OLD_WORLD_MAX, -UE_OLD_WORLD_MAX);

	AddGlobalGraphNode(GridNode);*/

	// -----------------------------------------------
	//	Always Relevant (to everyone) Actors
	// -----------------------------------------------
	AlwaysRelevantNode = CreateNewNode<UReplicationGraphNode_ActorList>();
	AddGlobalGraphNode(AlwaysRelevantNode);
}

void UDiscoverableActorsReplicationGraph::InitConnectionGraphNodes(UNetReplicationGraphConnection* RepGraphConnection)
{
	Super::InitConnectionGraphNodes(RepGraphConnection);

	UReplicationGraphNode_AlwaysRelevant_ForConnection* ConnectionBasedRootNode = CreateNewNode<UReplicationGraphNode_AlwaysRelevant_ForConnection>();
	AddConnectionGraphNode(ConnectionBasedRootNode, RepGraphConnection);

	AlwaysRelevantForConnectionList.Emplace(RepGraphConnection->NetConnection, ConnectionBasedRootNode);
}

void UDiscoverableActorsReplicationGraph::RouteAddNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo,
                                                                      FGlobalActorReplicationInfo& GlobalInfo)
{
	ensureMsgf((ActorInfo.Actor->bAlwaysRelevant && ActorInfo.Actor->bOnlyRelevantToOwner) == false,
	           TEXT("Replicated actor %s is both bAlwaysRelevant and bOnlyRelevantToOwner. Only one can be supported."), *ActorInfo.Actor->GetName());
	if (ActorInfo.Actor->bAlwaysRelevant)
	{
		AlwaysRelevantNode->NotifyAddNetworkActor(ActorInfo);
	}
	else if (ActorInfo.Actor->bOnlyRelevantToOwner)
	{
		ActorsWithoutNetConnection.Add(ActorInfo.Actor);
	}
	else
	{
		if(AlwaysRelevantForConnectionList.IsEmpty()) return;
		AlwaysRelevantForConnectionList[0].Node->NotifyAddNetworkActor(ActorInfo);

		// Note that UReplicationGraphNode_GridSpatialization2D has 3 methods for adding actor based on the mobility of the actor. Since AActor lacks this information, we will
		// add all spatialized actors as dormant actors: meaning they will be treated as possibly dynamic (moving) when not dormant, and as static (not moving) when dormant.
		// GridNode->AddActor_Dormancy(ActorInfo, GlobalInfo);
	}
}

void UDiscoverableActorsReplicationGraph::RouteRemoveNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo)
{
	if (ActorInfo.Actor->bAlwaysRelevant)
	{
		AlwaysRelevantNode->NotifyRemoveNetworkActor(ActorInfo);
		SetActorDestructionInfoToIgnoreDistanceCulling(ActorInfo.GetActor());
	}
	else if (ActorInfo.Actor->bOnlyRelevantToOwner)
	{
		if (UReplicationGraphNode* Node = ActorInfo.Actor->GetNetConnection()
			                                  ? GetAlwaysRelevantNodeForConnection(ActorInfo.Actor->GetNetConnection())
			                                  : nullptr)
		{
			if (Node == nullptr)
			{
				return;
			}
			Node->NotifyRemoveNetworkActor(ActorInfo);
		}
	}
	else
	{
		// GridNode->RemoveActor_Dormancy(ActorInfo);
	}
}

int32 UDiscoverableActorsReplicationGraph::ServerReplicateActors(const float DeltaSeconds)
{
	// Route Actors needing owning net connections to appropriate nodes
	for (int32 Idx = ActorsWithoutNetConnection.Num() - 1; Idx >= 0; --Idx)
	{
		bool bRemove = false;
		if (AActor* Actor = ActorsWithoutNetConnection[Idx])
		{
			if (UNetConnection* Connection = Actor->GetNetConnection())
			{
				bRemove = true;
				if (UReplicationGraphNode_AlwaysRelevant_ForConnection* Node = GetAlwaysRelevantNodeForConnection(Actor->GetNetConnection()))
				{
					Node->NotifyAddNetworkActor(FNewReplicatedActorInfo(Actor));
				}
			}
		}
		else
		{
			bRemove = true;
		}

		if (bRemove)
		{
			ActorsWithoutNetConnection.RemoveAtSwap(Idx, 1, false);
		}
	}


	return Super::ServerReplicateActors(DeltaSeconds);
}

void UDiscoverableActorsReplicationGraph::TearDown()
{
	Super::TearDown();
}

UReplicationGraphNode_AlwaysRelevant_ForConnection* UDiscoverableActorsReplicationGraph::GetAlwaysRelevantNodeForConnection(
	UNetConnection* Connection)
{
	UReplicationGraphNode_AlwaysRelevant_ForConnection* Node = nullptr;
	if (Connection)
	{
		if (const FConnectionAlwaysRelevant_NodePair* Pair = AlwaysRelevantForConnectionList.FindByKey(Connection))
		{
			if (Pair->Node)
			{
				Node = Pair->Node;
			}
			else
			{
				UE_LOG(LogNet, Warning, TEXT("AlwaysRelevantNode for connection %s is null."), *GetNameSafe(Connection));
			}
		}
		else
		{
			UE_LOG(LogNet, Warning,
			       TEXT(
				       "Could not find AlwaysRelevantNode for connection %s. This should have been created in UBasicReplicationGraph::InitConnectionGraphNodes."
			       ), *GetNameSafe(Connection));
		}
	}
	else
	{
		// Basic implementation requires owner is set on spawn that never changes. A more robust graph would have methods or ways of listening for owner to change
		UE_LOG(LogNet, Warning, TEXT("Actor: %s is bOnlyRelevantToOwner but does not have an owning Netconnection. It will not be replicated"));
	}

	return Node;
}

bool FConnectionAlwaysRelevant_NodePair::operator==(UNetConnection* InConnection) const
{
	// Any children should be looking at their parent connections instead.
	if (InConnection->GetUChildConnection() != nullptr)
	{
		InConnection = static_cast<UChildConnection*>(InConnection)->Parent;
	}

	return InConnection == NetConnection;
}
