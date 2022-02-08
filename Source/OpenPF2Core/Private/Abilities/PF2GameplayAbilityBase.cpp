// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2GameplayAbilityBase.h"

#include "Utilities/PF2LogUtilities.h"

bool UPF2GameplayAbilityBase::CheckCost(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        FGameplayTagContainer*           OptionalRelevantTags) const
{
	if (this->bEnforcingCosts)
	{
		return Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags);
	}
	else
	{
		return true;
	}
}

void UPF2GameplayAbilityBase::OnQueued()
{
	if (!this->bShouldBlockWhenQueued)
	{
		this->ForceSuspendBlocking();
	}

	if (!this->bShouldEnforceCostWhenQueued)
	{
		this->bEnforcingCosts = false;
	}
}

void UPF2GameplayAbilityBase::OnDequeued()
{
	if (!this->bShouldBlockWhenQueued)
	{
		this->ForceResumeBlocking();
	}

	if (!this->bShouldEnforceCostWhenQueued)
	{
		this->bEnforcingCosts = true;
	}
}

void UPF2GameplayAbilityBase::ForceSuspendBlocking()
{
	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] Ability blocking 'disabled' for action ('%s'). Previous state was: '%s'"),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs()),
		(this->IsBlockingOtherAbilities() ? TEXT("enabled") : TEXT("disabled"))
	);

	this->SetShouldBlockOtherAbilities(false);
}

void UPF2GameplayAbilityBase::ForceResumeBlocking()
{
	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] Ability blocking 'enabled' for action ('%s'). Previous state was: '%s'"),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs()),
		(this->IsBlockingOtherAbilities() ? TEXT("enabled") : TEXT("disabled"))
	);

	this->SetShouldBlockOtherAbilities(true);
}

FString UPF2GameplayAbilityBase::GetIdForLogs() const
{
	return this->GetName();
}
