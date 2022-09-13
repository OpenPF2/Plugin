// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2EncounterModeOfPlayRuleSetBase.h"

#include "OpenPF2Core.h"
#include "PF2CharacterInterface.h"
#include "PF2PlayerControllerBase.h"
#include "PF2PlayerControllerInterface.h"

#include "Commands/PF2CharacterCommandInterface.h"
#include "Commands/PF2CommandQueueInterface.h"

#include "GameModes/PF2CharacterInitiativeQueueComponent.h"

#include "Utilities/PF2InterfaceUtilities.h"

APF2EncounterModeOfPlayRuleSetBase::APF2EncounterModeOfPlayRuleSetBase()
{
	this->CharacterInitiativeQueue =
		this->CreateDefaultSubobject<UPF2CharacterInitiativeQueueComponent>(TEXT("CharacterInitiativeQueue"));
}

bool APF2EncounterModeOfPlayRuleSetBase::HavePlayableCharacters() const
{
	bool Result = false;

	if (!this->GetCharacterInitiativeQueue()->IsEmpty())
	{
		for (const TScriptInterface<IPF2CharacterInterface> Character : this->GetCharactersInInitiativeOrder())
		{
			if (Character->IsAlive())
			{
				Result = true;
				break;
			}
		}
	}

	return Result;
}

void APF2EncounterModeOfPlayRuleSetBase::StartTurnForCharacter(
	const TScriptInterface<IPF2CharacterInterface> Character)
{
	const TScriptInterface<IPF2PlayerControllerInterface> PlayerController = Character->GetPlayerController();

	check(Character != nullptr);

	UE_LOG(
		LogPf2CoreEncounters,
		Verbose,
		TEXT("Starting turn for character ('%s')."),
		*(Character->GetIdForLogs())
	);

	this->SetActiveCharacter(Character);

	if (PlayerController != nullptr)
	{
		IPF2PlayerControllerInterface::Execute_Multicast_OnEncounterTurnStarted(PlayerController.GetObject());
	}

	IPF2CharacterInterface::Execute_Multicast_OnEncounterTurnStarted(Character.GetObject());
}

void APF2EncounterModeOfPlayRuleSetBase::EndTurnForCharacter(const TScriptInterface<IPF2CharacterInterface> Character)
{
	const TScriptInterface<IPF2PlayerControllerInterface> PlayerController = Character->GetPlayerController();

	check(Character != nullptr);

	UE_LOG(
		LogPf2CoreEncounters,
		Verbose,
		TEXT("Ending turn for character ('%s')."),
		*(Character->GetIdForLogs())
	);

	this->SetActiveCharacter(TScriptInterface<IPF2CharacterInterface>(nullptr));

	if (PlayerController != nullptr)
	{
		IPF2PlayerControllerInterface::Execute_Multicast_OnEncounterTurnEnded(PlayerController.GetObject());
	}

	IPF2CharacterInterface::Execute_Multicast_OnEncounterTurnEnded(Character.GetObject());
}

void APF2EncounterModeOfPlayRuleSetBase::SetCharacterInitiative(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	const int32                                     Initiative)
{
	this->GetCharacterInitiativeQueue()->SetCharacterInitiative(Character, Initiative);
}

