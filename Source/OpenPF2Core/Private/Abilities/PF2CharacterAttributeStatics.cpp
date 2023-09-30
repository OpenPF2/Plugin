// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2CharacterAttributeStatics.h"

#include "GameplayEffectTypes.h"

#include "Utilities/PF2ArrayUtilities.h"

FORCEINLINE TArray<FGameplayEffectAttributeCaptureDefinition> FPF2CharacterAttributeStatics::GetCaptureDefinitions() const
{
	TArray<FGameplayEffectAttributeCaptureDefinition> Result;

	for (auto& Elem : this->CaptureDefinitions)
	{
		Result.Add(Elem.Value);
	}

	return Result;
}

TArray<FGameplayEffectAttributeCaptureDefinition> FPF2CharacterAttributeStatics::GetAbilityScoreCaptures() const
{
	return PF2ArrayUtilities::Map<FGameplayEffectAttributeCaptureDefinition>(
		this->GetAbilityNames(),
		[this](const FString& AbilityScoreAttributeName)
		{
			return *(this->GetCaptureByAttributeName(AbilityScoreAttributeName));
		}
	);
}
