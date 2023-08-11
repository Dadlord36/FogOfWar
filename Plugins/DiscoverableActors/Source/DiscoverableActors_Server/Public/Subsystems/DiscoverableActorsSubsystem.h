// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "DiscoverableActorsSubsystem.generated.h"

struct FActorDiscoveryRequestData;
class IUnitIDManager;
class INetRelevancyDecider;
class UDiscoverableActorsSystemSettings_Server;
/**
 *  Subsystem for managing actors discoverability
 */
UCLASS()
class DISCOVERABLEACTORS_SERVER_API UDiscoverableActorsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * @brief Makes actors replicated for player controller.
	 * @param Array - actors to make replicated.
	 * @param PlayerController - player controller to make actors replicated for.
	 */
	UFUNCTION(BlueprintCallable, Category = "DiscoverableActors")
	void MakeActorsReplicatedForPlayer(const TArray<AActor*>& Array, const APlayerController* PlayerController) const;
	/**
	 * @brief Makes actors not replicated for player controller.
	 * @param Array - actors to make not replicated.
	 * @param PlayerController - player controller to make actors not replicated for.
	 */
	UFUNCTION(BlueprintCallable, Category = "DiscoverableActors")
	void MakeActorsNotReplicatedForPlayer(const TArray<AActor*>& Array, const APlayerController* PlayerController) const;
	
	TScriptInterface<INetRelevancyDecider> GetNetRelevancyDecider() const;
	TScriptInterface<IUnitIDManager> GetUnitIDManager() const;
	static UDiscoverableActorsSubsystem* Get(const TObjectPtr<UObject> WorldContextObject);
	
protected:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void StartListeningForActorsDiscoverRequests();
	void StopListeningForActorsDiscoverRequests() const;

	void OnActorsDiscoverRequest(FGameplayTag GameplayTag, const FActorDiscoveryRequestData& ActorDiscoveryRequestData);
	void OnActorsHidingRequest(FGameplayTag GameplayTag, const FActorDiscoveryRequestData& ActorDiscoveryRequestData);
	
	static TObjectPtr<const UDiscoverableActorsSystemSettings_Server> GetDiscoverableActorsSystemSettings();

private:
	UPROPERTY(Transient)
	TScriptInterface<INetRelevancyDecider> NetRelevancyDecider;
	UPROPERTY(Transient)
	TScriptInterface<IUnitIDManager> UnitIDManager;

	FGameplayMessageListenerHandle ActorsDiscoveryListenerHandle;
	FGameplayMessageListenerHandle ActorsHidingListenerHandle;
};
