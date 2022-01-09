// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "Styling/SlateBrush.h"

#include "PF2QueuedActionInterface.generated.h"

UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UPF2QueuedActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for character actions that can be queued up to be executed later.
 *
 * The order in which actions are executed is usually based on the "initiative order" of each character and the order in
 * which the actions were queued.
 */
class OPENPF2CORE_API IPF2QueuedActionInterface
{
	GENERATED_BODY()

public:
	/**
	 * Gets the name to display for this action if the queue of actions are displayed to the player/user.
	 *
	 * @return
	 *	A textual description of this action.
	 */
	UFUNCTION(BlueprintCallable)
	virtual FText GetActionName() = 0;

	/**
	 * Gets the icon to display for this action if the queue of actions are displayed to the player/user.
	 *
	 * @return
	 *	A graphical representation of this action.
	 */
	UFUNCTION(BlueprintCallable)
	virtual FSlateBrush GetActionIcon() = 0;

	/**
	 * Performs this action.
	 *
	 * Once performed, the caller should remove this action from the queue of actions to perform; the queued action does
	 * not do so on its own.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void PerformAction() = 0;

	/**
	 * Notifies this action that it will not be performed and is instead being canceled.
	 *
	 * The action may have been canceled by a player, or as a consequence of a change in mode of play (e.g., leaving an
	 * encounter with some actions still queued).
	 *
	 * After the call, the caller should remove this action from the queue of actions to perform; the queued action does
	 * not do so on its own.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void CancelAction() = 0;
};
