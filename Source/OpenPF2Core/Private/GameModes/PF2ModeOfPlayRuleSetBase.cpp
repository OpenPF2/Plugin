// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2ModeOfPlayRuleSetBase.h"

#include "Utilities/PF2ArrayUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"

EPF2CommandExecuteOrQueueResult UPF2ModeOfPlayRuleSetBase::AttemptToExecuteOrQueueCommand_Implementation(
	const TScriptInterface<IPF2CharacterInterface>&        Character,
	const TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	EPF2CommandExecuteOrQueueResult Result;

	// By default there is no queue, so we perform the command immediately.
	Result = IPF2CharacterCommandInterface::ImmediateResultToExecuteOrQueueResult(Command->AttemptExecuteImmediately());

	return Result;
}

TScriptInterface<IPF2GameModeInterface> UPF2ModeOfPlayRuleSetBase::GetGameMode() const
{
	AGameModeBase* GameMode = this->GetWorld()->GetAuthGameMode();

	check(GameMode);

	return TScriptInterface<IPF2GameModeInterface>(GameMode);
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
	return PF2ArrayUtilities::Reduce<TArray<TScriptInterface<IPF2CharacterInterface>>>(
		this->GetPlayerControllers(),
		TArray<TScriptInterface<IPF2CharacterInterface>>(),
		[](TArray<TScriptInterface<IPF2CharacterInterface>>      Characters,
		   const TScriptInterface<IPF2PlayerControllerInterface> PlayerController)
		{
			Characters.Append(PlayerController->GetControlledCharacters());

			return Characters;
		}
	);
}
