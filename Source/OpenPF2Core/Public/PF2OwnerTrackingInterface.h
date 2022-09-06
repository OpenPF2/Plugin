// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2OwnerTrackingInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2PartyInterface;
class IPF2PlayerControllerInterface;
class IPF2PlayerStateInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2OwnerTrackingInterface : public UPF2LogIdentifiableInterface
{
	GENERATED_BODY()
};

/**
 * An interface for components that track which player "owns" or controls an actor (usually, a character).
 */
class OPENPF2CORE_API IPF2OwnerTrackingInterface : public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets the party with which the containing actor is affiliated.
	 *
	 * @return
	 *   The party to which this character corresponds.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner Tracking")
	virtual TScriptInterface<IPF2PartyInterface> GetParty() const = 0;

	/**
	 * Sets the party with which the containing actor is affiliated.
	 *
	 * If a player owns the containing actor, the player must be affiliated with the same party as the new party.
	 *
	 * @param NewParty
	 *   The new party to which this character will belong.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner Tracking")
	virtual void SetParty(const TScriptInterface<IPF2PartyInterface> NewParty) = 0;

	/**
	 * Gets the state of the player who owns the containing actor.
	 *
	 * @return
	 *	The interface to the player state of the player who owns this actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner Tracking")
	virtual TScriptInterface<IPF2PlayerStateInterface> GetStateOfOwningPlayer() const = 0;

	/**
	 * Sets the player who own this actor, identified by the controller of the player.
	 *
	 * @param NewController
	 *	The player controller for player that now owns this actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner Tracking")
	virtual void SetOwningPlayerByController(const TScriptInterface<IPF2PlayerControllerInterface> NewController) = 0;

	/**
	 * Sets the player who owns this actor, identified by the state of the player
	 *
	 * @param NewPlayerState
	 *	The state for player that now owns this actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner Tracking")
    virtual void SetOwningPlayerByState(const TScriptInterface<IPF2PlayerStateInterface> NewPlayerState) = 0;

	/**
	 * Checks whether this actor is affiliated with the same party as another actor.
	 *
	 * @param OtherActor
	 *	The other actor against which this actor will be checked.
	 *
	 * @return
	 *	TRUE if this actor belongs to the same party as the other actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner Tracking")
	virtual bool IsSamePartyAsActor(AActor* OtherActor) const = 0;

	/**
	 * Checks whether this actor is affiliated with the same party as another player, identified by their controller.
	 *
	 * @return
	 *	TRUE if this actor belongs to the same party as the player the given controller controls.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner Tracking")
	virtual bool IsSamePartyAsPlayerWithController(
		const TScriptInterface<IPF2PlayerControllerInterface> OtherController
	) const = 0;
};
