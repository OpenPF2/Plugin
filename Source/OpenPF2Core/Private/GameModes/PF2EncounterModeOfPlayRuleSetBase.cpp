// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2EncounterModeOfPlayRuleSetBase.h"

#include "OpenPF2Core.h"
#include "Utilities/PF2ArrayUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"
#include "Utilities/PF2MapUtilities.h"

void UPF2EncounterModeOfPlayRuleSetBase::SetCharacterInitiative(
	const TScriptInterface<IPF2CharacterInterface>& Character,
    const int32                                     Initiative)
{
	IPF2CharacterInterface* Pf2Character = PF2InterfaceUtilities::FromScriptInterface(Character);

	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Initiative ('%d') set for character ('%s.%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		Initiative,
		*(Cast<AActor>(Character.GetObject())->GetName()),
		*(Character->GetCharacterName().ToString())
	);

	// Ensure any existing initiative for this character is cleared.
	this->RemoveCharacterFromInitiativeMap(Pf2Character);

	this->CharactersByInitiatives.Add(Initiative, Pf2Character);
	this->RebuildCharacterSequence();
}

bool UPF2EncounterModeOfPlayRuleSetBase::IsInitiativeSetForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	const IPF2CharacterInterface* Pf2Character = PF2InterfaceUtilities::FromScriptInterface(Character);

	return this->CurrentCharacterSequence.Contains(Pf2Character);
}

void UPF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	const IPF2CharacterInterface* Pf2Character = PF2InterfaceUtilities::FromScriptInterface(Character);

	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Initiative cleared for character ('%s.%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Cast<AActor>(Character.GetObject())->GetName()),
		*(Character->GetCharacterName().ToString())
	);

	this->RemoveCharacterFromInitiativeMap(Pf2Character);
	this->RebuildCharacterSequence();
}

void UPF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForAllCharacters()
{
	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Initiative cleared for all characters."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld()))
	);

	this->CharactersByInitiatives.Empty();
	this->CurrentCharacterSequence.Empty();

	this->PreviousCharacter      = nullptr;
	this->PreviousCharacterIndex = -1;
}

TScriptInterface<IPF2CharacterInterface> UPF2EncounterModeOfPlayRuleSetBase::GetNextCharacterByInitiative()
{
	TScriptInterface<IPF2CharacterInterface> Result;
	const int32                              CharacterCount = this->CurrentCharacterSequence.Num();

	if (CharacterCount == 0)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			VeryVerbose,
			TEXT("[%s] There are no characters in the encounter."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld()))
		);

		// No characters to return.
		Result = TScriptInterface<IPF2CharacterInterface>();
	}
	else
	{
		int32                   NextCharacterIndex;
		IPF2CharacterInterface* NextCharacter;

		if ((this->PreviousCharacterIndex == -1) || (this->PreviousCharacterIndex == (CharacterCount - 1)))
		{
			// Restart at the beginning.
			NextCharacterIndex = 0;
		}
		else
		{
			// Advance to the character with the next-lowest initiative.
			NextCharacterIndex = this->PreviousCharacterIndex + 1;
		}

		NextCharacter = this->CurrentCharacterSequence[NextCharacterIndex];

		this->PreviousCharacterIndex = NextCharacterIndex;
		this->PreviousCharacter      = NextCharacter;

		Result = PF2InterfaceUtilities::ToScriptInterface(NextCharacter);
	}

	return Result;
}

