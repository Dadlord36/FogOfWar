// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicationGraph.h"

#include "DiscoverableActorsReplicationGraph.generated.h"

struct FNewReplicatedActorInfo;

USTRUCT()
struct FConnectionAlwaysRelevant_NodePair
{
	GENERATED_BODY()
	FConnectionAlwaysRelevant_NodePair() { }
	FConnectionAlwaysRelevant_NodePair(UNetConnection* InConnection, UReplicationGraphNode_AlwaysRelevant_ForConnection* InNode) : NetConnection(InConnection), Node(InNode) { }
	bool operator==(UNetConnection* InConnection) const;

	UPROPERTY()
	TObjectPtr<UNetConnection> NetConnection = nullptr;

	UPROPERTY()
	TObjectPtr<UReplicationGraphNode_AlwaysRelevant_ForConnection> Node = nullptr;	
};

/**
 * 
 */
UCLASS(Transient, Config=Engine)
class DISCOVERABLEACTORSREPGRAPH_SERVER_API UDiscoverableActorsReplicationGraph : public UReplicationGraph
{
	GENERATED_BODY()

public:
	virtual void InitForNetDriver(UNetDriver* InNetDriver) override;
	virtual void InitGlobalActorClassSettings() override;
	virtual void InitGlobalGraphNodes() override;
	virtual void InitConnectionGraphNodes(UNetReplicationGraphConnection* RepGraphConnection) override;
	virtual void RouteAddNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalInfo) override;
	virtual void RouteRemoveNetworkActorToNodes(const FNewReplicatedActorInfo& ActorInfo) override;

	virtual int32 ServerReplicateActors(float DeltaSeconds) override;
	virtual void TearDown() override;
	/*UPROPERTY()
	TObjectPtr<UReplicationGraphNode_GridSpatialization2D> GridNode;*/

	UPROPERTY()
	TObjectPtr<UReplicationGraphNode_ActorList> AlwaysRelevantNode;

	UPROPERTY()
	TArray<FConnectionAlwaysRelevant_NodePair> AlwaysRelevantForConnectionList;

	/** Actors that are only supposed to replicate to their owning connection, but that did not have a connection on spawn */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> ActorsWithoutNetConnection;


	UReplicationGraphNode_AlwaysRelevant_ForConnection* GetAlwaysRelevantNodeForConnection(UNetConnection* Connection);
};
