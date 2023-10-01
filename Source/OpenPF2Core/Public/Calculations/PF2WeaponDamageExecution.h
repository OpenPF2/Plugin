// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
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

#include <GameplayEffectExecutionCalculation.h>

#include "Abilities/PF2CharacterAbilitySystemInterface.h"

#include "Items/Weapons/PF2WeaponInterface.h"

#include "PF2WeaponDamageExecution.generated.h"

/**
 * Gameplay effect execution calculation for determining if a weapon attack is successful and applying resulting damage.
 */
UCLASS()
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2WeaponDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Static Methods
	// =================================================================================================================
	/**
	 * Attempts an an attack from the source character to the target character.
	 *
	 * An attack roll is performed to determine if the attack against the target is successful. If it is successful, a
	 * damage roll is performed to determine how much damage is inflicted.
	 *
	 * From the Pathfinder 2E Core Rulebook, Chapter 9, page 446, "Attack Rolls":
	 * "When you use a Strike action or make a spell attack, you attempt a check called an attack roll. Attack rolls
	 * take a variety of forms and are often highly variable based on the weapon you are using for the attack..."
	 *
	 * From the Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls":
	 * "When the result of your attack roll with a weapon or unarmed attack equals or exceeds your target’s AC, you hit
	 * your target! Roll the weapon or unarmed attack’s damage die and add the relevant modifiers, bonuses, and
	 * penalties to determine the amount of damage you deal."
	 *
	 * @param ExecutionParams
	 *	The context of the gameplay effect calculation that is being executed.
	 * @param Weapon
	 *	The weapon with which the attack is being attempted.
	 * @param SourceAsc
	 *	The Ability System Component of the character attempting the attack.
	 * @param TargetAsc
	 *	The Ability System Component of the character receiving the attack.
	 */
	static void AttemptAttack(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                          const IPF2WeaponInterface*                      Weapon,
	                          const IPF2CharacterAbilitySystemInterface*      SourceAsc,
	                          const IPF2CharacterAbilitySystemInterface*      TargetAsc);

	/**
	 * Calculates the attack roll, which determines if an attack was successful (it hit its target).
	 *
	 * From the Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Attack Rolls":
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
	 * @param ExecutionParams
	 *	The context of the gameplay effect calculation that is being executed.
	 * @param EvaluationParameters
	 *	Context about the source and target to pass in when obtaining captured attribute values.
	 * @param Weapon
	 *	The weapon with which the attack is being attempted.
	 * @param SourceAsc
	 *	The Ability System Component of the character attempting the attack.
	 *
	 * @return
	 *	The calculated attack roll for the weapon.
	 */
	static float CalculateAttackRoll(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                 const FAggregatorEvaluateParameters&            EvaluationParameters,
	                                 const IPF2WeaponInterface*                      Weapon,
	                                 const IPF2CharacterAbilitySystemInterface*      SourceAsc);

	/**
	 * Gets the armor class (AC) value of the target of an attack.
	 *
	 * From the Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls":
	 * "When the result of your attack roll with a weapon or unarmed attack equals or exceeds your target’s AC, you hit
	 * your target!"
	 *
	 * @param ExecutionParams
	 *	The context of the gameplay effect calculation that is being executed.
	 * @param EvaluationParameters
	 *	Context about the source and target to pass in when obtaining captured attribute values.
	 *
	 * @return
	 */
	static float GetTargetArmorClass(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                 const FAggregatorEvaluateParameters&            EvaluationParameters);

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor.
	 */
	UPF2WeaponDamageExecution();

	// =================================================================================================================
	// Public Methods - UGameplayEffectExecutionCalculation Implementation
	// =================================================================================================================
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
