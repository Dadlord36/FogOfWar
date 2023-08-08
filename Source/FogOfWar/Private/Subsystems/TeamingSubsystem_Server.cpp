// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TeamingSubsystem_Server.h"

#include "Subsystems/DiscoverableActorsSubsystem.h"

void UTeamingSubsystem_Server::RegisterActorsToNextTeam(const TArray<AActor*> Actors)
{
	RegisterActorsToTeam(Actors, TeamsNumber);
	TeamsNumber++;
}

void UTeamingSubsystem_Server::MakeBeTeamMateForNextTeam(APlayerController* PlayerController)
{
	MakeBeTeamMateFor(PlayerController, LastTeamToJoinNumber);
	LastTeamToJoinNumber++;
}

void UTeamingSubsystem_Server::MakeBeTeamMateFor(APlayerController* PlayerController, const int Team)
{
	const auto DiscoverableActorsSubsystem = UDiscoverableActorsSubsystem::Get(this);
	if (ensureAlwaysMsgf(DiscoverableActorsSubsystem, TEXT("DiscoverableActorsSubsystem is nullptr")) == false) return;
	TArray<TObjectPtr<AActor>>* ActorsPtr = TeamToActorsMap.Find(Team);
	if(ensureAlwaysMsgf(ActorsPtr, TEXT("ActorsPtr is nullptr")) == false) return;
	DiscoverableActorsSubsystem->MakeActorsDiscoverableForPlayer(ActorsPtr, PlayerController);
}

bool UTeamingSubsystem_Server::ShouldCreateSubsystem(UObject* Outer) const
{
	// Only create this subsystem on the server
	const auto NetMode = Outer->GetWorld()->GetNetMode();
	return NetMode == NM_DedicatedServer || NetMode == NM_ListenServer;
}

void UTeamingSubsystem_Server::RegisterActorsToTeam(const TArray<AActor*>& Actors, const int Team)
{
	TArray<TObjectPtr<AActor>>* ActorsPtr = TeamToActorsMap.Find(Team);
	if (ActorsPtr == nullptr)
	{
		TArray<TObjectPtr<AActor>> OutArray;
		MakeArray(Actors, OutArray);
		TeamToActorsMap.Add(Team, OutArray);
	}
	else
	{
		ActorsPtr->Append(Actors);
	}
}

void UTeamingSubsystem_Server::MakeArray(const TArray<AActor*>& Actors, TArray<TObjectPtr<AActor>>& OutArray)
{
	for (const auto& Actor : Actors)
	{
		OutArray.Add(Actor);
	}
}
