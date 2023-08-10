// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicationGraph.h"
#include "ReplicationGraphNode_PlayerSharedActors.generated.h"

/**
 * 
 */
UCLASS()
class DISCOVERABLEACTORSREPGRAPH_SERVER_API UReplicationGraphNode_PlayerSharedActors : public UReplicationGraphNode_ActorList
{
	GENERATED_BODY()

public:
	virtual void GatherActorListsForConnection(const FConnectionGatherActorListParameters& Params) override;
};
