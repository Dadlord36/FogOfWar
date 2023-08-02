// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorsGroupManager.h"

#include "Components/ColorizationController.h"


// Sets default values for this component's properties
UActorsGroupManager::UActorsGroupManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UActorsGroupManager::SetGroupActors(const TArray<TObjectPtr<AActor>>& Actors)
{
	SpawnedActors = Actors;
	ApplyColorToGroup();
}

void UActorsGroupManager::ClearSpawnedActors()
{
	if(SpawnedActors.IsEmpty())
	{
		//Remove and destroy all attached actors from owner transform
		auto Owner = GetOwner();
		Owner->ForEachAttachedActors([&Owner](AActor* AttachedActor)
		{
			AttachedActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			AttachedActor->Destroy();
			return false;
		});
		return;
	}
	
	for (const auto& SpawnedActor : SpawnedActors)
	{
		if (SpawnedActor)
		{
			//Remove spawned actor from owner
			SpawnedActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			//Destroy spawned actor in editor or in game
			SpawnedActor->Destroy();
			SpawnedActor->MarkAsGarbage();
		}
	}
	SpawnedActors.Empty();
}

void UActorsGroupManager::ApplyColorToGroup() const
{
	for (const auto& SpawnedActor : SpawnedActors)
	{
		if (SpawnedActor)
		{
			if (const auto ColorizationController = SpawnedActor->FindComponentByClass<UColorizationController>())
			{
				ColorizationController->ApplyColorToOwnerMesh(GroupColor);
			}
		}
	}
}
