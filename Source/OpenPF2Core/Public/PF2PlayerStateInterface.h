// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include "PF2PlayerControllerInterface.h"

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2PlayerStateInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class APlayerState;
class IPF2CharacterInterface;
class IPF2PartyInterface;

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
	static const int32 PlayerIndexNone;

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
	virtual int32 GetPlayerIndex() const = 0;

	/**
	 * Sets the index of the player to which this player state corresponds.
	 *
	 * (This should be assigned only by the game mode.)
	 */
	virtual void SetPlayerIndex(int32 NewPlayerIndex) = 0;

	/**
	 * Gets the party of the player to which this player state corresponds.
	 *
	 * @return
	 *	Information about the party that the player who owns this player state belongs to.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual TScriptInterface<IPF2PartyInterface> GetParty() const = 0;

	/**
	 * Sets the party of the player to which this player state corresponds.
	 *
	 * @param NewParty
	 *	The new party that this player should belong to.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual void SetParty(const TScriptInterface<IPF2PartyInterface> NewParty) = 0;

	/**
	 * Gets the player controller that owns this player state.
	 *
	 * @return
	 *	The player controller that owns this player state.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual TScriptInterface<IPF2PlayerControllerInterface> GetPlayerController() const = 0;

	/**
	 * Determines whether the player owning this player state belongs to the same party as another player.
	 *
	 * The other player is identified by their player controller.
	 *
	 * @return
	 *	TRUE if both player controllers are for players in the same party; or FALSE if they are from different parties.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual bool IsSamePartyAsPlayerWithController(
		const TScriptInterface<IPF2PlayerControllerInterface>& OtherController
	) const = 0;

	/**
	 * Determines whether the player owning this player state belongs to the same party as another player.
	 *
	 * The other player is identified by their player state.
	 *
	 * @return
	 *	TRUE if both player states are for players in the same party; or FALSE if they are from different parties.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual bool IsSamePartyAsPlayerWithState(
		const TScriptInterface<IPF2PlayerStateInterface>& OtherPlayerState
	) const = 0;

	/**
	 * Gets the player state that is implementing this interface.
	 *
	 * @return
	 *	This player state, as a player state actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player State")
	virtual APlayerState* ToPlayerState() = 0;
};
