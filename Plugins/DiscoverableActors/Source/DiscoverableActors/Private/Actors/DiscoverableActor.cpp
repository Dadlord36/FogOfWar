// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DiscoverableActor.h"


// Sets default values
ADiscoverableActor::ADiscoverableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ADiscoverableActor::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{

	
	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}

// Called when the game starts or when spawned
void ADiscoverableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADiscoverableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

