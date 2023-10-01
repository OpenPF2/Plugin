﻿// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
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

#include "Abilities/PF2CharacterAbilityScoreType.h"
#include "Items/PF2ItemInterface.h"

#include "PF2WeaponInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class APF2EffectCauseWrapper;
struct FGameplayTagContainer;
struct FGameplayEffectCustomExecutionParameters;

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
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
    /**
     * Unpacks an effect causer that could be either a PF2WeaponInterface object or Effect Cause Wrapper into a weapon.
     *
     * Most of the time, callers are going to be providing an instance of APF2EffectCauseWrapper to this method, but it
     * has been written to accept PF2WeaponInterface objects as well so that callers can call this method whenever they
     * receive a weapon in a GE execution, without having to be concerned about what type of object they have received
     * in the GE execution context. If an object that is neither an APF2EffectCauseWrapper nor PF2WeaponInterface is
     * provided, or this method is provided with nullptr, the result is nullptr.
     *
     * @param Object
     *	The weapon or wrapped weapon object to unwrap/convert into being a weapon.
     *
     * @return
     *	- If given an instance of APF2EffectCauseWrapper: The weapon the instance is wrapping.
     *	- If given an instance of PF2WeaponInterface: The same instance that was passed in.
     *	- If given an instance of any other object: nullptr.
     *	- If given nullptr: nullptr.
     */
	static TScriptInterface<IPF2WeaponInterface> EffectCauserToWeapon(UObject* Object);

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets the root/parent tag of each set of tags that represent a character's TEML proficiencies with this weapon.
	 *
	 * A character that possesses a tag underneath one such root tag has a proficiency with the weapon. Most weapons
	 * will typically expose only one root tag here. However, ancestry-specific weapons that are affected by a weapon
	 * familiarity feat will define at least two. The highest-granted proficiency wins.
	 *
	 * For example, a gnome martial weapon would have root gameplay tags of both "WeaponProficiency.Category.Martial"
	 * and "WeaponProficiency.Category.MartialGnome". This would allow a character to have proficiency with the weapon
	 * under the following scenarios:
	 *	- A Gnome with the "Gnome Weapon Familiarity" feat who is proficient with simple weapons, granting them both a
	 *	  "WeaponProficiency.Category.Simple.*" and "WeaponProficiency.Category.MartialGnome.*" gameplay tag, since the
	 *	  feat allows gnome martial weapons to be treated as simple weapons.
	 *	- Any character without the "Gnome Weapon Familiarity" feat who is proficient with martial weapons, since the
	 *	  proficiency grants them a "WeaponProficiency.Category.Martial.*" gameplay tag.
	 *
	 * @return
	 *	The root of the tag namespace for this weapon.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
	virtual FGameplayTagContainer GetProficiencyTagPrefixes() const = 0;

	/**
	 * Gets the type of ability modifier from the character's ASC that is added to *attack* rolls with this weapon.
	 *
	 * @return
	 *	The attack ability modifier for this weapon.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
	virtual EPF2CharacterAbilityScoreType GetAttackAbilityModifierType() const = 0;

	/**
	 * Gets the type of ability modifier from the character's ASC that is added to *damage* rolls with this weapon.
	 *
	 * @return
	 *	The damage ability modifier for this weapon.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
	virtual EPF2CharacterAbilityScoreType GetDamageAbilityModifierType() const = 0;

    /**
     * Converts this weapon into an actor that can represent a "effect causer" for replication.
     *
     * The causer is linked to the lifetime of the given owning actor.
     *
     * @param OwningActor
     *	The actor who owns or possesses this weapon.
     *
     * @return
     *	This instance, wrapped as a effect causer.
     */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
    virtual APF2EffectCauseWrapper* ToEffectCauser(AActor* OwningActor) = 0;

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
	 * @param ExecutionParams
	 *	The context of the gameplay effect calculation that is being executed.
	 *
	 * @return
	 *	The calculated damage roll for this weapon.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
	virtual float CalculateDamageRoll(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const = 0;
};
