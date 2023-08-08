// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DiscoverableActors_Shared/Public/Components/ActorsVisibilityController.h"
#include "DiscoverableActorsSubsystem_Client.generated.h"

/**
 * 
 */
UCLASS()
class DISCOVERABLEACTORS_CLIENT_API UDiscoverableActorsSubsystem_Client : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "DiscoverableActors")
	void TryToMakeActorDiscoverableForOwningPlayer(AActor* Actor) const;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	TObjectPtr<APlayerController> GetPrimaryPlayerControllerChecked() const;
	bool AttachVisibilityControllerComponentToPlayer() const;
};
