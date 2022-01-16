// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
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
	explicit FPF2QueuedActionHandle(const int32 HandleId, IPF2QueuedActionInterface* Action) :
		HandleId(HandleId),
		ActionName(Action->GetActionName()),
		ActionIcon(Action->GetActionIcon())
	{
	}
};
