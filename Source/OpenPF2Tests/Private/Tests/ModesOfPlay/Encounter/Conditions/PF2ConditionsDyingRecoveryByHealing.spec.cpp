// OpenPF2 Game Framework for Unreal Engine, Copyright 2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.


#include <AbilitySystemComponent.h>

#include "CharacterStats/PF2CharacterAttributeSet.h"

#include "GameplayTags/GameplayEffects/SetByCallerParameters.h"
#include "GameplayTags/Traits/Conditions.h"

#include "Tests/PF2SpecBase.h"

BEGIN_DEFINE_PF_SPEC(FPF2ConditionsDyingRecoveryByHealing,
                     "OpenPF2.Conditions.DyingRecoveryByHealing",
                     EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	UPF2CharacterAttributeSet* TestCharacterAttributeSet;
	TSubclassOf<UGameplayEffect> HealEffect;

	/**
	 * Applies healing to the test character via a Gameplay Effect (GE), increasing available hit points.
	 *
	 * @param HealingAmount
	 *	The amount of healing to apply.
	 */
	void HealTestCharacter(const float HealingAmount) const;
END_DEFINE_PF_SPEC(FPF2ConditionsDyingRecoveryByHealing)

void FPF2ConditionsDyingRecoveryByHealing::Define()
{
	static TSubclassOf<UGameplayAbility> BP_ConditionCheck_Ability;
	static TSubclassOf<UGameplayEffect>  BP_Unconscious_Effect,
	                                     BP_Wounded1_Effect,
	                                     BP_Wounded2_Effect,
	                                     BP_Wounded3_Effect,
	                                     BP_Wounded4_Effect,
	                                     BP_Dying1_Effect,
	                                     BP_Dying2_Effect,
	                                     BP_Dying3_Effect,
	                                     BP_Dying4_Effect;

	BeforeAll([&, this]
	{
		this->HealEffect = this->LoadBlueprint<UGameplayEffect>("/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime", "GE_Heal");

		BP_ConditionCheck_Ability = this->LoadBlueprint<UGameplayAbility>(
			"/OpenPF2/OpenPF2/Core",
			"GA_ConditionCheck"
		);

		BP_Unconscious_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Unconscious"
		);

		BP_Wounded1_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Wounded_Level1"
		);

		BP_Wounded2_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Wounded_Level2"
		);

		BP_Wounded3_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Wounded_Level3"
		);

		BP_Wounded4_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Wounded_Level4"
			);

		BP_Dying1_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Dying_Level1"
		);

		BP_Dying2_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Dying_Level2"
		);

		BP_Dying3_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Dying_Level3"
		);

		BP_Dying4_Effect = this->LoadBlueprint<UGameplayEffect>(
			"/OpenPF2/OpenPF2/Core/GameplayEffects/Anytime",
			"GE_Condition_Dying_Level4"
		);
	});

	LET(
		GameplayEffectsToApplyBeforeTest,
		TArray<TSubclassOf<UGameplayEffect>>,
		[],
		{ return TArray<TSubclassOf<UGameplayEffect>>(); }
	);

	BeforeEach([=, this]
	{
		this->SetupWorld();
		this->SetupTestCharacter();

		this->BeginPlay();

		this->TestCharacterAttributeSet =
			const_cast<UPF2CharacterAttributeSet*>(this->TestCharacterAsc->GetSet<UPF2CharacterAttributeSet>());

		// Ensure the character starts out already dying.
		this->TestCharacterAttributeSet->HitPoints = 0;
		// ReSharper disable once CppExpressionWithoutSideEffects
		this->ApplyGameplayEffectToTestCharacter(BP_Unconscious_Effect);

		// Ensure character is checking conditions so that tag updates happen as expected.
		this->GrantCharacterAbility(this->TestCharacter, BP_ConditionCheck_Ability);

		for (const TSubclassOf<UGameplayEffect>& Effect : *GameplayEffectsToApplyBeforeTest)
		{
			// ReSharper disable once CppExpressionWithoutSideEffects
			this->ApplyGameplayEffectToTestCharacter(Effect);
		}

		this->HealTestCharacter(1.0f);
	});

	AfterEach([=, this]
	{
		this->DestroyTestCharacter();
		this->DestroyWorld();
	});

	Describe("when a character has a 'PF2_Trait_Condition_Dying_1' gameplay tag", [=, this]
	{
		REDEFINE_LET(
			GameplayEffectsToApplyBeforeTest,
			TArray<TSubclassOf<UGameplayEffect>>,
			[],
			{ return TArray({ BP_Dying1_Effect }); }
		);

		Describe("when the character receives healing", [=, this]
		{
			Describe("when the character does not have any 'PF2_Trait_Condition_Wounded' tags", [=, this]
			{
				It("removes the 'PF2_Trait_Condition_Dying_1' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_1' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 1);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_1' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded1_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_1' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_2' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 2);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_2' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded2_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_1' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_3' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 3);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_3' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded3_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_1' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_4' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 4);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_4' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded4_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_1' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("retains the 'PF2_Trait_Condition_Wounded_4' gameplay tag on the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 4);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});
		});
	});

	Describe("when a character has a 'PF2_Trait_Condition_Dying_2' gameplay tag", [=, this]
	{
		REDEFINE_LET(
			GameplayEffectsToApplyBeforeTest,
			TArray<TSubclassOf<UGameplayEffect>>,
			[],
			{ return TArray({ BP_Dying2_Effect }); }
		);

		Describe("when the character receives healing", [=, this]
		{
			Describe("when the character does not have any 'PF2_Trait_Condition_Wounded' tags", [=, this]
			{
				It("removes the 'PF2_Trait_Condition_Dying_2' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_1' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 1);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_1' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded1_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_2' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_2' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 2);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_2' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded2_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_2' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_3' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 3);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_3' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded3_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_2' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_4' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 4);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_4' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded4_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_2' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("retains the 'PF2_Trait_Condition_Wounded_4' gameplay tag on the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 4);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});
		});
	});

	Describe("when a character has a 'PF2_Trait_Condition_Dying_3' gameplay tag (DC: 10 + 3 = 13)", [=, this]
	{
		REDEFINE_LET(
			GameplayEffectsToApplyBeforeTest,
			TArray<TSubclassOf<UGameplayEffect>>,
			[],
			{ return TArray({ BP_Dying3_Effect }); }
		);

		Describe("when the character receives healing", [=, this]
		{
			Describe("when the character does not have any 'PF2_Trait_Condition_Wounded' tags", [=, this]
			{
				It("removes the 'PF2_Trait_Condition_Dying_3' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_1' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 1);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_1' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded1_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_3' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_2' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 2);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_2' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded2_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_3' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_3' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 3);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_3' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded3_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_3' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("applies the 'PF2_Trait_Condition_Wounded_4' gameplay tag to the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 4);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});

			Describe("when the character has the 'PF2_Trait_Condition_Wounded_4' tag", [=, this]
			{
				REDEFINE_LET(
					GameplayEffectsToApplyBeforeTest,
					TArray<TSubclassOf<UGameplayEffect>>,
					[],
					{ return PF2ArrayUtilities::Concatenate(**Previous, TArray({ BP_Wounded4_Effect })); }
				);

				It("removes the 'PF2_Trait_Condition_Dying_3' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionDying);
				});

				It("retains the 'PF2_Trait_Condition_Wounded_4' gameplay tag on the character", [=, this]
				{
					TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionWounded, 4);
				});

				It("removes the 'PF2_Trait_Condition_Unconscious' gameplay tag from the character", [=, this]
				{
					TestCharacterNotHaveCondition(this->TestCharacter, Pf2TagTraitConditionUnconscious);
				});
			});
		});
	});

	Describe("when a character has a 'PF2_Trait_Condition_Dying_4' gameplay tag (DC: 10 + 4 = 14)", [=, this]
	{
		REDEFINE_LET(
			GameplayEffectsToApplyBeforeTest,
			TArray<TSubclassOf<UGameplayEffect>>,
			[],
			{ return TArray({ BP_Dying4_Effect }); }
		);

		Describe("when the character receives healing", [=, this]
		{
			It("has no effect because the character is already dead", [=, this]
			{
				TestCharacterHasConditionLevel(this->TestCharacter, Pf2TagTraitConditionDying, 4);
				TestCharacterHasCondition(this->TestCharacter, Pf2TagTraitConditionDead);
			});
		});
	});
}

void FPF2ConditionsDyingRecoveryByHealing::HealTestCharacter(const float HealingAmount) const
{
	const FGameplayEffectSpecHandle EffectSpecHandle =
		this->BuildEffectSpec(
			this->HealEffect,
			{
				{Pf2TagGameplayEffectParameterHealing, HealingAmount},
			}
		);

	this->TestCharacterAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
}
