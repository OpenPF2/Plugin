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
#include "RPGClassDifficultyClassModifierCalculation.generated.h"

/**
 * MMC that calculates the modifier for the "Class DC".
 *
 * From the Pathfinder 2E Core Rulebook, page 29:
 * "A class DC sets the difficulty for certain abilities granted by your character’s class. This DC equals 10 plus their
 * proficiency bonus for their class DC (+3 for most 1st-level characters) plus the modifier for the class’s key ability
 * score."
 */
UCLASS()
class TEENWOLFRPG_API URPGClassDifficultyClassModifierCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	/**
	 * Constructor for URPGClassDifficultyClassModifierCalculation.
	 */
	explicit URPGClassDifficultyClassModifierCalculation();

	/**
	 * Calculates the class difficulty class modifier based on the attributes captured by the provided GE specification.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character attributes for which a
	 *   calculated DC modifier is desired.
	 *
	 * @return
	 *   The calculated DC modifier.
	 */
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	/**
	 * Calculates the character's TEML proficiency in their class DC.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	static float CalculateProficiencyBonus(const FGameplayEffectSpec& Spec);

	/**
	 * Calculates the key ability modifier for the character.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character attribute upon which a
	 *   key ability modifier is desired.
	 */
	float CalculateKeyAbilityModifier(const FGameplayEffectSpec& Spec) const;

	/**
	 * Determines which ability is the character's key modifier.
	 *
	 * @param SourceTags
	 *   The tags on the character. A tag in this list should indicate the character's key ability (e.g.
	 *   "KeyAbility.Strength").
	 *
	 * @return
	 *   Either a capture definition that has a valid source attribute that can be used to capture the key ability
	 *   modifier that corresponds to the character's key ability; or, a capture definition that has an invalid source
	 *   attribute, signifying that the character is missing a key attribute tag.
	 */
	FGameplayEffectAttributeCaptureDefinition DetermineKeyAbility(const FGameplayTagContainer* SourceTags) const;

protected:
	/**
	 * Map from key ability tag names to capture definitions.
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
	 * spellcasting class, this key ability is used to calculate spell DCs and similar values.
	 *
	 * Most classes are associated with one key ability score, but some allow you to choose from two options. For
	 * instance, if you’re a fighter, you can choose either Strength or Dexterity as your key ability. A fighter who
	 * chooses Strength will excel in hand-to-hand combat, while those who choose Dexterity prefer ranged or finesse
	 * weapons.
	 */
	FString KeyAbilityGameplayTag;

	/**
	 * Adds a capture definition for the specified ability, keyed by the given key ability tag name.
	 *
	 * This is used to ensure we can retrieve the modifier for the specified ability later in the calculation phase.
	 *
	 * @param KeyAbilityTagName
	 *   The name of the gameplay tag that a character must have for the ability to be considered "key".
	 * @param Attribute
	 *   The definition of the attribute to capture.
	 */
	FORCEINLINE void DefineKeyAbilityCapture(const FString KeyAbilityTagName, const FGameplayAttribute Attribute)
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
