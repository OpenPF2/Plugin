// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2GameplayAbilityBase.h"

#include <AbilitySystemGlobals.h>

#include "PF2CharacterInterface.h"
#include "PF2EffectCauseWrapper.h"
#include "PF2GameplayEffectContainer.h"
#include "PF2GameplayEffectContainerSpec.h"

#include "Items/Weapons/PF2WeaponInterface.h"

#include "Utilities/PF2InterfaceUtilities.h"

FString UPF2GameplayAbilityBase::GetIdForLogs() const
{
	return this->GetName();
}

UTexture2D* UPF2GameplayAbilityBase::GetAbilityIcon() const
{
	return this->Icon;
}

FText UPF2GameplayAbilityBase::GetAbilityLabel() const
{
	return this->Label;
}

FText UPF2GameplayAbilityBase::GetAbilityDescription() const
{
	return this->Description;
}

UGameplayAbility* UPF2GameplayAbilityBase::ToGameplayAbility()
{
	return this;
}

FGameplayAbilitySpec UPF2GameplayAbilityBase::ToGameplayAbilitySpecForCharacter(
	const TScriptInterface<IPF2CharacterInterface> Character,
	bool& bOutSpecFound
) const
{
	FGameplayAbilitySpec AbilitySpec;

	if (Character == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Given null for character when attempting to find ability spec for ability ('%s')."),
			*(this->GetIdForLogs())
		);
	}
	else
	{
		UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();
		bool                     bFoundAbilitySpec      = false;

		check(AbilitySystemComponent != nullptr);

		for (const FGameplayAbilitySpec& CurrentAbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
		{
			if (CurrentAbilitySpec.Ability.Get() == this)
			{
				AbilitySpec       = CurrentAbilitySpec;
				bFoundAbilitySpec = true;
				break;
			}
		}

		if (!bFoundAbilitySpec)
		{
			UE_LOG(
				LogPf2CoreAbilities,
				Error,
				TEXT("Failed to find ability spec in ASC for ability ('%s') granted to character ('%s')."),
				*(this->GetIdForLogs()),
				*(Character->GetIdForLogs())
			);
		}

		bOutSpecFound = bFoundAbilitySpec;
	}

	return AbilitySpec;
}

FGameplayAbilitySpecHandle UPF2GameplayAbilityBase::ToGameplayAbilitySpecHandleForCharacter(
	const TScriptInterface<IPF2CharacterInterface> Character,
	bool&                                          bOutSpecHandleFound
) const
{
	return this->ToGameplayAbilitySpecForCharacter(Character, bOutSpecHandleFound).Handle;
}

FGameplayAbilitySpecHandle UPF2GameplayAbilityBase::GetSpecHandleOfCurrentActivation() const
{
	return this->GetCurrentAbilitySpecHandle();
}

TScriptInterface<IPF2CharacterInterface> UPF2GameplayAbilityBase::GetOwningCharacterFromActorInfo() const
{
	TScriptInterface<IPF2CharacterInterface> Result;
	AActor*                                  OwningActor     = this->GetOwningActorFromActorInfo();
	IPF2CharacterInterface*                  OwningCharacter = Cast<IPF2CharacterInterface>(OwningActor);

	if (OwningActor == nullptr)
	{
		Result = TScriptInterface<IPF2CharacterInterface>(nullptr);
	}
	else
	{
		Result = PF2InterfaceUtilities::ToScriptInterface(OwningCharacter);
	}

	return Result;
}

FPF2GameplayEffectContainerSpec UPF2GameplayAbilityBase::MakeEffectContainerSpecFromContainer(
	const FPF2GameplayEffectContainer& Container) const
{
	FPF2GameplayEffectContainerSpec Result;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.GameplayEffectsToApply)
	{
		Result.AddGameplayEffectSpec(this->MakeOutgoingGameplayEffectSpec(EffectClass));
	}

	return Result;
}

FPF2GameplayEffectContainerSpec UPF2GameplayAbilityBase::MakeEffectContainerSpecFromContainerAndWeapon(
	const FPF2GameplayEffectContainer&          Container,
	const TScriptInterface<IPF2WeaponInterface> Weapon,
	const float                                 Level) const
{
	FPF2GameplayEffectContainerSpec Result;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.GameplayEffectsToApply)
	{
		Result.AddGameplayEffectSpec(this->MakeOutgoingGameplayEffectSpecForWeapon(EffectClass, Weapon, Level));
	}

	return Result;
}

FPF2GameplayEffectContainerSpec UPF2GameplayAbilityBase::MakeEffectContainerSpecFromContainerAndCauser(
	const FPF2GameplayEffectContainer& Container,
	AActor*                            EffectCauser,
	const float                        Level) const
{
	FPF2GameplayEffectContainerSpec Result;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.GameplayEffectsToApply)
	{
		Result.AddGameplayEffectSpec(
			this->MakeOutgoingGameplayEffectSpecForCauser(EffectClass, EffectCauser, Level)
		);
	}

	return Result;
}

