// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2GameModeInterface.h"
#include "PF2ModeOfPlayRuleSetInterface.h"
#include "PF2PlayerControllerInterface.h"

#include "GameModes/PF2ModeOfPlayType.h"

#include "PF2ModeOfPlayRuleSetBase.generated.h"

/**
 * Default base class for OpenPF2 Mode of Play Rule Sets (MoPRS).
 *
 * @see IPF2GameModeInterface
 */
UCLASS(Abstract, Blueprintable)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2ModeOfPlayRuleSetBase : public AActor, public IPF2ModeOfPlayRuleSetInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - IPF2ModeOfPlayRuleSetInterface Implementation
	// =================================================================================================================
	virtual void OnModeOfPlayStart(const EPF2ModeOfPlayType ModeOfPlay) override;

	virtual void OnPlayableCharacterStarting(const TScriptInterface<IPF2CharacterInterface>& Character) override;

	virtual void OnCharacterAddedToEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) override;

	virtual void OnCharacterRemovedFromEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) override;

	virtual void OnModeOfPlayEnd(const EPF2ModeOfPlayType ModeOfPlay) override;

	virtual EPF2CommandExecuteOrQueueResult AttemptToExecuteOrQueueCommand_Implementation(
		const TScriptInterface<IPF2CharacterCommandInterface>& Command) override;

	virtual void AttemptToCancelCommand_Implementation(
		const TScriptInterface<IPF2CharacterCommandInterface>& Command) override;

protected:
	// =================================================================================================================
	// Blueprint Implementable Events
	// =================================================================================================================
	/**
	 * Callback to notify this rule set that the mode of play that invoked it is now active.
	 *
	 * The rule set should use this as an opportunity to initialize its state (e.g., roll initiative, assemble a list of
	 * enemies, etc.).
	 *
	 * @param ModeOfPlay
	 *	The mode of play that is just starting.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Mode of Play Rule Sets",
		meta=(DisplayName="On Mode of Play Start")
	)
	void BP_OnModeOfPlayStart(EPF2ModeOfPlayType ModeOfPlay);

	/**
	 * Callback to notify this rule set that a playable character has just joined the game.
	 *
	 * This only fires if a player joins the game while this rule set is already active. The rule set should use this as
	 * an opportunity to update character-tracking logic (e.g., add the player to an existing, on-going encounter,
	 * etc.).
	 *
	 * @param Character
	 *	The character of the player who just connected.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Mode of Play Rule Sets",
		meta=(DisplayName="On Playable Character Starting")
	)
	void BP_OnPlayableCharacterStarting(const TScriptInterface<IPF2CharacterInterface>& Character);

	/**
	 * Callback to notify this rule set that a character should be added to the current encounter.
	 *
	 * The rule set can choose to ignore this event if it's not applicable (e.g., this rule set is not for an
	 * encounter). This callback should also be ignored if the given character is already part of the encounter.
	 *
	 * @param Character
	 *	The character being added to the encounter.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Mode of Play Rule Sets",
		meta=(DisplayName="On Character Added to Encounter")
	)
	void BP_OnCharacterAddedToEncounter(const TScriptInterface<IPF2CharacterInterface>& Character);

	/**
	 * Callback to notify this rule set that a character should be removed from the current encounter.
	 *
	 * The rule set can choose to ignore this event if it's not applicable (e.g., this rule set is not for an
	 * encounter). This callback should also be ignored if the given character is not part of the encounter.
	 *
	 * @param Character
	 *	The character being removed from the encounter.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Mode of Play Rule Sets",
		meta=(DisplayName="On Character Removed from Encounter")
	)
	void BP_OnCharacterRemovedFromEncounter(const TScriptInterface<IPF2CharacterInterface>& Character);

	/**
	 * Callback to notify this rule set to wrap-up prior to a change in mode of play.
	 *
	 * The rule set should use this as an opportunity to apply any long-lasting effects of the mode (e.g., calculate
	 * experience and hero points, end encounter-only gameplay effects or abilities, etc.).
	 *
	 * @param ModeOfPlay
	 *	The mode of play that is ending.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Mode of Play Rule Sets",
		meta=(DisplayName="On Mode of Play End")
	)
	void BP_OnModeOfPlayEnd(EPF2ModeOfPlayType ModeOfPlay);

	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets the game mode.
	 *
	 * @return
	 *	OpenPF2-specific game mode.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets")
	TScriptInterface<IPF2GameModeInterface> GetGameMode() const;

	/**
	 * Gets controllers for all the characters in the world.
	 *
	 * @return
	 *	OpenPF2-specific controllers for all players in the world.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets")
	TArray<TScriptInterface<IPF2PlayerControllerInterface>> GetPlayerControllers() const;

	/**
	 * Gets all of the player-controlled OpenPF2 characters in the world.
	 *
	 * @return
	 *	OpenPF2-specific controllers for all players in the world.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets")
	TArray<TScriptInterface<IPF2CharacterInterface>> GetPlayerControlledCharacters() const;

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
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets")
	void AddCharacterToEncounter(const TScriptInterface<IPF2CharacterInterface> Character);

	/**
	 * Adds all characters controlled by players to the current encounter, if an encounter is active.
	 *
	 * This call will have no effect under the following circumstances:
	 *	- If there is no active encounter according to game mode rules or the current Mode of Play Rule Set (MoPRS).
	 *	- If there is an active encounter and all player-controlled characters are already part of the encounter.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets")
	void AddAllPlayerControlledCharactersToEncounter();

	/**
	 * Removes a character from the current encounter, if an encounter is active.
	 *
	 * This call will have no effect under the following circumstances:
	 *	- If there is no active encounter according to game mode rules or the current Mode of Play Rule Set (MoPRS).
	 *	- If there is an active encounter and no characters are part of the encounter.
	 *
	 * @param Character
	 *	The character being removed from the encounter.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets")
	void RemoveCharacterFromEncounter(const TScriptInterface<IPF2CharacterInterface> Character);
};
