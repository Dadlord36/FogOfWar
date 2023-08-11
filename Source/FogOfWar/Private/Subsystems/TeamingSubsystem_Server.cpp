// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TeamingSubsystem_Server.h"

#include "FogOfWarLogCategoires.h"
#include "Subsystems/DiscoverableActorsSubsystem.h"

void UTeamingSubsystem_Server::CreateTeam(const int Team)
{
	if (TeamExists(Team) == false)
	{
		TeamToActorsMap.Add(Team, {});
		TeamToPlayersMap.Add(Team, {});
	}
}

void UTeamingSubsystem_Server::RemoveTeam(const int Team)
{
	if (TeamExists(Team) == false) return;

	MakePlayersToLeaveTeam(Team);

	TeamToActorsMap.Remove(Team);
	TeamToPlayersMap.Remove(Team);
}

void UTeamingSubsystem_Server::RegisterActorsToTeam(const TArray<AActor*>& Actors, const int Team)
{
	if (TeamExists(Team) == false) return;

	const auto ActorsPtr = TeamToActorsMap.Find(Team);

	checkf(ActorsPtr != nullptr, TEXT("ActorsPtr is nullptr"));
	ActorsPtr->Append(Actors);

	ReplicateActorsToTeam(Actors, Team);
}

void UTeamingSubsystem_Server::RemoveActorsFromTeam(const TArray<AActor*>& Actors, const int Team)
{
	if (TeamExists(Team) == false) return;

	const auto ActorsPtr = TeamToActorsMap.Find(Team);
	if (ActorsPtr == nullptr) return;

	ActorsPtr->RemoveAllSwap([&Actors](const TObjectPtr<AActor>& Actor)
	{
		return Actors.Contains(Actor);
	});

	StopReplicatingActorsToTeam(Actors, Team);
}

void UTeamingSubsystem_Server::RegisterActorsToNextTeam(const TArray<AActor*>& Actors)
{
	RegisterActorsToTeam(Actors, TeamsNumber);
	TeamsNumber++;
}

void UTeamingSubsystem_Server::MakePlayerBeTeammateForNextTeam(APlayerController* PlayerController)
{
	if (ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is nullptr")) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("PlayerController is nullptr"));
		return;
	}

	MakePlayerBeTeammateForTeam(PlayerController, LastTeamToJoinNumber % 3);

	LastTeamToJoinNumber++;
}

void UTeamingSubsystem_Server::MakePlayerBeTeammateForTeam(APlayerController* PlayerController, const int Team)
{
	if (ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is nullptr")) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("PlayerController is nullptr"));
		return;
	}
	if (TeamExists(Team) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("Team %d does not exist"), Team);
	}

	RegisterPlayerToTeam(PlayerController, Team);

	MakeTeamActorsReplicatedToPlayer(PlayerController, Team);
}

void UTeamingSubsystem_Server::RemovePlayerFromTeam(const APlayerController* PlayerController, const int Team)
{
	if (ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is nullptr")) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("PlayerController is nullptr"));
		return;
	}
	if (TeamExists(Team) == false) return;

	UnregisterPlayerFromTeam(PlayerController, Team);

	MakeTeamActorsNotReplicatedToPlayer(PlayerController, Team);
}

void UTeamingSubsystem_Server::MakeActorsBeReplicatedToPlayer(const APlayerController* PlayerController,
                                                              const TArray<AActor*>& Actors) const
{
	GetDiscoverableActorsSubsystemChecked()->MakeActorsReplicatedForPlayer(Actors, PlayerController);
}

void UTeamingSubsystem_Server::MakeActorsNotBeReplicatedToPlayer(const APlayerController* PlayerController,
                                                                 const TArray<AActor*>& Actors) const
{
	GetDiscoverableActorsSubsystemChecked()->MakeActorsNotReplicatedForPlayer(Actors, PlayerController);
}

UDiscoverableActorsSubsystem* UTeamingSubsystem_Server::GetDiscoverableActorsSubsystemChecked() const
{
	const auto DiscoverableActorsSubsystem = UDiscoverableActorsSubsystem::Get(GetWorld());
	checkf(DiscoverableActorsSubsystem, TEXT("DiscoverableActorsSubsystem is nullptr"));
	return DiscoverableActorsSubsystem;
}

