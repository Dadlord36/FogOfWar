// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DefaultNetRelevancyDecider.h"

#include "Components/Interfaces/UnitIdProvider.h"


bool UDefaultNetRelevancyDecider::DetermineNetRelevancy_Implementation(const AActor* const RealViewer, const AActor* const ViewTarget,
                                                                       const FVector& SrcLocation)
{
	if (RealViewer == nullptr || ViewTarget == nullptr)
	{
		return false;
	}

	const IUnitIdProvider* const UnitIdProvider = Cast<IUnitIdProvider>(ViewTarget);
	if (UnitIdProvider == nullptr)
	{
		return false;
	}

	return UnitIDManager->IsUnitRelevantForPlayer(UnitIdProvider->GetUnitID(), GetPlayerControllerNumberChecked(RealViewer));
}

uint32 UDefaultNetRelevancyDecider::GetPlayerControllerNumberChecked(const AActor* RealViewer)
{
	checkf(RealViewer, TEXT("Invalid real viewer"));
	const APlayerController* PlayerController = Cast<APlayerController>(RealViewer);
	checkf(PlayerController, TEXT("Real viewer is not a player controller"));
	return PlayerController->GetUniqueID();
}