bool APF2EncounterModeOfPlayRuleSetBase::IsInitiativeSetForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character) const
{
	return this->GetCharacterInitiativeQueue()->IsInitiativeSetForCharacter(Character);
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void APF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	this->GetCharacterInitiativeQueue()->ClearInitiativeForCharacter(Character);
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void APF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForAllCharacters()
{
	this->GetCharacterInitiativeQueue()->ClearInitiativeForAllCharacters();
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
TScriptInterface<IPF2CharacterInterface> APF2EncounterModeOfPlayRuleSetBase::GetNextCharacterByInitiative()
{
	return this->GetCharacterInitiativeQueue()->GetNextCharacterByInitiative();
}

TArray<TScriptInterface<IPF2CharacterInterface>> APF2EncounterModeOfPlayRuleSetBase::GetCharactersInInitiativeOrder() const
{
	return this->GetCharacterInitiativeQueue()->GetCharactersInInitiativeOrder();
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void APF2EncounterModeOfPlayRuleSetBase::QueueCommandForCharacter(
	const TScriptInterface<IPF2CharacterInterface>&        Character,
	const TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	const TScriptInterface<IPF2CommandQueueInterface> CommandQueue = Character->GetCommandQueueComponent();

	if (CommandQueue == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Error,
			TEXT("Character ('%s') lacks a command queue component; unable to queue command ('%s')."),
			*(Character->GetIdForLogs()),
			*(Command->GetIdForLogs())
		);
	}
	else
	{
		UE_LOG(
			LogPf2CoreEncounters,
			VeryVerbose,
			TEXT("Queuing command ('%s') for character ('%s')."),
			*(Command->GetIdForLogs()),
			*(Character->GetIdForLogs())
		);

		CommandQueue->Enqueue(Command);
	}
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void APF2EncounterModeOfPlayRuleSetBase::CancelQueuedCommandsForAllCharacters()
{
	for (const TScriptInterface<IPF2CharacterInterface> Character : this->GetCharactersInInitiativeOrder())
	{
		const TScriptInterface<IPF2CommandQueueInterface> CommandQueue = Character->GetCommandQueueComponent();

		if (CommandQueue == nullptr)
		{
			UE_LOG(
				LogPf2CoreEncounters,
				Warning,
				TEXT("Character ('%s') lacks a command queue component; no commands to clear."),
				*(Character->GetIdForLogs())
			);
		}
		else
		{
			CommandQueue->Clear();
		}
	}
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
EPF2CommandExecuteImmediatelyResult APF2EncounterModeOfPlayRuleSetBase::ExecuteNextQueuedCommandForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	EPF2CommandExecuteImmediatelyResult               Result;
	const TScriptInterface<IPF2CommandQueueInterface> CommandQueue = Character->GetCommandQueueComponent();

	if (CommandQueue == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Warning,
			TEXT("Character ('%s') lacks a command queue component; unable to execute any commands."),
			*(Character->GetIdForLogs())
		);

		Result = EPF2CommandExecuteImmediatelyResult::None;
	}
	else
	{
		Result = CommandQueue->PopAndExecuteNext();
	}

	return Result;
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeStatic
bool APF2EncounterModeOfPlayRuleSetBase::DoesCharacterHaveNextCommandQueued(
	const TScriptInterface<IPF2CharacterInterface>& Character) const
{
	bool                                              Result;
	const TScriptInterface<IPF2CommandQueueInterface> CommandQueue = Character->GetCommandQueueComponent();

	if (CommandQueue == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Warning,
			TEXT("Character ('%s') lacks a command queue component; it is not possible to queue commands."),
			*(Character->GetIdForLogs())
		);

		Result = false;
	}
	else
	{
		TScriptInterface<IPF2CharacterCommandInterface> NextCommand;

		CommandQueue->PeekNext(NextCommand);

		Result = (NextCommand != nullptr);
	}

	return Result;
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeStatic
// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void APF2EncounterModeOfPlayRuleSetBase::PeekNextQueuedCommandForCharacter(
	const TScriptInterface<IPF2CharacterInterface>&  Character,
	TScriptInterface<IPF2CharacterCommandInterface>& NextCommand) const
{
	const TScriptInterface<IPF2CommandQueueInterface> CommandQueue = Character->GetCommandQueueComponent();

	if (CommandQueue == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Warning,
			TEXT("Character ('%s') lacks a command queue component; it is not possible to queue commands."),
			*(Character->GetIdForLogs())
		);

		NextCommand = TScriptInterface<IPF2CharacterCommandInterface>(nullptr);
	}
	else
	{
		CommandQueue->PeekNext(NextCommand);
	}
}

// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeStatic
// ReSharper disable once CppUE4BlueprintCallableFunctionMayBeConst
void APF2EncounterModeOfPlayRuleSetBase::PopNextCommandQueuedForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	TScriptInterface<IPF2CharacterCommandInterface>& NextCommand)
{
	const TScriptInterface<IPF2CommandQueueInterface> CommandQueue = Character->GetCommandQueueComponent();

	if (CommandQueue == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Warning,
			TEXT("Character ('%s') lacks a command queue component; it is not possible to queue commands."),
			*(Character->GetIdForLogs())
		);

		NextCommand = TScriptInterface<IPF2CharacterCommandInterface>(nullptr);
	}
	else
	{
		CommandQueue->PopNext(NextCommand);
	}
}

TScriptInterface<IPF2CharacterInterface> APF2EncounterModeOfPlayRuleSetBase::GetActiveCharacter() const
{
	return this->ActiveCharacter;
}

void APF2EncounterModeOfPlayRuleSetBase::SetActiveCharacter(
	const TScriptInterface<IPF2CharacterInterface>& NewActiveCharacter)
{
	this->ActiveCharacter = NewActiveCharacter;
}
