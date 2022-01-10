// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2ModeOfPlayRuleSetBase.h"

#include "PF2QueuedActionInterface.h"

#include "Utilities/PF2ArrayUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"

void UPF2ModeOfPlayRuleSetBase::OnQueueAction_Implementation(
	const TScriptInterface<IPF2CharacterInterface>&    Character,
	const TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	// By default there is no queue, so we perform the action immediately.
	Action->PerformAction();
}

void UPF2ModeOfPlayRuleSetBase::OnCancelQueuedAction_Implementation(
	const TScriptInterface<IPF2CharacterInterface>&    Character,
	const TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	// By default there is no queue, so we do nothing.
}

TArray<TScriptInterface<IPF2PlayerControllerInterface>> UPF2ModeOfPlayRuleSetBase::GetPlayerControllers() const
{
	TArray<TScriptInterface<IPF2PlayerControllerInterface>> PlayerControllers;
	const UWorld* const                                     World = this->GetWorld();

	for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();

		IPF2PlayerControllerInterface* const Pf2PlayerController =
			Cast<IPF2PlayerControllerInterface>(PlayerController);

		if (Pf2PlayerController != nullptr)
		{
			PlayerControllers.Add(PF2InterfaceUtilities::ToScriptInterface(Pf2PlayerController));
		}
	}

	return PlayerControllers;
}

TArray<TScriptInterface<IPF2CharacterInterface>> UPF2ModeOfPlayRuleSetBase::GetPlayerControlledCharacters() const
{
	return PF2ArrayUtilities::Map<TScriptInterface<IPF2CharacterInterface>>(
		this->GetPlayerControllers(),
		[](const TScriptInterface<IPF2PlayerControllerInterface> PlayerController)
		{
			return PlayerController->Execute_GetControlledCharacter(PlayerController.GetObject());
		});
}
