// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayEffectComponents/PF2ConditionalGameplayEffect.h"

bool FPF2ConditionalGameplayEffect::CanApply(const FGameplayTagContainer& SourceTags, const float SourceLevel) const
{
	const bool bMatchesAllRequired = SourceTags.HasAll(this->RequiredSourceTags),
	           bHasNoIgnored       = SourceTags.HasAny(this->IgnoredSourceTags),
	           bSatisfiesQuery     = this->SourceTagQuery.IsEmpty() || this->SourceTagQuery.Matches(SourceTags);

	return bMatchesAllRequired && !bHasNoIgnored && bSatisfiesQuery;
}

FGameplayEffectSpecHandle FPF2ConditionalGameplayEffect::CreateSpec(
	const FGameplayEffectContextHandle& EffectContext,
	const float                         SourceLevel) const
{
	if (this->EffectClass != nullptr)
	{
		const UGameplayEffect* EffectCDO = this->EffectClass->GetDefaultObject<UGameplayEffect>();

		return FGameplayEffectSpecHandle(new FGameplayEffectSpec(EffectCDO, EffectContext, SourceLevel));
	}
	else
	{
		return FGameplayEffectSpecHandle();
	}
}

bool FPF2ConditionalGameplayEffect::operator==(const FPF2ConditionalGameplayEffect& Other) const
{
	return (
		(this->EffectClass == Other.EffectClass) &&
		(this->RequiredSourceTags == Other.RequiredSourceTags) &&
		(this->IgnoredSourceTags == Other.IgnoredSourceTags) &&
		(this->SourceTagQuery == Other.SourceTagQuery)
	);
}

bool FPF2ConditionalGameplayEffect::operator!=(const FPF2ConditionalGameplayEffect& Other) const
{
	return (
		(this->EffectClass != Other.EffectClass) ||
		(this->RequiredSourceTags != Other.RequiredSourceTags) ||
		(this->IgnoredSourceTags != Other.IgnoredSourceTags) ||
		(this->SourceTagQuery != Other.SourceTagQuery)
	);
}
