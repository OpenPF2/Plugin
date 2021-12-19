// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Libraries/PF2CharacterStatLibrary.h"

#include "Tests/PF2SpecBase.h"

struct FAbilityBoostTestTuple
{
	float StartingAbilityScore;
	float BoostCount;
	float ExpectedBoostAmount;
};

BEGIN_DEFINE_PF_SPEC(FPF2CharacterStatLibrarySpec,
                     "OpenPF2.CharacterStatLibrary",
                     EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_PF_SPEC(FPF2CharacterStatLibrarySpec)

void FPF2CharacterStatLibrarySpec::Define()
{
	Describe(TEXT("CalculateAbilityBoostAmount"), [=, this]
	{
		const TArray<FAbilityBoostTestTuple> TestParameters =
		{
			{ 10, 1, 2 },
			{ 18, 1, 1 },
			{ 10, 5, 9 },
			{ 10, 0, 0 },
		};

		for (const auto& CurrentTestParameters : TestParameters)
		{
			const float StartingAbilityScore = CurrentTestParameters.StartingAbilityScore,
			            BoostCount           = CurrentTestParameters.BoostCount,
			            ExpectedBoostAmount  = CurrentTestParameters.ExpectedBoostAmount;

			Describe(FString::Format(TEXT("when the starting ability score is '{0}' and the boost count is '{1}'"), {FString::FormatAsNumber(StartingAbilityScore), FString::FormatAsNumber(BoostCount)}), [=, this]
			{
				It(FString::Format(TEXT("returns '{0}'"), {FString::FormatAsNumber(ExpectedBoostAmount)}), [=, this]
				{
					TestEqual(
						TEXT("Result"),
						UPF2CharacterStatLibrary::CalculateAbilityBoostAmount(StartingAbilityScore, BoostCount),
						ExpectedBoostAmount
					);
				});
			});
		}
	});
}
