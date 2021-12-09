// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2CharacterBase.h"

#include <AbilitySystemGlobals.h>
#include <Net/UnrealNetwork.h>
#include <UObject/ConstructorHelpers.h>

#include "Abilities/PF2AbilityBoostBase.h"
#include "Abilities/PF2AbilitySystemComponent.h"
#include "Abilities/PF2GameplayAbilityTargetData_BoostAbility.h"

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
		this->ApplyAbilityBoostSelections();
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
	check(this->AbilitySystemComponent);
	return this->AbilitySystemComponent;
}

FText APF2CharacterBase::GetCharacterName() const
{
	FText Name = this->CharacterName;

	if (Name.IsEmpty())
	{
		Name = FText::FromString(this->GetName());
	}

	return Name;
}

int32 APF2CharacterBase::GetCharacterLevel() const
{
	return this->CharacterLevel;
}

TArray<UPF2AbilityBoostBase *> APF2CharacterBase::GetPendingAbilityBoosts() const
{
	return this->GetCharacterAbilitySystemComponent()->GetPendingAbilityBoosts();
}

void APF2CharacterBase::AddAbilityBoostSelection(
	const TSubclassOf<class UPF2AbilityBoostBase> BoostGameplayAbility,
	const TSet<EPF2CharacterAbilityScoreType>     SelectedAbilities)
{
	this->AbilityBoostSelections.Add(FPF2CharacterAbilityBoostSelection(BoostGameplayAbility, SelectedAbilities));
}

void APF2CharacterBase::ApplyAbilityBoostSelections()
{
	if (this->IsAuthorityForEffects())
	{
		TArray<FPF2CharacterAbilityBoostSelection> UnmatchedAbilityBoostSelections;

		for (const auto& AbilityBoostSelection : this->AbilityBoostSelections)
		{
			TSubclassOf<UPF2AbilityBoostBase> BoostGa   = AbilityBoostSelection.BoostGameplayAbility;
			UAbilitySystemComponent*          Asc       = this->GetAbilitySystemComponent();
			FGameplayAbilitySpec*             BoostSpec = Asc->FindAbilitySpecFromClass(BoostGa);

			if (BoostSpec == nullptr)
			{
				UnmatchedAbilityBoostSelections.Add(AbilityBoostSelection);
			}
			else
			{
				this->ActivateAbilityBoost(BoostSpec, AbilityBoostSelection);

				this->AppliedAbilityBoostSelections.Add(AbilityBoostSelection);
			}
		}

		// In case we couldn't match some, put them back into the property. This is safer than trying to modify the
		// property in place while we iterate.
		this->AbilityBoostSelections = UnmatchedAbilityBoostSelections;
	}
}

FORCEINLINE void APF2CharacterBase::GetCharacterAbilitySystemComponent(
	TScriptInterface<IPF2CharacterAbilitySystemComponentInterface>& Output) const
{
	// This is weird, but the way that TScriptInterface objects work is it maintains a reference to a UObject that
	// *implements* an interface along with a pointer to the part of the UObject that provides the interface
	// implementation, so we need to provide the concrete object instead of the interface type.
	Output = this->AbilitySystemComponent;
}

