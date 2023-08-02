// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/NetRelevancyDecider.h"
#include "DefaultNetRelevancyDecider.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DISCOVERABLEACTORS_API UDefaultNetRelevancyDecider : public UActorComponent, public INetRelevancyDecider
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDefaultNetRelevancyDecider();
	virtual bool DetermineNetRelevancy_Implementation(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
