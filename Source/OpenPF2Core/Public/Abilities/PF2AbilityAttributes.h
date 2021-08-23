﻿// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "Abilities/PF2AttributeSet.h"

#define DEFINE_ABILITY_CAPTUREDEF(S, P, T, B) \
{ \
	DEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \
	this->CaptureDefinitions.Add(P##Property->GetName(), P##Def); \
}

/**
 * Singleton container for ability-related attribute capture definitions.
 */
class FPF2AbilityAttributes final
{
public:
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbBoostCount);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbCharisma);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbConstitution);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbDexterity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbIntelligence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbStrength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbWisdom);

	/**
	 * Gets an instance of this container.
	 *
	 * @return
	 *	A reference to the capture definition container.
	 */
	FORCEINLINE static const FPF2AbilityAttributes& GetInstance()
	{
		static FPF2AbilityAttributes AbilityStatics;

		return AbilityStatics;
	}

	/**
	 * Gets all of the ability-related capture definitions.
	 *
	 * @return
	 *	An array of all the capture definitions for character abilities.
	 */
	TArray<FGameplayEffectAttributeCaptureDefinition> GetCaptureDefinitions() const;

	/**
	 * Gets a capture definition for the given ability-related attribute.
	 *
	 * @param Attribute
	 *	The attribute for which a capture definition is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the given attribute doesn't correspond to a character
	 *	ability.
	 */
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetCaptureByAttribute(
																			const FGameplayAttribute Attribute) const
	{
		return this->GetCaptureByName(Attribute.GetName());
	}

	/**
	* Gets a capture definition for the specified ability-related attribute.
	*
	* @param Name
	*	The name of the attribute for which a capture definition is desired.
	*
	* @return
	*	Either the desired capture definition; or nullptr if the given attribute name doesn't correspond to a character
	*	ability.
	*/
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetCaptureByName(const FString Name) const
	{
		if (this->CaptureDefinitions.Contains(Name))
		{
			return &(this->CaptureDefinitions[Name]);
		}
		else
		{
			return nullptr;
		}
	}

private:
	/**
	 * A map of all capture definitions, keyed by property name.
	 */
	TMap<FString, FGameplayEffectAttributeCaptureDefinition> CaptureDefinitions;

	/**
	 * Constructor for FPF2AbilityAttributes.
	 */
	FPF2AbilityAttributes()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, AbBoostCount, Target, false);

		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbCharisma, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbConstitution, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbDexterity, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbIntelligence, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbStrength, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbWisdom, Target, false);
	}
};
