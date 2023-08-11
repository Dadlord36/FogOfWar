// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interfaces/UnitIDManager.h"
#include "UObject/Object.h"
#include "DefaultUnitIDManager.generated.h"

/**
 *  Default implementation of the unit ID manager that is mapping unit IDs to player IDs for visibility tracking
 */
UCLASS(BlueprintType)
class DISCOVERABLEACTORS_SERVER_API UDefaultUnitIDManager : public UObject, public IUnitIDManager
{
	GENERATED_BODY()

public:
	// Assign a unique ID to a unit and return it
	virtual uint32 AssignUnitID() override;

	// Release a unit's ID when it's destroyed
	virtual void ReleaseUnitID(const uint32 UnitID) override;

	// Update the visibility of a unit for a player
	virtual void UpdateVisibilityForPlayer(const uint32 UnitID, const uint32 PlayerID, const bool bIsVisible) override;

	// Check if a unit is relevant for a given player
	virtual bool IsUnitRelevantForPlayer(const uint32 UnitID, const uint32 PlayerID) const override;

private:
	// Track the next available unit ID
	uint32 NextAvailableUnitID = 1;

	// Store released IDs for reuse
	TSet<uint32> AvailableUnitIDs;

	// Map of unit IDs to arrays of player IDs for visibility tracking
	TMap<uint32, TArray<uint32>> UnitVisibilityMap;
};
