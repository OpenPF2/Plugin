// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2PlayerControllerBase.h"

#include "PF2CharacterInterface.h"

#include "GameModes/PF2GameModeInterface.h"

#include "Utilities/PF2ArrayUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"

TArray<TScriptInterface<IPF2CharacterInterface>> APF2PlayerControllerBase::GetControlledCharacters()
{
	return PF2ArrayUtilities::Reduce<TArray<TScriptInterface<IPF2CharacterInterface>>>(
		this->ControlledCharacters,
		TArray<TScriptInterface<IPF2CharacterInterface>>(),
		[](TArray<TScriptInterface<IPF2CharacterInterface>> Characters,
		   const TWeakInterfacePtr<IPF2CharacterInterface>  CurrentCharacter)
		{
			if (CurrentCharacter.IsValid())
			{
				Characters.Add(PF2InterfaceUtilities::ToScriptInterface(CurrentCharacter.Get()));
			}

			return Characters;
		});
}

APlayerController* APF2PlayerControllerBase::ToPlayerController()
{
	return this;
}

void APF2PlayerControllerBase::HandleModeOfPlayChanged(const EPF2ModeOfPlayType NewMode)
{
	this->OnModeOfPlayChanged(NewMode);
}

void APF2PlayerControllerBase::OnPossess(APawn* NewPawn)
{
	IPF2CharacterInterface* Pf2Pawn = Cast<IPF2CharacterInterface>(NewPawn);

	Super::OnPossess(NewPawn);

	if (Pf2Pawn != nullptr)
	{
		const TWeakInterfacePtr<IPF2CharacterInterface> WeakPf2Pawn =
			TWeakInterfacePtr<IPF2CharacterInterface>(Pf2Pawn);

		if (!this->ControlledCharacters.Contains(WeakPf2Pawn))
		{
			// TODO (#22): Expose an explicit way to manage party members and to switch between which one is being
			// controlled.
			this->ControlledCharacters.Add(WeakPf2Pawn);
		}
	}
}

void APF2PlayerControllerBase::MulticastHandleEncounterTurnStarted_Implementation()
{
	this->OnEncounterTurnStarted();
}

void APF2PlayerControllerBase::MulticastHandleEncounterTurnEnded_Implementation()
{
	this->OnEncounterTurnEnded();
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
