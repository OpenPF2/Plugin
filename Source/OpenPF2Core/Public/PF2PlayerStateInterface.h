// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// This code is adapted from the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick Pruehs, provided under the MIT
// License. Copyright (c) 2017 Nick Pruehs.
//
#pragma once

#include "PF2PlayerControllerInterface.h"

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2PlayerStateInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class APlayerState;
class IPF2CharacterInterface;
class IPF2Party;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2PlayerStateInterface : public UPF2LogIdentifiableInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Player State instances.
 */
class OPENPF2CORE_API IPF2PlayerStateInterface : public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Constants
	// =================================================================================================================
	/**
	 * Special constant value that signifies that a character does not belong to any player.
	 */
	static const uint8 PlayerIndexNone;

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================

	/**
	 * Gets the index of the player to which this player state corresponds.
	 *
	 * @return
	 *	The zero-based index in the server's list of players that corresponds to this player state.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual uint8 GetPlayerIndex() const = 0;

	/**
	 * Gets the party this player belongs to.
	 *
	 * @return
	 *	Information about the party that this player belongs to.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual TScriptInterface<IPF2Party> GetParty() const = 0;

	/**
	 * Gets the player controller that owns this player state.
	 *
	 * @return
	 *	The player controller that owns this player state.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual TScriptInterface<IPF2PlayerControllerInterface> GetPlayerController() const = 0;

	/**
	 * Gets whether the player belongs to the same party as the player having the given player controller.
	 *
	 * @return
	 *	TRUE if both player controllers are for players in the same party; or FALSE if they are from different parties.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual bool IsSamePartyAsPlayerWithController(
		const TScriptInterface<IPF2PlayerControllerInterface>& OtherPlayerController
	) const = 0;

	/**
	 * Gets whether the player belongs to the same party as the player having the given player state.
	 *
	 * @return
	 *	TRUE if both player states are for players in the same party; or FALSE if they are from different parties.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual bool IsSamePartyAsPlayerWithState(
		const TScriptInterface<IPF2PlayerStateInterface>& OtherPlayerState
	) const = 0;

	/**
	 * Gets the character(s) that this player has the ability to control or possess.
	 *
	 * For a single-player game that supports parties or squads, this may include both the character that the player
	 * is actively controlling as well as any controllable character in this player's party or squad. Otherwise, this
	 * will return only a single character per controller.
	 *
	 * All the characters returned will each be in the same party as the player, but not all characters in the party are
	 * necessarily controllable by the current player (e.g., in a multiplayer RPG, two players may be in the same party
	 * but may be restricted from being able to control each other's characters).
	 *
	 * @return
	 *	All of the characters that this player controller can control.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual TArray<TScriptInterface<IPF2CharacterInterface>> GetControllableCharacters() const = 0;

	/**
	 * Gets the player state that is implementing this interface.
	 *
	 * @return
	 *	This player state, as a player state actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual APlayerState* ToPlayerState() = 0;

	/**
	 * Notifies this player state that the player who owns it is now a member of a different party.
	 *
	 * @param NewParty
	 *	The new party to which the player is affiliated.
	 */
	virtual void NotifyOnPartyChanged(TScriptInterface<IPF2Party> NewParty) = 0;

	/**
	 * Notifies this player state that it is now the owner of an actor or that it no longer owns an actor.
	 *
	 * @param Actor
	 *	The actor that changed owners.
	 * @param PreviousOwner
	 *	The player state corresponding to the player who was the previous owner of this actor. Can be null.
	 * @param NewOwner
	 *	The player state corresponding to the player who is now the owner of this actor. Can be null.
	 */
	virtual void NotifyOnActorOwnershipChanged(
		AActor*                                           Actor,
		const TScriptInterface<IPF2PlayerStateInterface>& PreviousOwner,
		const TScriptInterface<IPF2PlayerStateInterface>& NewOwner
	) = 0;
};
