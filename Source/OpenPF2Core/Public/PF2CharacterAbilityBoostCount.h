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

#include "PF2CharacterAbilityBoostCount.generated.h"

/**
 * Data about how many boosts should be applied to a specific character ability.
 */
USTRUCT()
struct OPENPF2CORE_API FPF2CharacterAbilityBoostCount {
	GENERATED_BODY()

	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	/**
	 * Default constructor, called by UE.
	 */
	explicit FPF2CharacterAbilityBoostCount() :
		BoostCount(0)
	{
	}

	/**
	 * Constructor for FPF2CharacterAbilityBoostCount.
	 *
	 * @param AttributeName
	 *	The name of the attribute being boosted in the character's attribute set.
	 * @param BoostCount
	 *	The number of boosts to apply to the attribute.
	 */
	explicit FPF2CharacterAbilityBoostCount(const FString AttributeName, const int32 BoostCount) :
		AttributeName(AttributeName),
		BoostCount(BoostCount)
	{
	}

	/**
	 * Gets the name of the ability attribute being boosted.
	 *
	 * @return
	 *	The name of the attribute in the attribute set for the ability.
	 */
	FString GetAttributeName() const
	{
		return AttributeName;
	}

	/**
	 * Gets how many boosts to apply to the attribute.
	 *
	 * @return
	 *	The number of times that the ability score should be boosted.
	 */
	int32 GetBoostCount() const
	{
		return BoostCount;
	}

protected:
	// =================================================================================================================
	// Protected Properties
	// =================================================================================================================
	/**
	 * The name of the attribute being boosted in the character's attribute set.
	 */
	UPROPERTY(VisibleAnywhere)
	FString AttributeName;

	/**
	 * The number of boosts to apply to the attribute.
	 */
	UPROPERTY(EditAnywhere, meta=(ClampMin=0))
	int32 BoostCount;
};
