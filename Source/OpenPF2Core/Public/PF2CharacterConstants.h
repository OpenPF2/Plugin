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

	// TODO: Consider whether this needs to be split apart to support NPC characters.
	/**
	 * Paths to Gameplay Effect Blueprints for core stat calculations.
	 *
	 * The weight of each path controls the order in which the corresponding GE is applied. Base stat GEs are applied
	 * first, followed by ancestry and class GEs, ability boost GEs, additional passive GEs, and then all other core
	 * GEs.
	 */
	static const TMap<const FString, const int32> GeCoreBlueprintPaths = {
		// Initialize base stats.
		{ TEXT("GE_ApplyBaseCharacterStats"),  GeWeights::InitializeBaseStats  },
		{ TEXT("GE_CalcKeyAbilityBoost"),      GeWeights::InitializeBaseStats  },

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
}
