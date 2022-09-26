// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
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
	 * Add each unique element from one array to the end of the other.
	 *
	 * Elements that already exist in the target array are skipped.
	 *
	 * @tparam T
	 *	The type of elements in the array.
	 *
	 * @param NewElements
	 *	The array of elements to add to the target.
	 * @param Target
	 *	The array to which elements will be added.
	 */
	template <typename T>
	void AddAllUnique(TArray<T> NewElements, TArray<T>& Target)
	{
		TSet<T> TargetIndex = TSet<T>(Target);

		for (const auto& NewElement : NewElements)
		{
			// We could use Target.AddUnique() but for larger sets it's O(N^2) whereas building a set from the target
			// and then using the set as an index of what's in the array should cost only O(2N).
			if (!TargetIndex.Contains(NewElement))
			{
				Target.Add(Target);
			}
		}
	}

	/**
	 * Applies a transformation function to the values in an array, then returns the result of the transformation.
	 *
	 * The original array is not modified.
	 *
	 * @tparam In
	 *	The type of elements in the input array.
	 * @tparam Out
	 *	The type of elements in the output array. (The type into which input elements will be transformed).
	 * @tparam Func
	 *	The type of the lambda function to invoke on each element of the input array to return a new element to add to
	 *	the output array.
	 *
	 * @param Elements
	 *	The array of values to map.
	 * @param Callable
	 *	The transformation function/lambda invoked on each element in order to get the mapped value.
	 *
	 * @return
	 *	The array of values that resulted from applying the transformation to every value of the source array.
	 */
	template <typename Out, typename In, typename Func>
	TArray<Out> Map(const TArray<In> Elements, const Func Callable)
	{
		TArray<Out> Result;

		for (const In& Element : Elements)
		{
			const Out MappingOutput = Callable(Element);

			Result.Add(MappingOutput);
		}

		return Result;
	}

	/**
	 * Collapses all of the values of an array to a single value by use of a transformation function.
	 *
	 * The transformation function receives a pair of values -- the "previous value" and the "current value". The
	 * transformation function is invoked once for each value in the original array. For the first value of the array,
	 * the "previous value" is the starting value supplied to this function, and the "current value" is the first value
	 * in the original array. For each subsequent call, the "previous value" is the result that was returned during the
	 * previous call of the transformation function.
	 *
	 * The original array is not modified.
	 *
	 * @tparam In
	 *	The type of elements in the input array.
	 * @tparam Out
	 *	The type of result to return. (The type into which all input elements will be consolidated).
	 * @tparam Func
	 *	The type of the lambda function to invoke on each element of the input array, applying a transformation on the
	 *	element and the accumulated result to return a new output value.
	 *
	 * @param Elements
	 *	The array of values to reduce.
	 * @param StartingValue
	 *	The value passed-in to the Callable along side the first value of the array. If the array is empty, this will be
	 *	the value returned.
	 * @param Callable
	 *	The transformation function/lambda invoked to combine each element with the result of flattening/reducing the
	 *	previous element. This function is expected to take in the following two parameters and return a value that
	 *	matches the "Out" type:
	 *	  - PreviousValue: Which must match the "Out" type.
	 *	  - CurrentValue: Which must match the "In" type.
	 *
	 * @return
	 *	The result of reducing the values of the array.
	 */
	template <typename Out, typename In, typename Func>
	Out Reduce(const TArray<In> Elements, const Out StartingValue, const Func Callable)
	{
		Out PreviousValue = StartingValue;

		for (const In& CurrentValue : Elements)
		{
			PreviousValue = Callable(PreviousValue, CurrentValue);
		}

		return PreviousValue;
	}

	/**
	 * Filters out null values from an array.
	 *
	 * The original array is not modified.
	 *
	 * @tparam T
	 *	The type of elements in the array.
	 *
	 * @param Elements
	 *	The array of values to filter.
	 *
	 * @return
	 *	A new array containing all the values of the original array that were not null.
	 */
	template <typename T>
	TArray<T> Filter(const TArray<T> Elements)
	{
		return Filter<T>(
			Elements,
			[](const T Element)
			{
				return Element != nullptr;
			}
		);
	}

	/**
	 * Filters the values of an array using a predicate function.
	 *
	 * The predicate receives each value of the array and is expected to return true if a value should be included, or
	 * false if it should be omitted.
	 *
	 * The original array is not modified.
	 *
	 * @tparam T
	 *	The type of elements in the array.
	 *
	 * @param Elements
	 *	The array of values to filter.
	 * @param Callable
	 *	The predicate function/lambda invoked for each element of the array. This function is expected to take in a
	 *	parameter of type "In" and return a boolean.
	 *
	 * @return
	 *	A new array containing all the values of the original array for which the callable returned "true".
	 */
	template <typename T, typename Func>
	TArray<T> Filter(const TArray<T> Elements, const Func Callable)
	{
		return Elements.FilterByPredicate(Callable);
	}

	/**
	 * Typecast one array to an array of another type.
	 *
	 * This should only be used in cases when the types are compatible. For example, to downcast a generic type like
	 * TArray<Actor*> to TArray<IPF2CharacterInterface*> when it is know that an array of actors must all implement a
	 * particular interface.
	 *
	 * In development builds, the sizes of the types are checked for compatibility with assertions.
	 *
	 * Credit for this approach:
	 * https://forums.unrealengine.com/t/how-to-cast-tarray-to-another-type/293689/13
	 *
	 * @param InArray
	 *	The array to typecast.
	 *
	 * @return
	 *	The typecast array.
	 */
	template <typename In, typename Out>
	TArray<Out> Cast(TArray<In> InArray)
	{
		TArray<Out> Result;

		// Confirm compatible data types.
		check(sizeof(In) == sizeof(Out));

		Result = MoveTemp(*reinterpret_cast<TArray<Out>*>(&InArray));

		// Confirm all elements were moved.
		check(InArray.Num() == 0);

		return Result;
	}
}
