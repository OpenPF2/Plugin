// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "PF2GameplayAbilityInterface.generated.h"

UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UPF2GameplayAbilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Gameplay Abilities.
 */
class OPENPF2CORE_API IPF2GameplayAbilityInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Notifies this GA that it has been queued.
	 *
	 * Depending upon the GA configuration, after this call, the ability may allow other abilities of the same type or
	 * with the same blocking tags to still be activated. For example, the ability may allow a playable character to
	 * queue up the same action multiple times before and during their initiative turn, since each invocation of the
	 * ability will not happen concurrently.
	 *
	 * The ability may even be configured allow itself to be activated even if its cost check is not satisfied as long
	 * as the character cannot execute the ability immediately. This allows the player to queue up or execute this
	 * ability even if they don't satisfy the cost (e.g., not enough action points) right this moment. The cost is still
	 * taken into consideration at the time that the ability is de-queued and executed, so this only affects how costs
	 * work at the time they are being activated for queueing.
	 *
	 * This automatically gets called by Gameplay Ability Tasks like WaitForInitiativeTurn when an ability has been
	 * queued/suspended.
	 */
	virtual void OnQueued() = 0;

	/**
	 * Notifies this GA that it has been de-queued and is about to be executed.
	 *
	 * Depending upon the GA configuration, before this call, the ability may have allowed other abilities of the same
	 * type or with the same blocking tags to still be activated while it was queued. For example, the ability might
	 * have allowed a playable character to queue up the same action multiple times before and during their initiative
	 * turn, since each invocation of the ability will not happen concurrently. This call toggles that off.
	 *
	 * The ability may even have been configured to allow itself to be activated even if its cost check was not
	 * satisfied as long as the character could not execute the ability immediately. After this call, that is toggled
	 * off to prevent the player from queuing up or activating this ability if they don't satisfy the cost (e.g., if
	 * they are out of action points).
	 *
	 * This automatically gets called by Gameplay Ability Tasks like WaitForInitiativeTurn when an ability has been
	 * de-queued/resumed.
	 */
	virtual void OnDequeued() = 0;

	/**
	 * Forces this ability to not enforce blocking tags on this ability.
	 */
	virtual void ForceSuspendBlocking() = 0;

	/**
	 * Resumes enforcement of blocking tags on this ability.
	 */
	virtual void ForceResumeBlocking() = 0;
};
