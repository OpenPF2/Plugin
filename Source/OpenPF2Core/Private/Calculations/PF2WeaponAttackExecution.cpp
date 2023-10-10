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

#include "Calculations/PF2WeaponAttackExecution.h"

#include "PF2CharacterInterface.h"

#include "Abilities/PF2CharacterAbilitySystemInterface.h"
#include "Abilities/PF2SourceCharacterAttributeStatics.h"
#include "Abilities/PF2TargetCharacterAttributeStatics.h"

#include "Items/Weapons/PF2WeaponInterface.h"

#include "Libraries/PF2AttackStatLibrary.h"

void UPF2WeaponAttackExecution::AttemptAttack(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              const IPF2WeaponInterface*                      Weapon,
                                              const IPF2CharacterAbilitySystemInterface*      SourceAsc,
                                              const IPF2CharacterAbilitySystemInterface*      TargetAsc,
                                              FGameplayEffectCustomExecutionOutput&           OutExecutionOutput)
{
	const FGameplayEffectSpec     OwningSpec            = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer * SourceTags            = OwningSpec.CapturedSourceTags.GetAggregatedTags(),
	                            * TargetTags            = OwningSpec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	float                         TargetAc;
	EPF2CheckResult               AttackRollResult;

	UE_LOG(
		LogPf2CoreAbilities,
		Verbose,
		TEXT("Character ('%s') attempting attack with weapon ('%s') against character ('%s')."),
		*(SourceAsc->GetCharacter()->GetIdForLogs()),
		*(Weapon->GetIdForLogs()),
		*(TargetAsc->GetCharacter()->GetIdForLogs())
	);

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	TargetAc         = GetTargetArmorClass(ExecutionParams, EvaluationParameters);
	AttackRollResult = PerformAttackRoll(ExecutionParams, EvaluationParameters, Weapon, SourceAsc, TargetAc);

	// "When the result of your attack roll with a weapon or unarmed attack equals or exceeds your target’s AC, you hit
	// your target!"
	//
	// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls".
	if (UPF2AttackStatLibrary::IsSuccess(AttackRollResult))
	{
		const float DamageRoll       = CalculateDamageRoll(ExecutionParams, EvaluationParameters, Weapon),
		            Resistance       = GetTargetResistanceToWeaponDamage(ExecutionParams, EvaluationParameters, Weapon);
		float       DamageMultiplier,
		            DamageAmount,
		            ClampedDamageAmount;

		// "When you make an attack and succeed with a natural 20 (the number on the die is 20), or if the result of
		// your attack exceeds the target’s AC by 10, you achieve a critical success (also known as a critical hit)."
		//
		// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Critical Hits".
		if (AttackRollResult == EPF2CheckResult::CriticalSuccess)
		{
			DamageMultiplier = 2.0f;
		}
		else
		{
			DamageMultiplier = 1.0f;
		}

		DamageAmount = DamageRoll * DamageMultiplier;

		// Apply resistance to reduce damage, but don't allow resistance to make damage negative (i.e., damage can never
		// heal, but it can become ineffectual).
		//
		// From the Pathfinder 2E Core Rulebook, page 453, "Resistance":
		// "If you have resistance to a type of damage, each time you take that type of damage, you reduce the amount of
		// damage you take by the listed amount (to a minimum of 0 damage)."
		ClampedDamageAmount = FMath::Max(0.0f, DamageAmount - Resistance);

		UE_LOG(
			LogPf2CoreStats,
			VeryVerbose,
			TEXT("Damage Roll (%f) * Damage Multiplier (%f) - Resistance (%s: %f) = %f (CLAMPED >= 0)."),
			DamageRoll,
			DamageMultiplier,
			*(Weapon->GetDamageType().ToString()),
			Resistance,
			ClampedDamageAmount
		);

		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				FPF2TargetCharacterAttributeStatics::GetInstance().TmpDamageIncomingProperty,
				EGameplayModOp::Additive,
				ClampedDamageAmount
			)
		);
	}
}

EPF2CheckResult UPF2WeaponAttackExecution::PerformAttackRoll(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters&            EvaluationParameters,
	const IPF2WeaponInterface*                      Weapon,
	const IPF2CharacterAbilitySystemInterface*      SourceAsc,
	const float                                     TargetArmorClass)
{
	EPF2CheckResult                     Result;
	const int32                         CharacterLevel         = SourceAsc->GetCharacterLevel();
	const FGameplayTagContainer         CharacterTags          = SourceAsc->GetActiveGameplayTags();
	const EPF2CharacterAbilityScoreType AttackScoreType        = Weapon->GetAttackAbilityModifierType();
	const FGameplayTagContainer         ProficiencyTagPrefixes = Weapon->GetProficiencyTagPrefixes();
	float                               AttackAbilityModifier  = 0.0f,
	                                    MultipleAttackPenalty  = 0.0f;

	const FPF2SourceCharacterAttributeStatics& SourceStatics = FPF2SourceCharacterAttributeStatics::GetInstance();

	const FGameplayEffectAttributeCaptureDefinition* AbilityScoreCapture =
		SourceStatics.GetModifierCaptureByAbilityScoreType(AttackScoreType);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		*AbilityScoreCapture,
		EvaluationParameters,
		AttackAbilityModifier
	);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		SourceStatics.EncMultipleAttackPenaltyDef,
		EvaluationParameters,
		MultipleAttackPenalty
	);

	Result = UPF2AttackStatLibrary::PerformAttackRoll(
		CharacterLevel,
		CharacterTags,
		AttackAbilityModifier,
		MultipleAttackPenalty,
		ProficiencyTagPrefixes,
		TargetArmorClass
	);

	return Result;
}

