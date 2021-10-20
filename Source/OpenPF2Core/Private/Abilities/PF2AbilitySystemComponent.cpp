// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AbilitySystemComponent.h"

#include <UObject/ConstructorHelpers.h>

#include "PF2ArrayUtilities.h"
#include "PF2CharacterConstants.h"
#include "PF2CharacterInterface.h"
#include "PF2EnumUtils.h"

UPF2AbilitySystemComponent::UPF2AbilitySystemComponent() : bPassiveEffectsActivated(false)
{
	const FString DynamicTagsGeFilename =
		PF2CharacterConstants::GetBlueprintPath(*PF2CharacterConstants::GeDynamicTagsName);

	const ConstructorHelpers::FObjectFinder<UClass> DynamicTagsGeFinder(*DynamicTagsGeFilename);

	this->DynamicTagsEffect = DynamicTagsGeFinder.Object;

	for (const auto& Ability : TEnumRange<EPF2CharacterAbilityScoreType>())
	{
		const FString AbilityName = PF2EnumUtils::ToString(Ability);

		const FString Filename =
			PF2CharacterConstants::GetBlueprintPath(
				FString::Format(*PF2CharacterConstants::GeBlueprintBoostNameFormat, {AbilityName})
			);

		const ConstructorHelpers::FObjectFinder<UClass> BoostGeFinder(*Filename);

		// Allow boost effects to be looked-up by ability name later.
		this->AbilityBoostEffects.Add(Ability, BoostGeFinder.Object);
	}
}

void UPF2AbilitySystemComponent::AddPassiveGameplayEffect(const int32 Weight, const TSubclassOf<UGameplayEffect> Effect)
{
	this->InvokeAndReapplyPassiveGEs([this, Weight, Effect]
	{
		this->PassiveGameplayEffects.Add(Weight, Effect);
	});
}

void UPF2AbilitySystemComponent::SetPassiveGameplayEffects(const TMultiMap<int32, TSubclassOf<UGameplayEffect>> Effects)
{
	this->InvokeAndReapplyPassiveGEs([this, Effects]
	{
		this->PassiveGameplayEffects = Effects;
	});
}

void UPF2AbilitySystemComponent::RemoveAllPassiveGameplayEffects()
{
	this->DeactivatePassiveGameplayEffects();
	this->PassiveGameplayEffects.Empty();
}

void UPF2AbilitySystemComponent::ActivatePassiveGameplayEffects()
{
	if (!this->bPassiveEffectsActivated)
	{
		TMultiMap<int32, TSubclassOf<UGameplayEffect>> EffectsToApply = this->PassiveGameplayEffects;

		// Add a pseudo-GE for the dynamic tags.
		EffectsToApply.Add(PF2CharacterConstants::GeWeights::InitializeBaseStats, this->DynamicTagsEffect);

		// Ensure Passive GEs are always evaluated in weight order.
		EffectsToApply.KeyStableSort(TLess<int32>());

		for (const auto& EffectInfo : this->PassiveGameplayEffects)
		{
			const TSubclassOf<UGameplayEffect> GameplayEffect     = EffectInfo.Value;
			FGameplayEffectContextHandle       EffectContext      = this->MakeEffectContext();
			FGameplayEffectSpecHandle          NewHandle;
			FGameplayEffectSpec*               GameplayEffectSpec;

			// TODO: Confirm it's all right for the source object to be the ASC rather than the character. In the Action
			// RPG sample, the source was the actor, but it seems like as long as we're consistent about it here and in
			// DeactivatePassiveGameplayEffects, it doesn't matter. It feels cleaner to use the ASC since the ASC is
			// what actually manages and applies the passive GEs.
			EffectContext.AddSourceObject(this);

			NewHandle = this->MakeOutgoingSpec(
				GameplayEffect,
				this->GetCharacterLevel(),
				EffectContext
			);

			GameplayEffectSpec = NewHandle.Data.Get();

			if (GameplayEffect->GetName() == PF2CharacterConstants::GeDynamicTagsClassName)
			{
				GameplayEffectSpec->DynamicGrantedTags.AppendTags(this->DynamicTags);
			}

			if (NewHandle.IsValid())
			{
				this->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpec, this);
			}
		}

		this->bPassiveEffectsActivated = true;
	}
}

void UPF2AbilitySystemComponent::DeactivatePassiveGameplayEffects()
{
	if (this->bPassiveEffectsActivated)
	{
		FGameplayEffectQuery Query;

		// TODO: Confirm it's all right for the source object to be the ASC rather than the character. In the Action RPG
		// sample, the source was the actor, but it seems like as long as we're consistent about it here and in
		// ActivatePassiveGameplayEffects, it doesn't matter. It feels cleaner to use the ASC since the ASC is what
		// actually manages and applies the passive GEs.
		Query.EffectSource = this;

		this->RemoveActiveEffects(Query);

		this->bPassiveEffectsActivated = false;
	}
}

