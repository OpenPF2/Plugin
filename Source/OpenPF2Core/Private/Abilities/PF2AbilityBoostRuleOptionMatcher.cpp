// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AbilityBoostRuleOptionMatcher.h"

#include "PF2EnumUtils.h"

FPF2AbilityBoostRuleOptionMatcher::FPF2AbilityBoostRuleOptionMatcher(
	                                                             const TArray<FPF2AbilityBoostRuleOption> RuleOptions) :
	RuleOptions(RuleOptions)
{
}

bool FPF2AbilityBoostRuleOptionMatcher::CanApplyAbilityBoost(const EPF2CharacterAbilityScoreType AbilityScoreType)
{
	bool                                CanApply                 = false;
	TSet<EPF2CharacterAbilityScoreType> AbilityScoreTypesToMatch = this->UsedAbilities;

	// We can't apply more boosts than we have rules.
	// Also, the same ability score type can't be targeted twice in the same boost activation.
	if ((this->GetRemainingBoostCount() > 0) && !AbilityScoreTypesToMatch.Contains(AbilityScoreType))
	{
		TArray<TArray<FPF2AbilityBoostRuleOption>> RulePermutations      = this->CalculateRulePermutations();
		TArray<TArray<FPF2AbilityBoostRuleOption>> RemainingPermutations = RulePermutations;

		AbilityScoreTypesToMatch.Add(AbilityScoreType);

		for (const TArray<FPF2AbilityBoostRuleOption>& RulePermutation : RulePermutations)
		{
			for (int PositionIndex = 0; PositionIndex < AbilityScoreTypesToMatch.Num(); ++PositionIndex)
			{
				const FSetElementId                  ElementId               = FSetElementId::FromInteger(PositionIndex);
				const EPF2CharacterAbilityScoreType& AbilityScoreTypeToMatch = AbilityScoreTypesToMatch[ElementId];
				const FPF2AbilityBoostRuleOption&    RuleOption              = RulePermutation[PositionIndex];

				if (!RuleOption.bIsFreeBoost && !RuleOption.AbilityScoreTypes.Contains(AbilityScoreTypeToMatch))
				{
					// This permutation doesn't have a rule in this position of the sequence of rules that would match
					// this ability boost, so disqualify the permutation.
					RemainingPermutations.Remove(RulePermutation);
					break;
				}
			}
		}

		CanApply = (RemainingPermutations.Num() != 0);
	}

	return CanApply;
}

void FPF2AbilityBoostRuleOptionMatcher::ApplyAbilityBoost(const EPF2CharacterAbilityScoreType AbilityScoreType)
{
	checkf(
		this->CanApplyAbilityBoost(AbilityScoreType),
		TEXT("A boost to '%s' cannot be applied based on the unused rule options ('%d' boosts remain)."),
		*(PF2EnumUtils::ToString(AbilityScoreType)),
		this->GetRemainingBoostCount()
	);

	this->UsedAbilities.Add(AbilityScoreType);
}

int32 FPF2AbilityBoostRuleOptionMatcher::GetRemainingBoostCount() const
{
	return (this->RuleOptions.Num() - this->UsedAbilities.Num());
}

TSet<EPF2CharacterAbilityScoreType> FPF2AbilityBoostRuleOptionMatcher::GetRemainingOptions()
{
	TSet<EPF2CharacterAbilityScoreType> AllRuleAbilityOptions;
	TSet<EPF2CharacterAbilityScoreType> RemainingOptions;

	for (const auto& RuleOption : this->RuleOptions)
	{
		if (RuleOption.bIsFreeBoost)
		{
			for (const auto& AbilityScoreType : TEnumRange<EPF2CharacterAbilityScoreType>())
			{
				AllRuleAbilityOptions.Add(AbilityScoreType);
			}
		}
		else
		{
			AllRuleAbilityOptions.Append(RuleOption.AbilityScoreTypes);
		}
	}

	if (this->UsedAbilities.Num() == 0)
	{
		// We don't need to search any further, since all options are still on the table.
		RemainingOptions = AllRuleAbilityOptions;
	}
	else
	{
		for (const auto& AbilityScoreType : AllRuleAbilityOptions)
		{
			if (this->CanApplyAbilityBoost(AbilityScoreType))
			{
				RemainingOptions.Add(AbilityScoreType);
			}
		}
	}

	return RemainingOptions;
}

TArray<TArray<FPF2AbilityBoostRuleOption>> FPF2AbilityBoostRuleOptionMatcher::CalculateRulePermutations()
{
	if (this->CachedRulePermutations.Num() == 0)
	{
		this->CachedRulePermutations = this->CalculateRulePermutations({});
	}

	return this->CachedRulePermutations;
}

TArray<TArray<FPF2AbilityBoostRuleOption>> FPF2AbilityBoostRuleOptionMatcher::CalculateRulePermutations(
	                                                               TArray<FPF2AbilityBoostRuleOption> SeenOptions) const
{
	TArray<TArray<FPF2AbilityBoostRuleOption>> Result;

	if (SeenOptions.Num() == this->RuleOptions.Num())
	{
		// No more options to evaluate on this path. Return the path we've got!
		Result.Add(SeenOptions);
	}
	else
	{
		for (const FPF2AbilityBoostRuleOption& RuleOption : this->RuleOptions)
		{
			if (!SeenOptions.Contains(RuleOption))
			{
				TArray<FPF2AbilityBoostRuleOption> NewSeenOptions = SeenOptions;

				NewSeenOptions.Add(RuleOption);
				Result.Append(this->CalculateRulePermutations(NewSeenOptions));
			}
		}
	}

	return Result;
}
