// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridFormationSpawner.generated.h"


class UActorsGroupManager;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOGOFWAR_API UGridFormationSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGridFormationSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//This function can be called with actor inspector button
	UFUNCTION(CallInEditor, Category = "Debug")
	void RespawnActorsInGridFormation() const;
	virtual void OnRegister() override;

private:
	/**
	 * @brief Form spawn locations in grid formation.
	 * @return Spawn locations.
	 */
	TArray<FVector> FormSpawnLocations() const;

	/**
	 * @brief Spawn actors at specified locations.
	 * @param SpawnLocations Locations to spawn actors at.
	 */
	void SpawnActors(const TArray<FVector>& SpawnLocations) const;

	TObjectPtr<UActorsGroupManager> GetActorsGroupManager() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	TSoftClassPtr<AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float CellsDistance = 100.f;
	UPROPERTY(EditAnywhere, Category = "Parameters")
	FIntVector2 GridSize;
	
	UPROPERTY(Transient)
	TObjectPtr<UActorsGroupManager> GroupManager;
	
};
