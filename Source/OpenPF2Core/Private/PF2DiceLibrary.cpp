// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2DiceLibrary.h"

#include "PF2ArrayUtilities.h"

const FRegexPattern UPF2DiceLibrary::DiceRollPattern = FRegexPattern(TEXT("^(\\d{1,})d(\\d{1,})$"));

int32 UPF2DiceLibrary::RollStringSum(const FName RollExpression)
{
	return PF2ArrayUtilities::Reduce(
		RollString(RollExpression),
		0,
		[](const int32 PreviousValue, const int32 CurrentValue)
		{
			return PreviousValue + CurrentValue;
		});
}

int32 UPF2DiceLibrary::RollSum(const int32 RollCount, const int32 SideCount)
{
	return PF2ArrayUtilities::Reduce(
		Roll(RollCount, SideCount),
		0,
		[](const int32 PreviousValue, const int32 CurrentValue)
		{
			return PreviousValue + CurrentValue;
		});
}

TArray<int32> UPF2DiceLibrary::RollString(const FName RollExpression)
{
	FRegexMatcher ExpressionMatcher = FRegexMatcher(DiceRollPattern, RollExpression.ToString().ToLower());

	if (ExpressionMatcher.FindNext())
	{
		const FString RollCountString = ExpressionMatcher.GetCaptureGroup(1),
		              SideCountString = ExpressionMatcher.GetCaptureGroup(2);
		const int32   RollCount       = FCString::Atoi(*RollCountString),
		              SideCount       = FCString::Atoi(*SideCountString);

		return Roll(RollCount, SideCount);
	}
	else
	{
		return {};
	}
}

TArray<int32> UPF2DiceLibrary::Roll(const int32 RollCount, const int32 SideCount)
{
	TArray<int32> Rolls;

	for (int32 RollIndex = 0; RollIndex < RollCount; ++RollIndex)
	{
		int32 Roll = FMath::RandRange(1, SideCount);

		Rolls.Add(Roll);
	}

	return Rolls;
}
