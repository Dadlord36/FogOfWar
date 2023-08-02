// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GridFormationSpawner.h"

#include "Components/ActorsGroupManager.h"


// Sets default values for this component's properties
UGridFormationSpawner::UGridFormationSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGridFormationSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UGridFormationSpawner::RespawnActorsInGridFormation() const
{
	if (!ensureAlwaysMsgf(GroupManager, TEXT("GroupManager is not valid, check if ActorsGroupManager component is attached to owner")))
	{
		return;
	}

	GroupManager->ClearSpawnedActors();
	const auto SpawnLocations = FormSpawnLocations();
	SpawnActors(SpawnLocations);
}

void UGridFormationSpawner::OnRegister()
{
	Super::OnRegister();

	GroupManager = GetActorsGroupManager();
}

TArray<FVector> UGridFormationSpawner::FormSpawnLocations() const
{
	TArray<FVector> SpawnLocations;
	SpawnLocations.Reserve(GridSize.X * GridSize.Y);

	const auto Owner = GetOwner();
	if (IsValid(Owner) == false)
	{
		return SpawnLocations;
	}

	const auto OwnerLocation = Owner->GetActorLocation();
	//Calculate spawn locations for 2D grid relative to owner location

	//Make sure grid size is more than 0 in each dimension
	const int32 GridSizeX = FMath::Max(GridSize.X, 1);
	const int32 GridSizeY = FMath::Max(GridSize.Y, 1);

	//Calculate positions
	for (int32 X = 0; X < GridSizeX; ++X)
	{
		for (int32 Y = 0; Y < GridSizeY; ++Y)
		{
			const FVector SpawnLocation = OwnerLocation + FVector(X * CellsDistance, Y * CellsDistance, 0.f);
			SpawnLocations.Add(SpawnLocation);
		}
	}

	return SpawnLocations;
}

void UGridFormationSpawner::SpawnActors(const TArray<FVector>& SpawnLocations) const
{
	if (!ensureAlwaysMsgf(GroupManager, TEXT("GroupManager is not valid, check if ActorsGroupManager component is attached to owner")))
	{
		return;
	}

	TArray<TObjectPtr<AActor>> SpawnedActors;
	SpawnedActors.Reserve(SpawnLocations.Num());
	const auto Owner = GetOwner();
	if (IsValid(Owner) == false)
	{
		return;
	}

	const auto ActorToSpawnClass = ActorToSpawn.LoadSynchronous();
	const auto World = GetWorld();
	for (const auto& SpawnLocation : SpawnLocations)
	{
		const TObjectPtr<AActor> SpawnedActor = World->SpawnActor<AActor>(ActorToSpawnClass, SpawnLocation, FRotator::ZeroRotator);
		if (!SpawnedActor)
		{
			continue;
		}
		//Make spawned actor a child of owner
		SpawnedActor->AttachToActor(Owner, FAttachmentTransformRules::KeepWorldTransform);
		SpawnedActors.Add(SpawnedActor);
	}
	GroupManager->SetGroupActors(SpawnedActors);
}

TObjectPtr<UActorsGroupManager> UGridFormationSpawner::GetActorsGroupManager() const
{
	const auto Owner = GetOwner();
	if (IsValid(Owner) == false)
	{
		return nullptr;
	}
	return Owner->FindComponentByClass<UActorsGroupManager>();
}
