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

FName UPF2GameplayAbilityBase::GetDefaultInputActionMapping() const
{
	return this->DefaultInputActionMapping;
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
