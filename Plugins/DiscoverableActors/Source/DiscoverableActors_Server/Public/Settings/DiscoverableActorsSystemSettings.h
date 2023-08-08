// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DiscoverableActorsSystemSettings.generated.h"

class IUnitIDManager;
class INetRelevancyDecider;

/**
 * Game settings for Discoverable Actors System
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Discoverable Actors System Server")) 
class DISCOVERABLEACTORS_SERVER_API UDiscoverableActorsSystemSettings_Server : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (MustImplement = "NetRelevancyDecider"))
	TSoftClassPtr<UObject> NetRelevancyDeciderClass;
	UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (MustImplement = "UnitIDManager"))
	TSoftClassPtr<UObject> UnitIDManagerClass;
};
