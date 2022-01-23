// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/ObjectMacros.h>

/**
 * An enumeration of the different outcomes from attempting to activate a queued character ability.
 */
UENUM(BlueprintType)
enum class EPF2AbilityActivationResult : uint8
{
	/**
	 * No result yet.
	 */
	None,

	/**
	 * The ability was successfully executed/performed.
	 *
	 * The ability should be de-queued.
	 */
	Activated,

	/**
	 * The ability was not performed because another ability is running or the cost could not be satisfied.
	 *
	 * The ability should be re-queued, if possible.
	 */
	Blocked,

	/**
	 * The ability was not performed because it was canceled externally.
	 */
	Cancelled,
};
