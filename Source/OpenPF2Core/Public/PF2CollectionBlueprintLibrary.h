// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "PF2CollectionBlueprintLibrary.generated.h"

/**
 * Blueprint function library for working with maps and other collection types in OpenPF2.
 */
UCLASS()
class OPENPF2CORE_API UPF2CollectionBlueprintLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Builds a map by using one array for keys and another for its values.
	 *
	 * Both arrays must be the same length. A pair is assembled from each corresponding index in both arrays.
	 *
	 * @param Keys
	 *	The list of keys.
	 * @param Values
	 *	The list of values
	 * @param TargetMap
	 *   The new map.
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta=(DisplayName="Build", CompactNodeTitle="BUILD MAP", MapKeyParam="Keys", MapValueParam="Values", MapParam="TargetMap"), Category="Utilities|Map")
	static void Map_Build(const TArray<int32>& Keys, const TArray<int32>& Values, TMap<int32, int32>& TargetMap);

	/**
	 * Inverts the keys and values of a map, so that for each pair the key becomes the value and vice-versa.
	 *
	 * @param InputMap
	 *	The map to invert.
	 * @param OutputMap
	 *	Reference to the inverted map.
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, meta=(DisplayName="Invert", CompactNodeTitle="INVERT", MapParam="InputMap"), Category="Utilities|Map")
	static void Map_Invert(const TMap<int32, int32>& InputMap, TMap<int32, int32>& OutputMap);

	DECLARE_FUNCTION(execMap_Build)
	{
		FArrayProperty* KeysProperty;
		void*           KeysAddress;
		FArrayProperty* ValuesProperty;
		void*           ValuesAddress;
		FMapProperty*   TargetMapProperty;
		void*           TargetMapAddress;

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(nullptr);

		KeysProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		KeysAddress  = Stack.MostRecentPropertyAddress;

		if (!KeysProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(nullptr);

		ValuesProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		ValuesAddress  = Stack.MostRecentPropertyAddress;

		if (!ValuesProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FMapProperty>(nullptr);

		TargetMapProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
		TargetMapAddress  = Stack.MostRecentPropertyAddress;

		if (!TargetMapProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericMap_Build(KeysProperty, KeysAddress, ValuesProperty, ValuesAddress, TargetMapProperty, TargetMapAddress);
		P_NATIVE_END
	}

	DECLARE_FUNCTION(execMap_Invert)
	{
		FMapProperty* InputMapProperty;
		void*         InputMapAddress;
		FMapProperty* OutputMapProperty;
		void*         OutputMapAddress;

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FMapProperty>(nullptr);

		InputMapProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
		InputMapAddress  = Stack.MostRecentPropertyAddress;

		if (!InputMapProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FMapProperty>(nullptr);

		OutputMapProperty = CastField<FMapProperty>(Stack.MostRecentProperty);
		OutputMapAddress  = Stack.MostRecentPropertyAddress;

		if (!OutputMapProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericMap_Invert(InputMapProperty, InputMapAddress, OutputMapProperty, OutputMapAddress);
		P_NATIVE_END
	}

	/**
	 * Native implementation for the "Build" map function.
	 *
	 * Builds a map by using one array for keys and another for its values.
	 *
	 * @param KeysProperty
	 *	The property associated with the keys for the new map.
	 * @param Keys
	 *	Pointer to the raw data representation of the keys for the new map.
	 * @param ValuesProperty
	 *	The property associated with the values for the new map.
	 * @param Values
	 *	Pointer to the raw data representation of the values for the new map.
	 * @param TargetMapProperty
	 *	The property associated with the new map.
	 * @param TargetMap
	 *	Pointer to the raw data representation of the target map.
	 */
	static void GenericMap_Build(const FArrayProperty* KeysProperty,
	                             const void*           Keys,
	                             const FArrayProperty* ValuesProperty,
	                             const void*           Values,
	                             const FMapProperty*   TargetMapProperty,
	                             void*                 TargetMap);

	/**
	 * Native implementation for the "Invert" map function.
	 *
	 * Inverts the keys and values of a map, so that for each pair the key becomes the value and vice-versa.
	 *
	 * @param InputMapProperty
	 *	The property associated with the input map.
	 * @param InputMap
	 *	Pointer to the raw data representation of the input map.
	 * @param OutputMapProperty
	 *	The property associated with the output map.
	 * @param OutputMap
	 *	Pointer to the raw data representation of the output map.
	 */
	static void GenericMap_Invert(const FMapProperty* InputMapProperty,
	                              const void*         InputMap,
	                              const FMapProperty* OutputMapProperty,
	                              void*               OutputMap);
};
