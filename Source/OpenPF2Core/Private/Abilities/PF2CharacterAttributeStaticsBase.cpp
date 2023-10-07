// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2CharacterAttributeStaticsBase.h"

#include "GameplayEffectTypes.h"

#include "Utilities/PF2ArrayUtilities.h"

FORCEINLINE TArray<const FGameplayEffectAttributeCaptureDefinition*> FPF2CharacterAttributeStaticsBase::GetCaptureDefinitions() const
{
	TArray<const FGameplayEffectAttributeCaptureDefinition*> Result;

	this->CaptureDefinitions.GenerateValueArray(Result);

	return Result;
}

TArray<const FGameplayEffectAttributeCaptureDefinition*> FPF2CharacterAttributeStaticsBase::GetAllAbilityScoreCaptures() const
{
	return PF2ArrayUtilities::Map<const FGameplayEffectAttributeCaptureDefinition*>(
		this->GetAbilityNames(),
		[this](const FString& AbilityScoreAttributeName)
		{
			return this->GetCaptureByAttributeName(AbilityScoreAttributeName);
		}
	);
}

const FGameplayEffectAttributeCaptureDefinition* FPF2CharacterAttributeStaticsBase::GetResistanceCaptureForDamageType(
	const FName& DamageTypeName) const
{
	const FGameplayEffectAttributeCaptureDefinition* Result = nullptr;

	if (this->DamageTypeToResistanceAttributeMap.Contains(DamageTypeName))
	{
		const FName ResistanceAttributeName = this->DamageTypeToResistanceAttributeMap[DamageTypeName];

		Result = this->GetCaptureByAttributeName(ResistanceAttributeName.ToString());
	}
	else
	{
		UE_LOG(
			LogPf2CoreStats,
			Error,
			TEXT("No resistance attribute corresponds to damage type '%s'."),
			*(DamageTypeName.ToString())
		);
	}

	return Result;
}

TArray<const FGameplayEffectAttributeCaptureDefinition*> FPF2CharacterAttributeStaticsBase::GetAllResistanceCaptures() const
{
	TArray<FName> ResistanceAttributeNames;

	this->DamageTypeToResistanceAttributeMap.GenerateValueArray(ResistanceAttributeNames);

	return PF2ArrayUtilities::ReduceToArray<const FGameplayEffectAttributeCaptureDefinition*>(
		ResistanceAttributeNames,
		[this](TArray<const FGameplayEffectAttributeCaptureDefinition*> Captures, const FName& ResistanceAttributeName)
		{
			const FGameplayEffectAttributeCaptureDefinition* ResistanceCapture =
				this->CaptureDefinitions[ResistanceAttributeName.ToString()];

			Captures.Add(ResistanceCapture);
		}
	);
}
