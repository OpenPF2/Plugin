// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AttributeSet.h"
#include "Calculations/PF2AbilityBoostCalculationBase.h"
#include "Tests/PF2SpecBase.h"

BEGIN_DEFINE_PF_SPEC(FPF2AbilityBoostSpec,
                     "OpenPF2.AbilityBoosts",
                     EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	const FString BlueprintPath = TEXT("/OpenPF2Core/OpenPF2/Core/AbilityBoosts");

	const TArray<FString> BoostMmcNames = {
		TEXT("MMC_AbBoostCharisma"),
		TEXT("MMC_AbBoostConstitution"),
		TEXT("MMC_AbBoostDexterity"),
		TEXT("MMC_AbBoostIntelligence"),
		TEXT("MMC_AbBoostStrength"),
		TEXT("MMC_AbBoostWisdom"),
	};

	const TArray<FString> BoostGeNames = {
		TEXT("GE_BoostAbCharisma"),
		TEXT("GE_BoostAbConstitution"),
		TEXT("GE_BoostAbDexterity"),
		TEXT("GE_BoostAbIntelligence"),
		TEXT("GE_BoostAbStrength"),
		TEXT("GE_BoostAbWisdom"),
	};

	TMap<FString, TSubclassOf<UPF2AbilityBoostCalculationBase>> BoostMMCs;
	TMap<FString, TSubclassOf<UGameplayEffect>> BoostGEs;

	void LoadMMCs();
	void LoadGEs();

	void VerifyBoostApplied(const FString GameEffectName,
	                        const FString TargetAttributeName,
	                        const float   StartingValue,
	                        const float   ExpectedValueAfterBoost);

	void VerifyOtherBoostsUnaffected(const FString GameEffectName,
	                                 const FString TargetAttributeName);

	void VerifyBoostCounter(FString GameEffectName, FString TargetAttributeName, int NumTimes);

	void VerifyBoostRemoved(const FString GameEffectName,
	                        const FString TargetAttributeName,
	                        const float   StartingValue);
END_DEFINE_PF_SPEC(FPF2AbilityBoostSpec)

void FPF2AbilityBoostSpec::Define()
{
	Describe("Blueprint Loading for Ability Boost MMCs", [=]()
	{
		BeforeEach([=]()
		{
			this->LoadMMCs();
		});

		AfterEach([=]()
		{
			this->BoostMMCs.Empty();
		});

		for (const auto& BlueprintName : this->BoostMmcNames)
		{
			It(BlueprintName + " should load", [=]()
			{
				const TSubclassOf<UPF2AbilityBoostCalculationBase>& MmcBlueprint = this->BoostMMCs[BlueprintName];

				TestTrue(BlueprintName + " is not null.", IsValid(MmcBlueprint));
			});
		}
	});

	Describe("Blueprint Loading for Ability Boost GEs", [=]()
	{
		BeforeEach([=]()
		{
			this->LoadGEs();
		});

		AfterEach([=]()
		{
			this->BoostGEs.Empty();
		});

		for (const auto& BlueprintName : this->BoostGeNames)
		{
			It(BlueprintName + " should load", [=]()
			{
				const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[BlueprintName];

				TestTrue(BlueprintName + " is not null.", IsValid(EffectBP));
			});
		}
	});

	Describe("Effects of Boosts", [=]()
	{
		BeforeEach([=]()
		{
			this->SetupWorld();
			this->SetupPawn();

			this->LoadGEs();

			this->BeginPlay();
		});

		AfterEach([=]()
		{
			this->DestroyPawn();
			this->DestroyWorld();

			this->BoostGEs.Empty();
		});

		Describe("Charisma Boost", [=]()
		{
			const FString EffectName    = TEXT("GE_BoostAbCharisma");
			const FString AttributeName = TEXT("AbCharisma");

			Describe("when stat is below 18", [=]()
			{
				constexpr float StartingValue          = 10;
				constexpr float ExpectedValueWithBoost = 12;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +2 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +2", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is 18", [=]()
			{
				constexpr float StartingValue          = 18;
				constexpr float ExpectedValueWithBoost = 19;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is > 18", [=]()
			{
				constexpr float StartingValue          = 19;
				constexpr float ExpectedValueWithBoost = 20;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when GE is applied once", [=]()
			{
				It("increments the boost counter by 1", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 1);
				});
			});

			Describe("when GE is applied twice", [=]()
			{
				It("increments the boost counter by 2", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 2);
				});
			});
		});

		Describe("Constitution Boost", [=]()
		{
			const FString EffectName    = TEXT("GE_BoostAbConstitution");
			const FString AttributeName = TEXT("AbConstitution");

			Describe("when stat is below 18", [=]()
			{
				constexpr float StartingValue          = 10;
				constexpr float ExpectedValueWithBoost = 12;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +2 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +2", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is 18", [=]()
			{
				constexpr float StartingValue          = 18;
				constexpr float ExpectedValueWithBoost = 19;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is > 18", [=]()
			{
				constexpr float StartingValue          = 19;
				constexpr float ExpectedValueWithBoost = 20;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when GE is applied once", [=]()
			{
				It("increments the boost counter by 1", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 1);
				});
			});

			Describe("when GE is applied twice", [=]()
			{
				It("increments the boost counter by 2", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 2);
				});
			});
		});

		Describe("Dexterity Boost", [=]()
		{
			const FString EffectName    = TEXT("GE_BoostAbDexterity");
			const FString AttributeName = TEXT("AbDexterity");

			Describe("when stat is below 18", [=]()
			{
				constexpr float StartingValue          = 10;
				constexpr float ExpectedValueWithBoost = 12;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +2 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +2", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is 18", [=]()
			{
				constexpr float StartingValue          = 18;
				constexpr float ExpectedValueWithBoost = 19;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is > 18", [=]()
			{
				constexpr float StartingValue          = 19;
				constexpr float ExpectedValueWithBoost = 20;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when GE is applied once", [=]()
			{
				It("increments the boost counter by 1", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 1);
				});
			});

			Describe("when GE is applied twice", [=]()
			{
				It("increments the boost counter by 2", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 2);
				});
			});
		});

		Describe("Intelligence Boost", [=]()
		{
			const FString EffectName    = TEXT("GE_BoostAbIntelligence");
			const FString AttributeName = TEXT("AbIntelligence");

			Describe("when stat is below 18", [=]()
			{
				constexpr float StartingValue          = 10;
				constexpr float ExpectedValueWithBoost = 12;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +2 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +2", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is 18", [=]()
			{
				constexpr float StartingValue          = 18;
				constexpr float ExpectedValueWithBoost = 19;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is > 18", [=]()
			{
				constexpr float StartingValue          = 19;
				constexpr float ExpectedValueWithBoost = 20;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when GE is applied once", [=]()
			{
				It("increments the boost counter by 1", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 1);
				});
			});

			Describe("when GE is applied twice", [=]()
			{
				It("increments the boost counter by 2", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 2);
				});
			});
		});

		Describe("Strength Boost", [=]()
		{
			const FString EffectName    = TEXT("GE_BoostAbStrength");
			const FString AttributeName = TEXT("AbStrength");

			Describe("when stat is below 18", [=]()
			{
				constexpr float StartingValue          = 10;
				constexpr float ExpectedValueWithBoost = 12;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +2 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +2", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is 18", [=]()
			{
				constexpr float StartingValue          = 18;
				constexpr float ExpectedValueWithBoost = 19;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is > 18", [=]()
			{
				constexpr float StartingValue          = 19;
				constexpr float ExpectedValueWithBoost = 20;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when GE is applied once", [=]()
			{
				It("increments the boost counter by 1", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 1);
				});
			});

			Describe("when GE is applied twice", [=]()
			{
				It("increments the boost counter by 2", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 2);
				});
			});
		});

		Describe("Wisdom Boost", [=]()
		{
			const FString EffectName    = TEXT("GE_BoostAbWisdom");
			const FString AttributeName = TEXT("AbWisdom");

			Describe("when stat is below 18", [=]()
			{
				constexpr float StartingValue          = 10;
				constexpr float ExpectedValueWithBoost = 12;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +2 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +2", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is 18", [=]()
			{
				constexpr float StartingValue          = 18;
				constexpr float ExpectedValueWithBoost = 19;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when stat is > 18", [=]()
			{
				constexpr float StartingValue          = 19;
				constexpr float ExpectedValueWithBoost = 20;

				Describe("when GE is applied", [=]()
				{
					It("applies a boost of +1 to the current value", [=]()
					{
						this->VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
					});

					It("does not boost any other attributes", [=]()
					{
						this->VerifyOtherBoostsUnaffected(EffectName, AttributeName);
					});
				});

				Describe("when GE is removed after being applied", [=]()
				{
					It("removes a boost of +1", [=]()
					{
						this->VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
					});
				});
			});

			Describe("when GE is applied once", [=]()
			{
				It("increments the boost counter by 1", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 1);
				});
			});

			Describe("when GE is applied twice", [=]()
			{
				It("increments the boost counter by 2", [=]()
				{
					this->VerifyBoostCounter(EffectName, AttributeName, 2);
				});
			});
		});
	});
}

