// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TeamingSubsystem_Server.generated.h"

class UDiscoverableActorsSubsystem;
/**
 *  This subsystem is responsible for teaming players and actors.
 */
UCLASS()
class FOGOFWAR_API UTeamingSubsystem_Server : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * @brief Creates team with given number as id.
	 * @param Team - team number.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void CreateTeam(const int Team);
	/**
	 * @brief Removes team with given number as id.
	 * @param Team - team number.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void RemoveTeam(const int Team);
	/**
	 * @brief Register actors to team, making them replicated for team mates.
	 * @param Actors - actors to register.
	 * @param Team - team number.
     */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void RegisterActorsToTeam(const TArray<AActor*>& Actors, const int Team);
	/**
	 * @brief Removes actors from team, making them not replicated for team mates.
	 * @param Actors - actors to remove.
	 * @param Team - team number.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void RemoveActorsFromTeam(const TArray<AActor*>& Actors, const int Team);
	/**
	 * @brief Register actors to next team, making them replicated for team mates.
	 * @param Actors - actors to register.
	*/
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void RegisterActorsToNextTeam(const TArray<AActor*>& Actors);
	/**
	 * @brief Makes player controller team mate for team.
	 * @param PlayerController - player controller to make team mate.
	 * @param Team - team number.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void MakePlayerBeTeammateForTeam(APlayerController* PlayerController, int Team);
	/**
	 * @brief Removes player controller from team, making team actors not replicated for him.
	 * @param PlayerController - player controller to make team mate.
	 * @param Team - team number.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void RemovePlayerFromTeam(const APlayerController* PlayerController, int Team);
	/**
	 * @brief Makes player controller to be teammate for next team.
	 * @param PlayerController - player controller to make team mate. 
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void MakePlayerBeTeammateForNextTeam(APlayerController* PlayerController);
	/**
	 * @brief Makes player controller to leave the team. Team actors will not be replicated for him anymore.
	 * @param PlayerController - player controller to make team mate.
	 * @param Team - team number.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void MakePlayerToLeaveTeam(const APlayerController* PlayerController, const int Team);
	/**
	 * @brief Makes all players of the team leave it. Team actors will not be replicated for them anymore.
	 * @param Team - team number.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	void MakePlayersToLeaveTeam(const int Team);

	/**
	 * @brief Gets team number for player controller.
	 * @param PlayerController - player controller to get team number.
	 * @return team number. -1 if player controller is not in any team.
	 */
	UFUNCTION(BlueprintCallable, Category = "TeamingSubsystem")
	int GetPlayerTeam(const APlayerController* PlayerController) const;

protected:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

private:
	void MakeTeamActorsReplicatedToPlayer(const APlayerController* PlayerController, const int Team) const;
	void MakeTeamActorsNotReplicatedToPlayer(const APlayerController* PlayerController, const int Team) const;
	void ReplicateActorsToTeam(const TArray<AActor*>& Actors, const int Team) const;
	void StopReplicatingActorsToTeam(const TArray<AActor*>& Actors, const int Team) const;
	bool TeamExists(const int Team) const;;
	void MakeAllPlayersToLeaveAllTeams();

	void MakeActorsBeReplicatedToPlayer(const APlayerController* PlayerController, const TArray<AActor*>& Actors) const;
	void MakeActorsNotBeReplicatedToPlayer(const APlayerController* PlayerController, const TArray<AActor*>& Actors) const;

	UDiscoverableActorsSubsystem* GetDiscoverableActorsSubsystemChecked() const;
	void RegisterPlayerToTeam(APlayerController* PlayerController, const int Team);
	void UnregisterPlayerFromTeam(const APlayerController* PlayerController, const int Team);

	static void MakeArray(const TArray<AActor*>& Actors, TArray<TObjectPtr<const AActor>>& OutArray);

#pragma region Fields

private:
	TMap<int, TArray<AActor*>> TeamToActorsMap;
	TMap<int, TArray<const APlayerController*>> TeamToPlayersMap;

	int TeamsNumber = 0;
	int LastTeamToJoinNumber = 1;
	int32 PlayersPerTeam = 2;
#pragma endregion
};
