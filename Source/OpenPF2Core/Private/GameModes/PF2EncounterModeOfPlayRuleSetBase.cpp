// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2EncounterModeOfPlayRuleSetBase.h"

#include "OpenPF2Core.h"
#include "PF2CharacterInterface.h"
#include "PF2PlayerControllerBase.h"
#include "PF2PlayerControllerInterface.h"

#include "Commands/PF2CommandQueueInterface.h"

#include "Utilities/PF2ArrayUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"
#include "Utilities/PF2MapUtilities.h"

void APF2EncounterModeOfPlayRuleSetBase::StartTurnForCharacter(const TScriptInterface<IPF2CharacterInterface> Character)
{
	const TScriptInterface<IPF2PlayerControllerInterface> PlayerController = Character->GetPlayerController();

	check(Character != nullptr);

	UE_LOG(
		LogPf2CoreEncounters,
		Verbose,
		TEXT("[%s] Starting turn for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Character->GetIdForLogs())
	);

	if (PlayerController != nullptr)
	{
		IPF2PlayerControllerInterface::Execute_MulticastHandleEncounterTurnStarted(PlayerController.GetObject());
	}

	IPF2CharacterInterface::Execute_MulticastHandleEncounterTurnStarted(Character.GetObject());
}

void APF2EncounterModeOfPlayRuleSetBase::EndTurnForCharacter(const TScriptInterface<IPF2CharacterInterface> Character)
{
	const TScriptInterface<IPF2PlayerControllerInterface> PlayerController = Character->GetPlayerController();

	check(Character != nullptr);

	UE_LOG(
		LogPf2CoreEncounters,
		Verbose,
		TEXT("[%s] Ending turn for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Character->GetIdForLogs())
	);

	if (PlayerController != nullptr)
	{
		IPF2PlayerControllerInterface::Execute_MulticastHandleEncounterTurnEnded(PlayerController.GetObject());
	}

	IPF2CharacterInterface::Execute_MulticastHandleEncounterTurnEnded(Character.GetObject());
}

void APF2EncounterModeOfPlayRuleSetBase::SetCharacterInitiative(
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
		*(Character->GetIdForLogs())
	);

	// Ensure any existing initiative for this character is cleared.
	this->RemoveCharacterFromInitiativeMap(Pf2Character);

	this->CharactersByInitiatives.Add(Initiative, Pf2Character);
	this->RebuildCharacterSequence();
}

bool APF2EncounterModeOfPlayRuleSetBase::IsInitiativeSetForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character) const
{
	const IPF2CharacterInterface* Pf2Character = PF2InterfaceUtilities::FromScriptInterface(Character);

	return this->CurrentCharacterSequence.Contains(Pf2Character);
}

void APF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	const IPF2CharacterInterface* Pf2Character = PF2InterfaceUtilities::FromScriptInterface(Character);

	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Initiative cleared for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Character->GetIdForLogs())
	);

	this->RemoveCharacterFromInitiativeMap(Pf2Character);
	this->RebuildCharacterSequence();
}

void APF2EncounterModeOfPlayRuleSetBase::ClearInitiativeForAllCharacters()
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

TScriptInterface<IPF2CharacterInterface> APF2EncounterModeOfPlayRuleSetBase::GetNextCharacterByInitiative()
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

TArray<TScriptInterface<IPF2CharacterInterface>> APF2EncounterModeOfPlayRuleSetBase::GetCharactersInInitiativeOrder() const
{
	return PF2InterfaceUtilities::ToScriptInterfaces<IPF2CharacterInterface>(this->CurrentCharacterSequence);
}