void FPF2AbilityBoostSpec::LoadMMCs()
{
	for (auto& BlueprintName : this->BoostMmcNames)
	{
		TSubclassOf<UPF2AbilityBoostCalculationBase> CalculationBP =
			this->LoadBlueprint<UPF2AbilityBoostCalculationBase>(this->BlueprintPath, BlueprintName);

		this->BoostMMCs.Add(BlueprintName, CalculationBP);
	}
}

void FPF2AbilityBoostSpec::LoadGEs()
{
	for (auto& BlueprintName : this->BoostGeNames)
	{
		TSubclassOf<UGameplayEffect> GameplayEffectBP =
			this->LoadBlueprint<UGameplayEffect>(this->BlueprintPath, BlueprintName);

		this->BoostGEs.Add(BlueprintName, GameplayEffectBP);
	}
}

void FPF2AbilityBoostSpec::VerifyBoostApplied(const FString GameEffectName,
                                              const FString TargetAttributeName,
                                              const float   StartingValue,
                                              const float   ExpectedValueAfterBoost)
{
	const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[GameEffectName];

	if (IsValid(EffectBP))
	{
		const UPF2AttributeSet* AttributeSet    = this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
		FAttributeCapture       Attributes      = CaptureAbilityAttributes(AttributeSet);
		FGameplayAttributeData* TargetAttribute = Attributes[TargetAttributeName];

		// Sanity check test logic.
		TestNotEqual("Captured at least one ability attribute", Attributes.Num(), 0);

		this->ApplyGameEffect(*TargetAttribute, StartingValue, EffectBP);

		TestEqual(
			TargetAttributeName + ".BaseValue",
			TargetAttribute->GetBaseValue(),
			StartingValue
		);

		TestEqual(
			TargetAttributeName + ".CurrentValue",
			TargetAttribute->GetCurrentValue(),
			ExpectedValueAfterBoost
		);
	}
	else
	{
		AddWarning("GE is not loaded.");
	}
}

