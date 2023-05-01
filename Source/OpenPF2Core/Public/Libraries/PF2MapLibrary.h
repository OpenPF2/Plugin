// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include "PF2MapLibrary.generated.h"

// =====================================================================================================================
// Macro Declarations
// =====================================================================================================================
#define P_GET_TMAP_REF_UNCHECKED(ParamName)                                                \
	Stack.MostRecentProperty = nullptr;                                                    \
	Stack.StepCompiledIn<FMapProperty>(nullptr);                                           \
	void* ParamName##Addr = Stack.MostRecentPropertyAddress;                               \
	FMapProperty* ParamName##Property = CastField<FMapProperty>(Stack.MostRecentProperty); \
	if (ParamName##Property == nullptr)                                                    \
	{                                                                                      \
		Stack.bArrayContextFailed = true;                                                  \
		return;                                                                            \
	}

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Function library of TMap-related utility methods to improve game designer quality of life when working with OpenPF2.
 */
UCLASS()
class OPENPF2CORE_API UPF2MapLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	// ReSharper disable CppFunctionIsNotImplemented
	/**
	 * Inverts the keys and values of a map, so that for each pair the key becomes the value and vice-versa.
	 *
	 * @param InputMap
	 *	The map to invert.
	 * @param OutputMap
	 *	A reference to the map that will receive the inverted map output.
	 */
	UFUNCTION(
		BlueprintCallable,
		CustomThunk,
		BlueprintPure,
		BlueprintInternalUseOnly,
		meta=(CustomStructureParam="InputMap", MapParam="OutputMap")
	)
	static void InvertMap(const TMap<int32, int32>& InputMap, TMap<int32, int32>& OutputMap);
	DECLARE_FUNCTION(execInvertMap);
	// ReSharper restore CppFunctionIsNotImplemented

protected:
	// ReSharper disable IdentifierTypo
	/**
	 * The native C++ portion of the implementation for InvertMap.
	 *
	 * This is invoked by the custom thunk for InvertMap.
	 *
	 * @param InputMapAddr
	 *	Pointer to the input map.
	 * @param InputMapProperty
	 *	The Blueprint type information about the input map.
	 * @param OutputMapAddr
	 *	Pointer to the output map.
	 * @param OutputMapProperty
	 *	The Blueprint type information about the output map.
	 */
	static void GenericMap_Invert(
		const void* InputMapAddr,
		const FMapProperty* InputMapProperty,
		const void* OutputMapAddr,
		const FMapProperty* OutputMapProperty
	);
	// ReSharper restore IdentifierTypo
};
