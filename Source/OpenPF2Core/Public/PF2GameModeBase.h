// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/GameModeBase.h>

#include "PF2GameModeInterface.h"
#include "PF2GameStateInterface.h"

#include "PF2GameModeBase.generated.h"

/**
 * Default base class for PF2 Game Modes.
 *
 * @see IPF2GameModeInterface
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2GameModeBase : public AGameModeBase, public IPF2GameModeInterface
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Methods - IPF2GameModeInterface Implementation
	// =================================================================================================================
	virtual void StartEncounterMode() override;
	virtual void StartExplorationMode() override;
	virtual void StartDowntimeMode() override;

	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Sets the current play mode for all characters in the loaded level.
	 *
	 * The play mode is updated and replicated out through the game state.
	 *
	 * @see EPF2ModeOfPlay
	 *
	 * @param NewMode
	 *	The new play mode.
	 */
	void SwitchModeOfPlay(const EPF2ModeOfPlay NewMode) const;
};
