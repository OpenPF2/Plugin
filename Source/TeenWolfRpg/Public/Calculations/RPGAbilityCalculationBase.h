// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.

#pragma once

#include <GameplayModMagnitudeCalculation.h>
#include <CoreMinimal.h>
#include "RPGAbilityCalculationBase.generated.h"

/**
 * Base class for MMCs that provide values based on captured character ability values.
 */
UCLASS(Abstract)
class TEENWOLFRPG_API URPGAbilityCalculationBase : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	/**
	 * Calculates an ability-based modifier value based on the attribute captured by the specified GE specification.
	 *
	 * Most sub-classes should not need to override this implementation. Instead, this implementation does most of the
	 * hard work of extracting the ability score value and then calling DoCalculation(FGameplayAttribute, float).
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the ability score for which a calculated
	 *   value is desired.
	 *
	 * @return
	 *   The calculated value.
	 */
	virtual float DoCalculation(const FGameplayEffectSpec& Spec) const;

	/**
	 * Calculates an ability-based modifier value based on the value and metadata of a captured attribute.
	 *
	 * All sub-classes must override this implementation.
	 *
	 * @param AbilityAttribute
	*   The type of ability score for which a calculated value is desired.
	 * @param AbilityScore
	 *   The current base value of the ability attribute.
	 *
	 * @return
	 *   The calculated value.
	 */
	virtual float DoCalculation(const FGameplayAttribute AbilityAttribute, const float AbilityScore) const
	PURE_VIRTUAL(URPGAbilityCalculationBase::DoCalculation, return 0;);
};
