// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitIdProvider.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitIdProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DISCOVERABLEACTORS_SHARED_API IUnitIdProvider
{
	GENERATED_BODY()

public:
	virtual int GetUnitID() const = 0;
};
