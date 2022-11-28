// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/Tasks/PF2AbilityTaskBase.h"

#include "Abilities/PF2AbilitySystemInterface.h"
#include "Abilities/PF2CharacterAbilitySystemInterface.h"
#include "Abilities/PF2GameplayAbilityInterface.h"

#include "Utilities/PF2InterfaceUtilities.h"

TScriptInterface<IPF2GameplayAbilityInterface> UPF2AbilityTaskBase::GetAbility() const
{
	IPF2GameplayAbilityInterface* AbilityIntf = Cast<IPF2GameplayAbilityInterface>(this->GetNativeAbility());

	if (AbilityIntf == nullptr)
	{
		return TScriptInterface<IPF2GameplayAbilityInterface>(nullptr);
	}
	else
	{
		return PF2InterfaceUtilities::ToScriptInterface(AbilityIntf);
	}
}

TScriptInterface<IPF2AbilitySystemInterface> UPF2AbilityTaskBase::GetAbilitySystemComponent() const
{
	IPF2AbilitySystemInterface* AscIntf = Cast<IPF2AbilitySystemInterface>(this->GetNativeAbilitySystemComponent());

	if (AscIntf == nullptr)
	{
		return TScriptInterface<IPF2AbilitySystemInterface>(nullptr);
	}
	else
	{
		return PF2InterfaceUtilities::ToScriptInterface(AscIntf);
	}
}

TScriptInterface<IPF2CharacterAbilitySystemInterface> UPF2AbilityTaskBase::GetCharacterAbilitySystemComponent() const
{
	IPF2CharacterAbilitySystemInterface* AscIntf = Cast<IPF2CharacterAbilitySystemInterface>(this->GetNativeAbilitySystemComponent());

	if (AscIntf == nullptr)
	{
		return TScriptInterface<IPF2CharacterAbilitySystemInterface>(nullptr);
	}
	else
	{
		return PF2InterfaceUtilities::ToScriptInterface<IPF2CharacterAbilitySystemInterface>(AscIntf);
	}
}
