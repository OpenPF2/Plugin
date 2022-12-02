// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Net/UnrealNetwork.h>

#include "Abilities/PF2GameplayAbilityFilterActivationContext.h"

void UPF2GameplayAbilityFilterActivationContext::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPF2GameplayAbilityFilterActivationContext, InputName);
	DOREPLIFETIME(UPF2GameplayAbilityFilterActivationContext, ActivatedAbilityHandle);
}
