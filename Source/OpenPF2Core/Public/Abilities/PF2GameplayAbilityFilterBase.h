// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2GameplayAbilityBase.h"

#include "PF2GameplayAbilityFilterBase.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2AbilitySystemInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Abstract base class for gameplay abilities that filter the activation of other, input-bound abilities.
 *
 * GAs that extend from this base class must implement the "FilterAbilityActivation" blueprint event. They should NOT
 * override the ActivateAbility or ActivateAbilityFromEvent events.
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2GameplayAbilityFilterBase :
	public UGameplayAbility,
	public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle     Handle,
	                             const FGameplayAbilityActorInfo*     ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData*            TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent)
	void FilterAbilityActivation(
		const FName                                         InputName,
		const FGameplayAbilitySpecHandle                    ActivatedAbilityHandle,
		const FGameplayAbilitySpecHandle                    FilterHandle,
		const FGameplayEventData                            FilterTriggerEventData,
		const TScriptInterface<IPF2AbilitySystemInterface>& AbilitySystemInterface
	);

	/**
	 * Proceed with an attempt to activate the original ability that this ability was filtering.
	 *
	 * Command input bindings components support the definition of multiple filters in a filter pipeline, so additional
	 * filters may be activated before the final ability that was bound to input ends up being invoked.
	 */
	UFUNCTION(BlueprintCallable)
	void ProceedWithOriginalActivation(const FGameplayAbilitySpecHandle ActivatedAbilityHandle) const;

	UFUNCTION(BlueprintCallable)
	TScriptInterface<IPF2AbilitySystemInterface> GetAbilitySystemInterface() const;
};
