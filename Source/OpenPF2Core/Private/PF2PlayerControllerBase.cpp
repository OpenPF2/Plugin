// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#include "PF2PlayerControllerBase.h"

#include "PF2CharacterInterface.h"
#include "PF2PlayerStateInterface.h"

#include "GameModes/PF2GameModeInterface.h"

#include "Utilities/PF2EnumUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

#include <GameFramework/PlayerState.h>

void APF2PlayerControllerBase::InitPlayerState()
{
	Super::InitPlayerState();

	this->Native_OnPlayerStateAvailable(this->GetPlayerState());
}

void APF2PlayerControllerBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	this->Native_OnPlayerStateAvailable(this->GetPlayerState());
}

void APF2PlayerControllerBase::SetPawn(APawn* NewPawn)
{
	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("[%s] Player controller ('%s') has taken possession of pawn ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetName()),
		(NewPawn == nullptr) ? TEXT("null") : *(NewPawn->GetFullName())
	);

	Super::SetPawn(NewPawn);
}

TScriptInterface<IPF2PlayerStateInterface> APF2PlayerControllerBase::GetPlayerState() const
{
	TScriptInterface<IPF2PlayerStateInterface> Result;

	if (this->PlayerState == nullptr)
	{
		Result = TScriptInterface<IPF2PlayerStateInterface>();
	}
	else
	{
		Result = PF2InterfaceUtilities::ToScriptInterface(Cast<IPF2PlayerStateInterface>(this->PlayerState));
	}

	return Result;
}

APlayerController* APF2PlayerControllerBase::ToPlayerController()
{
	return this;
}

void APF2PlayerControllerBase::Native_OnModeOfPlayChanged(const EPF2ModeOfPlayType NewMode)
{
	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("[%s] Player controller ('%s') has been notified of a change in mode of play to '%s'."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetName()),
		*(PF2EnumUtilities::ToString(NewMode))
	);

	this->BP_OnModeOfPlayChanged(NewMode);
}

void APF2PlayerControllerBase::Multicast_OnEncounterTurnStarted_Implementation()
{
	this->BP_OnEncounterTurnStarted();
}

void APF2PlayerControllerBase::Multicast_OnEncounterTurnEnded_Implementation()
{
	this->BP_OnEncounterTurnEnded();
}

FString APF2PlayerControllerBase::GetIdForLogs() const
{
	return this->GetName();
}

void APF2PlayerControllerBase::Native_OnPlayerStateAvailable(
	const TScriptInterface<IPF2PlayerStateInterface> NewPlayerState)
{
	if (NewPlayerState == nullptr)
	{
		return;
	}

	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("[%s] Player controller ('%s') has made player state ('%s') available for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs()),
		*(NewPlayerState->GetIdForLogs()),
		*(NewPlayerState->ToPlayerState()->GetPlayerName())
	);

	this->BP_OnPlayerStateAvailable(NewPlayerState);
}
