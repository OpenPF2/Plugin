// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2ModeOfPlayRuleSetBase.h"

#include <Engine/World.h>

#include <GameFramework/GameModeBase.h>

#include "Commands/PF2CharacterCommandInterface.h"
#include "Commands/PF2CommandQueueInterface.h"

#include "Libraries/PF2CharacterCommandLibrary.h"
#include "Libraries/PF2CharacterLibrary.h"

void APF2ModeOfPlayRuleSetBase::OnModeOfPlayStart(const EPF2ModeOfPlayType ModeOfPlay)
{
	this->BP_OnModeOfPlayStart(ModeOfPlay);
}

void APF2ModeOfPlayRuleSetBase::OnPlayableCharacterStarting(const TScriptInterface<IPF2CharacterInterface>& Character)
{
	this->BP_OnPlayableCharacterStarting(Character);
}

void APF2ModeOfPlayRuleSetBase::OnCharacterAddedToEncounter(const TScriptInterface<IPF2CharacterInterface>& Character)
{
	this->BP_OnCharacterAddedToEncounter(Character);
}

void APF2ModeOfPlayRuleSetBase::OnCharacterRemovedFromEncounter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	this->BP_OnCharacterRemovedFromEncounter(Character);
}

void APF2ModeOfPlayRuleSetBase::OnModeOfPlayEnd(const EPF2ModeOfPlayType ModeOfPlay)
{
	this->BP_OnModeOfPlayEnd(ModeOfPlay);
}

EPF2CommandExecuteOrQueueResult APF2ModeOfPlayRuleSetBase::AttemptToExecuteOrQueueCommand_Implementation(
	const TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	EPF2CommandExecuteOrQueueResult Result;

	// By default there is no queue, so we perform the command immediately.
	Result = UPF2CharacterCommandLibrary::ImmediateResultToExecuteOrQueueResult(Command->AttemptExecuteImmediately());

	return Result;
}

void APF2ModeOfPlayRuleSetBase::AttemptToCancelCommand_Implementation(
	const TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	TScriptInterface<IPF2CharacterInterface>    Character;
	TScriptInterface<IPF2CommandQueueInterface> CommandQueue;

	if (Command.GetInterface() == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("AttemptToCancelCommand(): Command cannot be null."),
		);

		return;
	}

	Character = Command->GetTargetCharacter();

	if (Character.GetInterface() == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("AttemptToCancelCommand(%s): Command has null target character."),
			*(Command->GetIdForLogs())
		);

		return;
	}

	CommandQueue = Character->GetCommandQueueComponent();

	if (Character.GetInterface() == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Verbose,
			TEXT("AttemptToCancelCommand(%s): Character ('%s') has no command queue component -- nothing to cancel."),
			*(Command->GetIdForLogs()),
			*(Character->GetIdForLogs())
		);

		return;
	}

	// Default implementation -- remove the command from the character's command queue, if one exists.
	CommandQueue->Remove(Command);
}

TScriptInterface<IPF2GameModeInterface> APF2ModeOfPlayRuleSetBase::GetGameMode() const
{
	AGameModeBase* GameMode = this->GetWorld()->GetAuthGameMode();

	check(GameMode != nullptr);

	return TScriptInterface<IPF2GameModeInterface>(GameMode);
}

TArray<TScriptInterface<IPF2PlayerControllerInterface>> APF2ModeOfPlayRuleSetBase::GetPlayerControllers() const
{
	return UPF2CharacterLibrary::GetPlayerControllers(this->GetWorld());
}

TArray<TScriptInterface<IPF2CharacterInterface>> APF2ModeOfPlayRuleSetBase::GetPlayerControlledCharacters() const
{
	return UPF2CharacterLibrary::GetPlayerControlledCharacters(this->GetWorld());
}

void APF2ModeOfPlayRuleSetBase::AddCharacterToEncounter(const TScriptInterface<IPF2CharacterInterface> Character)
{
	this->OnCharacterAddedToEncounter(Character);
}

void APF2ModeOfPlayRuleSetBase::AddAllPlayerControlledCharactersToEncounter()
{
	for (const TScriptInterface<IPF2CharacterInterface>& Character : this->GetPlayerControlledCharacters())
	{
		this->AddCharacterToEncounter(Character);
	}
}

void APF2ModeOfPlayRuleSetBase::RemoveCharacterFromEncounter(
	const TScriptInterface<IPF2CharacterInterface> Character)
{
	this->OnCharacterRemovedFromEncounter(Character);
}
