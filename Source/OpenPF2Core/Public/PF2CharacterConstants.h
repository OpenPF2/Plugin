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
	 * Weights used to control the order that GEs are applied to a PF2 character.
	 */
	namespace GeWeights
	{
		/**
		 * The weight used for GEs that initialize base stats.
		 */
		static constexpr int32 InitializeBaseStats = 0;

		/**
		 * The weight used for managed, passive GEs generated from other values on this character.
		 */
		static constexpr int32 ManagedEffects = 10;

		/**
		 * The weight used for passive GEs provided by the game designer.
		 */
		static constexpr int32 AdditionalEffects = 25;

		/**
		 * The weight used for passive GEs that depend on the results of earlier GEs.
		 */
		static constexpr int32 FinalizeStats = 30;
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
	 * TODO: Consider whether we want to expose GE weights to Blueprint and then move this list into a Blueprint
	 * UPROPERTY instead, so that it's not hard-coded.
	 */
	static const TMap<const FString, const int32> GeCoreCharacterBlueprintPaths = {
		// Initialize base stats.
		{ TEXT("GE_ApplyBaseCharacterStats"),     GeWeights::InitializeBaseStats  },
		{ TEXT("GE_GrantCharacterBaseAbilities"), GeWeights::InitializeBaseStats  },
		{ TEXT("GE_CalcKeyAbilityBoost"),         GeWeights::InitializeBaseStats  },

		// Finalize stats.
		{ TEXT("GE_CalcAbilityModifiers"),     GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcClassDifficultyClass"), GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcArmorClass"),           GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcPerceptionModifier"),   GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcSavingThrowModifiers"), GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcSpellAttackRoll"),      GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcSpellDifficultyClass"), GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcSkillModifiers"),       GeWeights::FinalizeStats        },
		{ TEXT("GE_CalcAncestryFeatLimit"),    GeWeights::FinalizeStats        },
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
