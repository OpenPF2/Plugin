﻿// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
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
                                              const IPF2CharacterAbilitySystemInterface*      TargetAsc)
{
	const FGameplayEffectSpec     OwningSpec            = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer * SourceTags            = OwningSpec.CapturedSourceTags.GetAggregatedTags(),
	                            * TargetTags            = OwningSpec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	float                         AttackRoll,
	                              TargetAc;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	AttackRoll = CalculateAttackRoll(ExecutionParams, EvaluationParameters, Weapon, SourceAsc);
	TargetAc   = GetTargetArmorClass(ExecutionParams, EvaluationParameters);

	// "When the result of your attack roll with a weapon or unarmed attack equals or exceeds your target’s AC,
	// you hit your target!"
	//
	// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls".
	if (AttackRoll >= TargetAc)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Verbose,
			TEXT("Attack of character ('%s') against character ('%s') with weapon ('%s'): %f vs AC %f - HIT."),
			*(SourceAsc->GetCharacter()->GetIdForLogs()),
			*(TargetAsc->GetCharacter()->GetIdForLogs()),
			*(Weapon->GetIdForLogs()),
			AttackRoll,
			TargetAc
		);
	}
	else
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Verbose,
			TEXT("Attack of character ('%s') against character ('%s') with weapon ('%s'): %f vs AC %f - MISS."),
			*(SourceAsc->GetCharacter()->GetIdForLogs()),
			*(TargetAsc->GetCharacter()->GetIdForLogs()),
			*(Weapon->GetIdForLogs()),
			AttackRoll,
			TargetAc
		);
	}
}

float UPF2WeaponAttackExecution::CalculateAttackRoll(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FAggregatorEvaluateParameters&            EvaluationParameters,
	const IPF2WeaponInterface*                      Weapon,
	const IPF2CharacterAbilitySystemInterface*      SourceAsc)
{
	const FPF2SourceCharacterAttributeStatics& SourceStatics = FPF2SourceCharacterAttributeStatics::GetInstance();

	const int32                         CharacterLevel         = SourceAsc->GetCharacterLevel();
	const FGameplayTagContainer         CharacterTags          = SourceAsc->GetActiveGameplayTags();
	const EPF2CharacterAbilityScoreType AttackScoreType        = Weapon->GetAttackAbilityModifierType();
	const FGameplayTagContainer         ProficiencyTagPrefixes = Weapon->GetProficiencyTagPrefixes();
	float                               AttackAbilityModifier  = 0.0f,
	                                    MultipleAttackPenalty  = 0.0f;

	const FGameplayEffectAttributeCaptureDefinition* AbilityScoreCapture =
		SourceStatics.GetCaptureByAbilityScoreType(AttackScoreType);

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

	return UPF2AttackStatLibrary::CalculateAttackRoll(
		CharacterLevel,
		CharacterTags,
		AttackAbilityModifier,
		MultipleAttackPenalty,
		ProficiencyTagPrefixes
	);
}

float UPF2WeaponAttackExecution::GetTargetArmorClass(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     const FAggregatorEvaluateParameters& CaptureParameters)
{
	float                                      TargetArmorClass = 0.0f;
	const FPF2TargetCharacterAttributeStatics& TargetStatics    = FPF2TargetCharacterAttributeStatics::GetInstance();

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		TargetStatics.ArmorClassDef,
		CaptureParameters,
		TargetArmorClass
	);

	return TargetArmorClass;
}

UPF2WeaponAttackExecution::UPF2WeaponAttackExecution()
{
	const FPF2SourceCharacterAttributeStatics& SourceStatics = FPF2SourceCharacterAttributeStatics::GetInstance();
	const FPF2TargetCharacterAttributeStatics& TargetStatics = FPF2TargetCharacterAttributeStatics::GetInstance();

	// Capture all ability attributes, since attacks in OpenPF2 could theoretically be based on any ability score stat
	// even though the Core Rulebook only anticipates attacks that use Strength (for regular melee attacks) or Dexterity
	// (for ranged attacks and melee finesse attacks).
	for (const FGameplayEffectAttributeCaptureDefinition& Capture : SourceStatics.GetAbilityScoreCaptures())
	{
		this->RelevantAttributesToCapture.Add(Capture);
	}

	// The multiple attack penalty grows with each additional attack taken during the same turn.
	this->RelevantAttributesToCapture.Add(SourceStatics.EncMultipleAttackPenaltyDef);

	// The target Armor Class (AC) is needed for attack checks, to see if the target was hit at all.
	this->RelevantAttributesToCapture.Add(TargetStatics.ArmorClassDef);
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
			AttemptAttack(ExecutionParams, Weapon.GetInterface(), SourceCharacterAsc, TargetCharacterAsc);
		}
	}
}
