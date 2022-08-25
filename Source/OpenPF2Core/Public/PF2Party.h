// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.
//
#pragma once

#include <GameFramework/PlayerController.h>
#include <UObject/Interface.h>

#include "PF2PlayerControllerInterface.h"
#include "PF2PlayerStateInterface.h"
#include "PF2Party.generated.h"

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2Party : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for groups or "parties" that one or more players and characters can belong to in OpenPF2.
 *
 * Each player of the game is affiliated with a single party. All of the characters that the player can control are
 * affiliated with the same party, but not all of the *characters* affiliated with a party are necessarily controllable
 * by all *players* in the same party. For example, in a multiplayer RPG, two players may be in the same party but only
 * have the ability to control their own characters within the party (e.g., a party of 4 in which each player can only
 * control 2 characters each).
 */
class OPENPF2CORE_API IPF2Party
{
	GENERATED_BODY()

public:
	/** Gets the index of this team. */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual uint8 GetPartyIndex() const = 0;

	/**
	 * Gets player controllers for all players belonging to this party.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual TArray<TScriptInterface<IPF2PlayerControllerInterface>> GetMemberControllers() const = 0;

	/**
	 * Gets player state for all players belonging to this party.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual TArray<TScriptInterface<IPF2PlayerStateInterface>> GetMemberStates() const = 0;

	/**
	 * Gets the characters belonging to this party.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual TArray<TScriptInterface<IPF2CharacterInterface>> GetMemberCharacters() const = 0;

	/**
	 * Adds the player having the specified player controller to this party.
	 *
	 * @param PlayerController
	 *	The controller for the player to add to the party.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual void AddPlayerToPartyByController(TScriptInterface<IPF2PlayerStateInterface> PlayerController) = 0;

	/**
	 * Adds the player having the specified player state to this party.
	 *
	 * @param PlayerState
	 *	The state for the player to add to the party.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual void AddPlayerToPartyByState(TScriptInterface<IPF2PlayerStateInterface> PlayerState) = 0;

	/**
	 * Removes the player having the specified player controller from this party.
	 *
	 * @param Controller
	 *	The controller for the player to remove from the party.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual void RemovePlayerFromPartyByController(TScriptInterface<IPF2PlayerStateInterface> Controller) = 0;

	/**
	 * Removes the player having the specified player state from this party.
	 *
	 * @param PlayerState
	 *	The state for the player to remove from the party.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Parties")
	virtual void RemovePlayerFromPartyByState(TScriptInterface<IPF2PlayerStateInterface> PlayerState) = 0;
};
