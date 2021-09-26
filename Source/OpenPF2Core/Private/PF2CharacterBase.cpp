// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2CharacterBase.h"
#include "Abilities/PF2AbilitySystemComponent.h"

#include <AbilitySystemGlobals.h>
#include <Net/UnrealNetwork.h>

#include "Abilities/PF2AbilityAttributes.h"

APF2CharacterBase::APF2CharacterBase()
{
	UPF2AbilitySystemComponent* NewAbilitySystemComponent =
		this->CreateDefaultSubobject<UPF2AbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	NewAbilitySystemComponent->SetIsReplicated(true);

	this->AbilitySystemComponent     = NewAbilitySystemComponent;
	this->AttributeSet               = this->CreateDefaultSubobject<UPF2AttributeSet>(TEXT("AttributeSet"));
	this->CharacterLevel             = 1;
	this->bPassiveEffectsInitialized = false;
	this->CharacterName              = FText::FromString(TEXT("Character"));

	for (const auto& AbilityName : FPF2AbilityAttributes::GetInstance().GetAbilityNames())
	{
		this->AbilityBoosts.Add(FPF2CharacterAbilityBoostCount(AbilityName, 0));
	}
}

void APF2CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (this->AbilitySystemComponent)
	{
		this->AbilitySystemComponent->InitAbilityActorInfo(this, this);
		this->AddStartupPassiveGameplayEffects();
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

void APF2CharacterBase::AddStartupPassiveGameplayEffects()
{
	check(this->AbilitySystemComponent);

	if ((GetLocalRole() == ROLE_Authority) && !this->bPassiveEffectsInitialized)
	{
		for (const TSubclassOf<UGameplayEffect>& GameplayEffect : this->PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = this->AbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle    NewHandle;

			EffectContext.AddSourceObject(this);

			NewHandle = this->AbilitySystemComponent->MakeOutgoingSpec(
				GameplayEffect,
				this->GetCharacterLevel(),
				EffectContext
			);

			if (NewHandle.IsValid())
			{
				this->AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*NewHandle.Data.Get(),
					this->AbilitySystemComponent
				);
			}
		}

		this->bPassiveEffectsInitialized = true;
	}
}

void APF2CharacterBase::RemoveStartupPassiveGameplayEffects()
{
	check(this->AbilitySystemComponent);

	if ((GetLocalRole() == ROLE_Authority) && this->bPassiveEffectsInitialized)
	{
		FGameplayEffectQuery Query;

		Query.EffectSource = this;

		this->AbilitySystemComponent->RemoveActiveEffects(Query);

		this->bPassiveEffectsInitialized = false;
	}
}

void APF2CharacterBase::HandleCharacterLevelChanged(const float OldLevel, const float NewLevel)
{
	this->RemoveStartupPassiveGameplayEffects();

	this->CharacterLevel = NewLevel;

	this->AddStartupPassiveGameplayEffects();
}
