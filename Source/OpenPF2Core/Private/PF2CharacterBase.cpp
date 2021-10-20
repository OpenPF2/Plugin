// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2CharacterBase.h"

#include "Abilities/PF2AbilitySystemComponent.h"

#include <AbilitySystemGlobals.h>
#include <Net/UnrealNetwork.h>
#include <UObject/ConstructorHelpers.h>

#include "Abilities/PF2GameplayAbilityTargetData_BoostAbility.h"
#include "Abilities/PF2GameplayAbility_BoostAbilityBase.h"

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

FORCEINLINE IPF2CharacterAbilitySystemComponentInterface* APF2CharacterBase::GetCharacterAbilitySystemComponent() const
{
	// Too bad that ASCs in UE don't implement an interface; otherwise we could extend it so casts like this aren't
	// needed.
	IPF2CharacterAbilitySystemComponentInterface* CharacterAsc =
		Cast<IPF2CharacterAbilitySystemComponentInterface>(this->AbilitySystemComponent);

	check(CharacterAsc);
	return CharacterAsc;
}

bool APF2CharacterBase::IsAuthorityForEffects() const
{
	return (this->GetLocalRole() == ROLE_Authority);
}

int32 APF2CharacterBase::GetCharacterLevel() const
{
	return this->CharacterLevel;
}

TArray<UPF2GameplayAbility_BoostAbilityBase *> APF2CharacterBase::GetPendingAbilityBoosts() const
{
	return this->GetCharacterAbilitySystemComponent()->GetPendingAbilityBoosts();
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

void APF2CharacterBase::HandleCharacterLevelChanged(const float OldLevel, const float NewLevel)
{
	this->DeactivatePassiveGameplayEffects();

	this->CharacterLevel = NewLevel;
	this->OnCharacterLevelChanged(OldLevel, NewLevel);

	this->ActivatePassiveGameplayEffects();
}

void APF2CharacterBase::ApplyAbilityBoostSelections()
{
	if (this->IsAuthorityForEffects())
	{
		TArray<FPF2CharacterAbilityBoostSelection> UnmatchedAbilityBoostSelections;

		for (const auto& AbilityBoostSelection : this->AbilityBoostSelections)
		{
			TSubclassOf<UPF2GameplayAbility_BoostAbilityBase> BoostGa   = AbilityBoostSelection.BoostGameplayAbility;
			UAbilitySystemComponent*                          Asc       = this->GetAbilitySystemComponent();
			FGameplayAbilitySpec*                             BoostSpec = Asc->FindAbilitySpecFromClass(BoostGa);

			if (BoostSpec == nullptr)
			{
				UnmatchedAbilityBoostSelections.Add(AbilityBoostSelection);
			}
			else
			{
				this->ActivateAbilityBoost(BoostSpec, AbilityBoostSelection);
			}
		}

		// In case we couldn't match some, put them back into the property. This is safer than trying to modify the
		// property in place while we iterate.
		this->AbilityBoostSelections = UnmatchedAbilityBoostSelections;
	}
}

void APF2CharacterBase::ActivateAbilityBoost(FGameplayAbilitySpec* BoostSpec,
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
		UPF2GameplayAbility_BoostAbilityBase::GetTriggerTag(),
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

		CharacterAsc->ActivatePassiveGameplayEffects();
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
		this->GetCharacterAbilitySystemComponent()->DeactivatePassiveGameplayEffects();
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

		this->bManagedPassiveEffectsGenerated = true;
	}
}

void APF2CharacterBase::ClearManagedPassiveGameplayEffects()
{
	this->ManagedGameplayEffects.Empty();

	this->bManagedPassiveEffectsGenerated = false;
}
