// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// This code is adapted from the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick Pruehs, provided under the MIT
// License. Copyright (c) 2017 Nick Pruehs.
//
#pragma once

#include <GameFramework/Controller.h>

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2OwnerInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2PlayerControllerInterface;
class IPF2PlayerStateInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2OwnerInterface : public UPF2LogIdentifiableInterface
{
	GENERATED_BODY()
};

/**
 * An interface for components that track which player "owns" or controls a character.
 */
class OPENPF2CORE_API IPF2OwnerInterface : public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets the index of the player that should initially own the actor.
	 *
	 * @return
	 *	The zero-based index in the server's list of players that corresponds to the player that owns this character.
	 *	Can be -1 for characters owned by the server or story.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner")
	virtual uint8 GetIndexOfInitialOwningPlayer() const = 0;

	/**
	 * Gets the state of the player who owns this actor.
	 *
	 * @return
	 *	The interface to the player state of the player who owns this actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner")
	virtual TScriptInterface<IPF2PlayerStateInterface> GetStateOfOwningPlayer() const = 0;

	/**
	 * Sets the player who own this actor by the controller of the player.
	 *
	 * @param Controller
	 *	The player controller for player that now owns this actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner")
	virtual void SetOwningPlayerByController(TScriptInterface<IPF2PlayerControllerInterface> Controller) = 0;

	/**
	 * Sets the player who owns this actor by the state of the player
	 *
	 * @param PlayerState
	 *	The state for player that now owns this actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner")
    virtual void SetOwningPlayerByState(TScriptInterface<IPF2PlayerStateInterface> PlayerState) = 0;

	/**
	 * Checks whether this actor belongs to the same party as the specified one.
	 *
	 * @param OtherActor
	 *	The other actor against which this actor will be checked.
	 *
	 * @return
	 *	TRUE if this actor belongs to the same party as the other actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner")
	virtual bool IsSamePartyAsActor(AActor* OtherActor) const = 0;

	/**
	 * Checks whether the player owning this actor belongs to the same party as the character with the given controller.
	 *
	 * @return
	 *	TRUE if this actor belongs to the same party as the player the given controller controls.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Owner")
	virtual bool IsSamePartyAsPlayerWithController(AController* OtherController) const = 0;
};
