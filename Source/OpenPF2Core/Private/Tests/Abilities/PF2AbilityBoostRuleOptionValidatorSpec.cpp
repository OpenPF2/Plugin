﻿// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2EnumUtils.h"

#include "Abilities/PF2AbilityBoostRuleOption.h"
#include "Abilities/PF2AbilityBoostRuleOptionValidator.h"

#include "Tests/PF2SpecBase.h"

BEGIN_DEFINE_SPEC(FPF2AbilityBoostRuleOptionValidatorSpec,
                  "OpenPF2.FPF2AbilityBoostRuleOptionValidator",
                  EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_SPEC(FPF2AbilityBoostRuleOptionValidatorSpec)

void FPF2AbilityBoostRuleOptionValidatorSpec::Define()
{
	Describe(TEXT("when there are no rule options"), [=, this]()
	{
		const TArray<FPF2AbilityBoostRuleOption> RuleOptions = {};

		Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
		{
			It(TEXT("returns `false` for all abilities"), [=, this]()
			{
				FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

				for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
				{
					TestFalse(
						FString::Format(TEXT("CanApplyAbilityBoost({0})"), { PF2EnumUtils::ToString(AbilityScoreType)}),
						Validator.CanApplyAbilityBoost(AbilityScoreType)
					);
				}
			});
		});

		Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
		{
			It(TEXT("returns 0"), [=, this]()
			{
				const FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

				TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
			});
		});

		Describe(TEXT("GetRemainingOptions()"), [=, this]()
		{
			It(TEXT("returns an empty array"), [=, this]()
			{
				FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

				TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
			});
		});
	});

	Describe(TEXT("when there is only a free ability boost rule option"), [=, this]()
	{
		const TArray<FPF2AbilityBoostRuleOption> RuleOptions = {
			FPF2AbilityBoostRuleOption(true),
		};

		Describe(TEXT("before any ability boosts have been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all ability score types"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual("RemainingOptions.Num()", RemainingOptions.Num(), 6);

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("GetRemainingOptions() contains '{0}'"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							RemainingOptions.Contains(AbilityScoreType)
						);
					}
				});
			});
		});

		Describe(TEXT("after an ability boost has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(TEXT("CanApplyAbilityBoost({0})"), { PF2EnumUtils::ToString(AbilityScoreType)}),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});
	});

	Describe(TEXT("when there is only a rule option of Strength or Dexterity"), [=, this]()
	{
		const TArray<FPF2AbilityBoostRuleOption> RuleOptions = {
			FPF2AbilityBoostRuleOption({
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			}),
		};

		Describe(TEXT("before any ability boosts have been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` only for Strength and Dexterity"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					const FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only Strength and Dexterity"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						2
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);
				});
			});
		});

		Describe(TEXT("after an ability boost has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(TEXT("CanApplyAbilityBoost({0})"), { PF2EnumUtils::ToString(AbilityScoreType)}),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});
	});

	Describe(TEXT("when there are 2 rule options: one free ability boost; one Strength or Dexterity"), [=, this]()
	{
		const TArray<FPF2AbilityBoostRuleOption> RuleOptions = {
			// 1. Free ability boost.
			FPF2AbilityBoostRuleOption(true),

			// 2. Strength or Dexterity.
			FPF2AbilityBoostRuleOption({
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			}),
		};

		Describe(TEXT("before any ability boosts have been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 2"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 2);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all ability score types"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual("RemainingOptions.Num()", RemainingOptions.Num(), 6);

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("GetRemainingOptions() contains '{0}'"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							RemainingOptions.Contains(AbilityScoreType)
						);
					}
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities except 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all abilities except 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						5
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbConstitution'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbIntelligence'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbWisdom'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbCharisma'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Constitution' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbConstitution,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Dexterity' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});

		Describe(TEXT("after a boost to 'Intelligence' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbIntelligence,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for only 'Strength' and 'Dexterity"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only 'Strength' and 'Dexterity'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						2
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Intelligence' and 'Strength' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbIntelligence,
				EPF2CharacterAbilityScoreType::AbStrength,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});
	});

	Describe(TEXT("when there are 2 rule options: one Strength or Dexterity; one free ability boost"), [=, this]()
	{
		const TArray<FPF2AbilityBoostRuleOption> RuleOptions = {
			// 1. Strength or Dexterity.
			FPF2AbilityBoostRuleOption({
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			}),

			// 2. Free ability boost.
			FPF2AbilityBoostRuleOption(true),
		};

		Describe(TEXT("before any ability boosts have been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 2"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 2);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all ability score types"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual("RemainingOptions.Num()", RemainingOptions.Num(), 6);

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("GetRemainingOptions() contains '{0}'"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							RemainingOptions.Contains(AbilityScoreType)
						);
					}
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities except 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all abilities except 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						5
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbConstitution'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbIntelligence'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbWisdom'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbCharisma'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Constitution' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbConstitution,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Dexterity' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});

		Describe(TEXT("after a boost to 'Intelligence' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbIntelligence,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for only 'Strength' and 'Dexterity"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only 'Strength' and 'Dexterity'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						2
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Intelligence' and 'Strength' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbIntelligence,
				EPF2CharacterAbilityScoreType::AbStrength,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});
	});

	Describe(TEXT("when there are 2 rule options: one Strength or Dexterity; one Dexterity or Constitution"), [=, this]()
	{
		const TArray<FPF2AbilityBoostRuleOption> RuleOptions = {
			// 1. Strength or Dexterity.
			FPF2AbilityBoostRuleOption({
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			}),

			// 2. Dexterity or Constitution.
			FPF2AbilityBoostRuleOption({
				EPF2CharacterAbilityScoreType::AbDexterity,
				EPF2CharacterAbilityScoreType::AbConstitution,
			}),
		};

		Describe(TEXT("before any ability boosts have been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for 'Strength', 'Dexterity', and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 2"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 2);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only 'Strength', 'Dexterity', and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual("RemainingOptions.Num()", RemainingOptions.Num(), 3);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbConstitution'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for 'Dexterity' and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only 'Dexterity' and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						2
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbConstitution'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Dexterity' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for 'Constitution' and 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only 'Constitution' and 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						2
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbConstitution'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Constitution' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbConstitution,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(TEXT("CanApplyAbilityBoost({0})"), { PF2EnumUtils::ToString(AbilityScoreType)}),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Dexterity' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(TEXT("CanApplyAbilityBoost({0})"), { PF2EnumUtils::ToString(AbilityScoreType)}),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});
	});

	Describe(TEXT("when there are 3 rule options: one free ability boost; one Strength or Dexterity; one Dexterity or Constitution"), [=, this]()
	{
		const TArray<FPF2AbilityBoostRuleOption> RuleOptions = {
			// 1. Free ability boost.
			FPF2AbilityBoostRuleOption(true),

			// 2. Strength or Dexterity.
			FPF2AbilityBoostRuleOption({
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			}),

			// 3. Dexterity or Constitution.
			FPF2AbilityBoostRuleOption({
				EPF2CharacterAbilityScoreType::AbDexterity,
				EPF2CharacterAbilityScoreType::AbConstitution,
			}),
		};

		Describe(TEXT("before any ability boosts have been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("CanApplyAbilityBoost({0})"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 3"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 3);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all ability score types"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual("RemainingOptions.Num()", RemainingOptions.Num(), 6);

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestTrue(
							FString::Format(
								TEXT("GetRemainingOptions() contains '{0}'"),
								{ PF2EnumUtils::ToString(AbilityScoreType)}
							),
							RemainingOptions.Contains(AbilityScoreType)
						);
					}
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities except 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 2"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 2);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all abilities except 'Strength'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						5
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbConstitution'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbIntelligence'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbWisdom'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbCharisma'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Constitution' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbConstitution,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities except 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 2"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 2);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all abilities except 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						5
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbIntelligence'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbWisdom'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbCharisma'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Constitution' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbConstitution,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities except 'Strength' and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all abilities except 'Strength' and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						4
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbIntelligence'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbWisdom'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbCharisma'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Strength' and 'Dexterity' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbStrength,
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for all abilities except 'Strength' and 'Dexterity'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns all abilities except 'Strength' and 'Dexterity'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						4
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbIntelligence'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbIntelligence'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbWisdom'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbCharisma'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Intelligence' and 'Constitution' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbIntelligence,
				EPF2CharacterAbilityScoreType::AbConstitution,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` only for 'Strength' and 'Dexterity'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only 'Strength' and 'Dexterity'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						2
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbDexterity'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbDexterity)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Intelligence' and 'Dexterity' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbIntelligence,
				EPF2CharacterAbilityScoreType::AbDexterity,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `true` for only 'Strength' and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbStrength)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbDexterity)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbDexterity)
					);

					TestTrue(
						TEXT("CanApplyAbilityBoost(AbConstitution)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbConstitution)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbIntelligence)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbIntelligence)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbWisdom)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbWisdom)
					);

					TestFalse(
						TEXT("CanApplyAbilityBoost(AbCharisma)"),
						Validator.CanApplyAbilityBoost(EPF2CharacterAbilityScoreType::AbCharisma)
					);
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 1"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 1);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns only 'Strength' and 'Constitution'"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					const TSet<EPF2CharacterAbilityScoreType> RemainingOptions = Validator.GetRemainingOptions();

					TestEqual(
						"RemainingOptions.Num()",
						RemainingOptions.Num(),
						2
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbStrength'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbStrength)
					);

					TestTrue(
						TEXT("GetRemainingOptions() contains 'AbConstitution'"),
						RemainingOptions.Contains(EPF2CharacterAbilityScoreType::AbConstitution)
					);
				});
			});
		});

		Describe(TEXT("after a boost to 'Intelligence', 'Dexterity', and 'Constitution' has been applied"), [=, this]()
		{
			const TArray<EPF2CharacterAbilityScoreType> AbilityBoostsToApply = {
				EPF2CharacterAbilityScoreType::AbIntelligence,
				EPF2CharacterAbilityScoreType::AbDexterity,
				EPF2CharacterAbilityScoreType::AbConstitution,
			};

			Describe(TEXT("CanApplyAbilityBoost()"), [=, this]()
			{
				It(TEXT("returns `false` for all abilities"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
					{
						TestFalse(
							FString::Format(TEXT("CanApplyAbilityBoost({0})"), { PF2EnumUtils::ToString(AbilityScoreType)}),
							Validator.CanApplyAbilityBoost(AbilityScoreType)
						);
					}
				});
			});

			Describe(TEXT("GetRemainingBoostCount()"), [=, this]()
			{
				It(TEXT("returns 0"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual("Validator.GetRemainingBoostCount()", Validator.GetRemainingBoostCount(), 0);
				});
			});

			Describe(TEXT("GetRemainingOptions()"), [=, this]()
			{
				It(TEXT("returns an empty array"), [=, this]()
				{
					FPF2AbilityBoostRuleOptionValidator Validator(RuleOptions);

					for (auto& AbilityScoreType : AbilityBoostsToApply)
					{
						Validator.ApplyAbilityBoost(AbilityScoreType);
					}

					TestEqual(TEXT("GetRemainingOptions().Num()"), Validator.GetRemainingOptions().Num(), 0);
				});
			});
		});
	});
}