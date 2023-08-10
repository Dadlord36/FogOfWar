// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ActorsDiscoverySubsystem_Server.generated.h"

class UDiscoverableActorsReplicationGraph;
/**
 * 
 */
UCLASS()
class DISCOVERABLEACTORSREPGRAPH_SERVER_API UActorsDiscoverySubsystem_Server : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void SetReplicationGraph(UDiscoverableActorsReplicationGraph* InReplicationGraph) { ReplicationGraph = InReplicationGraph; }

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	void ClaimReplicationGraphPointerChecked();

private:
	UPROPERTY(Transient)
	TObjectPtr<UDiscoverableActorsReplicationGraph> ReplicationGraph;
};
