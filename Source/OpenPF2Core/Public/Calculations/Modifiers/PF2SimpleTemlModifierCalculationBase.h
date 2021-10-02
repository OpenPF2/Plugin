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
	 * The proficiency calculation is initialized so that the specified attribute is factored-in to the proficiency
	 * bonus, and TEML tags on the character that have the specified prefix determine the magnitude of the boost.
	 *
	 * @param BaseAttribute
	 *	The RPG attribute for the character ability that contributes to proficiency in the attribute. This is typically
	 *	one of the character's ability modifier. For example, "UPF2AttributeSet::GetAbDexterityModifierAttribute()" for
	 *	Acrobatics, "UPF2AttributeSet::GetAbIntelligenceModifierAttribute()" for Arcana, etc.)
	 * @param ProficiencyTagPrefix
	 *	The tag prefix to use for determining the character's training in the attribute. For example, "Skill.Acrobatics"
	 *	or "SavingThrow.Fortitude".
	 */
	explicit UPF2SimpleTemlModifierCalculationBase(const FGameplayAttribute BaseAttribute,
	                                               const FString            ProficiencyTagPrefix);

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Calculates attribute proficiency based on the attributes captured by the provided GE specification.
	 *
	 * Most sub-classes should not need to override this implementation. Instead, this implementation depends on other
	 * methods to provide the base attribute and proficiency tag.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character attributes for which a
	 *	calculated attribute proficiency is desired.
	 *
	 * @return
	 *	The calculated attribute proficiency.
	 */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * Capture definition for the RPG character attribute that contributes to proficiency in the attribute.
	 */
	FGameplayEffectAttributeCaptureDefinition BaseAbilityCaptureDefinition;

	/**
	 * The tag prefix to use for checking a character's training in the attribute.
	 */
	FString ProficiencyTagPrefix;
};
