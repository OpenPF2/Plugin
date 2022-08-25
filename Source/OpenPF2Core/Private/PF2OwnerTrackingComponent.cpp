// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.
//

#include "PF2OwnerTrackingComponent.h"

#include <Engine/World.h>

#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerState.h>

#include <Net/UnrealNetwork.h>

#include "PF2PlayerControllerInterface.h"
#include "PF2PlayerStateInterface.h"

#include "Utilities/PF2InterfaceUtilities.h"

UPF2OwnerTrackingComponent::UPF2OwnerTrackingComponent()
{
	this->SetIsReplicatedByDefault(true);

	this->IndexOfInitialOwningPlayer = IPF2PlayerStateInterface::PlayerIndexNone;
}

uint8 UPF2OwnerTrackingComponent::GetIndexOfInitialOwningPlayer() const
{
	return this->IndexOfInitialOwningPlayer;
}

TScriptInterface<IPF2PlayerStateInterface> UPF2OwnerTrackingComponent::GetStateOfOwningPlayer() const
{
	return this->OwningPlayerState;
}

void UPF2OwnerTrackingComponent::SetOwningPlayerByController(TScriptInterface<IPF2PlayerControllerInterface> Controller)
{
	this->SetOwningPlayerByState(Controller->GetPlayerState());
}

void UPF2OwnerTrackingComponent::SetOwningPlayerByState(TScriptInterface<IPF2PlayerStateInterface> PlayerState)
{
	const TScriptInterface<IPF2PlayerStateInterface> PreviousOwningPlayerState = this->OwningPlayerState;

	this->OwningPlayerState = PlayerState;

	if (PlayerState != PreviousOwningPlayerState)
	{
		this->Native_OnOwningPlayerStateChanged(PreviousOwningPlayerState, PlayerState);
	}
}

bool UPF2OwnerTrackingComponent::IsSamePartyAsActor(AActor* OtherActor) const
{
	bool Result = false;

	if (OtherActor != nullptr)
	{
		const TScriptInterface<IPF2PlayerStateInterface> MyOwner = this->GetStateOfOwningPlayer();
		const IPF2OwnerTrackingInterface* OtherComponent =
			PF2InterfaceUtilities::FindComponentByInterface<IPF2OwnerTrackingInterface, UPF2OwnerTrackingInterface>(OtherActor);

		if (OtherComponent != nullptr)
		{
			const TScriptInterface<IPF2PlayerStateInterface> OtherOwner = OtherComponent->GetStateOfOwningPlayer();

			Result = MyOwner->IsSamePartyAsPlayerWithState(OtherOwner);
		}
	}

	return Result;
}

bool UPF2OwnerTrackingComponent::IsSamePartyAsPlayerWithController(AController* OtherController) const
{
	bool Result = false;

	if (IsValid(OtherController))
	{
		const IPF2PlayerControllerInterface* OtherControllerIntf = Cast<IPF2PlayerControllerInterface>(OtherController);

		if (OtherControllerIntf != nullptr)
		{
			const TScriptInterface<IPF2PlayerStateInterface> MyOwner          = this->GetStateOfOwningPlayer();
			const TScriptInterface<IPF2PlayerStateInterface> OtherPlayerState = OtherControllerIntf->GetPlayerState();

			Result = MyOwner->IsSamePartyAsPlayerWithState(OtherPlayerState);
		}
	}
	return Result;
}

FString UPF2OwnerTrackingComponent::GetIdForLogs() const
{
	// ReSharper disable CppRedundantParentheses
	return FString::Format(
		TEXT("{0}.{1}"),
		{
			*(this->GetOwner()->GetName()),
			*(this->GetName())
		}
	);
}

void UPF2OwnerTrackingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPF2OwnerTrackingComponent, OwningPlayerState);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPF2OwnerTrackingComponent::OnRep_OwningPlayerState(const TScriptInterface<IPF2PlayerStateInterface> Owner)
{
    this->Native_OnOwningPlayerStateChanged(Owner, this->OwningPlayerState);
}

void UPF2OwnerTrackingComponent::Native_OnOwningPlayerStateChanged(
	const TScriptInterface<IPF2PlayerStateInterface> PreviousOwner,
	const TScriptInterface<IPF2PlayerStateInterface> NewOwner) const
{
	const UWorld* World = GetWorld();

	OnOwnerChanged.Broadcast(this->GetOwner(), Cast<AController>(NewOwner->ToPlayerState()->GetOwner()));

	if (IsValid(World))
	{
		const IPF2PlayerStateInterface* PreviousOwnerIntf = PF2InterfaceUtilities::FromScriptInterface(PreviousOwner);
		const IPF2PlayerStateInterface* NewOwnerIntf      = PF2InterfaceUtilities::FromScriptInterface(NewOwner);

		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			const TWeakObjectPtr<APlayerController> Controller  = *Iterator;
			IPF2PlayerStateInterface*               PlayerState = Controller->GetPlayerState<IPF2PlayerStateInterface>();

			if ((PlayerState != nullptr) &&
				((PlayerState == PreviousOwnerIntf) || (PlayerState == NewOwnerIntf)))
			{
				// Notify player controllers that have lost or gained ownership of an actor.
				PlayerState->Native_OnActorOwnershipChanged(this->GetOwner(), PreviousOwner, NewOwner);
			}
		}
	}
}
