// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DiscoverableActorsSubsystem_Client.h"

#include "DiscoverableActors_Shared/Public/LogCategoires.h"
#include "DiscoverableActors_Shared/Public/Components/ActorsVisibilityController.h"



void UDiscoverableActorsSubsystem_Client::TryToMakeActorDiscoverableForOwningPlayer(AActor* Actor) const
{
	if (ensureAlwaysMsgf(Actor, TEXT("Actor is nullptr")) == false) return;
	const auto ActorsVisibilityController = GetPrimaryPlayerControllerChecked()->FindComponentByClass<UActorsVisibilityController>();
	if (ensureAlwaysMsgf(ActorsVisibilityController, TEXT("ActorsVisibilityController is nullptr")) == false) return;
	ActorsVisibilityController->MakeActorDiscoverableForOwningPlayer(Actor);
}

bool UDiscoverableActorsSubsystem_Client::AttachVisibilityControllerComponentToPlayer() const
{
	const TObjectPtr<APlayerController> PlayerController = GetPrimaryPlayerControllerChecked();
	checkf(PlayerController, TEXT("PlayerController is nullptr"));
	if(PlayerController->FindComponentByClass<UActorsVisibilityController>() != nullptr)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("PlayerController already has UActorsVisibilityController component"));
		return true;
	}
	PlayerController->AddComponentByClass(UActorsVisibilityController::StaticClass(), true, FTransform::Identity, false);
	return false;
}

void UDiscoverableActorsSubsystem_Client::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

TObjectPtr<APlayerController> UDiscoverableActorsSubsystem_Client::GetPrimaryPlayerControllerChecked() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	checkf(PlayerController, TEXT("PlayerController is nullptr"));
	return PlayerController;
}


