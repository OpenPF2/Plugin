// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "PF2GameStateInterface.h"
#include "PF2ModeOfPlayType.h"

#include "PF2ModeOfPlayRuleset.generated.h"

UINTERFACE()
class OPENPF2CORE_API UPF2ModeOfPlayRuleSet : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Mode of Play Rule Sets (MoPRS), which provide strategies for the game should
 * behave while in a particular mode of PF2 play.
 *
 * MoPRS not only provide logic that control how different gameplay events are handled, but also can act as an extension
 * to game state by storing and maintaining variables that are relevant for the current mode of play. For example,
 * encounter modes maintain initiative order, number of enemies left standing, etc. which are not relevant in other game
 * modes like exploration mode. A new MoPRS instance is created each time that the mode of play changes, so this state
 * is only maintained while it is relevant.
 *
 * @see EPF2ModeOfPlayType
 */
class OPENPF2CORE_API IPF2ModeOfPlayRuleSet
{
	GENERATED_BODY()

public:
	/**
	 * Function called to notify this rule set that the mode of play that invoked it is now active.
	 *
	 * The rule set should use this as an opportunity to initialize its state (e.g., roll initiative, assemble a list of
	 * enemies, etc.).
	 *
	 * @param ModeOfPlay
	 *	The mode of play that is just starting.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnModeOfPlayStart(EPF2ModeOfPlayType ModeOfPlay);

	/**
	 * Function called to notify this rule set to wrap-up prior to a change in mode of play.
	 *
	 * The rule set should use this as an opportunity to apply any long-lasting effects of the mode (e.g., calculate
	 * experience and hero points, end encounter-only gameplay effects or abilities, etc.).
	 *
	 * @param ModeOfPlay
	 *	The mode of play that is ending.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnModeOfPlayEnd(EPF2ModeOfPlayType ModeOfPlay);

	/**
	 * Determines whether this rule set allows transitioning to the specified mode of play with the given game state.
	 *
	 * Some modes freely allow transitions to other game modes, while others place restrictions on transitions so that
	 * they depend on certain conditions being met. For example, it is common that encounters prevent players from
	 * returning to exploration until they have either: 1) vanquished all enemies within range; 2) retreated
	 * successfully; or 3) forced remaining enemies to retreat. Meanwhile, it is common for players to be able to leave
	 * exploration and downtime modes of play without any conditions.
	 *
	 * @param PF2GameState
	 *	The current game state.
	 * @param TargetMode
	 *	The mode of play to which the game is attempting to transition.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	bool CanTransitionTo(const TScriptInterface<IPF2GameStateInterface>& PF2GameState,
	                     const EPF2ModeOfPlayType                        TargetMode) const;
};
