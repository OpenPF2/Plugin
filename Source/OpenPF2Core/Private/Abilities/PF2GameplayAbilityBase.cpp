// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2GameplayAbilityBase.h"

#include "PF2CharacterInterface.h"

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
