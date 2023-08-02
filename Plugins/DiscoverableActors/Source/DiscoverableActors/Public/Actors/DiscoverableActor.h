// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiscoverableActor.generated.h"

/**
 *  Base class for discoverable actors. It will be replicated to clients only if it is visible for them. Relay on teaming system.
 */
UCLASS()
class DISCOVERABLEACTORS_API ADiscoverableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADiscoverableActor();

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
