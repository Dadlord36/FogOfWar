// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorsGroupManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOGOFWAR_API UActorsGroupManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActorsGroupManager();

	void SetGroupActors(const TArray<TObjectPtr<AActor>>& Actors);
	const TArray<TObjectPtr<AActor>>& GetGroupActors() const { return SpawnedActors; }

	/**
	* @brief Clear spawned actors. Should work both in editor and in game.
	*/
	UFUNCTION(CallInEditor, Category = "Debug")
	void ClearSpawnedActors();

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Debug")
	void ApplyColorToGroup() const;

private:
	UPROPERTY(EditAnywhere, Category = "Parameters")
	FLinearColor GroupColor = FLinearColor::Black;
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;
};
