// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/Public/Actors/BattleUnit.h"

#include "FogOfWar/Public/Components/ColorizationController.h"


// Sets default values
ABattleUnit::ABattleUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	ColorizationController = CreateDefaultSubobject<UColorizationController>(TEXT("ColorizationController"));
}

// Called when the game starts or when spawned
void ABattleUnit::BeginPlay()
{
	Super::BeginPlay();
}
