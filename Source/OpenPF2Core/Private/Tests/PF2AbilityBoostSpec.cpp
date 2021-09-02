// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Misc/AutomationTest.h>
#include "Abilities/PF2AttributeSet.h"
#include "Calculations/PF2AbilityBoostCalculation.h"
#include "Tests/PF2TestPawn.h"

#define GET_FIELD_CHECKED(Class, Field) FindFieldChecked<FProperty>(Class::StaticClass(), GET_MEMBER_NAME_CHECKED(Class, Field))
#define CONSTRUCT_CLASS(Class, Name) Class* Name = NewObject<Class>(GetTransientPackage(), FName(TEXT(#Name)))

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

BEGIN_DEFINE_SPEC(FPF2AbilityBoostSpec, "OpenPF2.AbilityBoosts",
                  EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	UWorld*                                                 World;
	APF2TestPawn*                                           TestPawn;
	UAbilitySystemComponent*                                PawnAbilityComponent;
	TMap<FString, TSubclassOf<UPF2AbilityBoostCalculation>> BoostMMCs;
	TMap<FString, TSubclassOf<UGameplayEffect>>             BoostGEs;

	template <typename BlueprintType>
	static TSubclassOf<BlueprintType> LoadBlueprint(const FString FolderPath, const FString BlueprintName);

	static FAttributeCapture CaptureAttributes(const UPF2AttributeSet* AttributeSet);

	void SetupWorld();
	void BeginPlay() const;
	void DestroyWorld() const;

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

	FActiveGameplayEffectHandle ApplyGameEffect(FGameplayAttributeData&             Attribute,
	                                            float                               StartingValue,
	                                            const TSubclassOf<UGameplayEffect>& EffectBP) const;
END_DEFINE_SPEC(FPF2AbilityBoostSpec)

template <typename BlueprintType>
TSubclassOf<BlueprintType> FPF2AbilityBoostSpec::LoadBlueprint(const FString FolderPath, const FString BlueprintName)
{
	const FString ObjectPath =
		FString::Printf(TEXT("BlueprintGeneratedClass'%s/%s.%s_C'"), *FolderPath, *BlueprintName, *BlueprintName);

	const TSoftClassPtr<BlueprintType> ObjectClass =
		TSoftClassPtr<BlueprintType>(FSoftObjectPath(ObjectPath));

	return ObjectClass.LoadSynchronous();
}

FAttributeCapture FPF2AbilityBoostSpec::CaptureAttributes(const UPF2AttributeSet* AttributeSet)
{
	FAttributeCapture Snapshot;

	Snapshot.Add(TEXT("AbCharisma"),     const_cast<FGameplayAttributeData *>(&AttributeSet->AbCharisma));
	Snapshot.Add(TEXT("AbConstitution"), const_cast<FGameplayAttributeData *>(&AttributeSet->AbConstitution));
	Snapshot.Add(TEXT("AbDexterity"),    const_cast<FGameplayAttributeData *>(&AttributeSet->AbDexterity));
	Snapshot.Add(TEXT("AbIntelligence"), const_cast<FGameplayAttributeData *>(&AttributeSet->AbIntelligence));
	Snapshot.Add(TEXT("AbStrength"),     const_cast<FGameplayAttributeData *>(&AttributeSet->AbStrength));
	Snapshot.Add(TEXT("AbWisdom"),       const_cast<FGameplayAttributeData *>(&AttributeSet->AbWisdom));

	return Snapshot;
}

void FPF2AbilityBoostSpec::SetupWorld()
{
	FWorldContext& WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);

	this->World = UWorld::CreateWorld(EWorldType::Game, false);

	WorldContext.SetCurrentWorld(this->World);
}

void FPF2AbilityBoostSpec::BeginPlay() const
{
	const FURL CommandLineURL;

	this->World->InitializeActorsForPlay(CommandLineURL);
	this->World->BeginPlay();
}

void FPF2AbilityBoostSpec::DestroyWorld() const
{
	GEngine->DestroyWorldContext(this->World);
	this->World->DestroyWorld(false);
}

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

			if (CurrentAttributeName != TargetAttributeName)
			{
				TestEqual(
					CurrentAttributeName + ".BaseValue",
					CurrentAttribute.GetBaseValue(),
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
	}
	else
	{
		AddWarning("GE is not loaded.");
	}
}

FActiveGameplayEffectHandle FPF2AbilityBoostSpec::ApplyGameEffect(FGameplayAttributeData&             Attribute,
                                                                  const float                         StartingValue,
                                                                  const TSubclassOf<UGameplayEffect>& EffectBP) const
{
	UGameplayEffect* GameplayEffect = EffectBP->GetDefaultObject<UGameplayEffect>();

	Attribute = StartingValue;

	const FActiveGameplayEffectHandle EffectHandle = this->PawnAbilityComponent->ApplyGameplayEffectToTarget(
		GameplayEffect,
		this->PawnAbilityComponent,
		1.0f
	);

	return EffectHandle;
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
				It("applies a boost of +2", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +2", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +2", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +2", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +2", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +2", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
				It("applies a boost of +1", [=, this]()
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
