// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ControllerComponent.h"
#include "ActorsVisibilityController.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DISCOVERABLEACTORS_SHARED_API UActorsVisibilityController : public UControllerComponent
{
	GENERATED_BODY()

public:
	UActorsVisibilityController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void MakeActorDiscoverableForOwningPlayer(AActor* Actor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION(Server, Reliable)
	void Server_BroadcastMakeActorDiscoverableRequest(AActor* Actor, APlayerController* PlayerController);
};
