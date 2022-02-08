// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Abilities/GameplayAbility.h>

#include "Abilities/PF2GameplayAbilityInterface.h"

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2GameplayAbilityBase.generated.h"

/**
 * Abstract base class for PF2-enabled gameplay abilities.
 *
 * GAs that extend from this base class automatically get ability queuing and de-queuing interactions for free.
 * If a GA supports waiting for initiative (i.e., action queueing while in an encounter), then this ability must be
 * instanced (instancing is required for ability tasks to work). It should additionally be configured as follows:
 * - If bShouldBlockWhenQueued is false, then the GA should be instanced per activation. Otherwise, the ability will
 *   still block.
 * - If bShouldBlockWhenQueued is true, then the GA can be instanced per actor or instanced per activation, since only
 *   one instance of it can be queued/active at a time per actor.
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class UPF2GameplayAbilityBase :
	public UGameplayAbility,
	public IPF2GameplayAbilityInterface,
	public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

protected:
	/**
	 * Controls whether blocking tags on this ability have any effect while it is queued, or whether it continues to
	 * block until it is finally de-queued and executed.
	 *
	 * The default is false, to allow a character to queue up multiple instances of this ability without limitation. If
	 * this is changed to true, the character will have to wait for a queued instance to be activated before queuing
	 * another instance.
	 *
	 * This only affects GAs that have blocking tags.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Encounter Queuing Behaviors")
	bool bShouldBlockWhenQueued;

	/**
	 * Controls whether this type of ability enforces cost checks while any instance of it has been queued.
	 *
	 * The default is false, to allow a character to queue up multiple instances of this ability even when they cannot
	 * afford those queued-up instances at the present moment (the cost will have to be satisfied at the time that the
	 * task is being dequeued, or it will not fire). If this is changed to true, and the character does not currently
	 * have enough to afford the cost of this ability, the character will not be able to queue up the ability until they
	 * can satisfy the cost.
	 *
	 * This only affects GAs that have a cost Gameplay Effect.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Encounter Queuing Behaviors")
	bool bShouldEnforceCostWhenQueued;

	/**
	 * Indicates whether this ability is currently checking costs before activation.
	 */
	UPROPERTY(BlueprintReadOnly, Category="OpenPF2|Gameplay Abilities")
	bool bEnforcingCosts;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Constructor for UPF2GameplayAbilityBase.
	 */
	explicit UPF2GameplayAbilityBase() :
		bShouldBlockWhenQueued(false),
		bShouldEnforceCostWhenQueued(false)
	{
	}

	// =================================================================================================================
	// Public Methods - UGameplayAbility Overrides
	// =================================================================================================================
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle,
	                       const FGameplayAbilityActorInfo* ActorInfo,
	                       FGameplayTagContainer*           OptionalRelevantTags) const override;

	// =================================================================================================================
	// Public Methods - IPF2GameplayAbilityInterface Overrides
	// =================================================================================================================
	virtual void OnQueued() override;
	virtual void OnDequeued() override;
	virtual void ForceSuspendBlocking() override;
	virtual void ForceResumeBlocking() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;
};
