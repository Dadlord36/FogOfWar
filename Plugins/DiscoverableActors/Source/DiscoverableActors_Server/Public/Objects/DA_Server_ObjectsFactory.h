// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DA_Server_ObjectsFactory.generated.h"

class UDefaultUnitIDManager;
/**
 * 
 */
UCLASS()
class DISCOVERABLEACTORS_SERVER_API UDA_Server_ObjectsFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Create UnitIDProvider object
	 * @param Owner - owner of the object
	 * @param UnitIDProviderClass - class of the object.
	 * @return UnitIDProvider object
	 */
	static TScriptInterface<class IUnitIDManager> CreateUnitIDProvider(const TObjectPtr<UObject>& Owner, const TSoftClassPtr<UObject>& UnitIDProviderClass);
};
