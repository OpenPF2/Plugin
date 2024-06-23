// OpenPF2 for UE Game Logic, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#include "PF2PlayerStateBase.h"

#include <Engine/World.h>

#include <GameFramework/GameSession.h>

#include <Kismet/GameplayStatics.h>

#include <Net/UnrealNetwork.h>

#include "OpenPF2GameFramework.h"
#include "PF2PartyInterface.h"

#include "Utilities/PF2InterfaceUtilities.h"

void APF2PlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APF2PlayerStateBase, PlayerIndex);
	DOREPLIFETIME(APF2PlayerStateBase, Party);
}

int32 APF2PlayerStateBase::GetPlayerIndex() const
{
	return this->PlayerIndex;
}

void APF2PlayerStateBase::SetPlayerIndex(int32 NewPlayerIndex)
{
	this->PlayerIndex = PlayerIndex;
}

TScriptInterface<IPF2PartyInterface> APF2PlayerStateBase::GetParty() const
{
	return this->Party;
}

void APF2PlayerStateBase::SetParty(const TScriptInterface<IPF2PartyInterface> NewParty)
{
	const TScriptInterface<IPF2PartyInterface> OldParty = this->GetParty();

	this->Party = NewParty;

	if (this->GetParty() != NewParty)
	{
		this->Native_OnPartyChanged(OldParty, NewParty);
	}
}

TScriptInterface<IPF2PlayerControllerInterface> APF2PlayerStateBase::GetPlayerControllerIntf() const
{
	if (this->CachedPlayerController.GetInterface() == nullptr)
	{
		UWorld*               World     = this->GetWorld();
		const AGameStateBase* GameState = UGameplayStatics::GetGameState(World);

		if (GameState == nullptr)
		{
			UE_LOG(
				LogPf2,
				Error,
				TEXT("No game state is available for player ('%s')."),
				*(this->GetIdForLogs())
			);
		}
		else
		{
			const FUniqueNetIdRepl         UniquePlayerId       = this->GetUniqueId();
			const FUniqueNetIdRepl         PlayerNetId          = UniquePlayerId->AsShared();
			APlayerController*             PlayerController     = GetPlayerControllerFromNetId(World, PlayerNetId);
			IPF2PlayerControllerInterface* PlayerControllerIntf = Cast<IPF2PlayerControllerInterface>(PlayerController);

			if (PlayerControllerIntf == nullptr)
			{
				UE_LOG(
					LogPf2,
					Error,
					TEXT("Player ('%s') does not have an OpenPF2-compatible player controller (given '%s' as a player controller)."),
					*(this->GetIdForLogs()),
					*GetNameSafe(PlayerController)
				);
			}
			else
			{
				this->CachedPlayerController = PF2InterfaceUtilities::ToScriptInterface(PlayerControllerIntf);
			}
		}
	}

	return this->CachedPlayerController;
}

bool APF2PlayerStateBase::IsSamePartyAsPlayerWithController(
	const TScriptInterface<IPF2PlayerControllerInterface>& OtherPlayerController) const
{
	check(OtherPlayerController.GetInterface() != nullptr);

	return this->IsSamePartyAsPlayerWithState(OtherPlayerController->GetPlayerState());
}

bool APF2PlayerStateBase::IsSamePartyAsPlayerWithState(
	const TScriptInterface<IPF2PlayerStateInterface>& OtherPlayerState) const
{
	const TScriptInterface<IPF2PartyInterface> ThisParty  = this->GetParty();
	TScriptInterface<IPF2PartyInterface>       OtherParty;

	check(OtherPlayerState.GetInterface() != nullptr);
	check(ThisParty.GetInterface() != nullptr);

	OtherParty = OtherPlayerState->GetParty();

	return (ThisParty->GetPartyIndex() == OtherParty->GetPartyIndex());
}

APlayerState* APF2PlayerStateBase::ToPlayerState()
{
	return this;
}

FString APF2PlayerStateBase::GetIdForLogs() const
{
	return this->GetName();
}

void APF2PlayerStateBase::OnRep_Party(const TScriptInterface<IPF2PartyInterface> OldParty)
{
	this->Native_OnPartyChanged(OldParty, this->Party);
}

void APF2PlayerStateBase::Native_OnPartyChanged(
	const TScriptInterface<IPF2PartyInterface> OldParty,
	const TScriptInterface<IPF2PartyInterface> NewParty)
{
	if ((OldParty.GetInterface() != nullptr) &&
	    (NewParty.GetInterface() == nullptr))
	{
		UE_LOG(
			LogPf2,
			Verbose,
			TEXT("Player ('%s') removed from party ('%s')."),
			*(this->GetIdForLogs()),
			*(OldParty->GetIdForLogs())
		);
	}

	if (NewParty.GetInterface() != nullptr)
	{
		UE_LOG(
			LogPf2,
			Verbose,
			TEXT("Player ('%s') added to party ('%s')."),
			*(this->GetIdForLogs()),
			*(NewParty->GetIdForLogs())
		);
	}

	// Notify listeners.
	this->BP_OnPartyChanged(OldParty, NewParty);
}
