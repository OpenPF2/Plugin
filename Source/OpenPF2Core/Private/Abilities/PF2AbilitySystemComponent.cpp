// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AbilitySystemComponent.h"

#include <UObject/ConstructorHelpers.h>

#include "PF2ArrayUtilities.h"
#include "PF2CharacterConstants.h"
#include "PF2CharacterInterface.h"
#include "PF2EnumUtilities.h"

UPF2AbilitySystemComponent::UPF2AbilitySystemComponent()
{
	const FString DynamicTagsGeFilename =
		PF2CharacterConstants::GetBlueprintPath(*PF2CharacterConstants::GeDynamicTagsName);

	const ConstructorHelpers::FObjectFinder<UClass> DynamicTagsGeFinder(*DynamicTagsGeFilename);

	this->DynamicTagsEffect = DynamicTagsGeFinder.Object;

	for (const auto& Ability : TEnumRange<EPF2CharacterAbilityScoreType>())
	{
		const FString AbilityName = PF2EnumUtilities::ToString(Ability);

		const FString Filename =
			PF2CharacterConstants::GetBlueprintPath(
				FName(FString::Format(*PF2CharacterConstants::GeBlueprintBoostNameFormat, {AbilityName}))
			);

		const ConstructorHelpers::FObjectFinder<UClass> BoostGeFinder(*Filename);

		// Allow boost effects to be looked-up by ability name later.
		this->AbilityBoostEffects.Add(Ability, BoostGeFinder.Object);
	}
}

void UPF2AbilitySystemComponent::AddPassiveGameplayEffect(const TSubclassOf<UGameplayEffect> Effect)
{
	const FName WeightGroup = PF2GameplayAbilityUtilities::GetWeightGroupOfGameplayEffect(Effect);

	this->AddPassiveGameplayEffectWithWeight(WeightGroup, Effect);
}

void UPF2AbilitySystemComponent::AddPassiveGameplayEffectWithWeight(
	const FName                        WeightGroup,
	const TSubclassOf<UGameplayEffect> Effect)
{
	// Special case: If this is the first time a GE from this weight group is being added, and other weight groups are
	// active, let's assume that we want to enable the new weight group.
	if ((this->PassiveGameplayEffects.Num(WeightGroup) == 0) && this->ArePassiveGameplayEffectsActive())
	{
		this->ActivatedWeightGroups.Add(WeightGroup);
	}

	this->InvokeAndReapplyPassiveGEsInSubsequentWeightGroups(WeightGroup, [this, WeightGroup, Effect]
	{
		this->PassiveGameplayEffects.Add(WeightGroup, Effect);

		if (this->ActivatedWeightGroups.Contains(WeightGroup))
		{
			// Activate the new passive GE since it's being put into an active group.
			this->ActivatePassiveGameplayEffect(WeightGroup, Effect);
		}
	});
}

void UPF2AbilitySystemComponent::SetPassiveGameplayEffects(const TMultiMap<FName, TSubclassOf<UGameplayEffect>> Effects)
{
	this->InvokeAndReapplyAllPassiveGEs([this, Effects]
	{
		this->PassiveGameplayEffects = Effects;
	});
}

void UPF2AbilitySystemComponent::RemoveAllPassiveGameplayEffects()
{
	this->DeactivateAllPassiveGameplayEffects();
	this->PassiveGameplayEffects.Empty();
}

void UPF2AbilitySystemComponent::ActivateAllPassiveGameplayEffects()
{
	const TMultiMap<FName, TSubclassOf<UGameplayEffect>> EffectsToApply = this->BuildPassiveGameplayEffectsToApply();

	TSet<FName> AllWeightGroups,
	            InactiveGroups;

	EffectsToApply.GetKeys(AllWeightGroups);

	InactiveGroups = AllWeightGroups.Difference(this->ActivatedWeightGroups);

	for (const auto& EffectInfo : EffectsToApply)
	{
		const FName CurrentWeightGroup = EffectInfo.Key;

		if (InactiveGroups.Contains(CurrentWeightGroup))
		{
			const TSubclassOf<UGameplayEffect> GameplayEffect = EffectInfo.Value;

			this->ActivatePassiveGameplayEffect(CurrentWeightGroup, GameplayEffect);

			this->ActivatedWeightGroups.Add(CurrentWeightGroup);
		}
	}
}

TSet<FName> UPF2AbilitySystemComponent::ActivatePassiveGameplayEffectsAfter(const FName WeightGroup)
{
	const TMultiMap<FName, TSubclassOf<UGameplayEffect>> EffectsToApply = this->BuildPassiveGameplayEffectsToApply();

	TSet<FName> AllWeightGroups,
	            InactiveGroups,
	            ActivatedGroups;

	EffectsToApply.GetKeys(AllWeightGroups);

	InactiveGroups = AllWeightGroups.Difference(this->ActivatedWeightGroups);

	for (const auto& EffectInfo : EffectsToApply)
	{
		const FName CurrentWeightGroup = EffectInfo.Key;

		if (InactiveGroups.Contains(CurrentWeightGroup) && WeightGroup.LexicalLess(CurrentWeightGroup))
		{
			const TSubclassOf<UGameplayEffect> GameplayEffect = EffectInfo.Value;

			this->ActivatePassiveGameplayEffect(CurrentWeightGroup, GameplayEffect);

			this->ActivatedWeightGroups.Add(CurrentWeightGroup);
			ActivatedGroups.Add(CurrentWeightGroup);
		}
	}

	return ActivatedGroups;
}

