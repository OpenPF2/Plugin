// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

/**
 * Constants related to PF2 character logic.
 */
namespace PF2CharacterConstants
{
	/**
	 * The name of each weight "group" for passive GEs on a character.
	 *
	 * Weight groups are evaluated in the order that their names are sorted. Placing different GEs in different groups
	 * allows game designers to control the order that GEs are applied to a PF2 character.
	 *
	 * For consistency, each name in this list must exactly match a tag in the "GameplayEffect.WeightGroup" group. This
	 * ensures that game designers have the same options for placing a GE in a weight group as exists in backend code.
	 */
	namespace GeWeightGroups
	{
		/**
		 * The weight group used for GEs that initialize base stats.
		 */
		static const FName InitializeBaseStats = FName("GameplayEffect.WeightGroup.00_InitializeBaseStats");

		/**
		 * The weight group used for managed GEs generated from other values on a character.
		 */
		static const FName ManagedEffects = FName("GameplayEffect.WeightGroup.10_ManagedEffects");

		/**
		 * The default weight group used for GEs provided by the game designer.
		 */
		static const FName AdditionalEffects = FName("GameplayEffect.WeightGroup.20_AdditionalEffects");

		/**
		 * The weight group used for GEs that must run last because they heavily depend on results of earlier GEs.
		 */
		static const FName FinalizeStats = FName("GameplayEffect.WeightGroup.30_FinalizeStats");
	}

	/**
	 * The path to the folder that contains GE blueprints.
	 */
	static const FString BlueprintBasePath = TEXT("/OpenPF2Core/OpenPF2/Core/");

	/**
	 * Format string for the name of the Gameplay Effect blueprint that boosts abilities.
	 */
	static const FString GeBlueprintBoostNameFormat = TEXT("GE_Boost{0}");

	/**
	 * The name of the Gameplay Effect that is used to apply tags that have been set on the character.
	 */
	static const FString GeDynamicTagsName = TEXT("GE_ApplyDynamicTags");

	/**
	* The name of the Gameplay Effect that is used to apply tags that have been set on the character.
	*/
	static const FString GeDynamicTagsClassName = FString::Format(TEXT("{0}_C"), { GeDynamicTagsName });

	/**
	 * Paths to Gameplay Effect Blueprints for core stat calculations in characters.
	 *
	 * The weight of each path controls the order in which the corresponding GE is applied. Base stat GEs are applied
	 * first, followed by ancestry and class GEs, ability boost GEs, additional passive GEs, and then all other core
	 * GEs. GEs that have the same weight are applied in the order they have been added/listed here.
	 *
	 * TODO: Consider whether we want to move this list into a Blueprint UPROPERTY, so that it's not hard-coded.
	 */
	static const TMap<const FString, FName> GeCoreCharacterBlueprintPaths = {
		// Initialize base stats.
		{ TEXT("GE_ApplyBaseCharacterStats"),     GeWeightGroups::InitializeBaseStats },
		{ TEXT("GE_GrantCharacterBaseAbilities"), GeWeightGroups::InitializeBaseStats },
		{ TEXT("GE_CalcKeyAbilityBoost"),         GeWeightGroups::InitializeBaseStats },

		// Finalize stats.
		{ TEXT("GE_CalcAbilityModifiers"),        GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcClassDifficultyClass"),    GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcArmorClass"),              GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcPerceptionModifier"),      GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcSavingThrowModifiers"),    GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcSpellAttackRoll"),         GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcSpellDifficultyClass"),    GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcSkillModifiers"),          GeWeightGroups::FinalizeStats       },
		{ TEXT("GE_CalcAncestryFeatLimit"),       GeWeightGroups::FinalizeStats       },
	};

	/**
	 * Returns the path to the Blueprint having the given name.
	 *
	 * @param Name
	 *	The name of the blueprint for which a path is desired.
	 *
	 * @return
	 *	The path to the blueprint.
	 */
	FORCEINLINE static FString GetBlueprintPath(FString Name)
	{
		return FString::Format(TEXT("{0}{1}.{1}_C"), { BlueprintBasePath, Name });
	}
}
