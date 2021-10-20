// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2CollectionBlueprintLibrary.h"

void UPF2CollectionBlueprintLibrary::GenericMap_Build(const FArrayProperty* KeysProperty,
                                                      const void*           Keys,
                                                      const FArrayProperty* ValuesProperty,
                                                      const void*           Values,
                                                      const FMapProperty*   TargetMapProperty,
                                                      void*                 TargetMap)
{
	if ((Keys != nullptr) && (Values != nullptr) && (TargetMap != nullptr) &&
		ensure(KeysProperty->Inner->ArrayDim == ValuesProperty->Inner->ArrayDim))
	{
		FScriptArrayHelper KeysHelper(KeysProperty, Keys);
		FScriptArrayHelper ValuesHelper(ValuesProperty, Values);
		FScriptMapHelper   TargetMapHelper(TargetMapProperty, TargetMap);

		const int32 MapSize  = KeysHelper.Num();
		int32       CopySize = MapSize;

		TargetMapHelper.EmptyValues();

		for (int32 PairIndex = 0; CopySize > 0; ++PairIndex)
		{
			if (KeysHelper.IsValidIndex(PairIndex) && ValuesHelper.IsValidIndex(PairIndex))
			{
				TargetMapHelper.AddPair(
					KeysHelper.GetRawPtr(PairIndex),
					ValuesHelper.GetRawPtr(PairIndex)
				);

				// BUGBUG: UBlueprintMapLibrary::GenericMap_Keys() and UBlueprintMapLibrary::GenericMap_Values() do
				// things this way instead of comparing PairIndex to the size of the map. The only way that makes sense
				// is if a given pair index can have no value and therefore the index is not bounded by the size of the
				// map. That seems counter-intuitive and non-obvious, though.
				--CopySize;
			}
		}
	}
}

void UPF2CollectionBlueprintLibrary::GenericMap_Invert(const FMapProperty* InputMapProperty,
                                                       const void*         InputMap,
                                                       const FMapProperty* OutputMapProperty,
                                                       void*               OutputMap)
{
	if ((InputMap != nullptr) && (OutputMap != nullptr))
	{
		FScriptMapHelper InputMapHelper(InputMapProperty, InputMap);
		FScriptMapHelper OutputMapHelper(OutputMapProperty, OutputMap);

		const int32 MapSize  = InputMapHelper.Num();
		int32       CopySize = MapSize;

		OutputMapHelper.EmptyValues();

		for (int32 PairIndex = 0; CopySize > 0; ++PairIndex)
		{
			if (InputMapHelper.IsValidIndex(PairIndex))
			{
				OutputMapHelper.AddPair(
					InputMapHelper.GetValuePtr(PairIndex),
					InputMapHelper.GetKeyPtr(PairIndex)
				);

				// BUGBUG: UBlueprintMapLibrary::GenericMap_Keys() and UBlueprintMapLibrary::GenericMap_Values() do
				// things this way instead of comparing PairIndex to the size of the map. The only way that makes sense
				// is if a given pair index can have no value and therefore the index is not bounded by the size of the
				// map. That seems counter-intuitive and non-obvious, though.
				--CopySize;
			}
		}
	}
}
