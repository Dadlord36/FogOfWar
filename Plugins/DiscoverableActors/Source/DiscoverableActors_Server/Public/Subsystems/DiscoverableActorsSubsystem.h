// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/NetRelevancyDecider.h"
#include "Components/Interfaces/UnitIDManager.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DiscoverableActorsSubsystem.generated.h"

struct FActorDiscoveryRequestData;
class UDiscoverableActorsSystemSettings_Server;
/**
 *  Subsystem for creating and storing discoverable actors system objects
 */
UCLASS()
class DISCOVERABLEACTORS_SERVER_API UDiscoverableActorsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UDiscoverableActorsSubsystem* Get(const TObjectPtr<UObject> WorldContextObject);
	TScriptInterface<INetRelevancyDecider> GetNetRelevancyDecider() const;
	TScriptInterface<IUnitIDManager> GetUnitIDManager() const;
	void MakeActorsDiscoverableForPlayer(TArray<TObjectPtr<AActor>>* Array, const APlayerController* PlayerController) const;

protected:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void StartListeningForActorsDiscoverRequests();
	void StopListeningForActorsDiscoverRequests() const;

	void OnActorDiscoverRequest(FGameplayTag Tag, const FActorDiscoveryRequestData& ActorDiscoveryRequestData);
	
	static TObjectPtr<const UDiscoverableActorsSystemSettings_Server> GetDiscoverableActorsSystemSettings();

private:
	UPROPERTY(Transient)
	TScriptInterface<INetRelevancyDecider> NetRelevancyDecider;
	UPROPERTY(Transient)
	TScriptInterface<IUnitIDManager> UnitIDManager;

	FGameplayMessageListenerHandle ActorsDiscoveryListenerHandle;
};
