// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleUnit.generated.h"

class UColorizationController;

UCLASS(Blueprintable, BlueprintType)
class FOGOFWARCOMMON_API ABattleUnit : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleUnit();
	UFUNCTION(NetMulticast, Reliable)
	void ApplyColorToOwnerMesh(FLinearColor GroupColor) const;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UColorizationController> ColorizationController;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;



	void ApplyColorToOwnerMesh_Internal(const FLinearColor& InColor) const;
};