FORCEINLINE IPF2CharacterAbilitySystemComponentInterface* APF2CharacterBase::GetCharacterAbilitySystemComponent() const
{
	// Too bad that ASCs in UE don't implement an interface; otherwise we could extend it so casts like this aren't
	// needed.
	IPF2CharacterAbilitySystemComponentInterface* CharacterAsc =
		Cast<IPF2CharacterAbilitySystemComponentInterface>(this->AbilitySystemComponent);

	check(CharacterAsc);
	return CharacterAsc;
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

void APF2CharacterBase::ApplyAbilityBoost(const EPF2CharacterAbilityScoreType TargetAbilityScore)
{
	this->GetCharacterAbilitySystemComponent()->ApplyAbilityBoost(TargetAbilityScore);
}

void APF2CharacterBase::RemoveRedundantPendingAbilityBoosts()
{
	if (this->IsAuthorityForEffects())
	{
		for (const auto& AbilityBoostSelection : this->AppliedAbilityBoostSelections)
		{
			TSubclassOf<UPF2AbilityBoostBase> BoostGa   = AbilityBoostSelection.BoostGameplayAbility;
			UAbilitySystemComponent*          Asc       = this->GetAbilitySystemComponent();
			FGameplayAbilitySpec*             BoostSpec = Asc->FindAbilitySpecFromClass(BoostGa);

			if (BoostSpec != nullptr)
			{
				// The player or a game designer already made a selection for this boost ability.
				Asc->ClearAbility(BoostSpec->Handle);
			}
		}
	}
}

bool APF2CharacterBase::IsAuthorityForEffects() const
{
	return (this->GetLocalRole() == ROLE_Authority);
}

void APF2CharacterBase::ActivateAbilityBoost(
	FGameplayAbilitySpec*                     BoostSpec,
	const FPF2CharacterAbilityBoostSelection& AbilityBoostSelection) const
{
	UAbilitySystemComponent*                    Asc               = this->GetAbilitySystemComponent();
	const TSet<EPF2CharacterAbilityScoreType>   SelectedAbilities = AbilityBoostSelection.SelectedAbilities;
	FPF2GameplayAbilityTargetData_BoostAbility* BoostTargetData   = new FPF2GameplayAbilityTargetData_BoostAbility();
	FGameplayAbilityTargetDataHandle            TargetDataHandle;
	FGameplayEventData                          BoostEventInfo;

	BoostSpec->RemoveAfterActivation   = true;
	BoostTargetData->SelectedAbilities = SelectedAbilities;

	TargetDataHandle.Add(BoostTargetData);

	BoostEventInfo.TargetData = TargetDataHandle;

	// Fire it up!
	Asc->TriggerAbilityFromGameplayEvent(
		BoostSpec->Handle,
		Asc->AbilityActorInfo.Get(),
		UPF2AbilityBoostBase::GetTriggerTag(),
		&BoostEventInfo,
		*Asc
	);
}

void APF2CharacterBase::ActivatePassiveGameplayEffects()
{
	IPF2CharacterAbilitySystemComponentInterface* CharacterAsc = this->GetCharacterAbilitySystemComponent();

	if (this->IsAuthorityForEffects() && !CharacterAsc->ArePassiveGameplayEffectsActive())
	{
		this->PopulatePassiveGameplayEffects();
		this->ApplyDynamicTags();

		CharacterAsc->ActivateAllPassiveGameplayEffects();

		// Ensure we do not re-prompt for boosts that have already chosen and applied to this character.
		this->RemoveRedundantPendingAbilityBoosts();
	}
}

void APF2CharacterBase::PopulatePassiveGameplayEffects()
{
	TMultiMap<FName, TSubclassOf<UGameplayEffect>> GameplayEffects;

	this->GenerateManagedPassiveGameplayEffects();

	GameplayEffects.Append(this->CoreGameplayEffects);
	GameplayEffects.Append(this->ManagedGameplayEffects);

	for (const auto& AdditionalEffect : this->AdditionalPassiveGameplayEffects)
	{
		// Allow GE to override the default weight group.
		const FName WeightGroup =
			PF2GameplayAbilityUtilities::GetWeightGroupOfGameplayEffect(
				AdditionalEffect,
				PF2CharacterConstants::GeWeightGroups::PreAbilityBoosts
			);

		GameplayEffects.Add(WeightGroup, AdditionalEffect);
	}

	this->GetCharacterAbilitySystemComponent()->SetPassiveGameplayEffects(GameplayEffects);
}

void APF2CharacterBase::ApplyDynamicTags() const
{
	FGameplayTagContainer DynamicTags;

	DynamicTags.AddTag(this->Alignment);
	DynamicTags.AppendTags(this->AdditionalLanguages);
	DynamicTags.AppendTags(this->AdditionalSkillProficiencies);

	this->GetCharacterAbilitySystemComponent()->AppendDynamicTags(DynamicTags);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APF2CharacterBase::DeactivatePassiveGameplayEffects()
{
	if (this->IsAuthorityForEffects())
	{
		this->GetCharacterAbilitySystemComponent()->DeactivateAllPassiveGameplayEffects();
	}
}

void APF2CharacterBase::GenerateManagedPassiveGameplayEffects()
{
	if (this->IsAuthorityForEffects() && !this->bManagedPassiveEffectsGenerated)
	{
		TArray<TSubclassOf<UGameplayEffect>> EffectBlueprints = {
			this->AncestryAndHeritage,
			this->Background,
		};

		for (const auto& EffectBlueprint : EffectBlueprints)
		{
			if (*EffectBlueprint != nullptr)
			{
				// Allow managed GE to override the default weight group.
				const FName WeightGroup =
					PF2GameplayAbilityUtilities::GetWeightGroupOfGameplayEffect(
						EffectBlueprint,
						PF2CharacterConstants::GeWeightGroups::ManagedEffects
					);

				this->ManagedGameplayEffects.Add(WeightGroup, EffectBlueprint);
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

void APF2CharacterBase::HandleCharacterLevelChanged(const float OldLevel, const float NewLevel)
{
	this->DeactivatePassiveGameplayEffects();

	this->CharacterLevel = NewLevel;
	this->OnCharacterLevelChanged(OldLevel, NewLevel);

	this->ActivatePassiveGameplayEffects();
}
