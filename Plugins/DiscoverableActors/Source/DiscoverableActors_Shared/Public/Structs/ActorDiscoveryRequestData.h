// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

#include "ActorDiscoveryRequestData.generated.h"

//Declare tag for messaging channel
DISCOVERABLEACTORS_SHARED_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ActorsDiscovery_ShowupForPlayer);
DISCOVERABLEACTORS_SHARED_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ActorsDiscovery_HideForPlayer);

/**
 *  Struct that contains data for actor discovery request
 */
USTRUCT()
struct DISCOVERABLEACTORS_SHARED_API FActorDiscoveryRequestData
{
	GENERATED_BODY()

public:
	FActorDiscoveryRequestData() = default;

	FActorDiscoveryRequestData(const TObjectPtr<APlayerController>& PlayerController, const TArray<AActor*>& ActorToMakeDiscoverable)
		: PlayerController(PlayerController),
		  ActorsToAlterVisibility(ActorToMakeDiscoverable)
	{
	}

	bool IsDataValid() const
	{
		return ensureAlwaysMsgf(PlayerController != nullptr, TEXT("Invalid actor discovery request data"));
	}

public:
	UPROPERTY(Transient)
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>> ActorsToAlterVisibility;
};
