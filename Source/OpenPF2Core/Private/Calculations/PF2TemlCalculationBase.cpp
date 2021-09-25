// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "Calculations/PF2TemlCalculationBase.h"

#include "GameplayAbilityUtils.h"
#include "Abilities/PF2AttributeSet.h"

float UPF2TemlCalculationBase::CalculateProficiencyBonus(const FGameplayTag TagPrefix, const FGameplayEffectSpec& Spec)
{
	return CalculateProficiencyBonus(TagPrefix.GetTagName(), Spec);
}

float UPF2TemlCalculationBase::CalculateProficiencyBonus(const FName TagPrefix, const FGameplayEffectSpec& Spec)
{
	return CalculateProficiencyBonus(TagPrefix.GetPlainNameString(), Spec);
}

float UPF2TemlCalculationBase::CalculateProficiencyBonus(const FString TagPrefix, const FGameplayEffectSpec& Spec)
{
	float                        ProficiencyBonus = 0.0f;
	const FGameplayTagContainer* SourceTags       = Spec.CapturedSourceTags.GetAggregatedTags();

	// Bypass additional checks if the character has no proficiency with this skill, to avoid checking every TEML
	// option.
	if (GameplayAbilityUtils::HasTag(SourceTags, TagPrefix))
	{
		const float CharacterLevel = Spec.GetLevel();

		// "When attempting a check that involves something you have some training in, you will also add your
		// proficiency bonus. This bonus depends on your proficiency rank: untrained, trained, expert, master, or
		// legendary. If you’re untrained, your bonus is +0—you must rely on raw talent and any bonuses from the
		// situation. Otherwise, the bonus equals your character’s level plus a certain amount depending on your rank.
		// If your proficiency rank is trained, this bonus is equal to your level + 2, and higher proficiency ranks
		// further increase the amount you add to your level."
		//
		// Source: Pathfinder 2E Core Rulebook, page 444, "Step 1: Roll D20 and Identify The Modifiers, Bonuses, and
		// Penalties That Apply".
		if (GameplayAbilityUtils::HasTag(SourceTags, TagPrefix + ".Legendary"))
		{
			// Legendary -> Your level + 8
			ProficiencyBonus = CharacterLevel + 8;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, TagPrefix + ".Master"))
		{
			// Master -> Your level + 6
			ProficiencyBonus = CharacterLevel + 6;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, TagPrefix + ".Expert"))
		{
			// Expert -> Your level + 4
			ProficiencyBonus = CharacterLevel + 4;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, TagPrefix + ".Trained"))
		{
			// Trained -> Your level + 2
			ProficiencyBonus = CharacterLevel + 2;
		}
		else
		{
			// Untrained -> No bonus at all, no matter what level.
			ProficiencyBonus = 0;
		}
	}

	return ProficiencyBonus;
}
