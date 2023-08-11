// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnitIDManager.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUnitIDManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for providing unique IDs to units
 */
class DISCOVERABLEACTORS_SERVER_API IUnitIDManager
{
	GENERATED_BODY()

public:
	// Assign a unique ID to a unit and return it
	virtual uint32 AssignUnitID() = 0;
	// Release a unit's ID when it's destroyed
	virtual void ReleaseUnitID(const uint32 UnitID) = 0;
	// Update the visibility of a unit for a player
	virtual void UpdateVisibilityForPlayer(const uint32 UnitID, const uint32 PlayerID, const bool bIsVisible) = 0;
	// Check if a unit is relevant for a given player
	virtual bool IsUnitRelevantForPlayer(const uint32 UnitID, const uint32 PlayerID) const = 0;
};
