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

#include <CoreMinimal.h>
#include <GameplayModMagnitudeCalculation.h>

#include "GameplayAbilityUtils.h"
#include "RPGKeyAbilityCalculationBase.generated.h"

/**
 * Base class for MMCs that are based on a character's "Key Ability" (Class DC, Spell Attack Roll, Spell DC, etc.).
 */
UCLASS(Abstract)
class TEENWOLFRPG_API URPGKeyAbilityCalculationBase : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	/**
	 * Default constructor UE4 invokes for objects of this type.
	 *
	 * Sub-classes must implement their own version of this constructor that calls
	 * URPGKeyAbilityCalculationBase(FString) instead of calling this constructor overload.
	 */
	explicit URPGKeyAbilityCalculationBase();

	/**
	 * Constructor for URPGKeyAbilityCalculationBase.
	 *
	 * The skill proficiency calculation is initialized so that the specified attribute is factored-in to the
	 * proficiency bonus, and TEML tags on the character that have the specified prefix determine the magnitude of the
	 * boost.
	 *
	 * @param StatGameplayTagPrefix
	 *   The tag prefix to use for checking a character's training in the stat. For example, "ClassDc", "SpellAttack",
	 *   or "SpellDc".
	 * @param KeyAbilityGameplayTagPrefix
	 *   The tag prefix to use to determine the key ability for this stat.  For the Class DC, this is "KeyAbility". For
	 *   Spell Attack and Spell DC, this is "SpellcastingKeyAbility".
	 * @param BaseValue
	 *   The base value for this stat. For DC stats, this is usually "10". For other stats (e.g. Spell Attack Roll),
	 *   this is 0.
	 */
	explicit URPGKeyAbilityCalculationBase(const FString StatGameplayTagPrefix,
										   const FString KeyAbilityGameplayTagPrefix,
										   const float BaseValue = 0.0f);

	/**
	 * Calculates this stat based on the Key Attribute captured by the provided GE specification.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character attributes for which a
	 *   calculated stat is desired.
	 *
	 * @return
	 *   The calculated stat value.
	 */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	/**
	 * Calculates the character's TEML proficiency in this stat.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	float CalculateProficiencyBonus(const FGameplayEffectSpec& Spec) const;

	/**
	 * Calculates the Key Ability modifier for the character.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character attribute upon which a
	 *   Key Ability modifier is desired.
	 */
	float CalculateKeyAbilityModifier(const FGameplayEffectSpec& Spec) const;

	/**
	 * Determines which ability is the character's key modifier.
	 *
	 * @param SourceTags
	 *   The tags on the character. A tag in this list should indicate the character's Key Ability (e.g.
	 *   "KeyAbility.Strength").
	 *
	 * @return
	 *   Either a capture definition that has a valid source attribute that can be used to capture the Key Ability
	 *   modifier that corresponds to the character's Key Ability; or, a capture definition that has an invalid source
	 *   attribute, signifying that the character is missing a key attribute tag.
	 */
	FGameplayEffectAttributeCaptureDefinition DetermineKeyAbility(const FGameplayTagContainer* SourceTags) const;

protected:
	/**
	 * The tag prefix to use for checking a character's training in this stat.
	 */
	FString StatGameplayTagPrefix;

	/**
	 * The base value for this stat.
	 *
	 * For DC stats, this is usually "10". For other stats (e.g. Spell Attack Roll), this is 0.
	 */
	float BaseValue;

	/**
	 * Map from Key Ability tag names to capture definitions.
	 *
	 * Each key in the map is a gameplay tag, which corresponds to a key character ability; and the value is the
	 * definition for capturing the modifier of that ability.
	 */
	TMap<FString, FGameplayEffectAttributeCaptureDefinition> KeyAbilityCaptureDefinitions;

	/**
	 * The name of the gameplay tag that indicates the character's Key Ability.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 67:
	 * "This is the ability score that a member of your class cares about the most. Many of your most useful and
	 * powerful abilities are tied to this ability in some way.
	 *
	 * For instance, this is the ability score you’ll use to determine the Difficulty Class (DC) associated with your
	 * character’s class features and feats. This is called your class DC. If your character is a member of a
	 * spellcasting class, this Key Ability is used to calculate spell DCs and similar values.
	 *
	 * Most classes are associated with one Key Ability score, but some allow you to choose from two options. For
	 * instance, if you’re a fighter, you can choose either Strength or Dexterity as your Key Ability. A fighter who
	 * chooses Strength will excel in hand-to-hand combat, while those who choose Dexterity prefer ranged or finesse
	 * weapons."
	 */
	FString KeyAbilityGameplayTag;

	/**
	 * Adds a capture definition for the specified ability, keyed by the given Key Ability tag name.
	 *
	 * This is used to ensure we can retrieve the modifier for the specified ability later in the calculation phase.
	 *
	 * @param KeyAbilityTagName
	 *   The name of the gameplay tag that a character must have for the ability to be considered "key".
	 * @param Attribute
	 *   The definition of the attribute to capture.
	 */
	void DefineKeyAbilityCapture(const FString KeyAbilityTagName, const FGameplayAttribute Attribute)
	{
		const FGameplayEffectAttributeCaptureDefinition CaptureDefinition =
			GameplayAbilityUtils::BuildSourceCaptureFor(Attribute);

		this->KeyAbilityCaptureDefinitions.Add(
			KeyAbilityTagName,
			CaptureDefinition
		);

		this->RelevantAttributesToCapture.Add(CaptureDefinition);
	}
};
