// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

//=============================================================================
// GameplayAbilityUtils.cpp: Utility logic for working with Gameplay Abilities.
//=============================================================================

#pragma once

#include <CoreMinimal.h>

#include "GameplayEffectTypes.h"

namespace GameplayAbilityUtils
{
	FGameplayEffectAttributeCaptureDefinition BuildSourceCaptureFor(const FGameplayAttribute Attribute)
	{
		FGameplayEffectAttributeCaptureDefinition CaptureDefinition;

		CaptureDefinition.AttributeToCapture = Attribute;
		CaptureDefinition.AttributeSource	 = EGameplayEffectAttributeCaptureSource::Source;
		CaptureDefinition.bSnapshot			 = false;

		return CaptureDefinition;
	}
}