void UPF2AbilitySystemComponent::AddDynamicTag(const FGameplayTag Tag)
{
	this->InvokeAndReapplyPassiveGEs([this, Tag]
	{
		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Adding a dynamic tag ('%s') to ASC on character ('%s')."),
			*(Tag.ToString()),
			*(this->GetOwnerActor()->GetName())
		);

		this->DynamicTags.AddTag(Tag);
	});
}

void UPF2AbilitySystemComponent::AppendDynamicTags(const FGameplayTagContainer Tags)
{
	this->InvokeAndReapplyPassiveGEs([this, Tags]
	{
		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Adding dynamic tags ('%s') to ASC on character ('%s')."),
			*(Tags.ToString()),
			*(this->GetOwnerActor()->GetName())
		);

		this->DynamicTags.AppendTags(Tags);
	});
}

void UPF2AbilitySystemComponent::SetDynamicTags(const FGameplayTagContainer Tags)
{
	this->InvokeAndReapplyPassiveGEs([this, Tags]
	{
		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Setting all dynamic tags ('%s') in ASC on character ('%s')."),
			*(Tags.ToString()),
			*(this->GetOwnerActor()->GetName())
		);

		this->DynamicTags = Tags;
	});
}

void UPF2AbilitySystemComponent::RemoveDynamicTag(const FGameplayTag Tag)
{
	this->InvokeAndReapplyPassiveGEs([this, Tag]
	{
		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Removing a dynamic tag ('%s') from ASC on character ('%s')."),
			*(Tag.ToString()),
			*(this->GetOwnerActor()->GetName())
		);

		this->DynamicTags.RemoveTag(Tag);
	});
}

void UPF2AbilitySystemComponent::RemoveDynamicTags(const FGameplayTagContainer Tags)
{
	this->InvokeAndReapplyPassiveGEs([this, Tags]
	{
		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Removing dynamic tags ('%s') from ASC on character ('%s')."),
			*(Tags.ToString()),
			*(this->GetOwnerActor()->GetName())
		);

		this->DynamicTags.RemoveTags(Tags);
	});
}

void UPF2AbilitySystemComponent::RemoveAllDynamicTags()
{
	this->InvokeAndReapplyPassiveGEs([this]
	{
		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Removing all dynamic tags from ASC on character ('%s')."),
			*(this->GetOwnerActor()->GetName())
		);

		this->DynamicTags.Reset();
	});
}

void UPF2AbilitySystemComponent::ApplyAbilityBoost(const EPF2CharacterAbilityScoreType TargetAbilityScore)
{
	this->InvokeAndReapplyPassiveGEs([this, TargetAbilityScore]
	{
		const TSubclassOf<UGameplayEffect> BoostEffect = this->AbilityBoostEffects[TargetAbilityScore];

		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Applying a boost to ability ('%s') through ASC for character ('%s') via GE ('%s')."),
			*(PF2EnumUtils::ToString(TargetAbilityScore)),
			*(this->GetOwnerActor()->GetName()),
			*(BoostEffect->GetName())
		);

		this->PassiveGameplayEffects.Add(PF2CharacterConstants::GeWeights::ManagedEffects, BoostEffect);
	});
}

FORCEINLINE TSubclassOf<UGameplayEffect> UPF2AbilitySystemComponent::GetBoostEffectForAbility(
	const EPF2CharacterAbilityScoreType AbilityScore)
{
	return this->AbilityBoostEffects[AbilityScore];
}

TArray<UPF2GameplayAbility_BoostAbilityBase *> UPF2AbilitySystemComponent::GetPendingAbilityBoosts() const
{
	TArray<UPF2GameplayAbility_BoostAbilityBase *> MatchingGameplayAbilities;
	TArray<FGameplayAbilitySpec*>                  MatchingGameplayAbilitySpecs;

	this->GetActivatableGameplayAbilitySpecsByAllMatchingTags(
		FGameplayTagContainer(PF2GameplayAbilityUtilities::GetTag(FName("Ability.ApplyAbilityBoost"))),
		MatchingGameplayAbilitySpecs,
		false
	);

	MatchingGameplayAbilities =
		PF2ArrayUtilities::Map<UPF2GameplayAbility_BoostAbilityBase *>(
			MatchingGameplayAbilitySpecs,
			[](const FGameplayAbilitySpec* AbilitySpec)
			{
				return Cast<UPF2GameplayAbility_BoostAbilityBase>(AbilitySpec->Ability);
			}
		);

	return MatchingGameplayAbilities;
}

FORCEINLINE int UPF2AbilitySystemComponent::GetCharacterLevel() const
{
	IPF2CharacterInterface* OwningCharacter = Cast<IPF2CharacterInterface>(this->GetOwnerActor());

	if (OwningCharacter == nullptr)
	{
		return 1;
	}
	else
	{
		return OwningCharacter->GetCharacterLevel();
	}
}

template <typename Func>
void UPF2AbilitySystemComponent::InvokeAndReapplyPassiveGEs(Func Callable)
{
	const bool WasActive = this->ArePassiveGameplayEffectsActive();

	if (WasActive)
	{
		this->DeactivatePassiveGameplayEffects();
	}

	Callable();

	if (WasActive)
	{
		this->ActivatePassiveGameplayEffects();
	}
}
