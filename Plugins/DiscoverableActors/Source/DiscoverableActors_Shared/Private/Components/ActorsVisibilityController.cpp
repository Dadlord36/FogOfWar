// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorsVisibilityController.h"

#include "LogCategoires.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Structs/ActorDiscoveryRequestData.h"

UActorsVisibilityController::UActorsVisibilityController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	// Make replicated
	SetIsReplicatedByDefault(true);
}

void UActorsVisibilityController::MakeActorsDiscoverableForOwningPlayer(const TArray<AActor*>& Actors) const
{
	Server_BroadcastMakeActorsDiscoverableRequest(Actors, GetControllerChecked<APlayerController>());
}


// Called when the game starts
void UActorsVisibilityController::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UActorsVisibilityController::Server_BroadcastMakeActorsDiscoverableRequest_Implementation(const TArray<AActor*>& Actors,
                                                                                               APlayerController* PlayerController) const 
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage<FActorDiscoveryRequestData>(TAG_ActorsDiscovery_ShowupForPlayer,
	                                                              FActorDiscoveryRequestData(PlayerController, Actors));
}
