// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AttributeSet.h"
#include "Calculations/PF2AbilityBoostCalculation.h"
#include "Tests/PF2SpecBase.h"
#include "Tests/PF2TestPawn.h"

namespace AbilityBoostTests
{
	const FString GBlueprintPath = TEXT("/OpenPF2Core/OpenPF2/Core");

	// If this is made constexp, it does not compile (see RSCPP-32172).
	// ReSharper disable once CppVariableCanBeMadeConstexpr
	const FString GBoostMmcNames[] = {
		TEXT("MMC_AbBoostCharisma"),
		TEXT("MMC_AbBoostConstitution"),
		TEXT("MMC_AbBoostDexterity"),
		TEXT("MMC_AbBoostIntelligence"),
		TEXT("MMC_AbBoostStrength"),
		TEXT("MMC_AbBoostWisdom"),
	};

	// If this is made constexp, it does not compile (see RSCPP-32172).
	// ReSharper disable once CppVariableCanBeMadeConstexpr
	const FString GBoostGeNames[] = {
		TEXT("GE_BoostAbCharisma"),
		TEXT("GE_BoostAbConstitution"),
		TEXT("GE_BoostAbDexterity"),
		TEXT("GE_BoostAbIntelligence"),
		TEXT("GE_BoostAbStrength"),
		TEXT("GE_BoostAbWisdom"),
	};
}

typedef TMap<FString, FGameplayAttributeData*> FAttributeCapture;

