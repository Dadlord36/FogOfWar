// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DiscoverableActor.h"
#include "GameFramework/Actor.h"
#include "BattleUnit.generated.h"

class UColorizationController;

UCLASS()
class FOGOFWAR_API ABattleUnit : public ADiscoverableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleUnit();

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UColorizationController> ColorizationController;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	

};
