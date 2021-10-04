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

#pragma once

#include "PF2CharacterAbilityScoreType.h"

#include "Abilities/GameplayAbility.h"
#include "PF2GameplayAbilityBoostAbilityBase.generated.h"

USTRUCT(BlueprintType)
struct OPENPF2CORE_API FPF2AbilityBoostOptions {
	GENERATED_BODY()

	explicit FPF2AbilityBoostOptions() : bIsFreeBoost(false)
	{
	}

protected:
	/**
	 * Whether this is a free ability boost option or not.
	 *
	 * If set, then "Ability Score Options" are ignored.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFreeBoost;

	/**
	 * The abilities from which the player can choose, if this is not a free ability boost.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition="!bIsFreeBoost"))
	TSet<EPF2CharacterAbilityScoreType> AbilityScoreOptions;
};

/**
 * Base class for a Gameplay Ability that gives the player the option to boost one or more character abilities.
 *
 * Each sub-class/instance of this class represents ability boosts that are coming from a single source (ancestry,
 * background, class, etc.) at a specific point in time. As such, when this ability is invoked by the player, care must
 * be taken to ensure that the same ability is not boosted more than once per activation.
 *
 * From the Pathfinder 2E Core Rulebook, page 20, "Ability Boosts":
 * "When your character receives an ability boost, the rules indicate whether it must be applied to a specific
 * ability score or to one of two specific ability scores, or whether it is a 'free' ability boost that can be
 * applied to any ability score of your choice. However, when you gain multiple ability boosts at the same time, you
 * must apply each one to a different score."
 */
UCLASS(Abstract)
class OPENPF2CORE_API UPF2GameplayAbilityBoostAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	/**
	 * The boost(s) this ability applies to the target.
	 *
	 * Each element is a single boost rule that offer the player either a free ability boost or the option of two or
	 * more ability options from which to choose.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ability Boost Rules")
	TArray<FPF2AbilityBoostOptions> BoostCombos;
};
