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

#include "PF2CharacterInterface.h"
#include "PF2PartyInterface.h"
#include "PF2PlayerControllerInterface.h"
#include "PF2PlayerStateInterface.h"

#include "Utilities/PF2InterfaceUtilities.h"

UPF2OwnerTrackingComponent::UPF2OwnerTrackingComponent()
{
	this->SetIsReplicatedByDefault(true);
}

void UPF2OwnerTrackingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPF2OwnerTrackingComponent, OwningPlayerState);
	DOREPLIFETIME(UPF2OwnerTrackingComponent, Party);
}

TScriptInterface<IPF2PartyInterface> UPF2OwnerTrackingComponent::GetParty() const
{
	return this->Party;
}

void UPF2OwnerTrackingComponent::SetParty(const TScriptInterface<IPF2PartyInterface> NewParty)
{
	const TScriptInterface<IPF2PartyInterface> OldParty = this->Party;

	if (NewParty != OldParty)
	{
		const TScriptInterface<IPF2PlayerStateInterface> PlayerState      = this->GetStateOfOwningPlayer();
		int32                                            OwningPartyIndex = IPF2PartyInterface::PartyIndexNone,
		                                                 NewPartyIndex    = IPF2PartyInterface::PartyIndexNone;

		if (PlayerState != nullptr)
		{
			const TScriptInterface<IPF2PartyInterface> OwningPlayerParty = PlayerState->GetParty();

			if (OwningPlayerParty != nullptr)
			{
				OwningPartyIndex = OwningPlayerParty->GetPartyIndex();
			}
		}

		if (NewParty != nullptr)
		{
			NewPartyIndex = NewParty->GetPartyIndex();
		}

		if ((PlayerState == nullptr) || (OwningPartyIndex == NewPartyIndex))
		{
			this->Party = Cast<AInfo>(NewParty.GetObject());

			this->Native_OnPartyChanged(OldParty, NewParty);
		}
		else
		{
			UE_LOG(
				LogPf2Core,
				Error,
				TEXT("Owner tracker ('%s') cannot be affiliated with a party ('%i') that differs from that of the party ('%i') of its owning player ('%s')."),
				*(this->GetIdForLogs()),
				NewPartyIndex,
				OwningPartyIndex,
				*(PlayerState->GetIdForLogs())
			);
		}
	}
}

TScriptInterface<IPF2PlayerStateInterface> UPF2OwnerTrackingComponent::GetStateOfOwningPlayer() const
{
	return this->OwningPlayerState;
}

void UPF2OwnerTrackingComponent::SetOwningPlayerByController(
	const TScriptInterface<IPF2PlayerControllerInterface> NewController)
{
	this->SetOwningPlayerByState(NewController->GetPlayerState());
}

void UPF2OwnerTrackingComponent::SetOwningPlayerByState(const TScriptInterface<IPF2PlayerStateInterface> NewPlayerState)
{
	const TScriptInterface<IPF2PlayerStateInterface> OldOwningPlayerState = this->OwningPlayerState;

	if (NewPlayerState != OldOwningPlayerState)
	{
		this->OwningPlayerState = Cast<APlayerState>(NewPlayerState.GetObject());

		this->Native_OnOwningPlayerStateChanged(OldOwningPlayerState, NewPlayerState);
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

bool UPF2OwnerTrackingComponent::IsSamePartyAsPlayerWithController(
	const TScriptInterface<IPF2PlayerControllerInterface> OtherController) const
{
	const TScriptInterface<IPF2PlayerStateInterface> PlayerState          = this->GetStateOfOwningPlayer();
	TScriptInterface<IPF2PlayerStateInterface>       OtherPlayerState;

	check(OtherController != nullptr);

	OtherPlayerState = OtherController->GetPlayerState();

	return PlayerState->IsSamePartyAsPlayerWithState(OtherPlayerState);
}

FString UPF2OwnerTrackingComponent::GetIdForLogs() const
{
	FString                             OwnerName;
	AActor*                             OwningActor = this->GetOwner();
	const IPF2LogIdentifiableInterface* OwnerLogId  = Cast<IPF2LogIdentifiableInterface>(OwningActor);

	if (OwnerLogId == nullptr)
	{
		// Fallback to vanilla UE if we're not in something that implements IPF2LogIdentifiableInterface
		OwnerName = OwningActor->GetName();
	}
	else
	{
		// Use the preferred log ID of the containing actor.
		OwnerName = OwnerLogId->GetIdForLogs();
	}

	// ReSharper disable CppRedundantParentheses
	return FString::Format(
		TEXT("{0}.{1}"),
		{
			*(OwnerName),
			*(this->GetName())
		}
	);
}

void UPF2OwnerTrackingComponent::OnRep_OwningPlayerState(APlayerState* OldOwner) const
{
	const TScriptInterface<IPF2PlayerStateInterface> OldPf2Owner = OldOwner;
	const TScriptInterface<IPF2PlayerStateInterface> NewPf2Owner = this->OwningPlayerState;

    this->Native_OnOwningPlayerStateChanged(OldPf2Owner, NewPf2Owner);
}

void UPF2OwnerTrackingComponent::OnRep_Party(AInfo* OldParty) const
{
	const TScriptInterface<IPF2PartyInterface> OldPf2Party = OldParty;
	const TScriptInterface<IPF2PartyInterface> NewPf2Party = this->Party;

	this->Native_OnPartyChanged(OldPf2Party, NewPf2Party);
}

void UPF2OwnerTrackingComponent::Native_OnOwningPlayerStateChanged(
	const TScriptInterface<IPF2PlayerStateInterface> OldOwner,
	const TScriptInterface<IPF2PlayerStateInterface> NewOwner) const
{
	this->OnOwnerChanged.Broadcast(this->GetOwner(), OldOwner, NewOwner);
}

void UPF2OwnerTrackingComponent::Native_OnPartyChanged(const TScriptInterface<IPF2PartyInterface> OldParty,
                                                       const TScriptInterface<IPF2PartyInterface> NewParty) const
{
	this->OnPartyChanged.Broadcast(this->GetOwner(), OldParty, NewParty);
}
