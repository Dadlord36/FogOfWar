// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/DA_Server_ObjectsFactory.h"

#include "Components/Interfaces/UnitIDManager.h"


TScriptInterface<IUnitIDManager> UDA_Server_ObjectsFactory::CreateUnitIDProvider(const TObjectPtr<UObject>& Owner,
                                                                                 const TSoftClassPtr<UObject>& UnitIDProviderClass)
{
	checkf(Owner, TEXT("Invalid owner object"));
	checkf(UnitIDProviderClass.IsNull() == false, TEXT("Invalid unit ID provider class"));
	checkf(UnitIDProviderClass->ImplementsInterface(UUnitIDManager::StaticClass()),
	       TEXT("Unit ID provider class must implement IUnitIDProvider interface"));

	return NewObject<UObject>(Owner.Get(), UnitIDProviderClass.LoadSynchronous());
}
