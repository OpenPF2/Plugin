﻿// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
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

BEGIN_DEFINE_SPEC(FPF2AbilityBoostSpec, "OpenPF2.AbilityBoosts", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	UWorld *World;
	APF2TestPawn* TestPawn;
	UAbilitySystemComponent* PawnAbilityComponent;
	TMap<FString, TSubclassOf<UPF2AbilityBoostCalculation>> BoostMMCs;
	TMap<FString, TSubclassOf<UGameplayEffect>> BoostGEs;

protected:
	template<typename BlueprintType>
	static TSubclassOf<BlueprintType> LoadBlueprint(const FString FolderPath, const FString BlueprintName);

	void SetupWorld();
	void BeginPlay() const;
	void DestroyWorld() const;

	void LoadMMCs();
	void LoadGEs();

	template<typename Modifier_T>
	static FGameplayModifierInfo& AddModifier(UGameplayEffect* Effect,
											  FProperty* Property,
											  const EGameplayModOp::Type Op,
											  const Modifier_T& Magnitude);
END_DEFINE_SPEC(FPF2AbilityBoostSpec)

template<typename BlueprintType>
TSubclassOf<BlueprintType> FPF2AbilityBoostSpec::LoadBlueprint(const FString FolderPath, const FString BlueprintName)
{
	const FString ObjectPath =
		FString::Printf(TEXT("BlueprintGeneratedClass'%s/%s.%s_C'"), *FolderPath, *BlueprintName, *BlueprintName);

	const TSoftClassPtr<BlueprintType> ObjectClass =
		TSoftClassPtr<BlueprintType>(FSoftObjectPath(ObjectPath));

	return ObjectClass.LoadSynchronous();
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

template <typename Modifier_T>
FGameplayModifierInfo& FPF2AbilityBoostSpec::AddModifier(UGameplayEffect* Effect,
														 FProperty* Property,
														 const EGameplayModOp::Type Op,
														 const Modifier_T& Magnitude)
{
	const int32				NextIndex	= Effect->Modifiers.Num();
	FGameplayModifierInfo&	Info		= Effect->Modifiers[NextIndex];

	Effect->Modifiers.SetNum(NextIndex + 1);

	Info.ModifierMagnitude	= Magnitude;
	Info.ModifierOp			= Op;

	Info.Attribute.SetUProperty(Property);

	return Info;
}

void FPF2AbilityBoostSpec::Define()
{
	BeforeEach([this]()
	{
		this->SetupWorld();

		this->LoadMMCs();
		this->LoadGEs();

		this->TestPawn				= this->World->SpawnActor<APF2TestPawn>();
		this->PawnAbilityComponent	= this->TestPawn->GetAbilitySystemComponent();

		this->BeginPlay();
	});

	AfterEach([this]()
	{
		if (this->TestPawn)
		{
			this->World->EditorDestroyActor(this->TestPawn, false);
		}

		this->BoostMMCs.Empty();
		this->BoostGEs.Empty();
	});

	Describe("Blueprint Loading for Ability Boost MMCs", [this]()
	{
		for (const auto& BlueprintName : AbilityBoostTests::GBoostMmcNames)
		{
			It(BlueprintName + " should load", [this, BlueprintName]()
			{
				const TSubclassOf<UPF2AbilityBoostCalculation>& MmcBlueprint = this->BoostMMCs[BlueprintName];

				TestTrue(BlueprintName + " is not null.", IsValid(MmcBlueprint));
			});
		}
	});

	Describe("Blueprint Loading for Ability Boost GEs", [this]()
	{
		for (const auto& BlueprintName : AbilityBoostTests::GBoostGeNames)
		{
			It(BlueprintName + " should load", [this, BlueprintName]()
			{
				const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[BlueprintName];

				TestTrue(BlueprintName + " is not null.", IsValid(EffectBP));
			});
		}
	});

	Describe("Charisma Boost", [this]()
	{
		Describe("when stat is below 18", [this]()
		{
			It("applies a boost of +2", [this]()
			{
				const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[TEXT("GE_BoostAbCharisma")];

				if (IsValid(EffectBP))
				{
					UGameplayEffect*			GameplayEffect		= EffectBP->GetDefaultObject<UGameplayEffect>();
					constexpr float				StartingCharisma	= 10.0f;
					const UPF2AttributeSet*		AttributeSet		= this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
					UPF2AttributeSet*			MutableAttributeSet = const_cast<UPF2AttributeSet *>(AttributeSet);
					FActiveGameplayEffectHandle EffectHandle;

					MutableAttributeSet->AbCharisma = StartingCharisma;

					EffectHandle = this->PawnAbilityComponent->ApplyGameplayEffectToTarget(
						GameplayEffect,
						this->PawnAbilityComponent,
						1.0f
					);

					TestEqual(
						TEXT("Base value changed to 12"),
						this->PawnAbilityComponent->GetSet<UPF2AttributeSet>()->AbCharisma.GetBaseValue(),
						12.0f
					);

					this->PawnAbilityComponent->RemoveActiveGameplayEffect(EffectHandle);
				}
				else
				{
					AddWarning("GE is not loaded.");
				}
			});
		});

		Describe("when stat is 18", [this]()
		{
			It("applies a boost of +1", [this]()
			{
				const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[TEXT("GE_BoostAbCharisma")];

				if (IsValid(EffectBP))
				{
					UGameplayEffect*			GameplayEffect		= EffectBP->GetDefaultObject<UGameplayEffect>();
					constexpr float				StartingCharisma	= 18.0f;
					const UPF2AttributeSet*		AttributeSet		= this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
					UPF2AttributeSet*			MutableAttributeSet = const_cast<UPF2AttributeSet *>(AttributeSet);
					FActiveGameplayEffectHandle EffectHandle;

					MutableAttributeSet->AbCharisma = StartingCharisma;

					EffectHandle = this->PawnAbilityComponent->ApplyGameplayEffectToTarget(
						GameplayEffect,
						this->PawnAbilityComponent,
						1.0f
					);

					TestEqual(
						TEXT("Base value changed to 12"),
						this->PawnAbilityComponent->GetSet<UPF2AttributeSet>()->AbCharisma.GetBaseValue(),
						19.0f
					);

					this->PawnAbilityComponent->RemoveActiveGameplayEffect(EffectHandle);
				}
				else
				{
					AddWarning("GE is not loaded.");
				}
			});
		});

		Describe("when stat is > 18", [this]()
		{
			It("applies a boost of +1", [this]()
			{
				const TSubclassOf<UGameplayEffect>& EffectBP = this->BoostGEs[TEXT("GE_BoostAbCharisma")];

				if (IsValid(EffectBP))
				{
					UGameplayEffect*			GameplayEffect		= EffectBP->GetDefaultObject<UGameplayEffect>();
					constexpr float				StartingCharisma	= 19.0f;
					const UPF2AttributeSet*		AttributeSet		= this->PawnAbilityComponent->GetSet<UPF2AttributeSet>();
					UPF2AttributeSet*			MutableAttributeSet = const_cast<UPF2AttributeSet *>(AttributeSet);
					FActiveGameplayEffectHandle EffectHandle;

					MutableAttributeSet->AbCharisma = StartingCharisma;

					EffectHandle = this->PawnAbilityComponent->ApplyGameplayEffectToTarget(
						GameplayEffect,
						this->PawnAbilityComponent,
						1.0f
					);

					TestEqual(
						TEXT("Base value changed to 20"),
						this->PawnAbilityComponent->GetSet<UPF2AttributeSet>()->AbCharisma.GetBaseValue(),
						20.0f
					);

					this->PawnAbilityComponent->RemoveActiveGameplayEffect(EffectHandle);
				}
				else
				{
					AddWarning("GE is not loaded.");
				}
			});
		});

		//
		// // remove the effect
		// {
		//
		// }
		//
		// // check that the value changed back
		// Test->TestEqual(TEXT("Mana Restored"), DestComponent->GetSet<UAbilitySystemTestAttributeSet>()->Mana, StartingMana);
	});
}
