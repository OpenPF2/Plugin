// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2EncounterModeOfPlayRuleSetBase.h"

#include "OpenPF2Core.h"
#include "PF2ArrayUtilities.h"
#include "PF2InterfaceUtilities.h"
#include "PF2LogUtilities.h"
#include "PF2MapUtilities.h"

void UPF2EncounterModeOfPlayRuleSetBase::SetCharacterInitiative(
	const TScriptInterface<IPF2CharacterInterface>& Character,
    const int32                                     Initiative)
{
	IPF2CharacterInterface* Pf2Character = PF2InterfaceUtilities::FromScriptInterface(Character);

	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Initiative ('%d') set for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		Initiative,
		*(Character->GetCharacterName().ToString())
	);

	this->CharacterInitiatives.Add(Pf2Character, Initiative);
	this->CharacterInitiatives.ValueStableSort(TGreater<int32>());
}

void UPF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	const IPF2CharacterInterface* Pf2Character = PF2InterfaceUtilities::FromScriptInterface(Character);

	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Initiative cleared for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Character->GetCharacterName().ToString())
	);

	this->CharacterInitiatives.Remove(Pf2Character);
}

void UPF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForAllCharacters()
{
	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Initiative cleared for all characters."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld()))
	);

	this->CharacterInitiatives.Empty();
}

void UPF2EncounterModeOfPlayRuleSetBase::GetCharactersInInitiativeOrder(
	TArray<TScriptInterface<IPF2CharacterInterface>>& Characters) const
{
	const TArray<IPF2CharacterInterface*> Pf2Characters = PF2MapUtilities::GetKeys(this->CharacterInitiatives);

	Characters =
		PF2ArrayUtilities::Map<TScriptInterface<IPF2CharacterInterface>>(
			Pf2Characters,
			[](IPF2CharacterInterface* Pf2Character)
			{
				return PF2InterfaceUtilities::ToScriptInterface(Pf2Character);
			}
		);
}

void UPF2EncounterModeOfPlayRuleSetBase::QueueActionForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	const TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Queuing action ('%s') for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Action->GetActionName().ToString()),
		*(Character->GetCharacterName().ToString())
	);

	this->CharacterQueues.Add(
		PF2InterfaceUtilities::FromScriptInterface(Character),
		PF2InterfaceUtilities::FromScriptInterface(Action)
	);
}

void UPF2EncounterModeOfPlayRuleSetBase::RemoveQueuedActionForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	const TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Removing queued action ('%s') for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Action->GetActionName().ToString()),
		*(Character->GetCharacterName().ToString())
	);

	this->CharacterQueues.RemoveSingle(
		PF2InterfaceUtilities::FromScriptInterface(Character),
		PF2InterfaceUtilities::FromScriptInterface(Action)
	);
}

bool UPF2EncounterModeOfPlayRuleSetBase::ExecuteNextQueuedActionForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	bool                                        ActionExecuted;
	TScriptInterface<IPF2QueuedActionInterface> NextAction;

	this->PopNextActionQueuedForCharacter(Character, NextAction);

	if (NextAction == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			VeryVerbose,
			TEXT("[%s] No actions are currently queued for character ('%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(Character->GetCharacterName().ToString())
		);

		ActionExecuted = false;
	}
	else
	{
		UE_LOG(
			LogPf2CoreEncounters,
			VeryVerbose,
			TEXT("[%s] Executing next queued action ('%s') for character ('%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(NextAction->GetActionName().ToString()),
			*(Character->GetCharacterName().ToString())
		);

		NextAction->PerformAction();

		ActionExecuted = true;
	}

	return ActionExecuted;
}

void UPF2EncounterModeOfPlayRuleSetBase::PeekNextQueuedActionForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	TScriptInterface<IPF2QueuedActionInterface>& NextAction) const
{
	const IPF2CharacterInterface*      PF2Character = PF2InterfaceUtilities::FromScriptInterface(Character);
	TArray<IPF2QueuedActionInterface*> CharacterActions;

	this->CharacterQueues.MultiFind(PF2Character, CharacterActions);

	if (CharacterActions.Num() != 0)
	{
		IPF2QueuedActionInterface* NextActionPtr = CharacterActions.Pop();

		NextAction = PF2InterfaceUtilities::ToScriptInterface<IPF2QueuedActionInterface>(NextActionPtr);
	}
}

void UPF2EncounterModeOfPlayRuleSetBase::PopNextActionQueuedForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	TScriptInterface<IPF2QueuedActionInterface>& NextAction)
{
	this->PeekNextQueuedActionForCharacter(Character, NextAction);

	if (NextAction != nullptr)
	{
		const IPF2CharacterInterface* CharacterInterface = PF2InterfaceUtilities::FromScriptInterface(Character);
		IPF2QueuedActionInterface*    ActionInterface    = PF2InterfaceUtilities::FromScriptInterface(NextAction);

		this->CharacterQueues.RemoveSingle(CharacterInterface, ActionInterface);
	}
}