void UTeamingSubsystem_Server::RegisterPlayerToTeam(APlayerController* PlayerController, const int Team)
{
	if (ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is nullptr")) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("PlayerController is nullptr"));
		return;
	}
	if (TeamExists(Team) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("Team %d does not exist"), Team);
		return;
	}
	const auto Players = TeamToPlayersMap.Find(Team);

	Players->Add(PlayerController);
}

void UTeamingSubsystem_Server::UnregisterPlayerFromTeam(const APlayerController* PlayerController, const int Team)
{
	if (ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is nullptr")) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("PlayerController is nullptr"));
		return;
	}
	if (TeamExists(Team) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("Team %d does not exist"), Team);
		return;
	}
	const auto Players = TeamToPlayersMap.Find(Team);

	Players->Remove(PlayerController);
}

void UTeamingSubsystem_Server::MakeTeamActorsReplicatedToPlayer(const APlayerController* PlayerController, const int Team) const
{
	if (ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is nullptr")) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("PlayerController is nullptr"));
		return;
	}

	if (TeamToActorsMap.Contains(Team) == false) return;

	const auto& Actors = TeamToActorsMap.FindRef(Team);
	MakeActorsBeReplicatedToPlayer(PlayerController, Actors);
}

void UTeamingSubsystem_Server::MakeTeamActorsNotReplicatedToPlayer(const APlayerController* PlayerController, const int Team) const
{
	if (ensureAlwaysMsgf(PlayerController, TEXT("PlayerController is nullptr")) == false)
	{
		UE_LOG(LogFogOfWar, Error, TEXT("PlayerController is nullptr"));
		return;
	}

	if (TeamToActorsMap.Contains(Team) == false) return;

	const auto& Actors = TeamToActorsMap.FindRef(Team);
	MakeActorsNotBeReplicatedToPlayer(PlayerController, Actors);
}

void UTeamingSubsystem_Server::ReplicateActorsToTeam(const TArray<AActor*>& Actors, const int Team) const
{
	if (TeamExists(Team) == false) return;
	auto Teammates = TeamToPlayersMap.FindRef(Team);
	for (const auto& PlayerController : Teammates)
	{
		MakeActorsBeReplicatedToPlayer(PlayerController, Actors);
	}
}

void UTeamingSubsystem_Server::StopReplicatingActorsToTeam(const TArray<AActor*>& Actors, const int Team) const
{
	if (TeamExists(Team) == false) return;
	auto Teammates = TeamToPlayersMap.FindRef(Team);
	for (const auto& PlayerController : Teammates)
	{
		MakeActorsNotBeReplicatedToPlayer(PlayerController, Actors);
	}
}

bool UTeamingSubsystem_Server::TeamExists(const int Team) const
{
	return TeamToActorsMap.Contains(Team) && TeamToPlayersMap.Contains(Team);
}

void UTeamingSubsystem_Server::MakePlayerToLeaveTeam(const APlayerController* PlayerController, const int Team)
{
	if (TeamExists(Team) == false) return;

	UnregisterPlayerFromTeam(PlayerController, Team);
	MakeTeamActorsNotReplicatedToPlayer(PlayerController, Team);
}

void UTeamingSubsystem_Server::MakePlayersToLeaveTeam(const int Team)
{
	if (TeamExists(Team) == false) return;

	auto Teammates = TeamToPlayersMap.FindRef(Team);
	for (const auto& PlayerController : Teammates)
	{
		MakePlayerToLeaveTeam(PlayerController, Team);
	}
}

int UTeamingSubsystem_Server::GetPlayerTeam(const APlayerController* PlayerController) const
{
	for (const auto& Team : TeamToPlayersMap)
	{
		if (Team.Value.Contains(PlayerController))
		{
			return Team.Key;
		}
	}
	return -1;
}

void UTeamingSubsystem_Server::MakeAllPlayersToLeaveAllTeams()
{
	for (const auto& Team : TeamToPlayersMap)
	{
		MakePlayersToLeaveTeam(Team.Key);
	}
}

bool UTeamingSubsystem_Server::ShouldCreateSubsystem(UObject* Outer) const
{
	// Only create this subsystem on the server
	const auto NetMode = Outer->GetWorld()->GetNetMode();
	return NetMode == NM_DedicatedServer || NetMode == NM_ListenServer;
}

void UTeamingSubsystem_Server::MakeArray(const TArray<AActor*>& Actors, TArray<TObjectPtr<const AActor>>& OutArray)
{
	for (const auto& Actor : Actors)
	{
		OutArray.Add(Actor);
	}
}