TArray<TScriptInterface<IPF2CharacterInterface>> UPF2EncounterModeOfPlayRuleSetBase::GetCharactersInInitiativeOrder() const
{
	return PF2ArrayUtilities::Map<TScriptInterface<IPF2CharacterInterface>>(
		this->CurrentCharacterSequence,
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
		TEXT("[%s] Queuing action ('%s') for character ('%s.%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Action->GetActionName().ToString()),
		*(Cast<AActor>(Character.GetObject())->GetName()),
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
		TEXT("[%s] Removing queued action ('%s') for character ('%s.%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Action->GetActionName().ToString()),
		*(Cast<AActor>(Character.GetObject())->GetName()),
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
	bool                                        ActionExecuted = false;
	TScriptInterface<IPF2QueuedActionInterface> NextAction;

	this->PeekNextQueuedActionForCharacter(Character, NextAction);

	if (NextAction == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			VeryVerbose,
			TEXT("[%s] No actions are currently queued for character ('%s.%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(Cast<AActor>(Character.GetObject())->GetName()),
			*(Character->GetCharacterName().ToString())
		);
	}
	else
	{
		UE_LOG(
			LogPf2CoreEncounters,
			VeryVerbose,
			TEXT("[%s] Executing next queued action ('%s') for character ('%s.%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(NextAction->GetActionName().ToString()),
			*(Cast<AActor>(Character.GetObject())->GetName()),
			*(Character->GetCharacterName().ToString())
		);

		if (NextAction->PerformAction() == EPF2AbilityActivationOutcomeType::Activated)
		{
			this->RemoveQueuedActionForCharacter(Character, NextAction);

			ActionExecuted = true;
		}
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
		this->RemoveQueuedActionForCharacter(Character, NextAction);
	}
}

void UPF2EncounterModeOfPlayRuleSetBase::RebuildCharacterSequence()
{
	TArray<IPF2CharacterInterface*> NewCharacterSequence;

	const TArray<IPF2CharacterInterface*> PlayableCharacters =
		PF2ArrayUtilities::Map<IPF2CharacterInterface*>(
			this->GetPlayerControlledCharacters(),
			[](const TScriptInterface<IPF2CharacterInterface> Character)
			{
				return PF2InterfaceUtilities::FromScriptInterface(Character);
			}
		);

	this->CharactersByInitiatives.KeyStableSort(TGreater<int32>());

	for (const int32 Initiative : PF2MapUtilities::GetKeys(this->CharactersByInitiatives))
	{
		TArray<IPF2CharacterInterface*> CharactersForInitiative;

		this->CharactersByInitiatives.MultiFind(Initiative, CharactersForInitiative, true);

		CharactersForInitiative.StableSort(
			[PlayableCharacters](IPF2CharacterInterface& A, IPF2CharacterInterface& B)
			{
				bool       CharacterAComesFirst  = false;
				const bool bIsCharacterAPlayable = PlayableCharacters.Contains(&A),
				           bIsCharacterBPlayable = PlayableCharacters.Contains(&B);

				if (bIsCharacterAPlayable && !bIsCharacterBPlayable)
				{
					// PCs come after NPCs.
					CharacterAComesFirst = false;
				}
				else if (bIsCharacterAPlayable == bIsCharacterBPlayable)
				{
					// Characters of the same type get randomized.
					// We use the IDs of the objects so that any given pair sorts the same way in future rebuilds.
					if (A.ToActor()->GetUniqueID() < B.ToActor()->GetUniqueID())
					{
						CharacterAComesFirst = true;
					}
					else
					{
						CharacterAComesFirst = false;
					}
				}
				else if (!bIsCharacterAPlayable && bIsCharacterBPlayable)
				{
					// NPCs come before PCs.
					CharacterAComesFirst = true;
				}

				return CharacterAComesFirst;
			}
		);

		NewCharacterSequence.Append(CharactersForInitiative);
	}

	this->CurrentCharacterSequence = NewCharacterSequence;

	// Fix-up our iterator so that we maintain where we're pointing in the sequence after everything shuffled around.
	if (this->PreviousCharacter != nullptr)
	{
		for (int CharacterIndex = 0; CharacterIndex < NewCharacterSequence.Num(); ++CharacterIndex)
		{
			if (this->PreviousCharacter == NewCharacterSequence[CharacterIndex])
			{
				this->PreviousCharacterIndex = CharacterIndex;
				break;
			}
		}
	}
}

void UPF2EncounterModeOfPlayRuleSetBase::RemoveCharacterFromInitiativeMap(const IPF2CharacterInterface* Character)
{
	if (this->PreviousCharacter == Character)
	{
		int32 NewPreviousCharacterIndex;

		// If the character being removed was the last character we returned, jump back to pointing at the character
		// right before the character being removed so that the next character we return comes after what just got
		// removed.
		if (this->PreviousCharacterIndex > 0)
		{
			NewPreviousCharacterIndex = this->PreviousCharacterIndex - 1;
		}
		else
		{
			// NOTE: Length will drop after the removal, but that's not important yet because we're just grabbing what
			// currently occupies this slot.
			NewPreviousCharacterIndex = this->CurrentCharacterSequence.Num() - 1;
		}

		// We do not update PreviousCharacterIndex; it will get updated during the next call to
		// RebuildCharacterSequence().
		this->PreviousCharacter = this->CurrentCharacterSequence[NewPreviousCharacterIndex];
	}

	for (const TTuple<int, IPF2CharacterInterface*>& CharacterInitiativePair :
		 TMultiMap<int32, IPF2CharacterInterface*>(this->CharactersByInitiatives))
	{
		if (CharacterInitiativePair.Value == Character)
		{
			// Remove existing initiative for this character.
			this->CharactersByInitiatives.Remove(CharacterInitiativePair.Key, CharacterInitiativePair.Value);
			break;
		}
	}
}
