// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DiscoverableActorsSubsystem.h"

// #include "GameFramework/GameplayMessageSubsystem.h"
// #include "Structs/ActorDiscoveryRequestData.h"
#include "LogCategoires.h"
#include "Components/Factories/DA_ComponentsFactory.h"
#include "Components/Interfaces/NetRelevancyDecider.h"
#include "Components/Interfaces/UnitIDManager.h"
#include "Components/Interfaces/UnitIdProvider.h"
#include "Objects/DA_Server_ObjectsFactory.h"
#include "Settings/DiscoverableActorsSystemSettings.h"


UDiscoverableActorsSubsystem* UDiscoverableActorsSubsystem::Get(const TObjectPtr<UObject> WorldContextObject)
{
	checkf(WorldContextObject, TEXT("Invalid world context object"));
	const auto World = WorldContextObject->GetWorld();
	checkf(World, TEXT("Invalid world"));
	const auto Subsystem = World->GetSubsystem<UDiscoverableActorsSubsystem>();
	checkf(Subsystem, TEXT("Invalid discoverable actors subsystem"));
	return Subsystem;
}

bool UDiscoverableActorsSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// Create subsystem only if we are running in a server or listen server
	const ENetMode NetMode = Outer->GetWorld()->GetNetMode();
	return NetMode == NM_DedicatedServer || NetMode == NM_ListenServer;
}

void UDiscoverableActorsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const auto Settings = GetDiscoverableActorsSystemSettings();

	UnitIDManager = UDA_Server_ObjectsFactory::CreateUnitIDProvider(
		this, Settings->UnitIDManagerClass);
	NetRelevancyDecider = UDA_ComponentsFactory::CreateNetRelevancyDecider(
		this, Settings->NetRelevancyDeciderClass, UnitIDManager);

	// StartListeningForActorsDiscoverRequests();
}

void UDiscoverableActorsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	// StopListeningForActorsDiscoverRequests();
}

/*void UDiscoverableActorsSubsystem::StartListeningForActorsDiscoverRequests()
{
	auto& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	ActorsDiscoveryListenerHandle = MessageSubsystem.RegisterListener<FActorDiscoveryRequestData>(TAG_ActorsDiscovery_ShowupForPlayer,
	                                                                                              this,
	                                                                                              &UDiscoverableActorsSubsystem::OnActorsDiscoverRequest);
	ActorsHidingListenerHandle = MessageSubsystem.RegisterListener<FActorDiscoveryRequestData>(TAG_ActorsDiscovery_HideForPlayer,
	                                                                                           this,
	                                                                                           &UDiscoverableActorsSubsystem::OnActorsHidingRequest);
}*/

/*void UDiscoverableActorsSubsystem::StopListeningForActorsDiscoverRequests() const
{
	auto& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.UnregisterListener(ActorsDiscoveryListenerHandle);
	MessageSubsystem.UnregisterListener(ActorsHidingListenerHandle);
}*/

/*void UDiscoverableActorsSubsystem::OnActorsDiscoverRequest(FGameplayTag, const FActorDiscoveryRequestData& ActorDiscoveryRequestData)
{
	if (ActorDiscoveryRequestData.IsDataValid() == false)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor discovery request data is invalid"));
		return;
	}

	auto& ActorsToAlterVisibility = ActorDiscoveryRequestData.ActorsToAlterVisibility;

	for (auto& Actor : ActorsToAlterVisibility)
	{
		const IUnitIdProvider* UnitIDProvider = Cast<IUnitIdProvider>(Actor);
		if (UnitIDProvider == nullptr)
		{
			UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor is nullptr"));
			continue;
		}

		UnitIDManager->UpdateVisibilityForPlayer(UnitIDProvider->GetUnitID(),
		                                         ActorDiscoveryRequestData.PlayerController->GetUniqueID(), true);
	}
}*/

/*void UDiscoverableActorsSubsystem::OnActorsHidingRequest(FGameplayTag, const FActorDiscoveryRequestData& ActorDiscoveryRequestData)
{
	if (ActorDiscoveryRequestData.IsDataValid() == false)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor discovery request data is invalid"));
		return;
	}

	auto& ActorsToAlterVisibility = ActorDiscoveryRequestData.ActorsToAlterVisibility;

	for (auto& Actor : ActorsToAlterVisibility)
	{
		const IUnitIdProvider* UnitIDProvider = Cast<IUnitIdProvider>(Actor);
		if (UnitIDProvider == nullptr)
		{
			UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor is nullptr"));
			continue;
		}

		UnitIDManager->UpdateVisibilityForPlayer(UnitIDProvider->GetUnitID(),
		                                         ActorDiscoveryRequestData.PlayerController->GetUniqueID(), false);
	}
}*/

TScriptInterface<INetRelevancyDecider> UDiscoverableActorsSubsystem::GetNetRelevancyDecider() const
{
	return NetRelevancyDecider;
}

TScriptInterface<IUnitIDManager> UDiscoverableActorsSubsystem::GetUnitIDManager() const
{
	return UnitIDManager;
}

void UDiscoverableActorsSubsystem::MakeActorsReplicatedForPlayer(const TArray<AActor*>& Array, const APlayerController* PlayerController) const
{
	if (Array.IsEmpty())
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Array is empty"));
		return;
	}

	if (PlayerController == nullptr)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Player controller is nullptr"));
		return;
	}

	for (auto& Actor : Array)
	{
		const IUnitIdProvider* UnitIDProvider = Cast<IUnitIdProvider>(Actor);
		if (UnitIDProvider == nullptr)
		{
			UE_LOG(LogDiscoverableActors, Warning, TEXT("UnitIDProvider is nullptr"));
			continue;
		}

		UnitIDManager->UpdateVisibilityForPlayer(UnitIDProvider->GetUnitID(), PlayerController->GetUniqueID(), true);
	}
}

void UDiscoverableActorsSubsystem::MakeActorsNotReplicatedForPlayer(const TArray<AActor*>& Array,
                                                                    const APlayerController* PlayerController) const
{
	if (Array.IsEmpty())
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Array is empty"));
		return;
	}

	if (PlayerController == nullptr)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Player controller is nullptr"));
		return;
	}

	for (auto& Actor : Array)
	{
		const IUnitIdProvider* UnitIDProvider = Cast<IUnitIdProvider>(Actor);
		if (UnitIDProvider == nullptr)
		{
			UE_LOG(LogDiscoverableActors, Warning, TEXT("UnitIDProvider is nullptr"));
			continue;
		}

		UnitIDManager->UpdateVisibilityForPlayer(UnitIDProvider->GetUnitID(), PlayerController->GetUniqueID(), false);
	}
}

TObjectPtr<const UDiscoverableActorsSystemSettings_Server> UDiscoverableActorsSubsystem::GetDiscoverableActorsSystemSettings()
{
	return GetDefault<UDiscoverableActorsSystemSettings_Server>();
}
