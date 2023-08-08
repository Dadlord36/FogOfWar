// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/DefaultUnitIDManager.h"


int32 UDefaultUnitIDManager::AssignUnitID()
{
	if (AvailableUnitIDs.Num() > 0)
	{
		const int32 UnitID = *AvailableUnitIDs.CreateConstIterator();
		AvailableUnitIDs.Remove(UnitID);
		return UnitID;
	}
	else
	{
		return NextAvailableUnitID++;
	}
}

void UDefaultUnitIDManager::ReleaseUnitID(const int32 UnitID)
{
	AvailableUnitIDs.Add(UnitID);
	UnitVisibilityMap.Remove(UnitID); // Clean up the visibility map entry for this unit
}

void UDefaultUnitIDManager::UpdateVisibilityForPlayer(const int32 UnitID, const int32 PlayerID, const bool bIsVisible)
{
	if (bIsVisible)
	{
		if (!UnitVisibilityMap.Contains(UnitID))
		{
			UnitVisibilityMap.Add(UnitID, TArray<int32>());
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

bool UDefaultUnitIDManager::IsUnitRelevantForPlayer(const int32 UnitID, const int32 PlayerID) const
{
	if (UnitVisibilityMap.Contains(UnitID))
	{
		return UnitVisibilityMap[UnitID].Contains(PlayerID);
	}
	return false;
}
