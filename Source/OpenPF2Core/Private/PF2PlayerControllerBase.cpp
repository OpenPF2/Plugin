// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2PlayerControllerBase.h"

#include "PF2CharacterInterface.h"

#include "GameModes/PF2GameModeInterface.h"

TScriptInterface<IPF2CharacterInterface> APF2PlayerControllerBase::GetControlledCharacter()
{
	return this->GetPawn();
}

APlayerController* APF2PlayerControllerBase::ToPlayerController()
{
	return this;
}

void APF2PlayerControllerBase::HandleModeOfPlayChanged(const EPF2ModeOfPlayType NewMode)
{
	this->OnModeOfPlayChanged(NewMode);
}

void APF2PlayerControllerBase::MulticastHandleActionQueued_Implementation(const FPF2QueuedActionHandle ActionHandle)
{
	this->OnActionQueued(ActionHandle);
}

void APF2PlayerControllerBase::MulticastHandleActionDequeued_Implementation(const FPF2QueuedActionHandle ActionHandle)
{
	this->OnActionDequeued(ActionHandle);
}

void APF2PlayerControllerBase::ServerCancelQueuedAction_Implementation(const FPF2QueuedActionHandle ActionHandle)
{
	const UWorld*          World    = this->GetWorld();
	IPF2GameModeInterface* GameMode = Cast<IPF2GameModeInterface>(World->GetAuthGameMode());

	if (GameMode != nullptr)
	{
		GameMode->CancelActionQueuedForInitiativeTurnByHandle(ActionHandle);
	}
}
