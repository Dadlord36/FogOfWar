// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DefaultNetRelevancyDecider.h"


// Sets default values for this component's properties
UDefaultNetRelevancyDecider::UDefaultNetRelevancyDecider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UDefaultNetRelevancyDecider::DetermineNetRelevancy_Implementation(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation)
{
	
	return INetRelevancyDecider::DetermineNetRelevancy_Implementation(RealViewer, ViewTarget, SrcLocation);
}


// Called when the game starts
void UDefaultNetRelevancyDecider::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}