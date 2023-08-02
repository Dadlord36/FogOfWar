// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DiscoverableActorsSubsystem.h"

#include "Components/Interfaces/NetRelevancyDecider.h"
#include "Settings/DiscoverableActorsSystemSettings.h"

bool UDiscoverableActorsSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// Create subsystem only if we are running in a server
	const ENetMode NetMode = Outer->GetWorld()->GetNetMode();
	return NetMode != NM_Client && NetMode != NM_Standalone;
}

void UDiscoverableActorsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const TObjectPtr<const UDiscoverableActorsSystemSettings> DiscoverableActorsSystemSettings = GetDiscoverableActorsSystemSettings();

	NetRelevancyDecider = NewObject<UActorComponent>(GetTransientPackage(),
	                                                 DiscoverableActorsSystemSettings->NetRelevancyDeciderComponentClass.LoadSynchronous());
}

INetRelevancyDecider* UDiscoverableActorsSubsystem::GetNetRelevancyDecider() const
{
	return CastChecked<INetRelevancyDecider>(NetRelevancyDecider.Get());
}

TObjectPtr<const UDiscoverableActorsSystemSettings> UDiscoverableActorsSubsystem::GetDiscoverableActorsSystemSettings()
{
	return GetDefault<UDiscoverableActorsSystemSettings>();
}
