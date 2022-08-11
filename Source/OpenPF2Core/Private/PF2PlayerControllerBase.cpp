// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2PlayerControllerBase.h"

#include "PF2CharacterInterface.h"
#include "PF2PlayerStateInterface.h"

#include "GameModes/PF2GameModeInterface.h"

#include "Utilities/PF2EnumUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

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
	return PF2InterfaceUtilities::ToScriptInterface(Cast<IPF2PlayerStateInterface>(this->PlayerState));
}

APlayerController* APF2PlayerControllerBase::ToPlayerController()
{
	return this;
}

void APF2PlayerControllerBase::HandleModeOfPlayChanged(const EPF2ModeOfPlayType NewMode)
{
	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("[%s] Player controller ('%s') has been notified of a change in mode of play to '%s'."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetName()),
		*(PF2EnumUtilities::ToString(NewMode))
	);

	this->OnModeOfPlayChanged(NewMode);
}

void APF2PlayerControllerBase::MulticastHandleEncounterTurnStarted_Implementation()
{
	this->OnEncounterTurnStarted();
}

void APF2PlayerControllerBase::MulticastHandleEncounterTurnEnded_Implementation()
{
	this->OnEncounterTurnEnded();
}

FString APF2PlayerControllerBase::GetIdForLogs() const
{
	return this->GetName();
}
