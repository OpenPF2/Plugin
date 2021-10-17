// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2GameplayAbility_BoostAbilityBase.h"

#include "Abilities/PF2AbilityBoostRuleOptionValidator.h"
#include "Abilities/PF2AttributeSet.h"
#include "Abilities/PF2CharacterAbilitySystemComponentInterface.h"
#include "Abilities/PF2GameplayAbilityTargetData_BoostAbility.h"

UPF2GameplayAbility_BoostAbilityBase::UPF2GameplayAbility_BoostAbilityBase()
{
	FAbilityTriggerData TriggerData;

	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag    = GetTriggerTag();

	this->AbilityTriggers.Add(TriggerData);

	// We don't maintain any local state.
	this->InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

bool UPF2GameplayAbility_BoostAbilityBase::CheckCost(const FGameplayAbilitySpecHandle Handle,
                                                     const FGameplayAbilityActorInfo* ActorInfo,
                                                     FGameplayTagContainer*           OptionalRelevantTags) const
{
	if (Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags))
	{
		const UPF2AttributeSet* AttributeSet  = this->GetAttributeSet(ActorInfo);
		const float             BoostsToApply = this->BoostRuleOptions.Num(),
		                        BoostsApplied = AttributeSet->GetAbBoostCount(),
		                        BoostLimit    = AttributeSet->GetAbBoostLimit();

		// We can apply this set of ability boosts if the difference between how many boosts are applied and the boost
		// limit is large enough to accomodate all of the boost options on this ability.
		return ((BoostsApplied + BoostsToApply) <= BoostLimit);
	}
	else
	{
		return false;
	}
}

void UPF2GameplayAbility_BoostAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle     Handle,
                                                           const FGameplayAbilityActorInfo*     ActorInfo,
                                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                                           const FGameplayEventData*            TriggerEventData)
{
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		const TSet<EPF2CharacterAbilityScoreType> BoostSelections = this->GetBoostSelections(TriggerEventData);

		IPF2CharacterAbilitySystemComponentInterface* CharacterAsc =
			this->GetCharacterAbilitySystemComponent(ActorInfo);

		UPF2AbilityBoostRuleOptionValidator* Validator = NewObject<UPF2AbilityBoostRuleOptionValidator>();

		Validator->AppendRuleOptions(this->BoostRuleOptions);

		for (auto& Selection : BoostSelections)
		{
			Validator->ApplyAbilityBoost(Selection);
		}

		checkf(
			Validator->GetRemainingBoostCount() == 0,
			TEXT("There must be a selection for every rule option.")
		);

		for (auto& Selection : BoostSelections)
		{
			CharacterAsc->ApplyAbilityBoost(Selection);
		}

		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}

TSet<EPF2CharacterAbilityScoreType> UPF2GameplayAbility_BoostAbilityBase::GetBoostSelections(
	const FGameplayEventData* TriggerEventData) const
{
	const FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle = TriggerEventData->TargetData;
	const FGameplayAbilityTargetData*      AbilityTargetData               = GameplayAbilityTargetDataHandle.Get(0);

	const FPF2GameplayAbilityTargetData_BoostAbility* BoostTargetData;

	check(AbilityTargetData != nullptr);

	BoostTargetData = StaticCast<const FPF2GameplayAbilityTargetData_BoostAbility*>(AbilityTargetData);
	check(BoostTargetData != nullptr);

	return BoostTargetData->SelectedAbilities;
}

FORCEINLINE IPF2CharacterAbilitySystemComponentInterface* UPF2GameplayAbility_BoostAbilityBase::GetCharacterAbilitySystemComponent(
	const FGameplayAbilityActorInfo* ActorInfo)
{
	IPF2CharacterAbilitySystemComponentInterface* CharacterAsc;
	UAbilitySystemComponent*                      AbilitySystemComponent = GetAbilitySystemComponent(ActorInfo);

	CharacterAsc = Cast<IPF2CharacterAbilitySystemComponentInterface>(AbilitySystemComponent);
	check(CharacterAsc != nullptr);

	return CharacterAsc;
}

FORCEINLINE UAbilitySystemComponent* UPF2GameplayAbility_BoostAbilityBase::GetAbilitySystemComponent(
	const FGameplayAbilityActorInfo* ActorInfo)
{
	UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
	check(AbilitySystemComponent != nullptr);

	return AbilitySystemComponent;
}

FORCEINLINE const UPF2AttributeSet* UPF2GameplayAbility_BoostAbilityBase::GetAttributeSet(
	const FGameplayAbilityActorInfo* ActorInfo)
{
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent(ActorInfo);
	const UPF2AttributeSet*        AttributeSet;

	AttributeSet = AbilitySystemComponent->GetSet<UPF2AttributeSet>();
	check(AttributeSet != nullptr);

	return AttributeSet;
}
