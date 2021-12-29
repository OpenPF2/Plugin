// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>
#include <UObject/ScriptInterface.h>

#include "PF2ModeOfPlayRuleSet.h"

#include "PF2GameModeInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
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
	virtual TScriptInterface<IPF2ModeOfPlayRuleSet> CreateModeOfPlayRuleSet(const EPF2ModeOfPlayType ModeOfPlay) = 0;

	/**
	 * Requests a switch of the play mode to encounter mode.
	 *
	 * The request is subject to any business rules of the game mode. If the switch is not allowed by current game
	 * rules, the game mode will not be changed.
	 *
	 * @see EPF2ModeOfPlay
	 */
	UFUNCTION(BlueprintCallable)
	virtual void StartEncounterMode() = 0;

	/**
	 * Requests a switch of the play mode to exploration mode.
	 *
	 * The request is subject to any business rules of the game mode. If the switch is not allowed by current game
	 * rules, the game mode will not be changed.
	 *
	 * @see EPF2ModeOfPlay
	 */
	UFUNCTION(BlueprintCallable)
	virtual void StartExplorationMode() = 0;

	/**
	 * Requests a switch of the play mode to downtime mode.
	 *
	 * The request is subject to any business rules of the game mode. If the switch is not allowed by current game
	 * rules, the game mode will not be changed.
	 *
	 * @see EPF2ModeOfPlay
	 */
	UFUNCTION(BlueprintCallable)
	virtual void StartDowntimeMode() = 0;
};
