// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>
#include <GameplayModMagnitudeCalculation.h>

#include "Calculations/RPGTemlCalculationBase.h"
#include "RPGModifierCalculationBase.generated.h"

/**
 * Base class for MMCs that calculate the proficiency a character has in a particular skill.
 */
UCLASS(Abstract)
class TEENWOLFRPG_API URPGModifierCalculationBase : public URPGTemlCalculationBase
{
	GENERATED_BODY()

public:
	/**
	 * Default constructor UE4 invokes for objects of this type.
	 *
	 * Sub-classes must implement their own version of this constructor that calls
	 * URPGModifierCalculationBase(FGameplayAttribute, FString) instead of calling this
	 * constructor overload.
	 */
	explicit URPGModifierCalculationBase() : URPGTemlCalculationBase()
	{
	};

	/**
	 * Constructor for URPGModifierCalculationBase.
	 *
	 * The skill proficiency calculation is initialized so that the specified attribute is factored-in to the
	 * proficiency bonus, and TEML tags on the character that have the specified prefix determine the magnitude of the
	 * boost.
	 *
	 * @param SkillAbilityAttribute
	 *   The RPG attribute for the character ability that contributes to proficiency in the skill. For example,
	 *   "URPGAttributeSet::GetAbDexterityModifierAttribute()" for Acrobatics,
	 *   "URPGAttributeSet::GetAbIntelligenceModifierAttribute()" for Arcana, etc.)
	 * @param SkillGameplayTagPrefix
	 *   The tag prefix to use for checking a character's training in the skill. For example, "Skill.Acrobatics" or
	 *   "Skill.Arcana".
	 */
	explicit URPGModifierCalculationBase(const FGameplayAttribute SkillAbilityAttribute,
										 const FString SkillGameplayTagPrefix);

	/**
	 * Calculates a skill proficiency based on the attributes captured by the provided GE specification.
	 *
	 * Most sub-classes should not need to override this implementation. Instead, this implementation depends on other
	 * methods to provide the source skill and skill tags.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character attributes for which a
	 *   calculated skill proficiency is desired.
	 *
	 * @return
	 *   The calculated skill proficiency.
	 */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	/**
	 * Capture definition for the RPG character attribute that contributes to proficiency in the skill.
	 */
	FGameplayEffectAttributeCaptureDefinition SkillAbilityCaptureDefinition;

	/**
	 * The tag prefix to use for checking a character's training in the skill.
	 */
	FString SkillGameplayTagPrefix;
};
