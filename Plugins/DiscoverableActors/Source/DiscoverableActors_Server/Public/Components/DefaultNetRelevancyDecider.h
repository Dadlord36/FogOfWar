// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Interfaces/NetRelevancyDecider.h"
#include "Interfaces/UnitIDManager.h"
#include "DefaultNetRelevancyDecider.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DISCOVERABLEACTORS_SERVER_API UDefaultNetRelevancyDecider : public UObject, public INetRelevancyDecider
{
	GENERATED_BODY()

public:
	void Initialize(const TScriptInterface<IUnitIDManager> InUnitIDManager) { UnitIDManager = InUnitIDManager; }
	virtual bool DetermineNetRelevancy_Implementation(const AActor* RealViewer,const AActor* ViewTarget, const FVector& SrcLocation) override;

protected:
	static uint32 GetPlayerControllerNumberChecked(const AActor* RealViewer);
	
private:
	UPROPERTY(Transient)
	TScriptInterface<IUnitIDManager> UnitIDManager;
};
