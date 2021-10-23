// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
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
#include "Abilities/PF2GameplayAbility_BoostAbilityBase.h"

#include "PF2CharacterInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPF2CharacterInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2 characters.
 */
class OPENPF2CORE_API IPF2CharacterInterface
{
    GENERATED_BODY()

public:
	/**
	 * Gets the current level of this character.
	 *
	 * The character level impacts the character's stats and how many boosts and feats the character can have.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 31, "Leveling Up":
	 * "Each level grants greater skill, increased resiliency, and new capabilities, allowing your character to face
	 * even greater challenges and go on to earn even more impressive rewards."
	 */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const = 0;

	/**
	 * Gets all of the ability boosts that have been granted to this character that require choices from the player.
	 *
	 * @return
	 *	The ability boost GAs that are still pending for this character.
	 */
	UFUNCTION(BlueprintCallable)
	virtual TArray<UPF2GameplayAbility_BoostAbilityBase*> GetPendingAbilityBoosts() const = 0;
};
