// Fill out your copyright notice in the Description page of Project Settings.

#include "FogOfWarGameMode.h"

#include "Graphs/DiscoverableActorsReplicationGraph.h"
#include "FogOfWarLogCategoires.h"


void AFogOfWarGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
}

void AFogOfWarGameMode::CheckNetDriver() const
{
	if (const UNetDriver* NetDriver = GetWorld()->GetNetDriver())
	{
		// Log driver class name
		UE_LOG(LogFogOfWar, Log, TEXT("AFogOfWarGameMode::PostInitializeComponents() NetDriver is %s"), *NetDriver->GetClass()->GetName());
		if (const UDiscoverableActorsReplicationGraph* RepGraph = Cast<UDiscoverableActorsReplicationGraph>(NetDriver->GetReplicationDriver()))
		{
			UE_LOG(LogFogOfWar, Warning, TEXT("AFogOfWarGameMode::PostInitializeComponents() RepGraph is %s"), *RepGraph->GetName());
		}
	}
	else
	{
		UE_LOG(LogFogOfWar, Warning, TEXT("AFogOfWarGameMode::PostInitializeComponents() NetDriver is nullptr"));
	}
}
