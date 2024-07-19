// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#pragma once

#include <GameplayModMagnitudeCalculation.h>

#include "PF2KeyAbilityTemlCalculationBase.generated.h"

/**
 * Base class for MMCs that are based on the key ability of the character (Class DC, Spell Attack Roll, Spell DC, etc.).
 */
UCLASS(Abstract)
class OPENPF2GAMEFRAMEWORK_API UPF2KeyAbilityTemlCalculationBase : public UGameplayModMagnitudeCalculation
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
	 * UPF2KeyAbilityTemlCalculationBase(FString) instead of calling this constructor overload.
	 */
	explicit UPF2KeyAbilityTemlCalculationBase();

	/**
	 * Constructor for UPF2KeyAbilityTemlCalculationBase.
	 *
	 * The skill proficiency calculation is initialized so that the specified attribute is factored-in to the
	 * proficiency bonus, and TEML tags on the character that have the specified prefix determine the magnitude of the
	 * boost.
	 *
	 * @param StatPrefixTag
	 *	The tag prefix to use for checking a character's training in the stat. For example, "PF2.Proficiency.ClassDc",
	 *	"PF2.Proficiency.SpellAttack", or "PF2.Proficiency.SpellDc".
	 * @param KeyAbilityPrefixTag
	 *	The tag prefix to use to determine the key ability for this stat.  For the Class DC, this is "PF2.KeyAbility".
	 *	For Spell Attack and Spell DC, this is "PF2.SpellcastingAbility".
	 * @param BaseValue
	 *	The base value for this stat. For DC stats, this is usually "10". For other stats (e.g. Spell Attack Roll),
	 *	this is 0.
	 */
	explicit UPF2KeyAbilityTemlCalculationBase(
		const FGameplayTag& StatPrefixTag,
		const FGameplayTag& KeyAbilityPrefixTag,
		const float         BaseValue = 0.0f);

	// =================================================================================================================
	// Public Methods - UGameplayModMagnitudeCalculation Implementation
	// =================================================================================================================
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The tag prefix to use for checking a character's training in this stat.
	 */
	FGameplayTag StatPrefixTag;

	/**
	 * The base value for this stat.
	 *
	 * For DC stats, this is usually "10". For other stats (e.g. Spell Attack Roll), this is 0.
	 */
	float BaseValue;

	/**
	 * Map from Key Ability tag names to capture definitions.
	 *
	 * Each key in the map is a gameplay tag that corresponds to a key character ability, while the value is the
	 * definition for capturing the modifier of that ability.
	 */
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> KeyAbilityCaptureDefinitions;

	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Adds a capture definition for the specified ability, keyed by the given Key Ability tag name.
	 *
	 * This is used to ensure we can retrieve the modifier for the specified ability later in the calculation phase.
	 *
	 * @param KeyAbilityTag
	 *	The gameplay tag that a character must have for the ability to be considered "key". For example,
	 *	"PF2.KeyAbility.Strength" or "PF2.SpellcastingAbility.Intelligence".
	 * @param Attribute
	 *	The definition of the attribute to capture.
	 */
	void DefineKeyAbilityCapture(const FGameplayTag& KeyAbilityTag, const FGameplayAttribute& Attribute);

	/**
	 * Calculates the Key Ability modifier for the character.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character attribute upon which a
	 *	Key Ability modifier is desired.
	 *
	 * @return
	 *	The modifier calculated for this ability, based on the modifier the character has in the key ability.
	 */
	float CalculateKeyAbilityModifier(const FGameplayEffectSpec& Spec) const;

	/**
	 * Determines which ability is the character's key modifier.
	 *
	 * @param SourceTags
	 *	The tags on the character. A tag in this list should indicate the character's Key Ability (e.g.
	 *	"PF2.KeyAbility.Strength").
	 *
	 * @return
	 *	Either a capture definition that has a valid source attribute that can be used to capture the Key Ability
	 *	modifier that corresponds to the character's Key Ability; or, a capture definition that has an invalid source
	 *	attribute, signifying that the character is missing a key attribute tag.
	 */
	FGameplayEffectAttributeCaptureDefinition DetermineKeyAbility(const FGameplayTagContainer* SourceTags) const;
};
