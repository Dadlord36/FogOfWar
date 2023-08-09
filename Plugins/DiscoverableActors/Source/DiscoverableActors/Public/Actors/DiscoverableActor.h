// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/UnitIdProvider.h"
#include "GameFramework/Actor.h"
#include "DiscoverableActor.generated.h"

#if WITH_SERVER_CODE
class IUnitIDManager;
class INetRelevancyDecider;
#endif

/**
 *  Base class for discoverable actors. It will be replicated to clients only if it is visible for them. Relay on teaming system.
 *  Once created it will claim unit id from UnitIDManager and release it when destroyed.
 */
UCLASS()
class DISCOVERABLEACTORS_API ADiscoverableActor : public AActor, public IUnitIdProvider
{
	GENERATED_BODY()

public:
	ADiscoverableActor();

#if WITH_SERVER_CODE
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

	virtual int GetUnitID() const override { return UnitID; }
	void SetFallbackToDefaultRelevancy(const bool bInFallbackToDefaultRelevancy) { bFallbackToDefaultRelevancy = bInFallbackToDefaultRelevancy; }
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the game ends or when destroyed 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
#if WITH_SERVER_CODE
	void ClaimUnitID();
	void ReleaseUnitID() const;
#endif

private:
#if WITH_SERVER_CODE
#pragma region Fileds
	int32 bFallbackToDefaultRelevancy = 0;
	int UnitID = -1;
	TScriptInterface<INetRelevancyDecider> NetRelevancyDecider;
	TScriptInterface<IUnitIDManager> UnitIDManager;
#pragma endregion
#endif
};