void FPF2AbilityBoostSpec::VerifyOtherBoostsUnaffected(const FString GameEffectName,
                                                       const FString TargetAttributeName)
{
	const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[GameEffectName];

	if (IsValid(EffectBP))
	{
		const UPF2AttributeSet* AttributeSet    = this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
		FAttributeCapture       Attributes      = CaptureAbilityAttributes(AttributeSet);
		FGameplayAttributeData* TargetAttribute = Attributes[TargetAttributeName];

		// Sanity check test logic.
		TestNotEqual("Captured at least one ability attribute", Attributes.Num(), 0);

		for (const auto AttributePair : Attributes)
		{
			FGameplayAttributeData& CurrentAttribute = *(AttributePair.Value);

			CurrentAttribute = 10.0f;
		}

		this->ApplyGameEffect(*TargetAttribute, 10.0f, EffectBP);

		for (const auto AttributePair : Attributes)
		{
			FGameplayAttributeData& CurrentAttribute     = *(AttributePair.Value);
			FString                 CurrentAttributeName = AttributePair.Key;

			if (CurrentAttributeName == TargetAttributeName)
			{
				TestEqual(
					CurrentAttributeName + ".BaseValue",
					CurrentAttribute.GetBaseValue(),
					10.0f
				);

				TestNotEqual(
					CurrentAttributeName + ".CurrentValue",
					CurrentAttribute.GetCurrentValue(),
					10.0f
				);
			}
			else
			{
				TestEqual(
					CurrentAttributeName + ".BaseValue",
					CurrentAttribute.GetBaseValue(),
					10.0f
				);

				TestEqual(
					CurrentAttributeName + ".CurrentValue",
					CurrentAttribute.GetCurrentValue(),
					10.0f
				);
			}
		}
	}
	else
	{
		AddWarning("GE is not loaded.");
	}
}

