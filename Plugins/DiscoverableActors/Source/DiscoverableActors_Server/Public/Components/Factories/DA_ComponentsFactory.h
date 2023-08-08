// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/NetRelevancyDecider.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DA_ComponentsFactory.generated.h"

class IUnitIDManager;
/**
 * Factory class for creating components
 */
UCLASS()
class DISCOVERABLEACTORS_SERVER_API UDA_ComponentsFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Creates net relevancy decider object
	 * @param Outer Outer object
	 * @param Subclass Class of the Decider. Must implement INetRelevancyDecider interface. Will be loaded synchronously.
	 * @param UnitIDManager Unit ID Manager
	 * @return Created object interface
	 */
	static TScriptInterface<INetRelevancyDecider> CreateNetRelevancyDecider(TObjectPtr<UObject> const Outer, const TSoftClassPtr<>& Subclass,
	                                                                        const TScriptInterface<IUnitIDManager> UnitIDManager);
};