void UPF2AbilitySystemComponent::DeactivateAllPassiveGameplayEffects()
{
	FGameplayEffectQuery Query;

	Query.EffectSource = this;

	this->RemoveActiveEffects(Query);
	this->ActivatedWeightGroups.Empty();
}

TSet<FName> UPF2AbilitySystemComponent::DeactivatePassiveGameplayEffectsAfter(const FName WeightGroup)
{
	const TMultiMap<FName, TSubclassOf<UGameplayEffect>> EffectsToApply = this->BuildPassiveGameplayEffectsToApply();

	TSet<FName>           AllWeightGroups,
	                      TargetWeightGroupNames;
	FGameplayTagContainer TargetWeightGroupTags;
	FGameplayEffectQuery  Query;

	EffectsToApply.GetKeys(AllWeightGroups);

	for (auto& CurrentWeightGroup : AllWeightGroups)
	{
		if (WeightGroup.LexicalLess(CurrentWeightGroup))
		{
			TargetWeightGroupNames.Add(CurrentWeightGroup);
			TargetWeightGroupTags.AddTag(PF2GameplayAbilityUtilities::GetTag(CurrentWeightGroup));
		}
	}

	Query.EffectSource   = this;
	Query.EffectTagQuery = FGameplayTagQuery::MakeQuery_MatchAnyTags(TargetWeightGroupTags);

	this->RemoveActiveEffects(Query);

	return TargetWeightGroupNames;
}

void UPF2AbilitySystemComponent::ActivatePassiveGameplayEffect(
	const FName                        WeightGroup,
	const TSubclassOf<UGameplayEffect> GameplayEffect)
{
	FGameplayEffectContextHandle EffectContext = this->MakeEffectContext();
	FGameplayEffectSpecHandle    NewHandle;
	FGameplayEffectSpec*         GameplayEffectSpec;

	EffectContext.AddSourceObject(this);

	NewHandle = this->MakeOutgoingSpec(
		GameplayEffect,
		this->GetCharacterLevel(),
		EffectContext
	);

	GameplayEffectSpec = NewHandle.Data.Get();

	// Ensure that the GE spec is tagged with its weight no matter how the weight was set (either through API or through
	// a tag in the InheritableGameplayEffectTags field on the GE definition class itself). Without this, only the tag
	// from the GE definition spec would pass through.
	GameplayEffectSpec->DynamicAssetTags.AddTag(PF2GameplayAbilityUtilities::GetTag(WeightGroup));

	if (GameplayEffect->GetName() == PF2CharacterConstants::GeDynamicTagsClassName)
	{
		GameplayEffectSpec->DynamicGrantedTags.AppendTags(this->DynamicTags);
	}

	if (NewHandle.IsValid())
	{
		this->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpec, this);
	}
}

