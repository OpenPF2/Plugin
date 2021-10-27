// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>

#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "PF2CharacterConstants.h"

/**
 * Utility logic for working with the Gameplay Abilities System (GAS).
 */
namespace PF2GameplayAbilityUtilities
{
	/**
	 * Gets the specified tag out of the tags known to the project.
	 *
	 * The tag must already exist in one of the INI files under Config/Tags; otherwise, this will trigger an error.
	 *
	 * @param TagName
	 *	The name of the tag, as an FName.
	 *
	 * @return
	 *	The desired tag.
	 */
	FORCEINLINE FGameplayTag GetTag(const FName TagName)
	{
		return FGameplayTag::RequestGameplayTag(TagName);
	}

	/**
	 * Gets the specified tag out of the tags known to the project.
	 *
	 * The tag must already exist in one of the INI files under Config/Tags; otherwise, this will trigger an error.
	 *
	 * @param TagName
	 *	The name of the tag, as a string.
	 *
	 * @return
	 *	The desired tag.
	 */
	FORCEINLINE FGameplayTag GetTag(const FString TagName)
	{
		return GetTag(FName(TagName));
	}

	/**
	 * Checks if a tag with the given name or prefix is present.
	 *
	 * @param Tags
	 *	The list of tags in which to search.
	 * @param TagNameOrPrefix
	 *	The name of the tag or the prefix; as an FName.
	 *
	 * @return
	 *	- TRUE if given a tag name, and a tag with the specified name is present in the tag list.
	 *	- TRUE if given a tag prefix, and there is a tag present in the tag list that starts with that prefix.
	 *	- FALSE, otherwise.
	 */
	FORCEINLINE bool HasTag(const FGameplayTagContainer *Tags, const FName TagNameOrPrefix)
	{
		return Tags->HasTag(GetTag(TagNameOrPrefix));
	}

	/**
	 * Checks if a tag with the given name or prefix is present.
	 *
	 * @param Tags
	 *	The list of tags in which to search.
	 * @param TagNameOrPrefix
	 *	The name of the tag or the prefix; as a string.
	 *
	 * @return
	 *	- TRUE if given a tag name, and a tag with the specified name is present in the tag list.
	 *	- TRUE if given a tag prefix, and there is a tag present in the tag list that starts with that prefix.
	 *	- FALSE, otherwise.
	 */
	FORCEINLINE bool HasTag(const FGameplayTagContainer *Tags, const FString TagNameOrPrefix)
	{
		return Tags->HasTag(GetTag(TagNameOrPrefix));
	}

	/**
	 * Creates an attribute capture definition for the specified Gameplay Attribute.
	 *
	 * @param Attribute
	 *	The Gameplay Attribute that should be captured.
	 *
	 * @return
	 *	The capture definition for the specified attribute.
	 */
	OPENPF2CORE_API FGameplayEffectAttributeCaptureDefinition BuildSourceCaptureFor(const FGameplayAttribute Attribute);

	/**
	 * Gets the name of the default weight group into which the given GE should be placed.
	 *
	 * If the GE does not define a default weight group, PF2CharacterConstants::GeWeightGroups::PreAbilityBoosts is
	 * returned.
	 *
	 * @param GameplayEffect
	 *	The effect for which a weight group is desired.
	 * @param DefaultWeight
	 *	The weight to return if the gameplay effect does not indicate its weight with a tag.
	 *
	 * @return
	 *	The name of the weight group for the effect.
	 */
	OPENPF2CORE_API FName GetWeightGroupOfGameplayEffect(
		const TSubclassOf<UGameplayEffect> GameplayEffect,
		const FName DefaultWeight = PF2CharacterConstants::GeWeightGroups::PreAbilityBoosts
	);
}
