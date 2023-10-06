// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2CharacterAttributeStaticsBase.h"

#include "GameplayEffectTypes.h"

#include "Utilities/PF2ArrayUtilities.h"

FORCEINLINE TArray<FGameplayEffectAttributeCaptureDefinition> FPF2CharacterAttributeStaticsBase::GetCaptureDefinitions() const
{
	TArray<FGameplayEffectAttributeCaptureDefinition> Result;

	for (auto& Elem : this->CaptureDefinitions)
	{
		Result.Add(Elem.Value);
	}

	return Result;
}

TArray<FGameplayEffectAttributeCaptureDefinition> FPF2CharacterAttributeStaticsBase::GetAllAbilityScoreCaptures() const
{
	return PF2ArrayUtilities::Map<FGameplayEffectAttributeCaptureDefinition>(
		this->GetAbilityNames(),
		[this](const FString& AbilityScoreAttributeName)
		{
			return *(this->GetCaptureByAttributeName(AbilityScoreAttributeName));
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

TArray<FGameplayEffectAttributeCaptureDefinition> FPF2CharacterAttributeStaticsBase::GetAllResistanceCaptures()
{
	TArray<FGameplayEffectAttributeCaptureDefinition> Result;
	TArray<FName>                                     ResistanceAttributeNames;

	this->DamageTypeToResistanceAttributeMap.GenerateValueArray(ResistanceAttributeNames);

	Result.Reserve(ResistanceAttributeNames.Num());

	for (const FName& ResistanceAttributeName : ResistanceAttributeNames)
	{
		FGameplayEffectAttributeCaptureDefinition& ResistanceCapture =
			this->CaptureDefinitions[ResistanceAttributeName.ToString()];

		Result.Add(ResistanceCapture);
	}

	return Result;
}
