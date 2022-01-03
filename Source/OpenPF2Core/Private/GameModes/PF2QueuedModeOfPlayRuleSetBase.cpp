// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2QueuedModeOfPlayRuleSetBase.h"

#include "PF2InterfaceUtilities.h"

void UPF2QueuedModeOfPlayRuleSetBase::QueueActionForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	const TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	this->CharacterQueues.Add(
		PF2InterfaceUtilities::FromScriptInterface(Character),
		PF2InterfaceUtilities::FromScriptInterface(Action)
	);
}

void UPF2QueuedModeOfPlayRuleSetBase::RemoveQueuedActionForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	const TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	this->CharacterQueues.RemoveSingle(
		PF2InterfaceUtilities::FromScriptInterface(Character),
		PF2InterfaceUtilities::FromScriptInterface(Action)
	);
}

bool UPF2QueuedModeOfPlayRuleSetBase::ExecuteNextQueuedActionForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	bool                                        ActionExecuted;
	TScriptInterface<IPF2QueuedActionInterface> NextAction;

	this->PopNextActionQueuedForCharacter(Character, NextAction);

	if (NextAction == nullptr)
	{
		ActionExecuted = false;
	}
	else
	{
		NextAction->PerformAction();

		ActionExecuted = true;
	}

	return ActionExecuted;
}

void UPF2QueuedModeOfPlayRuleSetBase::PeekNextQueuedActionForCharacter(
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

void UPF2QueuedModeOfPlayRuleSetBase::PopNextActionQueuedForCharacter(
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
