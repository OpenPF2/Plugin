﻿// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#pragma once

#include <UObject/Interface.h>
#include <UObject/ScriptInterface.h>

#include "GameModes/PF2ModeOfPlayType.h"

#include "PF2GameStateInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class IPF2ModeOfPlayRuleSet;
class IPF2QueuedActionInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPF2GameStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Game States.
 *
 * Game States track information that satisfies the following criteria:
 *   1. Relevant to all players in the same level (e.g., timers, team scores, mode of play).
 *   2. Not specific to any particular character. It should still be valid and relevant even if a player joins or
 *      leaves in the middle of the game. Information tied to a specific character (such as health or stats) should not
 *      be tracked here; it should instead be kept in Player State.
 *   3. Varies throughout gameplay, rather than being constant for the entire session/level. Static information that
 *      only varies level-to-level should be tracked by the Game Mode.
 */
class OPENPF2CORE_API IPF2GameStateInterface
{
	GENERATED_BODY()

public:
	/**
	 * Gets the current play mode for all characters in the loaded level.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 493, "Running Modes of Play":
	 * "Pathfinder sessions are divided into three different modes of play: encounters, exploration, and downtime. Each
	 * mode represents different kinds of situations, with specific stakes and time scales, and characters can use
	 * different sorts of actions and reactions in each."
	 *
	 * This is tracked in the game state rather than in the game mode to allow characters to transition into and out of
	 * encounters while in the same level/map. For example, a character's party may start out in encounter mode in a
	 * meadow but then encounter an assailant, resulting in the play mode changing to encounter mode until either the
	 * assailant or the party have been killed or have fled.
	 */
	UFUNCTION(BlueprintCallable)
	virtual EPF2ModeOfPlayType GetModeOfPlay() = 0;

	/**
	 * Gets the set of rules that govern how the game behaves in the current play mode.
	 *
	 * @return
	 *	The current rule set for the current mode of play.
	 */
	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2ModeOfPlayRuleSet> GetModeOfPlayRuleSet() = 0;

	/**
	 * Sets the current play mode for all characters in the loaded level.
	 *
	 * This should only get called by the game mode (on the server).
	 *
	 * @see EPF2ModeOfPlay
	 *
	 * @param NewMode
	 *	The new play mode.
	 * @param NewRuleSet
	 *	The rules that govern how the game will behave while in the new play mode.
	 */
	virtual void SwitchModeOfPlay(const EPF2ModeOfPlayType                NewMode,
	                              TScriptInterface<IPF2ModeOfPlayRuleSet> NewRuleSet) = 0;

	/**
	 * Adds a character to the current encounter, if an encounter is active.
	 *
	 * This call will have no effect under the following circumstances:
	 *	- If there is no active encounter according to the current Mode of Play Rule Set (MoPRS).
	 *  - If there is an active encounter and the given character is already part of the encounter.
	 *
	 * @param Character
	 *	The character being added to the encounter.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AddCharacterToEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) = 0;

	/**
	 * Removes a character from the current encounter, if an encounter is active.
	 *
	 * This call will have no effect under the following circumstances:
	 *	- If there is no active encounter according to the current Mode of Play Rule Set (MoPRS).
	 *	- If there is an active encounter but the given character is not already part of the encounter.
	 *
	 * @param Character
	 *	The character being added to the encounter.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void RemoveCharacterFromEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) = 0;

	/**
	 * Notifies the Mode of Play Rule Set (MoPRS) that a character wishes to perform an action.
	 *
	 * If the current Mode of Play is structured (e.g., Encounter mode), then the action will be placed into a queue of
	 * actions for the character -- preserving the order that the actions were queued -- and the action will be executed
	 * when it is the character's turn (e.g., according to initiative order). On the other hand, if the current Mode of
	 * Play allows characters to perform actions immediately, the action will not be queued and will instead be given
	 * the opportunity to run before this call returns.
	 *
	 * This should only get called on the server.
	 *
	 * @param Character
	 *	The character for which the action is being queued.
	 * @param Action
	 *	The action being queued.
	 */
	virtual void QueueActionForInitiativeTurn(TScriptInterface<IPF2CharacterInterface>&    Character,
	                                          TScriptInterface<IPF2QueuedActionInterface>& Action) = 0;

	/**
	 * Notifies the Mode of Play Rule Set (MoPRS) that a character no longer wishes to perform a previously-queued
	 * action.
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
	virtual void CancelActionQueuedForInitiativeTurn(TScriptInterface<IPF2CharacterInterface>&    Character,
	                                                 TScriptInterface<IPF2QueuedActionInterface>& Action) = 0;
};
