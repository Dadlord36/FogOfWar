// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DiscoverableActorsSubsystem.h"

#include "LogCategoires.h"
#include "Components/Factories/DA_ComponentsFactory.h"
#include "Components/Interfaces/NetRelevancyDecider.h"
#include "Components/Interfaces/UnitIDManager.h"
#include "Components/Interfaces/UnitIdProvider.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Objects/DA_Server_ObjectsFactory.h"
#include "Settings/DiscoverableActorsSystemSettings.h"
#include "Structs/ActorDiscoveryRequestData.h"

UDiscoverableActorsSubsystem* UDiscoverableActorsSubsystem::Get(const TObjectPtr<UObject> WorldContextObject)
{
	checkf(WorldContextObject, TEXT("Invalid world context object"));
	const auto GameInstance = WorldContextObject->GetWorld()->GetGameInstance();
	checkf(GameInstance, TEXT("Invalid game instance"));
	const auto Subsystem = GameInstance->GetSubsystem<UDiscoverableActorsSubsystem>();
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

	StartListeningForActorsDiscoverRequests();
}

void UDiscoverableActorsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	StopListeningForActorsDiscoverRequests();
}

void UDiscoverableActorsSubsystem::StartListeningForActorsDiscoverRequests()
{
	auto& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	ActorsDiscoveryListenerHandle = MessageSubsystem.RegisterListener<FActorDiscoveryRequestData>(Channels_ActorsControl_ActorsDiscovery,
	                                                                                              this,
	                                                                                              &UDiscoverableActorsSubsystem::OnActorDiscoverRequest);
}

void UDiscoverableActorsSubsystem::StopListeningForActorsDiscoverRequests() const
{
	auto& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.UnregisterListener(ActorsDiscoveryListenerHandle);
}

void UDiscoverableActorsSubsystem::OnActorDiscoverRequest(FGameplayTag, const FActorDiscoveryRequestData& ActorDiscoveryRequestData)
{
	if (ActorDiscoveryRequestData.IsDataValid() == false)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor discovery request data is invalid"));
		return;
	}

	const IUnitIdProvider* UnitIDProvider(ActorDiscoveryRequestData.ActorToMakeDiscoverable);
	if (ensureAlwaysMsgf(UnitIDProvider, TEXT("Actor %s is not implementing IUnitIdProvider"),
	                     *ActorDiscoveryRequestData.ActorToMakeDiscoverable->GetName()))
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor %s is not implementing IUnitIdProvider"),
		       *ActorDiscoveryRequestData.ActorToMakeDiscoverable->GetName());
		return;
	}

	const auto UnitID = UnitIDProvider->GetUnitID();
	const auto PlayerControllerID = ActorDiscoveryRequestData.PlayerController->GetUniqueID();
	UnitIDManager->UpdateVisibilityForPlayer(UnitID, PlayerControllerID, true);
}

TScriptInterface<INetRelevancyDecider> UDiscoverableActorsSubsystem::GetNetRelevancyDecider() const
{
	return NetRelevancyDecider;
}

TScriptInterface<IUnitIDManager> UDiscoverableActorsSubsystem::GetUnitIDManager() const
{
	return UnitIDManager;
}

void UDiscoverableActorsSubsystem::MakeActorsDiscoverableForPlayer(TArray<TObjectPtr<AActor>>* Array, const APlayerController* PlayerController) const
{
	if (Array == nullptr)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Array is nullptr"));
		return;
	}

	if (PlayerController == nullptr)
	{
		UE_LOG(LogDiscoverableActors, Warning, TEXT("Player controller is nullptr"));
		return;
	}

	for (auto& Actor : *Array)
	{
		const IUnitIdProvider* UnitIDProvider = Cast<IUnitIdProvider>(Actor);
		if (UnitIDProvider == nullptr)
		{
			UE_LOG(LogDiscoverableActors, Warning, TEXT("Actor is nullptr"));
			continue;
		}

		UnitIDManager->UpdateVisibilityForPlayer(UnitIDProvider->GetUnitID(), PlayerController->GetUniqueID(), true);
	}
}

TObjectPtr<const UDiscoverableActorsSystemSettings_Server> UDiscoverableActorsSubsystem::GetDiscoverableActorsSystemSettings()
{
	return GetDefault<UDiscoverableActorsSystemSettings_Server>();
}
