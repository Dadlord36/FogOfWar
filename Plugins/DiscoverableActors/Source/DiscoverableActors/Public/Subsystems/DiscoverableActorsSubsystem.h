// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DiscoverableActorsSubsystem.generated.h"

class INetRelevancyDecider;
class UDiscoverableActorsSystemSettings;
/**
 * 
 */
UCLASS()
class DISCOVERABLEACTORS_API UDiscoverableActorsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	INetRelevancyDecider* GetNetRelevancyDecider() const;

private:
	static TObjectPtr<const UDiscoverableActorsSystemSettings> GetDiscoverableActorsSystemSettings();

private:
	UPROPERTY(Transient)
	TObjectPtr<UActorComponent> NetRelevancyDecider;
};
