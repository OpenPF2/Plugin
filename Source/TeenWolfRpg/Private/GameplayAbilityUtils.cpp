// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.

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
