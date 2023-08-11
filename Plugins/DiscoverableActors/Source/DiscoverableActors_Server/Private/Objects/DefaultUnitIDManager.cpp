// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/DefaultUnitIDManager.h"


uint32 UDefaultUnitIDManager::AssignUnitID()
{
	if (AvailableUnitIDs.Num() > 0)
	{
		const uint32 UnitID = *AvailableUnitIDs.CreateConstIterator();
		AvailableUnitIDs.Remove(UnitID);
		return UnitID;
	}
	else
	{
		return NextAvailableUnitID++;
	}
}

void UDefaultUnitIDManager::ReleaseUnitID(const uint32 UnitID)
{
	AvailableUnitIDs.Add(UnitID);
	UnitVisibilityMap.Remove(UnitID); // Clean up the visibility map entry for this unit
}

void UDefaultUnitIDManager::UpdateVisibilityForPlayer(const uint32 UnitID, const uint32 PlayerID, const bool bIsVisible)
{
	if (bIsVisible)
	{
		if (!UnitVisibilityMap.Contains(UnitID))
		{
			UnitVisibilityMap.Add(UnitID, TArray<uint32>());
		}
		UnitVisibilityMap[UnitID].AddUnique(PlayerID);
	}
	else
	{
		if (UnitVisibilityMap.Contains(UnitID))
		{
			UnitVisibilityMap[UnitID].Remove(PlayerID);
		}
	}
}

bool UDefaultUnitIDManager::IsUnitRelevantForPlayer(const uint32 UnitID, const uint32 PlayerID) const
{
	if (UnitVisibilityMap.Contains(UnitID))
	{
		return UnitVisibilityMap[UnitID].Contains(PlayerID);
	}
	return false;
}