void APF2EncounterModeOfPlayRuleSetBase::QueueCommandForCharacter(
	const TScriptInterface<IPF2CharacterInterface>&        Character,
	const TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	const IPF2CharacterInterface* CharacterIntf = PF2InterfaceUtilities::FromScriptInterface(Character);

	check(CharacterIntf != nullptr);

	UE_LOG(
		LogPf2CoreEncounters,
		VeryVerbose,
		TEXT("[%s] Queuing command ('%s') for character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(Command->GetIdForLogs()),
		*(Character->GetIdForLogs())
	);

	CharacterIntf->GetCommandQueueComponent()->Enqueue(Command);
}

void APF2EncounterModeOfPlayRuleSetBase::CancelQueuedCommandsForAllCharacters()
{
	for (const IPF2CharacterInterface* Character : this->CurrentCharacterSequence)
	{
		Character->GetCommandQueueComponent()->Clear();
	}
}

EPF2ImmediateCommandExecutionResult APF2EncounterModeOfPlayRuleSetBase::ExecuteNextQueuedCommandForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character)
{
	return Character->GetCommandQueueComponent()->PopAndExecuteNext();
}

bool APF2EncounterModeOfPlayRuleSetBase::DoesCharacterHaveNextCommandQueued(
	const TScriptInterface<IPF2CharacterInterface>& Character) const
{
	TScriptInterface<IPF2CharacterCommandInterface> NextCommand;

	Character->GetCommandQueueComponent()->PeekNext(NextCommand);

	return (NextCommand != nullptr);
}

void APF2EncounterModeOfPlayRuleSetBase::PeekNextQueuedCommandForCharacter(
	const TScriptInterface<IPF2CharacterInterface>&  Character,
	TScriptInterface<IPF2CharacterCommandInterface>& NextCommand) const
{
	Character->GetCommandQueueComponent()->PeekNext(NextCommand);
}

void APF2EncounterModeOfPlayRuleSetBase::PopNextCommandQueuedForCharacter(
	const TScriptInterface<IPF2CharacterInterface>& Character,
	TScriptInterface<IPF2CharacterCommandInterface>& NextCommand)
{
	Character->GetCommandQueueComponent()->PopNext(NextCommand);
}

void APF2EncounterModeOfPlayRuleSetBase::RebuildCharacterSequence()
{
	TArray<IPF2CharacterInterface*> NewCharacterSequence;

	const TArray<IPF2CharacterInterface*> PlayableCharacters =
		PF2InterfaceUtilities::FromScriptInterfaces<IPF2CharacterInterface>(this->GetPlayerControlledCharacters());

	this->CharactersByInitiatives.KeyStableSort(TGreater<int32>());

	for (const int32 Initiative : PF2MapUtilities::GetKeys(this->CharactersByInitiatives))
	{
		TArray<IPF2CharacterInterface*> CharactersForInitiative;

		this->CharactersByInitiatives.MultiFind(Initiative, CharactersForInitiative, true);

		CharactersForInitiative.StableSort(
			[PlayableCharacters](IPF2CharacterInterface& A, IPF2CharacterInterface& B)
			{
				bool       bCharacterAComesFirst = false;
				const bool bIsCharacterAPlayable = PlayableCharacters.Contains(&A),
				           bIsCharacterBPlayable = PlayableCharacters.Contains(&B);

				if (bIsCharacterAPlayable && !bIsCharacterBPlayable)
				{
					// PCs come after NPCs.
					bCharacterAComesFirst = false;
				}
				else if (bIsCharacterAPlayable == bIsCharacterBPlayable)
				{
					// Characters of the same type get randomized.
					// We use the IDs of the objects so that any given pair sorts the same way in future rebuilds.
					if (A.ToActor()->GetUniqueID() < B.ToActor()->GetUniqueID())
					{
						bCharacterAComesFirst = true;
					}
					else
					{
						bCharacterAComesFirst = false;
					}
				}
				else if (!bIsCharacterAPlayable && bIsCharacterBPlayable)
				{
					// NPCs come before PCs.
					bCharacterAComesFirst = true;
				}

				return bCharacterAComesFirst;
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

void APF2EncounterModeOfPlayRuleSetBase::RemoveCharacterFromInitiativeMap(const IPF2CharacterInterface* Character)
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
