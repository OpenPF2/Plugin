// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
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

#include "PF2GameStateInterface.generated.h"

/**
 * An enumeration of the different play modes in PF2.
 *
 * From the Pathfinder 2E Core Rulebook, page 493, "Running Modes of Play":
 * "Pathfinder sessions are divided into three different modes of play: encounters, exploration, and downtime. Each mode
 * represents different kinds of situations, with specific stakes and time scales, and characters can use different
 * sorts of actions and reactions in each."
 */
UENUM(BlueprintType)
enum class EPF2ModeOfPlay : uint8
{
	/**
	 * Encounter mode.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 468, "Encounter Mode":
	 * "When every individual action counts, you enter the encounter mode of play. In this mode, time is divided into
	 * rounds, each of which is 6 seconds of time in the game world. Every round, each participant takes a turn in an
	 * established order. During your turn, you can use actions, and depending on the details of the encounter, you
	 * might have the opportunity to use reactions and free actions on your own turn and on others’ turns."
	 */
	Encounter,

	/**
	 * Exploration mode.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 479, "Exploration Mode":
	 * "While encounters use rounds for combat, exploration is more free form. The GM determines the flow of time, as
	 * you could be traveling by horseback across craggy highlands, negotiating with merchants, or delving in a dungeon
	 * in search of danger and treasure. Exploration lacks the immediate danger of encounter mode, but it offers its own
	 * challenges."
	 */
	Exploration,

	/**
	 * Downtime mode.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 481, "Downtime Mode":
	 * "Downtime mode is played day-by-day rather than minute-by-minute or scene-by-scene. Usually this mode of play
	 * occurs when you are in the safety of a settlement, maybe recovering from your adventures or studying an artifact
	 * you found."
	 */
	Downtime,
};

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
	virtual EPF2ModeOfPlay GetModeOfPlay() = 0;

	/**
	 * Sets the current play mode for all characters in the loaded level.
	 *
	 * This should only get called by the game mode (on the server).
	 *
	 * @see EPF2ModeOfPlay
	 *
	 * @param NewMode
	 *	The new play mode.
	 */
	virtual void SwitchModeOfPlay(const EPF2ModeOfPlay NewMode) = 0;
};
