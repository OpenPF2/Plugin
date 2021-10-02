// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>
#include <GameplayModMagnitudeCalculation.h>

#include "Calculations/PF2TemlCalculationBase.h"
#include "PF2SimpleTemlModifierCalculationBase.generated.h"

/**
 * Base class for MMCs that calculate the proficiency modifier for a character attribute. This base class is only used
 * for calculations that are "simple"; that is to say, this base class is only used to calculate proficiencies that are
 * a function of the value of a character's ability score modifier (Strength, Dexterity, Intelligence, etc.) and a TEML
 * proficiency (e.g. skills, saving throws, and perception).
 *
 * More advanced calculations (Armor Class, Class DC, Spell Attack Roll, and Spell DC) derive from
 * UPF2TemlCalculationBase directly, instead of deriving from this base class, as they have more complex business logic.
 */
UCLASS(Abstract)
class OPENPF2CORE_API UPF2SimpleTemlModifierCalculationBase : public UPF2TemlCalculationBase
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	/**
	 * Default constructor UE4 invokes for objects of this type.
	 *
	 * Sub-classes must implement their own version of this constructor that calls
	 * UPF2SimpleTemlModifierCalculationBase(FGameplayAttribute, FString) instead of calling this constructor overload.
	 */
	explicit UPF2SimpleTemlModifierCalculationBase() : UPF2TemlCalculationBase()
	{
	};

	/**
	 * Constructor for UPF2SimpleTemlModifierCalculationBase.
	 *
	 * The skill proficiency calculation is initialized so that the specified attribute is factored-in to the
	 * proficiency bonus, and TEML tags on the character that have the specified prefix determine the magnitude of the
	 * boost.
	 *
	 * @param SkillAbilityAttribute
	 *	The RPG attribute for the character ability that contributes to proficiency in the skill. For example,
	 *	"UPF2AttributeSet::GetAbDexterityModifierAttribute()" for Acrobatics,
	 *	"UPF2AttributeSet::GetAbIntelligenceModifierAttribute()" for Arcana, etc.)
	 * @param SkillGameplayTagPrefix
	 *	The tag prefix to use for checking a character's training in the skill. For example, "Skill.Acrobatics" or
	 *	"Skill.Arcana".
	 */
	explicit UPF2SimpleTemlModifierCalculationBase(const FGameplayAttribute SkillAbilityAttribute,
	                                               const FString            SkillGameplayTagPrefix);

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Calculates a skill proficiency based on the attributes captured by the provided GE specification.
	 *
	 * Most sub-classes should not need to override this implementation. Instead, this implementation depends on other
	 * methods to provide the source skill and skill tags.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character attributes for which a
	 *	calculated skill proficiency is desired.
	 *
	 * @return
	 *	The calculated skill proficiency.
	 */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * Capture definition for the RPG character attribute that contributes to proficiency in the skill.
	 */
	FGameplayEffectAttributeCaptureDefinition SkillAbilityCaptureDefinition;

	/**
	 * The tag prefix to use for checking a character's training in the skill.
	 */
	FString SkillGameplayTagPrefix;
};
