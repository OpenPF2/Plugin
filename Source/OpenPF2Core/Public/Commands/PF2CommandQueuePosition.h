// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2CommandQueuePosition.generated.h"

/**
 * An enumeration of different preferences a command can have for where to place it in the command queue.
 *
 * This is merely a preference; a Mode of Play Rule Set (MoPRS) ultimately has the final say on whether to honor the
 * preference or disregard it.
 */
UENUM(BlueprintType)
enum class EPF2CommandQueuePosition : uint8
{
	/**
	 * Queue at the very beginning of the queue.
	 *
	 * If the queue is full, the queue may still choose to enqueue this command but then drop the last command from the
	 * queue.
	 */
	BeginningOfQueue,

	/**
	 * Queue immediately after the command that is first in the queue (if any).
	 *
	 * - If the queue is empty, this is identical to BeginningOfQueue.
	 * - If the queue is full, the queue may still choose to enqueue this command but then drop the last command from
	 *   the queue.
	 */
	NextAfterBeginningOfQueue,

	/**
	 * Queue at the very end of the queue (this is typically the most common).
	 *
	 * If the queue is full, the queue may refuse to queue this command.
	 */
	EndOfQueue
};
