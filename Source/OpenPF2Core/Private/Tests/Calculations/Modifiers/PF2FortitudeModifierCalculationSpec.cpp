// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AttributeSet.h"
#include "Tests/PF2SpecBase.h"

BEGIN_DEFINE_PF_SPEC(FPF2FortitudeModifierCalculationSpec,
                     "OpenPF2.FortitudeModifierCalculations",
                     EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	TSubclassOf<UGameplayEffect> LoadGE() const;
END_DEFINE_PF_SPEC(FPF2FortitudeModifierCalculationSpec)

void FPF2FortitudeModifierCalculationSpec::Define()
{
	const FString SavingModAttributeFriendlyName = TEXT("Fortitude");
	const FString SavingModAttributeName         = TEXT("StFortitudeModifier");
	const FString AbModFriendlyName              = TEXT("Constitution");
	const FString AbModAttributeName             = TEXT("AbConstitutionModifier");

	TMap<float, TMap<FString, float>> ExpectedValues =
	{
		{
			-5.0f,
			{
				{"Untrained", -5.0f},
				{"Trained",   -2.0f},
				{"Expert",     0.0f},
				{"Master",     2.0f},
				{"Legendary",  4.0f},
			},
		},
		{
			0.0f,
			{
				{"Untrained",  0.0f},
				{"Trained",    3.0f},
				{"Expert",     5.0f},
				{"Master",     7.0f},
				{"Legendary",  9.0f},
			},
		},
		{
			3.0f,
			{
				{"Untrained",  3.0f},
				{"Trained",    6.0f},
				{"Expert",     8.0f},
				{"Master",    10.0f},
				{"Legendary", 12.0f},
			},
		},
	};

	BeforeEach([=, this]()
	{
		this->SetupWorld();
		this->SetupPawn();

		this->BeginPlay();
	});

	AfterEach([=, this]()
	{
		this->DestroyPawn();
		this->DestroyWorld();
	});

	for (const auto AbilityValues : ExpectedValues)
	{
		const float                AbModScore     = AbilityValues.Key;
		const TMap<FString, float> TrainingScores = AbilityValues.Value;

		Describe(FString::Format(TEXT("when the character has a {0} modifier of {1}"), {AbModFriendlyName, FString::FormatAsNumber(AbModScore)}), [=, this]()
		{
			for (const auto ProficiencyValues : TrainingScores)
			{
				const FString ProficiencyLevel  = ProficiencyValues.Key;
				const float   ExpectedSavingMod = ProficiencyValues.Value;

				Describe(FString::Format(TEXT("when the character is '{0}' in {1} saving throws"), {ProficiencyLevel, SavingModAttributeFriendlyName}), [=, this]()
				{
					It(FString::Format(TEXT("calculates a {0} saving throw of {1}"), {SavingModAttributeFriendlyName, FString::FormatAsNumber(ExpectedSavingMod)}), [=, this]()
					{
						const UPF2AttributeSet* AttributeSet = this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();

						FAttributeCapture                   Attributes      = CaptureAttributes(AttributeSet);
						FGameplayAttributeData*             AbModAttribute  = Attributes[AbModAttributeName];
						const FGameplayAttributeData*       SavingAttribute = Attributes[SavingModAttributeName];
						const TSubclassOf<UGameplayEffect>& EffectBP        = this->LoadGE();

						this->PawnAbilityComponent->AddLooseGameplayTag(
							FGameplayTag::RequestGameplayTag(
								FName(
									FString::Format(
										TEXT("SavingThrow.{0}.{1}"),
										{SavingModAttributeFriendlyName, ProficiencyLevel}
									)
								)
							)
						);

						ApplyGameEffect(*AbModAttribute, AbModScore, EffectBP);

						TestEqual(
							FString::Format(TEXT("{0}.BaseValue"), {SavingModAttributeName}),
							SavingAttribute->GetBaseValue(),
							0.0f
						);

						TestEqual(
							FString::Format(TEXT("{0}.CurrentValue"), {SavingModAttributeName}),
							SavingAttribute->GetCurrentValue(),
							ExpectedSavingMod
						);
					});
				});
			}
		});
	}
}

TSubclassOf<UGameplayEffect> FPF2FortitudeModifierCalculationSpec::LoadGE() const
{
	const FString BlueprintPath = TEXT("/OpenPF2Core/OpenPF2/Core");
	const FString BlueprintName = TEXT("GE_CalcSavingThrowModifiers");

	return this->LoadBlueprint<UGameplayEffect>(BlueprintPath, BlueprintName);
}
