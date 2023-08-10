// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ColorizationController.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOGOFWARCOMMON_API UColorizationController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UColorizationController();
	
	virtual void OnRegister() override;
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void ApplyColorToOwnerMesh(const FLinearColor InColor) const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ApplyColorToOwnerMesh_Internal(const FLinearColor& InColor) const;
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Parameters")
	FLinearColor Color = FLinearColor::Black;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
	FName ColorParameterName = TEXT("Color");
};
