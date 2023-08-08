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

void UActorsVisibilityController::MakeActorDiscoverableForOwningPlayer(AActor* Actor)
{
	if (!Actor)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor is nullptr"));
		return;
	}

	Server_BroadcastMakeActorDiscoverableRequest(Actor, GetControllerChecked<APlayerController>());
}

// Called when the game starts
void UActorsVisibilityController::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UActorsVisibilityController::Server_BroadcastMakeActorDiscoverableRequest_Implementation(AActor* Actor, APlayerController* PlayerController)
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage<FActorDiscoveryRequestData>(Channels_ActorsControl_ActorsDiscovery,
	                                                              FActorDiscoveryRequestData(PlayerController, Actor));
}
