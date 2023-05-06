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
// ReSharper disable once IdentifierTypo
#define P_GET_TMAP_PTR_UNCHECKED(ParamName)                                                \
	Stack.MostRecentProperty = nullptr;                                                    \
	Stack.StepCompiledIn<FMapProperty>(nullptr);                                           \
	void* ParamName##Addr = Stack.MostRecentPropertyAddress;                               \
	FMapProperty* ParamName##Property = CastField<FMapProperty>(Stack.MostRecentProperty); \
	if (ParamName##Property == nullptr)                                                    \
	{                                                                                      \
		Stack.bArrayContextFailed = true;                                                  \
		return;                                                                            \
	}

#define P_GET_OBJECT_PTR_UNCHECKED(ParamName)                                              \
	Stack.MostRecentProperty = nullptr;                                                    \
	Stack.StepCompiledIn<FUInt32Property>(nullptr);                                        \
	void* ParamName##Addr = Stack.MostRecentPropertyAddress;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * A Blueprint-friendly wrapper around an FScriptMapHelper pair iterator.
 *
 * This object abstracts away the minutia of working with maps of any type of key or value.
 */
USTRUCT(BlueprintType)
struct FPF2MapPairIterator
{
	GENERATED_BODY()

	/**
	 * Default constructor for FPF2MapPairIterator.
	 */
	explicit FPF2MapPairIterator() : MapHelper(nullptr), Iterator(nullptr)
	{
	}

	/**
	 * Constructs an iterator for navigating through the pairs of the given map.
	 *
	 * @param MapProperty
	 *	Metadata about the structure and type of map.
	 * @param MapData
	 *	A pointer to the raw data in the map.
	 */
	explicit FPF2MapPairIterator(const FMapProperty* MapProperty, const void* MapData) : Iterator(nullptr)
	{
		this->MapHelper = MakeShared<FScriptMapHelper>(MapProperty, MapData);
		this->Iterator  = MakeShared<FScriptMapHelper::FIterator>(*this->MapHelper);
	}

	/**
	 * Gets whether this iterator is currently pointing at a valid pair/location in the map.
	 *
	 * @return
	 *	- true if the iterator is pointing at a valid pair in the element.
	 *	- false if the iterator has moved past the last element in the map or was initialized on an empty map.
	 */
	FORCEINLINE bool HasPair() const
	{
		return ((this->Iterator != nullptr) && *this->Iterator);
	}

	/**
	 * Increments the position of the iterator to the next pair, if available.
	 *
	 * @return
	 *	This object.
	 */
	FORCEINLINE FPF2MapPairIterator& operator++()
	{
		++(*this->Iterator);
		return *this;
	}

	/**
	 * Gets the key from the current pair and copies it into the variable de-referenced by the given pointer.
	 *
	 * @param OutKeyPtr
	 *	A pointer to the address where the value should be copied. This should always correspond to the BASE + OFFSET,
	 *	where:
	 *	- BASE   = (for member properties) the address of the UObject which contains this data
	 *	           (for locals/parameters) the address of the space allocated for the function's locals
	 *	- OFFSET = the Offset of the FProperty
	 */
	FORCEINLINE void GetCurrentKey(void* OutKeyPtr) const
	{
		check(this->HasPair());

		{
			const uint8*     MapRelativeKeyPtr = this->MapHelper->GetKeyPtr(**this->Iterator);
			const FProperty* KeyProperty       = this->MapHelper->GetKeyProperty();

			KeyProperty->CopyCompleteValueFromScriptVM(OutKeyPtr, MapRelativeKeyPtr);
		}
	}

	/**
	 * Gets the value from the current pair and copies it into the variable de-referenced by the given pointer.
	 *
	 * @param OutValuePtr
	 *	A pointer to the address where the value should be copied. This should always correspond to the BASE + OFFSET,
	 *	where:
	 *	- BASE   = (for member properties) the address of the UObject which contains this data
	 *	           (for locals/parameters) the address of the space allocated for the function's locals
	 *	- OFFSET = the Offset of the FProperty
	 */
	FORCEINLINE void GetCurrentValue(void* OutValuePtr) const
	{
		check(this->HasPair());

		{
			const uint8*     MapRelativeValuePtr = this->MapHelper->GetValuePtr(**this->Iterator);
			const FProperty* ValueProperty       = this->MapHelper->GetValueProperty();

			ValueProperty->CopyCompleteValueFromScriptVM(OutValuePtr, MapRelativeValuePtr);
		}
	}

protected:
	/**
	 * A wrapper around the raw data of the map.
	 */
	TSharedPtr<FScriptMapHelper> MapHelper;

	/**
	 * A special iterator provided by the map helper for navigating through map pairs.
	 */
	TSharedPtr<FScriptMapHelper::FIterator> Iterator;
};

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

	/**
	 * Obtains an iterator for pairs of a map.
	 *
	 * @param Map
	 *	The map for which an iterator is needed.
	 *
	 * @return
	 *	The new iterator.
	 */
	UFUNCTION(
		BlueprintCallable,
		CustomThunk,
		BlueprintPure,
		BlueprintInternalUseOnly,
		meta=(CustomStructureParam="Map")
	)
	static UPARAM(DisplayName = "Iterator") FPF2MapPairIterator GetMapPairIterator(
		UPARAM(ref)
		TMap<int32, int32>& Map
	);
	DECLARE_FUNCTION(execGetMapPairIterator);

	/**
	 * Moves a map iterator to the next pair in the map.
	 *
	 * @param Iterator
	 *	The map iterator that will be incremented.
	 */
	UFUNCTION(
		BlueprintCallable,
		CustomThunk,
		BlueprintInternalUseOnly
	)
	static void IncrementMapPairIterator(
		UPARAM(ref)
		FPF2MapPairIterator& Iterator
	);
	DECLARE_FUNCTION(execIncrementMapPairIterator);

	/**
	 * Determines if a map pair iterator is pointing at a valid pair.
	 *
	 * This will return false if the map is empty or the iterator has advanced of the end of the map.
	 *
	 * @param Iterator
	 *	The iterator to check the status of.
	 */
	UFUNCTION(
		BlueprintCallable,
		CustomThunk,
		BlueprintPure,
		BlueprintInternalUseOnly
	)
	static UPARAM(DisplayName = "Has pair") bool DoesMapPairIteratorHavePair(const FPF2MapPairIterator& Iterator);
	DECLARE_FUNCTION(execDoesMapPairIteratorHavePair);

	/**
	 * Gets the current key from a map pair iterator.
	 *
	 * If the iterator is not pointing at a valid pair, INDEX_NONE is returned.
	 *
	 * @param Iterator
	 *	The map pair iterator from which a key will be returned.
	 * @param Key
	 *	A reference to the variable that will receive the key.
	 */
	UFUNCTION(
		BlueprintCallable,
		CustomThunk,
		BlueprintPure,
		BlueprintInternalUseOnly,
		meta=(CustomStructureParam="Key")
	)
	static void GetKeyFromMapPairIterator(const FPF2MapPairIterator& Iterator, int32& Key);
	DECLARE_FUNCTION(execGetKeyFromMapPairIterator);

	/**
	 * Gets the current value from a map pair iterator.
	 *
	 * If the iterator is not pointing at a valid pair, INDEX_NONE is returned.
	 *
	 * @param Iterator
	 *	The map pair iterator from which a value will be returned.
	 * @param Value
	 *	A reference to the variable that will receive the value.
	 */
	UFUNCTION(
		BlueprintCallable,
		CustomThunk,
		BlueprintPure,
		BlueprintInternalUseOnly,
		meta=(CustomStructureParam="Value")
	)
	static void GetValueFromMapPairIterator(const FPF2MapPairIterator& Iterator, int32& Value);
	DECLARE_FUNCTION(execGetValueFromMapPairIterator);
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
