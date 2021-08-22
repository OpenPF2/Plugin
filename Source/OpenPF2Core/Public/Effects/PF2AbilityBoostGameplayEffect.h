// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Abilities/PF2AttributeSet.h"
#include "PF2AbilityBoostGameplayEffect.generated.h"

/**
 * A custom GameplayEffect that boosts a specific character ability.
 *
 * Only sub-classes of this GE are eligible to invoke a UPF2AbilityBoostExecution execution.
 *
 * Since this GE manages its own Modifiers and Executions, we hide the GE settings from the Blueprint Details pane. This
 * ensures that a game designer does not provide settings that are lost or that conflict with what this custom GE
 * manages on its own.
 */
UCLASS(Abstract, HideCategories=(GameplayEffect))
class UPF2AbilityBoostGameplayEffect : public UGameplayEffect
{
public:
	GENERATED_BODY()

	/**
	 * Gets the character ability that this GE is targeting.
	 *
	 * @return
	 *   The target ability.
	 */
	EPF2AbilityType GetTargetAbility() const
	{
		return TargetAbility;
	}

	/**
	 * Gets the attribute for the character ability that this GE is targeting.
	 *
	 * @return
	 *   The attribute for the target ability.
	 */
	FGameplayAttribute GetTargetAbilityAttribute() const
	{
		return UPF2AttributeSet::GetByAbilityType(this->GetTargetAbility());
	}

	/**
	 * Gets the number of times that a boost should be applied.
	 *
	 * @return
	 *   How many boosts to apply to the character ability.
	 */
	int32 GetBoostCount() const
	{
		return BoostCount;
	}

	/**
	 * Callback invoked when the GE has been loaded but before it fires.
	 *
	 * We use this as an opportunity to initialize the lower-level GE properties of the object from the high-level
	 * properties provided by the game designer.
	 */
	virtual void PostLoad() override;

protected:
	/** The type of ability to boost. */
	UPROPERTY(EditDefaultsOnly, Category=BoostedAbility)
	EPF2AbilityType TargetAbility;

	/** The number of boosts to apply to the ability. */
	UPROPERTY(EditDefaultsOnly, Category=BoostedAbility, meta = (ClampMin = 1, ClampMax = 100))
	int32 BoostCount = 1;

	/**
	 * Populates the executions of the GE based on the target ability and boost count.
	 */
	void PopulateExecutions();
};