TArray<FActiveGameplayEffectHandle> UPF2GameplayAbilityBase::ApplyEffectContainerSpec(
	const FPF2GameplayEffectContainerSpec& ContainerSpec) const
{
	TArray<FActiveGameplayEffectHandle> AppliedEffects;

	check(this->CurrentSpecHandle.IsValid());
	check(this->CurrentActorInfo != nullptr);

	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.GameplayEffectSpecsToApply)
	{
		AppliedEffects.Append(
			ApplyGameplayEffectSpecToTarget(
				this->CurrentSpecHandle,
				this->CurrentActorInfo,
				this->CurrentActivationInfo,
				SpecHandle,
				ContainerSpec.TargetData
			)
		);
	}

	return AppliedEffects;
}

FGameplayEffectSpecHandle UPF2GameplayAbilityBase::MakeOutgoingGameplayEffectSpecForWeapon(
	const TSubclassOf<UGameplayEffect>          GameplayEffectClass,
	const TScriptInterface<IPF2WeaponInterface> Weapon,
	const float                                 Level) const
{
	check(this->CurrentActorInfo != nullptr);
	check(this->CurrentActorInfo->AbilitySystemComponent.IsValid());

	return this->MakeOutgoingGameplayEffectSpecForCauser(
		this->CurrentSpecHandle,
		this->CurrentActorInfo,
		GameplayEffectClass,
		Weapon->ToEffectCauser(this->CurrentActorInfo->OwnerActor.Get()),
		Level
	);
}

FGameplayEffectSpecHandle UPF2GameplayAbilityBase::MakeOutgoingGameplayEffectSpecForCauser(
	const TSubclassOf<UGameplayEffect> GameplayEffectClass,
	AActor*                            EffectCauser,
	const float                        Level) const
{
	check(this->CurrentActorInfo != nullptr);
	check(this->CurrentActorInfo->AbilitySystemComponent.IsValid());

	return this->MakeOutgoingGameplayEffectSpecForCauser(
		this->CurrentSpecHandle,
		this->CurrentActorInfo,
		GameplayEffectClass,
		EffectCauser,
		Level
	);
}

FGameplayEffectSpecHandle UPF2GameplayAbilityBase::MakeOutgoingGameplayEffectSpecForCauser(
	const FGameplayAbilitySpecHandle   AbilityHandle,
	const FGameplayAbilityActorInfo*   AbilityOwnerInfo,
	const TSubclassOf<UGameplayEffect> GameplayEffectClass,
	AActor*                            EffectCauser,
	const float                        Level) const
{
	check(AbilityOwnerInfo != nullptr);

	UAbilitySystemComponent* const SourceAsc = AbilityOwnerInfo->AbilitySystemComponent.Get();

	const FGameplayEffectContextHandle EffectContext =
		this->MakeEffectContextForCauser(AbilityHandle, AbilityOwnerInfo, EffectCauser);

	FGameplayEffectSpecHandle EffectHandle = SourceAsc->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContext);

	if (EffectHandle.IsValid())
	{
		FGameplayAbilitySpec* AbilitySpec = SourceAsc->FindAbilitySpecFromHandle(AbilityHandle);

		this->ApplyAbilityTagsToGameplayEffectSpec(*EffectHandle.Data.Get(), AbilitySpec);

		// Copy over set by caller magnitudes
		if (AbilitySpec != nullptr)
		{
			EffectHandle.Data->SetByCallerTagMagnitudes = AbilitySpec->SetByCallerTagMagnitudes;
		}

	}

	return EffectHandle;
}

FGameplayEffectContextHandle UPF2GameplayAbilityBase::MakeEffectContextForCauser(
	const FGameplayAbilitySpecHandle AbilityHandle,
	const FGameplayAbilityActorInfo* AbilityOwnerInfo,
	AActor*                          EffectCauser) const
{
	check(AbilityOwnerInfo != nullptr);

	FGameplayEffectContextHandle Context =
		FGameplayEffectContextHandle(UAbilitySystemGlobals::Get().AllocGameplayEffectContext());

	// Use the character who activated the ability as the instigator, while using a caller-supplied effect causer.
	Context.AddInstigator(AbilityOwnerInfo->OwnerActor.Get(), EffectCauser);

	// Add in the ability tracking here.
	Context.SetAbility(this);

	// Pass along the source ability object to the effect, as long as it is available.
	{
		const FGameplayAbilitySpec* AbilitySpec =
			AbilityOwnerInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(AbilityHandle);

		if (AbilitySpec != nullptr)
		{
			Context.AddSourceObject(AbilitySpec->SourceObject.Get());
		}
	}

	return Context;
}
