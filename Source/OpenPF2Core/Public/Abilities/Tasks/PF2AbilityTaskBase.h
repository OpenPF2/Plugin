// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Abilities/Tasks/AbilityTask.h>

#include "PF2AbilityTaskBase.generated.h"

/**
 * Common base class for PF2 Ability Tasks.
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2AbilityTaskBase : public UAbilityTask
{
	GENERATED_BODY()

protected:
	/**
	 * Gets whether this ability task has a valid ability.
	 *
	 * @return
	 *	true if the ability in this task is properly set; or false if it is null.
	 */
	FORCEINLINE bool HasAbility() const
	{
		return this->Ability != nullptr;
	}

	/**
	 * Gets whether this ability task has a valid Ability System Component.
	 *
	 * @return
	 *	true if the ASC in this task is properly set; or false if it is null.
	 */
	FORCEINLINE bool HasAsc() const
	{
		return this->AbilitySystemComponent != nullptr;
	}
};
