// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>
#include <GameFramework/PlayerController.h>

#include "PF2GameStateInterface.h"
#include "GameModes/PF2ModeOfPlayType.h"

#include "PF2PlayerControllerInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2PlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Player Controllers.
 */
class OPENPF2CORE_API IPF2PlayerControllerInterface
{
	GENERATED_BODY()

public:
	/**
	 * Notifies this player controller that the mode of play has changed.
	 *
	 * (This should normally be invoked only by the game state).
	 *
	 * @see EPF2ModeOfPlay
	 *
	 * @param NewMode
	 *	The new mode of play.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual void HandleModeOfPlayChanged(EPF2ModeOfPlayType NewMode) = 0;

	/**
	 * Notifies this player controller that an action/ability for the character being controlled has been queued-up.
	 *
	 * This happens if the active Mode of Play Rule Set (MoPRS) is requiring characters to queue up execution of
	 * abilities until their turn to attack/act.
	 *
	 * (This should normally be invoked only by the MoPRS).
	 *
	 * @param Action
	 *	The ability that was queued.
	 */
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category="OpenPF2|Player Controllers")
	virtual void HandleActionQueued(const TScriptInterface<IPF2QueuedActionInterface>& Action) = 0;

	/**
	 * Notifies this player controller a previously queued action/ability has been removed from the queue.
	 *
	 * (This should normally be invoked only by the MoPRS).
	 *
	 * @param Action
	 *	The ability that has been removed.
	 */
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category="OpenPF2|Player Controllers")
	virtual void HandleActionDequeued(const TScriptInterface<IPF2QueuedActionInterface>& Action) = 0;

	/**
	 * Gets the character that this player controller is controlling.
	 *
	 * @return
	 *	Either the controller character (if this controller is controlling a PF2 character), or a null character
	 *	reference.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual TScriptInterface<IPF2CharacterInterface> GetControlledCharacter() = 0;

	/**
	 * Gets the player controller that is implementing this interface.
	 *
	 * @return
	 *	This player controller, as a player controller actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual APlayerController* ToPlayerController() = 0;
};
