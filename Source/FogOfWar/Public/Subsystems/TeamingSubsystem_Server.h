// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TeamingSubsystem_Server.generated.h"

/**
 * 
 */
UCLASS()
class FOGOFWAR_API UTeamingSubsystem_Server : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterActorsToNextTeam(TArray<AActor*> Actors);
	UFUNCTION(BlueprintCallable)
	void MakeBeTeamMateForNextTeam(APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable)
	void MakeBeTeamMateFor(APlayerController* PlayerController, int Team);

protected:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

private:
	void RegisterActorsToTeam(const TArray<AActor*>& Actors, int Team);
	static void MakeArray(const TArray<AActor*>& Actors, TArray<TObjectPtr<AActor>>& OutArray);
	
private:
	TMap<int, TArray<TObjectPtr<AActor>>> TeamToActorsMap;

	int TeamsNumber = 0;
	int LastTeamToJoinNumber = 0;
};
