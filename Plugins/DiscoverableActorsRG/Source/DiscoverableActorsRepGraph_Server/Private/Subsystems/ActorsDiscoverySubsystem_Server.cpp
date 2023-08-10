// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ActorsDiscoverySubsystem_Server.h"

#include "Graphs/DiscoverableActorsReplicationGraph.h"

void UActorsDiscoverySubsystem_Server::ClaimReplicationGraphPointerChecked()
{
	const auto World = GetWorld();
	const auto NetDriver = World->GetNetDriver();
	checkf(NetDriver, TEXT("NetDriver is nullptr"));
	const auto ReplicationDriver = NetDriver->GetReplicationDriver();
	checkf(ReplicationDriver, TEXT("ReplicationDriver is nullptr"));
	
	ReplicationGraph =  Cast<UDiscoverableActorsReplicationGraph>(ReplicationDriver);
	checkf(ReplicationGraph, TEXT("ReplicationGraph is nullptr"));
}

void UActorsDiscoverySubsystem_Server::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}
