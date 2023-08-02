// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NetRelevancyDecider.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNetRelevancyDecider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DISCOVERABLEACTORS_API INetRelevancyDecider
{
	GENERATED_BODY()

public:
	/**
	 * @brief Determine if actor is relevant for given viewer.
	 * @param RealViewer Viewer that is trying to see actor. Is the Actor being used as the point of view for the RealViewer.
	 * Is the "controlling net object" associated with the client for which network relevancy is being checked (typically player controller)
	 * @param ViewTarget Target that viewer is looking at.
	 * @param SrcLocation Location of viewer.
	 * @return True if actor is relevant for viewer.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NetRelevancyDecider")
	bool DetermineNetRelevancy(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation);
};
