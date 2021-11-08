// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2GameplayAbilityUtilities.h"

/**
 * Utility logic for working with Gameplay Abilities.
 */
namespace PF2GameplayAbilityUtilities
{
	FGameplayEffectAttributeCaptureDefinition BuildSourceCaptureFor(
		const FGameplayAttribute Attribute)
	{
		FGameplayEffectAttributeCaptureDefinition CaptureDefinition;

		CaptureDefinition.AttributeToCapture = Attribute;
		CaptureDefinition.AttributeSource    = EGameplayEffectAttributeCaptureSource::Source;
		CaptureDefinition.bSnapshot          = false;

		return CaptureDefinition;
	}

	FName GetWeightGroupOfGameplayEffect(
		const TSubclassOf<UGameplayEffect> GameplayEffect,
		const FName DefaultWeight)
	{
		FName                  WeightGroup;
		const FGameplayTag     WeightTagParent = GetTag(FName(TEXT("GameplayEffect.WeightGroup")));
		const UGameplayEffect* Effect          = GameplayEffect.GetDefaultObject();

		const FGameplayTagContainer WeightTags =
			Effect->InheritableGameplayEffectTags.CombinedTags.Filter(FGameplayTagContainer(WeightTagParent));

		if (WeightTags.IsEmpty())
		{
			WeightGroup = DefaultWeight;
		}
		else
		{
			const FGameplayTag WeightTag = WeightTags.First();

			checkf(
				WeightTags.Num() < 2,
				TEXT("A Gameplay Effect can only have a single weight group assigned (this GE has been assigned '%d' weight groups)."),
				WeightTags.Num()
			);

			checkf(
				WeightTag != WeightTagParent,
				TEXT("Parent tag of weight groups ('%s') cannot be used as a weight group "),
				*WeightTagParent.ToString()
			);

			WeightGroup = WeightTag.GetTagName();
		}

		return WeightGroup;
	}
}
