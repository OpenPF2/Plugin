// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2GameplayAbilityFilterBase.h"

#include <AbilitySystemComponent.h>

#include "Abilities/PF2AbilitySystemInterface.h"
#include "Abilities/PF2GameplayAbilityFilterActivationContext.h"

#include "Utilities/PF2InterfaceUtilities.h"

FString UPF2GameplayAbilityFilterBase::GetIdForLogs() const
{
	return this->GetName();
}

void UPF2GameplayAbilityFilterBase::ActivateAbility(const FGameplayAbilitySpecHandle     Handle,
                                                    const FGameplayAbilityActorInfo*     ActorInfo,
                                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                                    const FGameplayEventData*            TriggerEventData)
{
	if (TriggerEventData == nullptr)
	{
		constexpr bool bReplicateEndAbility = false;
		constexpr bool bWasCancelled        = true;

		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Ability ('%s') must be provided with event data, but none was supplied."),
			*this->GetIdForLogs()
		);

		this->EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	else
	{
		const UObject* RawContext = TriggerEventData->OptionalObject;

		if (RawContext == nullptr)
		{
			UE_LOG(
				LogPf2CoreAbilities,
				Error,
				TEXT("Filter ability ('%s') must be provided with a context object in the 'OptionalObject' field of target data, but none was supplied."),
				*(this->GetIdForLogs())
			);
		}
		else
		{
			const UPF2GameplayAbilityFilterActivationContext* ActivationContext =
				Cast<UPF2GameplayAbilityFilterActivationContext>(RawContext);

			if (ActivationContext == nullptr)
			{
				UE_LOG(
					LogPf2CoreAbilities,
					Error,
					TEXT("Filter ability ('%s') must be provided with an OpenPF2-compatible filter activation context object, but the wrong type ('%s') was supplied."),
					*(this->GetIdForLogs()),
					*(RawContext->GetClass()->GetName())
				);
			}
			else
			{
				this->FilterAbilityActivation(
					ActivationContext->GetInputName(),
					ActivationContext->GetActivatedAbilityHandle(),
					Handle,
					*TriggerEventData,
					this->GetAbilitySystemInterface()
				);
			}
		}
	}
}

void UPF2GameplayAbilityFilterBase::ProceedWithOriginalActivation(
	const FGameplayAbilitySpecHandle ActivatedAbilityHandle) const
{
	this->GetAbilitySystemComponentFromActorInfo_Checked()->TryActivateAbility(ActivatedAbilityHandle);
}

TScriptInterface<IPF2AbilitySystemInterface> UPF2GameplayAbilityFilterBase::GetAbilitySystemInterface() const
{
	UAbilitySystemComponent*    Asc     = this->GetAbilitySystemComponentFromActorInfo();
	IPF2AbilitySystemInterface* AscIntf = Cast<IPF2AbilitySystemInterface>(Asc);

	if (AscIntf == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Filter ability ('%s') requires an OpenPF2-compatible ability system component ."),
			*(this->GetIdForLogs())
		);

		return TScriptInterface<IPF2AbilitySystemInterface>(nullptr);
	}
	else
	{
		return PF2InterfaceUtilities::ToScriptInterface(AscIntf);
	}
}
