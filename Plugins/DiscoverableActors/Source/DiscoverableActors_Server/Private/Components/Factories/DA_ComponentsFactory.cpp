// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Factories/DA_ComponentsFactory.h"

#include "Components/DefaultNetRelevancyDecider.h"

TScriptInterface<INetRelevancyDecider> UDA_ComponentsFactory::CreateNetRelevancyDecider(TObjectPtr<UObject> const Outer,
                                                                                        const TSoftClassPtr<>& Subclass,
                                                                                        const TScriptInterface<IUnitIDManager> UnitIDManager)
{
	checkf(Outer, TEXT("Invalid outer object"));
	checkf(Subclass.IsNull() == false, TEXT("Invalid component class"));
	checkf(Subclass.Get()->ImplementsInterface(UNetRelevancyDecider::StaticClass()),
	       TEXT("Component class must implement INetRelevancyDecider interface"));
	checkf(UnitIDManager, TEXT("Invalid unit ID manager"));
	const auto NetRelevancyDecider = NewObject<UDefaultNetRelevancyDecider>(Outer, Subclass.LoadSynchronous());
	NetRelevancyDecider->Initialize(UnitIDManager);

	return NetRelevancyDecider;
}
