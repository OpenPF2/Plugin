// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
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

#include <UObject/Interface.h>

#include "Items/PF2ItemInterface.h"

#include "PF2WeaponInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class APF2EffectCauseWrapper;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2WeaponInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Weapons.
 */
class OPENPF2CORE_API IPF2WeaponInterface : public IPF2ItemInterface
{
    GENERATED_BODY()

public:
    /**
     * Converts this weapon into an actor that can represent a "effect causer" for replication.
     *
     * @return
     *	This instance, wrapped as a effect causer.
     */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
    virtual APF2EffectCauseWrapper* ToEffectCauser() = 0;

	/**
	 * Calculates the attack roll, which determines if an attack was successful (it hit its target).
	 *
	 * "When making an attack roll, determine the result by rolling 1d20 and adding your attack modifier for the weapon
	 * or unarmed attack you’re using. Modifiers for melee and ranged attacks are calculated differently.
	 *
	 * Melee attack modifier = Strength modifier (or optionally Dexterity for a finesse weapon) + proficiency bonus +
	 * other bonuses + penalties
	 *
	 * Ranged attack modifier = Dexterity modifier + proficiency bonus + other bonuses + penalties
	 *
	 * Bonuses, and penalties apply to these rolls just like with other types of checks. Weapons with potency runes add
	 * an item bonus to your attack rolls."
	 *
	 * Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Attack Rolls".
	 *
	 * @param CharacterAsc
	 *	The character's ability system component.
	 *
	 * @return
	 *	The calculated attack roll for this weapon.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
	virtual float CalculateAttackRoll(const TScriptInterface<IPF2CharacterAbilitySystemInterface>& CharacterAsc) = 0;

	/**
	 * Calculates the damage roll, which determines how much of an effect an attack has on the target.
	 *
	 * "When the result of your attack roll with a weapon or unarmed attack equals or exceeds your target’s AC, you hit
	 * your target! Roll the weapon or unarmed attack’s damage die and add the relevant modifiers, bonuses, and
	 * penalties to determine the amount of damage you deal. Calculate a damage roll as follows.
	 *
	 * Melee damage roll = damage die of weapon or unarmed attack + Strength modifier + bonuses + penalties
	 *
	 * Ranged damage roll = damage die of weapon + Strength modifier for thrown weapons + bonuses + penalties"
	 *
	 * Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls".
	 *
	 * @param CharacterAsc
	 *	The character's ability system component.
	 *
	 * @return
	 *	The calculated damage roll for this weapon.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
	virtual float CalculateDamageRoll(const TScriptInterface<IPF2CharacterAbilitySystemInterface>& CharacterAsc) = 0;
};
