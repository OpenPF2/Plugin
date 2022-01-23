// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/ObjectMacros.h>

/**
 * An enumeration of the different outcomes from attempting to queue an action/ability for a character.
 */
UENUM(BlueprintType)
enum class EPF2ActionQueueResult : uint8
{
	/**
	 * No result yet.
	 */
	None,

	/**
	 * The ability did not need to be queued and was executed immediately.
	 */
	ExecutedImmediately,

	/**
	 * The ability was successfully queued.
	 */
	Queued,

	/**
	 * The ability was neither queued nor executed and should be canceled and ended.
	 */
	Refused,
};