void FPF2AbilityBoostSpec::VerifyBoostCounter(const FString GameEffectName,
                                              const FString TargetAttributeName,
                                              const int NumTimes)
{
	const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[GameEffectName];

	if (IsValid(EffectBP))
	{
		const UPF2AttributeSet* AttributeSet        = this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
		FAttributeCapture       Attributes          = CaptureAttributes(AttributeSet);
		const FString           CountAttributeName  = "AbBoostCount";
		FGameplayAttributeData *TargetAttribute     = Attributes[TargetAttributeName],
		                       *BoostCountAttribute = Attributes[CountAttributeName];

		// Sanity check test logic.
		TestNotEqual("Captured at least one attribute", Attributes.Num(), 0);

		*(BoostCountAttribute) = 0.0f;

		for (int AppliedCount = 0; AppliedCount < NumTimes; ++AppliedCount)
		{
			this->ApplyGameEffect(*TargetAttribute, 10.0f, EffectBP);
		}

		TestEqual(
			CountAttributeName + ".BaseValue",
			BoostCountAttribute->GetBaseValue(),
			0.0f
		);

		TestEqual(
			CountAttributeName + ".CurrentValue",
			BoostCountAttribute->GetCurrentValue(),
			static_cast<float>(NumTimes)
		);
	}
	else
	{
		AddWarning("GE is not loaded.");
	}
}

void FPF2AbilityBoostSpec::VerifyBoostRemoved(const FString GameEffectName,
                                              const FString TargetAttributeName,
                                              const float   StartingValue)
{
	const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[GameEffectName];

	if (IsValid(EffectBP))
	{
		const UPF2AttributeSet* AttributeSet    = this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
		FAttributeCapture       Attributes      = CaptureAbilityAttributes(AttributeSet);
		FGameplayAttributeData* TargetAttribute = Attributes[TargetAttributeName];

		const FActiveGameplayEffectHandle EffectHandle =
			this->ApplyGameEffect(*TargetAttribute, StartingValue, EffectBP);

		// Sanity check test logic.
		TestNotEqual("Captured at least one ability attribute", Attributes.Num(), 0);

		this->PawnAbilityComponent->RemoveActiveGameplayEffect(EffectHandle);

		TestEqual(
			TargetAttributeName + ".BaseValue",
			TargetAttribute->GetBaseValue(),
			StartingValue
		);

		TestEqual(
			TargetAttributeName + ".CurrentValue",
			TargetAttribute->GetCurrentValue(),
			StartingValue
		);
	}
	else
	{
		AddWarning("GE is not loaded.");
	}
}