float UPF2WeaponAttackExecution::CalculateDamageRoll(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters&            EvaluationParameters,
	const IPF2WeaponInterface*                      Weapon)
{
	const FPF2SourceCharacterAttributeStatics& SourceStatics = FPF2SourceCharacterAttributeStatics::GetInstance();

	const FName                         DamageDie             = Weapon->GetDamageDie();
	const EPF2CharacterAbilityScoreType DamageScoreType       = Weapon->GetDamageAbilityModifierType();
	float                               DamageAbilityModifier = 0.0f;

	const FGameplayEffectAttributeCaptureDefinition* AbilityScoreCapture =
		SourceStatics.GetModifierCaptureByAbilityScoreType(DamageScoreType);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		*AbilityScoreCapture,
		EvaluationParameters,
		DamageAbilityModifier
	);

	return UPF2AttackStatLibrary::CalculateDamageRoll(
		DamageDie,
		DamageAbilityModifier
	);
}

float UPF2WeaponAttackExecution::GetTargetArmorClass(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     const FAggregatorEvaluateParameters& EvaluationParameters)
{
	float                                      TargetArmorClass = 0.0f;
	const FPF2TargetCharacterAttributeStatics& TargetStatics    = FPF2TargetCharacterAttributeStatics::GetInstance();

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		TargetStatics.ArmorClassDef,
		EvaluationParameters,
		TargetArmorClass
	);

	return TargetArmorClass;
}

float UPF2WeaponAttackExecution::GetTargetResistanceToWeaponDamage(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters&            EvaluationParameters,
	const IPF2WeaponInterface*                      Weapon)
{
	float                                      TargetResistance = 0.0f;
	const FPF2TargetCharacterAttributeStatics& TargetStatics    = FPF2TargetCharacterAttributeStatics::GetInstance();
	const FGameplayTag                         DamageType       = Weapon->GetDamageType();

	const FGameplayEffectAttributeCaptureDefinition* ResistanceCapture =
		TargetStatics.GetResistanceCaptureForDamageType(DamageType);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		*ResistanceCapture,
		EvaluationParameters,
		TargetResistance
	);

	return TargetResistance;
}

UPF2WeaponAttackExecution::UPF2WeaponAttackExecution()
{
	const FPF2SourceCharacterAttributeStatics& SourceStatics = FPF2SourceCharacterAttributeStatics::GetInstance();
	const FPF2TargetCharacterAttributeStatics& TargetStatics = FPF2TargetCharacterAttributeStatics::GetInstance();

	// Capture all ability score attributes, since attacks in OpenPF2 could theoretically be based on any ability score
	// stat even though the Core Rulebook only anticipates attacks that use Strength (for regular melee attacks) or
	// Dexterity (for ranged attacks and melee finesse attacks).
	for (const FGameplayEffectAttributeCaptureDefinition* Capture : SourceStatics.GetAllAbilityScoreCaptures())
	{
		this->RelevantAttributesToCapture.Add(*Capture);
	}

	// Capture the multiple attack penalty, which grows with each additional attack taken during the same turn.
	this->RelevantAttributesToCapture.Add(SourceStatics.EncMultipleAttackPenaltyDef);

	// Capture the target Armor Class (AC) for checks against attack rolls, to see if the target was hit at all.
	this->RelevantAttributesToCapture.Add(TargetStatics.ArmorClassDef);

	// Capture all damage resistances that the target has so that final damage can be reduced appropriately.
	for (const FGameplayEffectAttributeCaptureDefinition* Capture : TargetStatics.GetAllResistanceCaptures())
	{
		this->RelevantAttributesToCapture.Add(*Capture);
	}
}

void UPF2WeaponAttackExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                       FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec         = ExecutionParams.GetOwningSpec();
	AActor*                    EffectCauser = Spec.GetEffectContext().GetEffectCauser();

	if (const TScriptInterface<IPF2WeaponInterface> Weapon = IPF2WeaponInterface::EffectCauserToWeapon(EffectCauser);
		Weapon == nullptr)
	{
		// "An unarmed attack uses your body rather than a manufactured weapon. An unarmed attack isn’t a weapon, though
		// it’s categorized with weapons for weapon groups, and it might have weapon traits."
		//
		// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 283, "Weapon Traits".
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Cannot calculate attack because no weapon was provided in the effect context. If this was an unarmed attack, the source of the attack must still implement the weapon interface.")
		);
	}
	else
	{
		const UAbilitySystemComponent             *SourceAsc          = ExecutionParams.GetSourceAbilitySystemComponent(),
		                                          *TargetAsc          = ExecutionParams.GetTargetAbilitySystemComponent();
		const IPF2CharacterAbilitySystemInterface *SourceCharacterAsc = Cast<IPF2CharacterAbilitySystemInterface>(SourceAsc),
		                                          *TargetCharacterAsc = Cast<IPF2CharacterAbilitySystemInterface>(TargetAsc);

		if (SourceCharacterAsc == nullptr)
		{
			UE_LOG(
				LogPf2CoreAbilities,
				Error,
				TEXT("Cannot calculate attack because source ASC is not compatible with OpenPF2.")
			);
		}
		else if (TargetCharacterAsc == nullptr)
		{
			UE_LOG(
				LogPf2CoreAbilities,
				Error,
				TEXT("Cannot calculate attack because target ASC is not compatible with OpenPF2.")
			);
		}
		else
		{
			AttemptAttack(
				ExecutionParams,
				Weapon.GetInterface(),
				SourceCharacterAsc,
				TargetCharacterAsc,
				OutExecutionOutput
			);
		}
	}
}
