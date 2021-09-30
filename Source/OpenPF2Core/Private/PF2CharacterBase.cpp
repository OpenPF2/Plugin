// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2CharacterBase.h"
#include "Abilities/PF2AbilitySystemComponent.h"

#include <AbilitySystemGlobals.h>
#include <Net/UnrealNetwork.h>
#include <UObject/ConstructorHelpers.h>

APF2CharacterBase::APF2CharacterBase() :
	APF2CharacterBase(TPF2CharacterComponentFactory<UPF2AbilitySystemComponent, UPF2AttributeSet>())
{
}

void APF2CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (this->AbilitySystemComponent)
	{
		this->AbilitySystemComponent->InitAbilityActorInfo(this, this);
		this->ActivatePassiveGameplayEffects();
	}
}

void APF2CharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (this->AbilitySystemComponent)
	{
		this->AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

void APF2CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APF2CharacterBase, CharacterLevel);
}

UAbilitySystemComponent* APF2CharacterBase::GetAbilitySystemComponent() const
{
	return this->AbilitySystemComponent;
}

bool APF2CharacterBase::IsAuthorityForEffects() const
{
	return (this->GetLocalRole() == ROLE_Authority);
}

int32 APF2CharacterBase::GetCharacterLevel() const
{
	return this->CharacterLevel;
}

bool APF2CharacterBase::SetCharacterLevel(const int32 NewLevel)
{
	const int32 OldLevel = this->CharacterLevel;

	if ((OldLevel != NewLevel) && (NewLevel > 0))
	{
		this->HandleCharacterLevelChanged(OldLevel, NewLevel);
		return true;
	}
	else
	{
		return false;
	}
}

void APF2CharacterBase::HandleCharacterLevelChanged(const float OldLevel, const float NewLevel)
{
	this->DeactivatePassiveGameplayEffects();

	this->CharacterLevel = NewLevel;
	this->OnCharacterLevelChanged(OldLevel, NewLevel);

	this->ActivatePassiveGameplayEffects();
}

void APF2CharacterBase::ActivatePassiveGameplayEffects()
{
	check(this->AbilitySystemComponent);

	if (this->IsAuthorityForEffects() && !this->bPassiveEffectsActivated)
	{
		this->PopulatePassiveGameplayEffects();

		for (const auto& EffectInfo : this->PassiveGameplayEffects)
		{
			const TSubclassOf<UGameplayEffect> GameplayEffect     = EffectInfo.Value;
			FGameplayEffectContextHandle       EffectContext      = this->AbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle          NewHandle;
			FGameplayEffectSpec*               GameplayEffectSpec;

			EffectContext.AddSourceObject(this);

			NewHandle = this->AbilitySystemComponent->MakeOutgoingSpec(
				GameplayEffect,
				this->GetCharacterLevel(),
				EffectContext
			);

			GameplayEffectSpec = NewHandle.Data.Get();

			if (GameplayEffect->GetName() == PF2CharacterConstants::GeDynamicTagsClassName)
			{
				this->ApplyDynamicTags(GameplayEffectSpec);
			}

			if (NewHandle.IsValid())
			{
				this->AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*GameplayEffectSpec,
					this->AbilitySystemComponent
				);
			}
		}

		this->bPassiveEffectsActivated = true;
	}
}

void APF2CharacterBase::PopulatePassiveGameplayEffects()
{
	TMultiMap<int32, TSubclassOf<UGameplayEffect>> GameplayEffects;

	this->GenerateManagedPassiveGameplayEffects();

	GameplayEffects.Append(this->CoreGameplayEffects);
	GameplayEffects.Append(this->ManagedGameplayEffects);

	for (const auto& AdditionalEffect : this->AdditionalPassiveGameplayEffects)
	{
		GameplayEffects.Add(PF2CharacterConstants::GeWeights::AdditionalEffects, AdditionalEffect);
	}

	GameplayEffects.KeyStableSort(TLess<int32>());

	this->PassiveGameplayEffects = GameplayEffects;
}

void APF2CharacterBase::ApplyDynamicTags(FGameplayEffectSpec* GameplayEffectSpec) const
{
	FGameplayTagContainer DynamicTags;

	DynamicTags.AddTag(this->Alignment);
	DynamicTags.AppendTags(this->AdditionalLanguages);
	DynamicTags.AppendTags(this->AdditionalSkillProficiencies);

	GameplayEffectSpec->DynamicGrantedTags.AppendTags(DynamicTags);
}

void APF2CharacterBase::DeactivatePassiveGameplayEffects()
{
	check(this->AbilitySystemComponent);

	if (this->IsAuthorityForEffects() && this->bPassiveEffectsActivated)
	{
		FGameplayEffectQuery Query;

		Query.EffectSource = this;

		this->AbilitySystemComponent->RemoveActiveEffects(Query);

		this->bPassiveEffectsActivated = false;
	}
}

void APF2CharacterBase::GenerateManagedPassiveGameplayEffects()
{
	if (this->IsAuthorityForEffects() && !this->bManagedPassiveEffectsGenerated)
	{
		TArray<TSubclassOf<UGameplayEffect>> BlueprintEffects = {
			this->AncestryAndHeritage,
			this->Background,
		};

		for (const auto& BlueprintEffect : BlueprintEffects)
		{
			if (*BlueprintEffect != nullptr)
			{
				this->ManagedGameplayEffects.Add(PF2CharacterConstants::GeWeights::ManagedEffects, BlueprintEffect);
			}
		}

		for (const auto& CharacterBoost : this->AdditionalAbilityBoosts)
		{
			const FString                      AttributeName = CharacterBoost.GetAttributeName();
			const int32                        BoostCount    = CharacterBoost.GetBoostCount();
			const TSubclassOf<UGameplayEffect> BoostEffect   = this->AbilityBoostEffects[AttributeName];

			for (int32 BoostIndex = 0; BoostIndex < BoostCount; ++BoostIndex)
			{
				this->ManagedGameplayEffects.Add(PF2CharacterConstants::GeWeights::ManagedEffects, BoostEffect);
			}
		}

		this->bManagedPassiveEffectsGenerated = true;
	}
}

void APF2CharacterBase::ClearManagedPassiveGameplayEffects()
{
	this->ManagedGameplayEffects.Empty();

	this->bManagedPassiveEffectsGenerated = false;
}