BEGIN_DEFINE_PF_SPEC(FPF2AbilityBoostSpec, "OpenPF2.AbilityBoosts", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	TMap<FString, TSubclassOf<UPF2AbilityBoostCalculation>> BoostMMCs;
	TMap<FString, TSubclassOf<UGameplayEffect>> BoostGEs;

	void LoadMMCs();
	void LoadGEs();

	void VerifyBoostApplied(const FString GameEffectName,
	                        const FString TargetAttributeName,
	                        const float   StartingValue,
	                        const float   ExpectedValueAfterBoost);

	void VerifyOtherBoostsUnaffected(const FString GameEffectName,
	                                 const FString TargetAttributeName);

	void VerifyBoostRemoved(const FString GameEffectName,
	                        const FString TargetAttributeName,
	                        const float   StartingValue);
END_DEFINE_PF_SPEC(FPF2AbilityBoostSpec)

void FPF2AbilityBoostSpec::LoadMMCs()
{
	for (auto& BlueprintName : AbilityBoostTests::GBoostMmcNames)
	{
		TSubclassOf<UPF2AbilityBoostCalculation> CalculationBP =
			this->LoadBlueprint<UPF2AbilityBoostCalculation>(AbilityBoostTests::GBlueprintPath, BlueprintName);

		this->BoostMMCs.Add(BlueprintName, CalculationBP);
	}
}

void FPF2AbilityBoostSpec::LoadGEs()
{
	for (auto& BlueprintName : AbilityBoostTests::GBoostGeNames)
	{
		TSubclassOf<UGameplayEffect> GameplayEffectBP =
			this->LoadBlueprint<UGameplayEffect>(AbilityBoostTests::GBlueprintPath, BlueprintName);

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
		FAttributeCapture       Attributes      = CaptureAttributes(AttributeSet);
		FGameplayAttributeData* TargetAttribute = Attributes[TargetAttributeName];

		ApplyGameEffect(*TargetAttribute, StartingValue, EffectBP);

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
		FAttributeCapture       Attributes      = CaptureAttributes(AttributeSet);
		FGameplayAttributeData* TargetAttribute = Attributes[TargetAttributeName];

		for (const auto AttributePair : Attributes)
		{
			FGameplayAttributeData& CurrentAttribute = *(AttributePair.Value);

			CurrentAttribute = 10.0f;
		}

		ApplyGameEffect(*TargetAttribute, 10.0f, EffectBP);

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

void FPF2AbilityBoostSpec::VerifyBoostRemoved(const FString GameEffectName,
                                              const FString TargetAttributeName,
                                              const float   StartingValue)
{
	const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[GameEffectName];

	if (IsValid(EffectBP))
	{
		const UPF2AttributeSet* AttributeSet    = this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
		FAttributeCapture       Attributes      = CaptureAttributes(AttributeSet);
		FGameplayAttributeData* TargetAttribute = Attributes[TargetAttributeName];

		const FActiveGameplayEffectHandle EffectHandle =
			ApplyGameEffect(*TargetAttribute, StartingValue, EffectBP);

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

void FPF2AbilityBoostSpec::Define()
{
	BeforeEach([=, this]()
	{
		this->SetupWorld();

		this->LoadMMCs();
		this->LoadGEs();

		this->TestPawn             = this->World->SpawnActor<APF2TestPawn>();
		this->PawnAbilityComponent = this->TestPawn->GetAbilitySystemComponent();

		this->BeginPlay();
	});

	AfterEach([=, this]()
	{
		if (this->TestPawn)
		{
			this->World->EditorDestroyActor(this->TestPawn, false);
		}

		this->BoostMMCs.Empty();
		this->BoostGEs.Empty();
	});

	Describe("Blueprint Loading for Ability Boost MMCs", [=, this]()
	{
		for (const auto& BlueprintName : AbilityBoostTests::GBoostMmcNames)
		{
			It(BlueprintName + " should load", [=, this]()
			{
				const TSubclassOf<UPF2AbilityBoostCalculation>& MmcBlueprint = this->BoostMMCs[BlueprintName];

				TestTrue(BlueprintName + " is not null.", IsValid(MmcBlueprint));
			});
		}
	});

	Describe("Blueprint Loading for Ability Boost GEs", [=, this]()
	{
		for (const auto& BlueprintName : AbilityBoostTests::GBoostGeNames)
		{
			It(BlueprintName + " should load", [=, this]()
			{
				const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[BlueprintName];

				TestTrue(BlueprintName + " is not null.", IsValid(EffectBP));
			});
		}
	});

	Describe("Charisma Boost", [=, this]()
	{
		const FString EffectName    = TEXT("GE_BoostAbCharisma");
		const FString AttributeName = TEXT("AbCharisma");

		Describe("when stat is below 18", [=, this]()
		{
			constexpr float StartingValue          = 10;
			constexpr float ExpectedValueWithBoost = 12;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +2 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +2", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is 18", [=, this]()
		{
			constexpr float StartingValue          = 18;
			constexpr float ExpectedValueWithBoost = 19;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is > 18", [=, this]()
		{
			constexpr float StartingValue          = 19;
			constexpr float ExpectedValueWithBoost = 20;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});
	});

	Describe("Constitution Boost", [=, this]()
	{
		const FString EffectName    = TEXT("GE_BoostAbConstitution");
		const FString AttributeName = TEXT("AbConstitution");

		Describe("when stat is below 18", [=, this]()
		{
			constexpr float StartingValue          = 10;
			constexpr float ExpectedValueWithBoost = 12;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +2 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +2", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is 18", [=, this]()
		{
			constexpr float StartingValue          = 18;
			constexpr float ExpectedValueWithBoost = 19;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is > 18", [=, this]()
		{
			constexpr float StartingValue          = 19;
			constexpr float ExpectedValueWithBoost = 20;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});
	});

	Describe("Dexterity Boost", [=, this]()
	{
		const FString EffectName    = TEXT("GE_BoostAbDexterity");
		const FString AttributeName = TEXT("AbDexterity");

		Describe("when stat is below 18", [=, this]()
		{
			constexpr float StartingValue          = 10;
			constexpr float ExpectedValueWithBoost = 12;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +2 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +2", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is 18", [=, this]()
		{
			constexpr float StartingValue          = 18;
			constexpr float ExpectedValueWithBoost = 19;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is > 18", [=, this]()
		{
			constexpr float StartingValue          = 19;
			constexpr float ExpectedValueWithBoost = 20;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});
	});

	Describe("Intelligence Boost", [=, this]()
	{
		const FString EffectName    = TEXT("GE_BoostAbIntelligence");
		const FString AttributeName = TEXT("AbIntelligence");

		Describe("when stat is below 18", [=, this]()
		{
			constexpr float StartingValue          = 10;
			constexpr float ExpectedValueWithBoost = 12;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +2 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +2", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is 18", [=, this]()
		{
			constexpr float StartingValue          = 18;
			constexpr float ExpectedValueWithBoost = 19;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is > 18", [=, this]()
		{
			constexpr float StartingValue          = 19;
			constexpr float ExpectedValueWithBoost = 20;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});
	});

	Describe("Strength Boost", [=, this]()
	{
		const FString EffectName    = TEXT("GE_BoostAbStrength");
		const FString AttributeName = TEXT("AbStrength");

		Describe("when stat is below 18", [=, this]()
		{
			constexpr float StartingValue          = 10;
			constexpr float ExpectedValueWithBoost = 12;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +2 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +2", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is 18", [=, this]()
		{
			constexpr float StartingValue          = 18;
			constexpr float ExpectedValueWithBoost = 19;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is > 18", [=, this]()
		{
			constexpr float StartingValue          = 19;
			constexpr float ExpectedValueWithBoost = 20;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});
	});

	Describe("Wisdom Boost", [=, this]()
	{
		const FString EffectName    = TEXT("GE_BoostAbWisdom");
		const FString AttributeName = TEXT("AbWisdom");

		Describe("when stat is below 18", [=, this]()
		{
			constexpr float StartingValue          = 10;
			constexpr float ExpectedValueWithBoost = 12;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +2 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +2", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is 18", [=, this]()
		{
			constexpr float StartingValue          = 18;
			constexpr float ExpectedValueWithBoost = 19;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});

		Describe("when stat is > 18", [=, this]()
		{
			constexpr float StartingValue          = 19;
			constexpr float ExpectedValueWithBoost = 20;

			Describe("when GE is applied", [=, this]()
			{
				It("applies a boost of +1 to the current value", [=, this]()
				{
					VerifyBoostApplied(EffectName, AttributeName, StartingValue, ExpectedValueWithBoost);
				});

				It("dost not boost any other attributes", [=, this]()
				{
					VerifyOtherBoostsUnaffected(EffectName, AttributeName);
				});
			});

			Describe("when GE is removed after being applied", [=, this]()
			{
				It("removes a boost of +1", [=, this]()
				{
					VerifyBoostRemoved(EffectName, AttributeName, StartingValue);
				});
			});
		});
	});
}
