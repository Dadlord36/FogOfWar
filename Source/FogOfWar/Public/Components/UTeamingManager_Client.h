// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ControllerComponent.h"
#include "UTeamingManager_Client.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOGOFWAR_API UTeamingManager_Client : public UControllerComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTeamingManager_Client(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
