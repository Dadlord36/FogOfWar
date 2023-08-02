// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleUnit.generated.h"

class UColorizationController;

UCLASS()
class FOGOFWAR_API ABattleUnit : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleUnit();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UColorizationController> ColorizationController;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	

};
