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
	// =================================================================================================================
	// Protected Properties
	// =================================================================================================================
	/**
	 * The icon to represent this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Icon;

	/**
	 * The name of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(BlueprintReadWrite)
	FText Label;

	/**
	 * The description of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(BlueprintReadWrite)
	FText Description;

public:
	// =================================================================================================================
	// Public Methods - IPF2GameplayAbilityInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual UTexture2D* GetAbilityIcon() const override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetAbilityLabel() const override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetAbilityDescription() const override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;
};
