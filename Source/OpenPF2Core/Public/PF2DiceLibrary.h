// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Internationalization/Regex.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "PF2DiceLibrary.generated.h"

/**
 * Simple function library for rolling dice of any size.
 *
 * Dice rolls can either be done by specifying the number of sides and number of rolls numerically; or by describing the
 * roll in a string format like "2d6" (for rolling two, six-sided dice). For example, the following calls would produce
 * equivalent results:
 *	- RollString("2d6") and Roll(2,6) - Roll two, six-sided dice.
 *	- RollString("1d4") and Roll(1,4) - Roll one, four-sided dice.
 *	- RollString("10d12") and Roll(10,12) - Roll ten, twelve-sided dice.
 *
 * Unlike other RPG systems like Dungeons and Dragons, P2E game rules do *not* appear to require the ability to evaluate
 * complex dice rolling expressions like "5d4+3", "3d6x10", or "d6/2". Consequently, these types of expressions are not
 * supported at this time.
 */
UCLASS()
class OPENPF2CORE_API UPF2DiceLibrary final : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

protected:
	/**
	 * Regular expression pattern used to parse dice rolling expressions.
	 */
	static const FRegexPattern DiceRollPattern;

public:
	/**
	 * Returns the sum of a dice roll for the given dice roll expression string.
	 *
	 * Complex roll expressions like "3d6x10" are not supported at this time.
	 *
	 * @param RollExpression
	 *	The description of the roll, in "CdS" format, where "C" represents the count or number of dice to roll, and "S"
	 *	represents the number of sides of each die. For example, "1d6" represents a single roll of a six-sided die,
	 *	while "2d4" represents rolling two dice having four sides each.
	 *
	* @return
	 *	The sum of the dice roll(s).
	 */
	UFUNCTION(BlueprintPure)
	static int32 RollStringSum(const FName RollExpression);

	/**
	 * Returns the sum of a dice roll for the given numeric parameters.
	 *
	 * @param RollCount
	 *	The count or number of dice to roll.
	 * @param SideCount
	 *	The number of sides of each die.
	 *
	 * @return
	 *	The sum of the dice roll(s).
	 */
	UFUNCTION(BlueprintPure)
	static int32 RollSum(const int32 RollCount, const int32 SideCount);

	/**
	 * Returns the result of a dice roll for the given dice roll expression string.
	 *
	 * Complex roll expressions like "3d6x10" are not supported at this time.
	 *
	 * @param RollExpression
	 *	The description of the roll, in "CdS" format, where "C" represents the count or number of dice to roll, and "S"
	 *	represents the number of sides of each die. For example, "1d6" represents a single roll of a six-sided die,
	 *	while "2d4" represents rolling two dice having four sides each.
	 *
	* @return
	 *	The result of each dice roll.
	 */
	UFUNCTION(BlueprintPure)
	static TArray<int32> RollString(const FName RollExpression);

	/**
	 * Returns the result of a dice roll for the given numeric parameters.
	 *
	 * @param RollCount
	 *	The count or number of dice to roll.
	 * @param SideCount
	 *	The number of sides of each die.
	 *
	 * @return
	 *	The result of each dice roll.
	 */
	UFUNCTION(BlueprintPure)
	static TArray<int32> Roll(const int32 RollCount, const int32 SideCount);

	/**
	 * Increases the size of a given dice expression, returning the next dice size up,
	 *
	 * @param RollExpression
	 *	The description of the roll, in "CdS" format, where "C" represents the count or number of dice to roll, and "S"
	 *	represents the number of sides of each die. For example, "1d6" represents a single roll of a six-sided die,
	 *	while "2d4" represents rolling two dice having four sides each.
	 *
	 * @return
	 *	A roll expression for the next size up (for example, given "1d6" this would return "1d8"; given "2d4", this
	 *	would return "2d6").
	 */
	UFUNCTION(BlueprintPure)
	static FName NextSizeString(const FName RollExpression);

	/**
	 * Gets the number of sides of the next-largest die from a die having the given number of sides.
	 *
	 * @param SideCount
	 *	The number of sides of the die.
	 *
	 * @return
	 *	The number of sides on the die of the next size up.
	 */
	UFUNCTION(BlueprintPure)
	static int32 NextSize(const int32 SideCount);

	/**
	 * Gets a regular expression matcher for the given roll expression.
	 *
	 * @param RollExpression
	 *	The expression to parse/match with a regex.
	 *
	 * @return
	 *	The matcher for parsing the expression.
	 */
	static FRegexMatcher GetRollExpressionMatcher(FName RollExpression);
};
