// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Libraries/PF2DiceLibrary.h"

#include "Tests/PF2SpecBase.h"

BEGIN_DEFINE_PF_SPEC(FPF2DiceLibrarySpec,
                     "OpenPF2.Libraries.Dice",
                     EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
END_DEFINE_PF_SPEC(FPF2DiceLibrarySpec)

void FPF2DiceLibrarySpec::Define()
{
	struct FDiceRollStringTestTuple
	{
		FString RollString;
		int MinRoll;
		int MaxRoll;
	};

	struct FDiceRollTestTuple
	{
		int RollCount;
		int DieSize;
		int MinRoll;
		int MaxRoll;
	};

	Describe(TEXT("RollStringSum"), [=]
	{
		TArray<FDiceRollStringTestTuple> ExpectedRanges =
		{
			{ "0d5", 0,  0 },
			{ "1d0", 0,  0 },
			{ "BAD", 0,  0 },
			{ "1d6", 1,  6 },
			{ "2d6", 1, 12 },
			{ "1d2", 1,  2 },
			{ "3d5", 1, 15 },
		};

		for (const auto& TestParameters : ExpectedRanges)
		{
			const FString RollString = TestParameters.RollString;
			const int     MinRoll    = TestParameters.MinRoll,
			              MaxRoll    = TestParameters.MaxRoll;

			Describe(FString::Format(TEXT("when given '{0}'"), {RollString}), [=]
			{
				It(FString::Format(TEXT("returns a number greater than or equal to '{0}' over 10 rolls"), {FString::FormatAsNumber(MinRoll)}), [=]
				{
					float MinRollSeen = 9999;

					for (int RollIndex = 0; RollIndex < 10; ++RollIndex)
					{
						const float RollSum = UPF2DiceLibrary::RollStringSum(FName(RollString));

						MinRollSeen = FMath::Min(MinRollSeen, RollSum);
					}

					TestTrue(
						FString::Format(
							TEXT("{0} >= {1}"),
							{
								FString::FormatAsNumber(MinRollSeen),
								FString::FormatAsNumber(MinRoll),
							}
						),
						MinRollSeen >= MinRoll
					);
				});

				It(FString::Format(TEXT("returns a number less than or equal to '{0}' over 10 rolls"), {FString::FormatAsNumber(MaxRoll)}), [=]
				{
					float MaxRollSeen = -1;

					for (int RollIndex = 0; RollIndex < 10; ++RollIndex)
					{
						const float RollSum = UPF2DiceLibrary::RollStringSum(FName(RollString));

						MaxRollSeen = FMath::Max(MaxRollSeen, RollSum);
					}

					TestTrue(
						FString::Format(
							TEXT("{0} <= {1}"),
							{
								FString::FormatAsNumber(MaxRollSeen),
								FString::FormatAsNumber(MaxRoll)
							}),
						MaxRollSeen <= MaxRoll
					);
				});
			});
		}
	});

	Describe(TEXT("RollSum"), [=]
	{
		TArray<FDiceRollTestTuple> ExpectedRanges =
		{
			{ 0, 5, 0,  0 },
			{ 1, 0, 0,  0 },
			{ 1, 6, 1,  6 },
			{ 2, 6, 1, 12 },
			{ 1, 2, 1,  2 },
			{ 3, 5, 1, 15 },
		};

		for (const auto& TestParameters : ExpectedRanges)
		{
			const int RollCount = TestParameters.RollCount,
			          DieSize   = TestParameters.DieSize,
			          MinRoll   = TestParameters.MinRoll,
			          MaxRoll   = TestParameters.MaxRoll;

			Describe(FString::Format(TEXT("when given '{0}d{1}'"), {FString::FormatAsNumber(RollCount), FString::FormatAsNumber(DieSize)}), [=]
			{
				It(FString::Format(TEXT("returns a number greater than or equal to '{0}' over 10 rolls"), {FString::FormatAsNumber(MinRoll)}), [=]
				{
					float MinRollSeen = 9999;

					for (int RollIndex = 0; RollIndex < 10; ++RollIndex)
					{
						const float RollSum = UPF2DiceLibrary::RollSum(RollCount, DieSize);

						MinRollSeen = FMath::Min(MinRollSeen, RollSum);
					}

					TestTrue(
						FString::Format(
							TEXT("{0} >= {1}"),
							{
								FString::FormatAsNumber(MinRollSeen),
								FString::FormatAsNumber(MinRoll),
							}
						),
						MinRollSeen >= MinRoll
					);
				});

				It(FString::Format(TEXT("returns a number less than or equal to '{0}' over 10 rolls"), {FString::FormatAsNumber(MaxRoll)}), [=]
				{
					float MaxRollSeen = -1;

					for (int RollIndex = 0; RollIndex < 10; ++RollIndex)
					{
						const float RollSum = UPF2DiceLibrary::RollSum(RollCount, DieSize);

						MaxRollSeen = FMath::Max(MaxRollSeen, RollSum);
					}

					TestTrue(
						FString::Format(
							TEXT("{0} <= {1}"),
							{
								FString::FormatAsNumber(MaxRollSeen),
								FString::FormatAsNumber(MaxRoll)
							}),
						MaxRollSeen <= MaxRoll
					);
				});
			});
		}
	});

	Describe(TEXT("RollString"), [=]
	{
		TArray<FDiceRollStringTestTuple> ExpectedRanges =
		{
			{ "0d5", 0,  0 },
			{ "1d0", 0,  0 },
			{ "BAD", 0,  0 },
			{ "1d6", 1,  6 },
			{ "2d6", 1,  6 },
			{ "1d2", 1,  2 },
			{ "3d5", 1,  5 },
		};

		for (const auto& TestParameters : ExpectedRanges)
		{
			const FString RollString = TestParameters.RollString;
			const int     MinRoll    = TestParameters.MinRoll,
			              MaxRoll    = TestParameters.MaxRoll;

			Describe(FString::Format(TEXT("when given '{0}'"), {RollString}), [=]
			{
				It(FString::Format(TEXT("returns a number greater than or equal to '{0}' over 10 rolls"), {FString::FormatAsNumber(MinRoll)}), [=]
				{
					float MinRollSeen = 9999;

					const TArray<int32> Rolls = UPF2DiceLibrary::RollString(FName(RollString));

					for (const int& Roll : Rolls)
					{
						MinRollSeen = FMath::Min(MinRollSeen, static_cast<float>(Roll));
					}

					TestTrue(
						FString::Format(
							TEXT("{0} >= {1}"),
							{
								FString::FormatAsNumber(MinRollSeen),
								FString::FormatAsNumber(MinRoll),
							}
						),
						MinRollSeen >= MinRoll
					);
				});

				It(FString::Format(TEXT("returns a number less than or equal to '{0}' over 10 rolls"), {FString::FormatAsNumber(MaxRoll)}), [=]
				{
					float MaxRollSeen = -1;

					const TArray<int32> Rolls = UPF2DiceLibrary::RollString(FName(RollString));

					for (const int& Roll : Rolls)
					{
						MaxRollSeen = FMath::Max(MaxRollSeen, static_cast<float>(Roll));
					}

					TestTrue(
						FString::Format(
							TEXT("{0} <= {1}"),
							{
								FString::FormatAsNumber(MaxRollSeen),
								FString::FormatAsNumber(MaxRoll)
							}),
						MaxRollSeen <= MaxRoll
					);
				});
			});
		}
	});

	Describe(TEXT("Roll"), [=]
	{
		for (int DieSize = 1; DieSize < 64; ++DieSize)
		{
			Describe(FString::Format(TEXT("when given a '{0}'-sided die"), {FString::FormatAsNumber(DieSize)}), [=]
			{
				It(TEXT("returns an array that contains one result for each roll"), [=]
				{
					TestEqual(
						FString::Format(TEXT("Roll(3, {0}).Num() == 3"), {DieSize}),
						UPF2DiceLibrary::Roll(3, DieSize).Num(),
						3
					);

					TestEqual(
						FString::Format(TEXT("Roll(10, {0}).Num() == 10"), {DieSize}),
						UPF2DiceLibrary::Roll(10, DieSize).Num(),
						10
					);
				});

				It(TEXT("returns a number greater than or equal to '1' over 10 rolls"), [=]
				{
					float               MinRollSeen = 9999;
					const TArray<int32> Rolls       = UPF2DiceLibrary::Roll(10, DieSize);

					for (const int& Roll : Rolls)
					{
						MinRollSeen = FMath::Min(MinRollSeen, static_cast<float>(Roll));
					}

					TestTrue(
						FString::Format(TEXT("{0} >= 1"), {FString::FormatAsNumber(MinRollSeen)}),
						MinRollSeen >= 1
					);
				});

				It(FString::Format(TEXT("returns a number less than or equal to '{0}' over 10 rolls"), {FString::FormatAsNumber(DieSize)}), [=]
				{
					float               MaxRollSeen = -1;
					const TArray<int32> Rolls       = UPF2DiceLibrary::Roll(10, DieSize);

					for (const int& Roll : Rolls)
					{
						MaxRollSeen = FMath::Max(MaxRollSeen, static_cast<float>(Roll));
					}

					TestTrue(
						FString::Format(
							TEXT("{0} <= {1}"),
							{
								FString::FormatAsNumber(MaxRollSeen),
								FString::FormatAsNumber(DieSize)
							}),
						MaxRollSeen <= DieSize
					);
				});
			});
		}
	});

	Describe(TEXT("NextSizeString"), [=]
	{
		TMap<FString, FString> ExpectedValues =
		{
			{ "1d6",  "1d8"  },
			{ "2d6",  "2d8"  },
			{ "1d3",  "1d5"  },
			{ "8d1",  "8d3"  },
			{ "1d16", "1d18" },
		};

		for (const auto& TestParameters : ExpectedValues)
		{
			const FString RollExpression = TestParameters.Key;
			const FString ExpectedOutput = TestParameters.Value;

			Describe(FString::Format(TEXT("when given '{0}'"), {RollExpression}), [=]
			{
				It(FString::Format(TEXT("returns '{0}'"), {ExpectedOutput}), [=]
				{
					TestEqual(
						"Result",
						UPF2DiceLibrary::NextSizeString(FName(RollExpression)),
						FName(ExpectedOutput)
					);
				});
			});
		}
	});

	Describe(TEXT("NextSize"), [=]
	{
		TMap<int32, int32> ExpectedValues =
		{
			{  6,  8 },
			{  3,  5 },
			{  1,  3 },
			{ 16, 18 },
		};

		for (const auto& TestParameters : ExpectedValues)
		{
			const int32 DieSize        = TestParameters.Key;
			const int32 ExpectedOutput = TestParameters.Value;

			Describe(FString::Format(TEXT("when given '{0}'"), {FString::FormatAsNumber(DieSize)}), [=]
			{
				It(FString::Format(TEXT("returns '{0}'"), {FString::FormatAsNumber(ExpectedOutput)}), [=]
				{
					TestEqual(
						"Result",
						UPF2DiceLibrary::NextSize(DieSize),
						ExpectedOutput
					);
				});
			});
		}
	});
}
