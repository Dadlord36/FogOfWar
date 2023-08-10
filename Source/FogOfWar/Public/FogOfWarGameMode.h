// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FogOfWarGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FOGOFWAR_API AFogOfWarGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

private:
	void CheckNetDriver() const;
};
