// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Libraries/PF2DiceLibrary.h"

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

int32 UPF2DiceLibrary::RollSum(const int32 RollCount, const int32 DieSize)
{
	return PF2ArrayUtilities::Reduce(
		Roll(RollCount, DieSize),
		0,
		[](const int32 PreviousValue, const int32 CurrentValue)
		{
			return PreviousValue + CurrentValue;
		});
}

TArray<int32> UPF2DiceLibrary::RollString(const FName RollExpression)
{
	FRegexMatcher ExpressionMatcher = GetRollExpressionMatcher(RollExpression);

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

TArray<int32> UPF2DiceLibrary::Roll(const int32 RollCount, const int32 DieSize)
{
	TArray<int32> Rolls;

	for (int32 RollIndex = 0; RollIndex < RollCount; ++RollIndex)
	{
		int32 Roll;

		if (DieSize == 0)
		{
			// Edge case: Unlikely to happen, but just in case, we need to make sure that rolling a zero-sided die does
			// not return 1. Could happen if the die size is passed-in dynamically.
			Roll = 0;
		}
		else
		{
			Roll = FMath::RandRange(1, DieSize);
		}

		Rolls.Add(Roll);
	}

	return Rolls;
}

FRegexMatcher UPF2DiceLibrary::GetRollExpressionMatcher(const FName RollExpression)
{
	return FRegexMatcher(DiceRollPattern, RollExpression.ToString().ToLower());
}

FName UPF2DiceLibrary::NextSizeString(const FName RollExpression)
{
	FName Result;

	FRegexMatcher ExpressionMatcher = GetRollExpressionMatcher(RollExpression);

	if (ExpressionMatcher.FindNext())
	{
		const FString RollCountString = ExpressionMatcher.GetCaptureGroup(1),
		              SideCountString = ExpressionMatcher.GetCaptureGroup(2);
		const int32   SideCount       = FCString::Atoi(*SideCountString),
		              NextSideCount   = NextSize(SideCount);

		Result = FName(
			FString::Format(
				TEXT("{0}d{1}"),
				{RollCountString, FString::FormatAsNumber(NextSideCount)}
			)
		);
	}
	else
	{
		Result = FName(TEXT("0d0"));
	}

	return Result;
}

int32 UPF2DiceLibrary::NextSize(const int32 DieSize)
{
	return DieSize + 2;
}