void UPF2AbilitySystemComponent::AddDynamicTag(const FGameplayTag Tag)
{
	this->InvokeAndReapplyAllPassiveGEs([this, Tag]
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
	this->InvokeAndReapplyAllPassiveGEs([this, Tags]
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
	this->InvokeAndReapplyAllPassiveGEs([this, Tags]
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
	this->InvokeAndReapplyAllPassiveGEs([this, Tag]
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
	this->InvokeAndReapplyAllPassiveGEs([this, Tags]
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
	this->InvokeAndReapplyAllPassiveGEs([this]
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
	const TSubclassOf<UGameplayEffect> BoostEffect = this->AbilityBoostEffects[TargetAbilityScore];

	// Allow boost GE to override the default weight group.
	const FName WeightGroup =
		PF2GameplayAbilityUtilities::GetWeightGroupOfGameplayEffect(
			BoostEffect,
			PF2CharacterConstants::GeWeightGroups::AbilityBoosts
		);

	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("Applying a boost to ability ('%s') through ASC for character ('%s') via GE ('%s')."),
		*(PF2EnumUtilities::ToString(TargetAbilityScore)),
		*(this->GetOwnerActor()->GetName()),
		*(BoostEffect->GetName())
	);

	this->AddPassiveGameplayEffectWithWeight(WeightGroup, BoostEffect);
}

FORCEINLINE TSubclassOf<UGameplayEffect> UPF2AbilitySystemComponent::GetBoostEffectForAbility(
	const EPF2CharacterAbilityScoreType AbilityScore)
{
	return this->AbilityBoostEffects[AbilityScore];
}

TArray<UPF2GameplayAbility_BoostAbilityBase*> UPF2AbilitySystemComponent::GetPendingAbilityBoosts() const
{
	TArray<UPF2GameplayAbility_BoostAbilityBase*> MatchingGameplayAbilities;
	TArray<FGameplayAbilitySpec*>                 MatchingGameplayAbilitySpecs;

	this->GetActivatableGameplayAbilitySpecsByAllMatchingTags(
		FGameplayTagContainer(PF2GameplayAbilityUtilities::GetTag(FName("GameplayAbility.ApplyAbilityBoost"))),
		MatchingGameplayAbilitySpecs,
		false
	);

	MatchingGameplayAbilities =
		PF2ArrayUtilities::Map<UPF2GameplayAbility_BoostAbilityBase*>(
			MatchingGameplayAbilitySpecs,
			[](const FGameplayAbilitySpec* AbilitySpec)
			{
				return Cast<UPF2GameplayAbility_BoostAbilityBase>(AbilitySpec->Ability);
			}
		);

	return MatchingGameplayAbilities;
}

TMap<EPF2CharacterAbilityScoreType, FPF2AttributeModifierSnapshot> UPF2AbilitySystemComponent::GetAbilityScoreValues() const
{
	const UPF2AttributeSet* AttributeSet =
		Cast<UPF2AttributeSet>(this->GetAttributeSubobject(UPF2AttributeSet::StaticClass()));

	const TMap<EPF2CharacterAbilityScoreType, FPF2AttributeModifierSnapshot> Values =
		{
			{
				EPF2CharacterAbilityScoreType::AbStrength,
				FPF2AttributeModifierSnapshot(
					AttributeSet->AbStrength.GetCurrentValue(),
					AttributeSet->AbStrengthModifier.GetCurrentValue()
				)
			},
			{
				EPF2CharacterAbilityScoreType::AbDexterity,
				FPF2AttributeModifierSnapshot(
					AttributeSet->AbDexterity.GetCurrentValue(),
					AttributeSet->AbDexterityModifier.GetCurrentValue()
				)
			},
			{
				EPF2CharacterAbilityScoreType::AbConstitution,
				FPF2AttributeModifierSnapshot(
					AttributeSet->AbConstitution.GetCurrentValue(),
					AttributeSet->AbConstitutionModifier.GetCurrentValue()
				)
			},
			{
				EPF2CharacterAbilityScoreType::AbIntelligence,
				FPF2AttributeModifierSnapshot(
					AttributeSet->AbIntelligence.GetCurrentValue(),
					AttributeSet->AbIntelligenceModifier.GetCurrentValue()
				)
			},
			{
				EPF2CharacterAbilityScoreType::AbWisdom,
				FPF2AttributeModifierSnapshot(
					AttributeSet->AbWisdom.GetCurrentValue(),
					AttributeSet->AbWisdomModifier.GetCurrentValue()
				)
			},
			{
				EPF2CharacterAbilityScoreType::AbCharisma,
				FPF2AttributeModifierSnapshot(
					AttributeSet->AbCharisma.GetCurrentValue(),
					AttributeSet->AbCharismaModifier.GetCurrentValue()
				)
			},
		};

	return Values;
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

TMultiMap<FName, TSubclassOf<UGameplayEffect>> UPF2AbilitySystemComponent::BuildPassiveGameplayEffectsToApply() const
{
	TMultiMap<FName, TSubclassOf<UGameplayEffect>> EffectsToApply = this->PassiveGameplayEffects;

	// Add a pseudo-GE for the dynamic tags.
	EffectsToApply.Add(PF2CharacterConstants::GeWeightGroups::InitializeBaseStats, this->DynamicTagsEffect);

	// Ensure Passive GEs are always evaluated in weight order.
	EffectsToApply.KeyStableSort(FNameLexicalLess());

	return EffectsToApply;
}

template <typename Func>
void UPF2AbilitySystemComponent::InvokeAndReapplyAllPassiveGEs(const Func Callable)
{
	const bool WasActive = this->ArePassiveGameplayEffectsActive();

	if (WasActive)
	{
		this->DeactivateAllPassiveGameplayEffects();
	}

	Callable();

	if (WasActive)
	{
		this->ActivateAllPassiveGameplayEffects();
	}
}

template<typename Func>
void UPF2AbilitySystemComponent::InvokeAndReapplyPassiveGEsInSubsequentWeightGroups(
	const TSubclassOf<UGameplayEffect> Effect,
	const Func Callable)
{
	FName WeightGroup = PF2GameplayAbilityUtilities::GetWeightGroupOfGameplayEffect(Effect);

	this->InvokeAndReapplyPassiveGEsInSubsequentWeightGroups(WeightGroup, Callable);
}


template <typename Func>
void UPF2AbilitySystemComponent::InvokeAndReapplyPassiveGEsInSubsequentWeightGroups(
	const FName WeightGroup,
	const Func Callable)
{
	// NOTE: If the group we are affecting isn't active, we don't bother to re-apply subsequent groups because they
	// won't be affected.
	const bool SubsequentGroupsWereActive =
		this->ActivatedWeightGroups.Contains(WeightGroup) &&
		(this->DeactivatePassiveGameplayEffectsAfter(WeightGroup).Num() != 0);

	Callable();

	if (SubsequentGroupsWereActive)
	{
		this->ActivatePassiveGameplayEffectsAfter(WeightGroup);
	}
}
