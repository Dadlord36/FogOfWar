// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DiscoverableActorsSystemSettings.generated.h"

/**
 * 
 */
UCLASS(config = DiscoverableActorsSystem, defaultconfig)
class DISCOVERABLEACTORS_API UDiscoverableActorsSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (MustImplement = "INetRelevancyDecider"))
	TSoftClassPtr<UActorComponent> NetRelevancyDeciderComponentClass;
};
