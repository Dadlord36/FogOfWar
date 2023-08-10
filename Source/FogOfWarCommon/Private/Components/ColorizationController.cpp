// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ColorizationController.h"

// Sets default values for this component's properties
UColorizationController::UColorizationController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UColorizationController::OnRegister()
{
	Super::OnRegister();
}

void UColorizationController::ApplyColorToOwnerMesh_Internal(const FLinearColor& InColor) const
{
	const auto Owner = GetOwner();
	const auto OwnerMeshComponent = Owner->FindComponentByClass<UStaticMeshComponent>();
	if (!ensureAlwaysMsgf(IsValid(OwnerMeshComponent), TEXT("OwnerMeshComponent is not valid")))
	{
		return;
	}

	//Convert color to vector
	const FVector ColorAsVector(InColor);
	//Get mesh material and set it's color value
	OwnerMeshComponent->SetVectorParameterValueOnMaterials(ColorParameterName, ColorAsVector);
}

void UColorizationController::ApplyColorToOwnerMesh_Implementation(const FLinearColor InColor) const
{
	ApplyColorToOwnerMesh_Internal(InColor);
}

// Called when the game starts
void UColorizationController::BeginPlay()
{
	Super::BeginPlay();
}
