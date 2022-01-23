// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>
#include <UObject/ScriptInterface.h>

#include "PF2ModeOfPlayRuleSetInterface.h"

#include "Abilities/PF2ActionQueueResult.h"

#include "PF2GameModeInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2GameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Player Modes.
 */
class OPENPF2CORE_API IPF2GameModeInterface
{
	GENERATED_BODY()

public:
	/**
	 * Creates the appropriate rule set for the given mode of play.
	 *
	 * @return
	 *	The rule set for the current mode of play.
	 */
	virtual TScriptInterface<IPF2ModeOfPlayRuleSetInterface> CreateModeOfPlayRuleSet(const EPF2ModeOfPlayType ModeOfPlay) = 0;

	/**
	 * Requests a switch of the play mode to encounter mode.
	 *
	 * The request is subject to any business rules of the game mode. If the switch is not allowed by current game
	 * rules, the game mode will not be changed.
	 *
	 * @see EPF2ModeOfPlay
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual void RequestEncounterMode() = 0;

	/**
	 * Requests a switch of the play mode to exploration mode.
	 *
	 * The request is subject to any business rules of the game mode. If the switch is not allowed by current game
	 * rules, the game mode will not be changed.
	 *
	 * @see EPF2ModeOfPlay
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual void RequestExplorationMode() = 0;

	/**
	 * Requests a switch of the play mode to downtime mode.
	 *
	 * The request is subject to any business rules of the game mode. If the switch is not allowed by current game
	 * rules, the game mode will not be changed.
	 *
	 * @see EPF2ModeOfPlay
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual void RequestDowntimeMode() = 0;

	/**
	 * Adds a character to the current encounter, if an encounter is active.
	 *
	 * This call will have no effect under the following circumstances:
	 *	- If there is no active encounter according to game mode rules or the current Mode of Play Rule Set (MoPRS).
	 *	- If there is an active encounter and the given character is already part of the encounter.
	 *
	 * @param Character
	 *	The character being added to the encounter.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual void AddCharacterToEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) = 0;

	/**
	 * Removes a character from the current encounter, if an encounter is active.
	 *
	 * This call will have no effect under the following circumstances:
	 *	- If there is no active encounter according to game mode rules or the current Mode of Play Rule Set (MoPRS).
	 *	- If there is an active encounter but the given character is not already part of the encounter.
	 *
	 * @param Character
	 *	The character being added to the encounter.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual void RemoveCharacterFromEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) = 0;

	/**
	 * Notifies game rules and/or the Mode of Play Rule Set (MoPRS) that a character wishes to perform an action.
	 *
	 * If the current mode is structured (e.g., Encounter mode), then the action will be placed into a queue of actions
	 * for the character -- preserving the order that the actions were queued -- and the action will be executed when it
	 * is the character's turn (e.g., according to initiative order). On the other hand, if the current Mode of Play
	 * allows characters to perform actions immediately, the action will not be queued and will instead be given the
	 * opportunity to run before this call returns.
	 *
	 * @param Character
	 *	The character for which the action is being queued.
	 * @param Action
	 *	The action being queued.
	 * @param OutQueueResult
	 *	An optional output parameter to be notified of whether the action was actually queued, executed immediately,
	 *	or refused.
	 * @return
	 *	If the action was queued: a handle to refer to the action on the server in the future.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual FPF2QueuedActionHandle QueueActionForInitiativeTurn(
		TScriptInterface<IPF2CharacterInterface>&    Character,
		TScriptInterface<IPF2QueuedActionInterface>& Action,
		EPF2ActionQueueResult&                       OutQueueResult) = 0;

	/**
	 * Notifies the game rules and/or the Mode of Play Rule Set (MoPRS) that a character no longer wishes to perform a
	 * previously-queued action.
	 *
	 * This should be used if the action is being garbage collected/destroyed; or if the action has been canceled by
	 * other means, such as via a HUD or UMG widget that a player has used to second-guess an action decision they have
	 * previously made.
	 *
	 * If the specified action is not in the queue for the specified character, no changes are made to the action queue
	 * and this method simply returns.
	 *
	 * This should only get called on the server.
	 *
	 * @param ActionHandle
	 *	A reference to the action to remove from the queue.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual void CancelActionQueuedForInitiativeTurnByHandle(const FPF2QueuedActionHandle ActionHandle) = 0;

	/**
	 * Notifies the game rules and/or the Mode of Play Rule Set (MoPRS) that a character no longer wishes to perform a
	 * previously-queued action.
	 *
	 * This should be used if the action is being garbage collected/destroyed; or if the action has been canceled by
	 * other means, such as via a HUD or UMG widget that a player has used to second-guess an action decision they have
	 * previously made.
	 *
	 * If the specified action is not in the queue for the specified character, no changes are made to the action queue
	 * and this method simply returns.
	 *
	 * This should only get called on the server.
	 *
	 * @param Character
	 *	The character for which the action was previously queued.
	 * @param Action
	 *	The action to remove from the queue.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Game Modes")
	virtual void CancelActionQueuedForInitiativeTurn(const TScriptInterface<IPF2CharacterInterface>&    Character,
	                                                 const TScriptInterface<IPF2QueuedActionInterface>& Action) = 0;
};
