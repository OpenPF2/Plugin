// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/ScriptInterface.h>

#include "PF2CharacterInterface.h"
#include "PF2ModeOfPlayRuleSetBase.h"
#include "PF2QueuedActionInterface.h"

#include "PF2EncounterModeOfPlayRuleSetBase.generated.h"

/**
 * Base class for PF2 Mode of Play Rule Sets (MoPRS) that need encounter logic, including initiative and queued actions.
 *
 * Encounters often involve each character "rolling" for their initiative order, and then performing attacks in order of
 * their initiative. Since OpenPF2 is intended to support action RPGs just as well as turn-based RPGs, this base class
 * provides the ability for characters to "queue-up" abilities/actions that they want to perform when it is their turn
 * to keep combat flowing despite the turn-based nature of PF2 rules.
 */
UCLASS(Abstract, Blueprintable)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2EncounterModeOfPlayRuleSetBase : public UPF2ModeOfPlayRuleSetBase
{
	GENERATED_BODY()

protected:
	/**
	 * The queue of actions for each character in the encounter.
	 */
	TMultiMap<const IPF2CharacterInterface*, IPF2QueuedActionInterface *> CharacterQueues;

	/**
	 * A map of characters to their initiative.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 13, "Initiative":
	 * "At the start of an encounter, all creatures involved roll for initiative to determine the order in which they
	 * act. The higher the result of its roll, the earlier a creature gets to act."
	 */
	TMap<IPF2CharacterInterface*, int> CharacterInitiatives;

	/**
	 * Sets the initiative of the specified character.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 13, "Initiative":
	 * "At the start of an encounter, all creatures involved roll for initiative to determine the order in which they
	 * act. The higher the result of its roll, the earlier a creature gets to act."
	 *
	 * @param Character
	 *	The character for which initiative is being set.
	 * @param Initiative
	 *	The initiative value to use for the specified character.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Initiative")
	void SetCharacterInitiative(const TScriptInterface<IPF2CharacterInterface>& Character, const int32 Initiative);

	/**
	 * Clears any initiative value set for the specified character.
	 *
	 * If the character does not have any initiative set, this has no effect.
	 *
	 * @param Character
	 *	The character for which initiative is being cleared.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Initiative")
	void ClearInitiativeForCharacter(const TScriptInterface<IPF2CharacterInterface>& Character);

	/**
	 * Clears all initiative values set for all characters.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Initiative")
	void ClearInitiativeForAllCharacters();

	/**
	 * Gets all characters in the order of their initiative.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 13, "Initiative":
	 * "At the start of an encounter, all creatures involved roll for initiative to determine the order in which they
	 * act. The higher the result of its roll, the earlier a creature gets to act."
	 *
	 * Only characters that have an initiative set are returned; all others are excluded.
	 *
	 * @param Characters
	 *	The list of characters, sorted in order of highest to lowest initiative.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Initiative")
	void GetCharactersInInitiativeOrder(TArray<TScriptInterface<IPF2CharacterInterface>>& Characters) const;

	/**
	 * Adds the specified action to the queue of actions being maintained for the specified PF2 character.
	 *
	 * @param Character
	 *	The character that is queuing the action up.
	 * @param Action
	 *	The action that is being queued.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Action Queue")
	void QueueActionForCharacter(
		const TScriptInterface<IPF2CharacterInterface>&    Character,
		const TScriptInterface<IPF2QueuedActionInterface>& Action);

	/**
	 * Removes the specified action from the queue of actions being maintained for the specified PF2 character.
	 *
	 * @param Character
	 *	The character that queued-up the action.
	 * @param Action
	 *	The previously-queued action that is being canceled.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Action Queue")
	void RemoveQueuedActionForCharacter(
		const TScriptInterface<IPF2CharacterInterface>&    Character,
		const TScriptInterface<IPF2QueuedActionInterface>& Action);

	/**
	 * Performs the next action in the specified character's queue of actions (if there is one).
	 *
	 * The action is automatically removed from the character's queue of actions.
	 *
	 * @param Character
	 *	The character whose turn it is to act.
	 *
	 * @return
	 *	- true if the character had an action queued up that was executed
	 *	- false if no action was executed because the character is out of actions to execute.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Action Queue")
	UPARAM(DisplayName = "Was Executed")
	bool ExecuteNextQueuedActionForCharacter(const TScriptInterface<IPF2CharacterInterface>& Character);

	/**
	 * Returns the next action in the specified character's queue of actions (if there is one).
	 *
	 * The action is not removed from the queue.
	 *
	 * @param Character
	 *	The character for which an action is desired.
	 * @param NextAction
	 *	The output -- either the next action for the specified character; or an invalid reference if the character does
	 *	not have any more queued actions.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Action Queue")
	void PeekNextQueuedActionForCharacter(
		const TScriptInterface<IPF2CharacterInterface>& Character,
		TScriptInterface<IPF2QueuedActionInterface>& NextAction) const;

	/**
	 * Removes and returns the next action in the specified character's queue of actions (if there is one).
	 *
	 * The action is removed from the queue.
	 *
	 * @param Character
	*	The character for which an action is desired.
	 * @param NextAction
	 *	The output -- either the next action for the specified character; or an invalid reference if the character does
	 *	not have any more queued actions.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Action Queue")
	void PopNextActionQueuedForCharacter(
		const TScriptInterface<IPF2CharacterInterface>& Character,
		TScriptInterface<IPF2QueuedActionInterface>& NextAction);
};
