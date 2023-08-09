// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DiscoverableActor.h"

#include "LogCategoires.h"
#if WITH_SERVER_CODE
#include "Components/Interfaces/UnitIDManager.h"
#include "Components/Interfaces/NetRelevancyDecider.h"
#include "Subsystems/DiscoverableActorsSubsystem.h"
#endif


ADiscoverableActor::ADiscoverableActor() : Super()
{
	//Make replicated
	bReplicates = true;
}

/*
  If relevancy decider determines that this actor is relevant for the viewer - then we will use default relevancy check,
  as it will check if actor is visible for player camera.
 */
#if WITH_SERVER_CODE
bool ADiscoverableActor::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (bFallbackToDefaultRelevancy)
	{
		return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}
	if (ensureMsgf(NetRelevancyDecider.GetObject() != nullptr, TEXT("NetRelevancyDecider is not set")) == false)
	{
		return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}

	//TODO: Maybe be improved with enum that will allow to fallback to default relevancy check from NetRelevancyDecider result
	return INetRelevancyDecider::Execute_DetermineNetRelevancy(NetRelevancyDecider.GetObject(), RealViewer, this, SrcLocation)
		       ? Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation)
		       : false;
}
#endif

// Called when the game starts or when spawned
void ADiscoverableActor::BeginPlay()
{
	Super::BeginPlay();
	//if is client - do nothing
	if (HasAuthority() == false)
	{
		return;
	}

#if WITH_SERVER_CODE
	const auto DiscoverableActorsSubsystem = UDiscoverableActorsSubsystem::Get(this);
	NetRelevancyDecider = DiscoverableActorsSubsystem->GetNetRelevancyDecider();
#if DA_DEBUG
	if (ensureAlwaysMsgf(NetRelevancyDecider, TEXT("NetRelevancyDecider is not set for %s"), *GetName()) == false)
	{
		UE_LOG(LogDiscoverableActors, Error, TEXT("NetRelevancyDecider is not set for %s"), *GetName());
	}
#endif
	UnitIDManager = DiscoverableActorsSubsystem->GetUnitIDManager();
	ClaimUnitID();
#endif
}

void ADiscoverableActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (HasAuthority() == false)
	{
		Super::EndPlay(EndPlayReason);
		return;
	}
#if WITH_SERVER_CODE
	ReleaseUnitID();
#endif
	Super::EndPlay(EndPlayReason);
}

#if WITH_SERVER_CODE
void ADiscoverableActor::ClaimUnitID()
{
	if (UnitIDManager == nullptr)
	{
		UE_LOG(LogDiscoverableActors, Error, TEXT("UnitIDManager is not set for %s"), *GetName());
		return;
	}

	UnitID = UnitIDManager->AssignUnitID();
}

void ADiscoverableActor::ReleaseUnitID() const
{
	if (UnitIDManager == nullptr)
	{
		UE_LOG(LogDiscoverableActors, Error, TEXT("UnitIDManager is not set for %s"), *GetName());
		return;
	}

	UnitIDManager->ReleaseUnitID(UnitID);
}
#endif
