// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BattleUnit.h"

#include "Components/ColorizationController.h"

// Sets default values
ABattleUnit::ABattleUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	ColorizationController = CreateDefaultSubobject<UColorizationController>(TEXT("ColorizationController"));
	bReplicates = true;
}

void ABattleUnit::ApplyColorToOwnerMesh_Implementation(const FLinearColor GroupColor) const
{
	ApplyColorToOwnerMesh_Internal(GroupColor);
}

void ABattleUnit::ApplyColorToOwnerMesh_Internal(const FLinearColor& InColor) const
{
	const auto OwnerMeshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (!ensureAlwaysMsgf(IsValid(OwnerMeshComponent), TEXT("OwnerMeshComponent is not valid")))
	{
		return;
	}

	//Convert color to vector
	const FVector ColorAsVector(InColor);
	//Get mesh material and set it's color value
	OwnerMeshComponent->SetVectorParameterValueOnMaterials(TEXT("Color"), ColorAsVector);
}
