// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

/**
 * Various utilities for functional programming with arrays and similar structures.
 */
namespace PF2ArrayUtilities
{
	/**
	 * Applies a transformation function to the values in an array, then returns the result of the transformation.
	 *
	 * The original array is not modified.
	 */
	template <typename Out, typename In, typename Func>
	TArray<Out> Map(const TArray<In> Elements, const Func Callable)
	{
		TArray<Out> Result;

		for (const auto& Element : Elements)
		{
			const Out MappingOutput = Callable(Element);

			Result.Add(MappingOutput);
		}

		return Result;
	}
}
