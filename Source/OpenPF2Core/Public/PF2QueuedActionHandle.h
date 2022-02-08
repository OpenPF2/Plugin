// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Styling/SlateBrush.h>

#include "PF2QueuedActionInterface.h"
#include "PF2QueuedActionHandle.generated.h"

/**
 * A partially-opaque handle to a queued action on the server.
 *
 * Queued action handles support replication and expose information for display to players. A handle can also be used to
 * cancel a queued action, in case a player needs the option to cancel it.
 */
USTRUCT(BlueprintType)
struct FPF2QueuedActionHandle
{
	GENERATED_BODY()

	/**
	 * The unique identifier for this queued action on the server.
	 *
	 * Do not modify.
	 */
	UPROPERTY(BlueprintReadOnly)
	int32 HandleId;

	/**
	 * The name of the action.
	 *
	 * Do not modify.
	 */
	UPROPERTY(BlueprintReadOnly)
	FText ActionName;

	/**
	 * An icon representing the action.
	 *
	 * Do not modify.
	 */
	UPROPERTY(BlueprintReadOnly)
	FSlateBrush ActionIcon;

	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for FPF2QueuedActionHandle.
	 */
	explicit FPF2QueuedActionHandle() :
		HandleId(-1),
		ActionName(FText()),
		ActionIcon(FSlateBrush())
	{
	}

	/**
	 * Constructor for FPF2QueuedActionHandle that initializes a handle from ID and action reference.
	 *
	 * @param HandleId
	 *	The unique ID for the action, as assigned by the server.
	 * @param Action
	 *	The action for which a handle is being instantiated.
	 */
	explicit FPF2QueuedActionHandle(const int32 HandleId, const IPF2QueuedActionInterface* Action) :
		HandleId(HandleId),
		ActionName(Action->GetActionName()),
		ActionIcon(Action->GetActionIcon())
	{
	}

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets whether this handle is a valid reference to a queued action.
	 *
	 * Mode of Play Rule Sets (MoPRS) can return an invalid handle if they do not support action queueing.
	 *
	 * This is only a local check. The handle is still considered valid even after the queued action has been executed
	 * or canceled remotely, as checking the status of the handle would require an RPC connection to the server.
	 *
	 * @return
	 *	- true if this handle is a valid reference to a queued action on the server, even if the queued action has
	 *	  already been canceled or has been completed.
	 *	- false if this handle does not reference any queued actions on the server.
	 */
	bool FORCEINLINE IsValid() const
	{
		return (this->HandleId != -1);
	}
};
