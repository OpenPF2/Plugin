// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

// ReSharper disable CppRedundantQualifier

#include "Libraries/PF2MapLibrary.h"

DEFINE_FUNCTION(UPF2MapLibrary::execInvertMap)
{
	P_GET_TMAP_REF_UNCHECKED(InputMap);
	P_GET_TMAP_REF_UNCHECKED(OutputMap);
	P_FINISH;

	P_NATIVE_BEGIN;
	UPF2MapLibrary::GenericMap_Invert(InputMapAddr, InputMapProperty, OutputMapAddr, OutputMapProperty);
	P_NATIVE_END;
}

// ReSharper disable IdentifierTypo
void UPF2MapLibrary::GenericMap_Invert(const void* InputMapAddr,
                                       const FMapProperty* InputMapProperty,
                                       const void* OutputMapAddr,
                                       const FMapProperty* OutputMapProperty)
{
	FScriptMapHelper InputMapHelper  = FScriptMapHelper(InputMapProperty, InputMapAddr);
	FScriptMapHelper OutputMapHelper = FScriptMapHelper(OutputMapProperty, OutputMapAddr);

	OutputMapHelper.EmptyValues(InputMapHelper.Num());

	for (FScriptMapHelper::FIterator InputMapIt = InputMapHelper.CreateIterator(); InputMapIt; ++InputMapIt)
	{
		const uint8* InputMapKeyPtr   = InputMapHelper.GetKeyPtr(*InputMapIt);
		const uint8* InputMapValuePtr = InputMapHelper.GetValuePtr(*InputMapIt);

		// Search for a _key_ in the output map that has a hash equal to that of the _value_ from the input map.
		if (OutputMapHelper.FindValueFromHash(InputMapValuePtr))
		{
			FString          ValueString;
			const FProperty* OutputKeyProperty = OutputMapHelper.GetKeyProperty();

			OutputKeyProperty->ExportTextItem_Direct(ValueString, InputMapValuePtr, nullptr, nullptr, PPF_None);

			UE_LOG(
				LogPf2CoreBlueprintNodes,
				Warning,
				TEXT("GenericMap_Invert: Key (%s) already exists in output map (%s)."),
				*ValueString,
				*(OutputMapProperty->GetFullName())
			);
		}

		// Now, invert the key and value as a new pair in the output map.
		OutputMapHelper.AddPair(InputMapValuePtr, InputMapKeyPtr);
	}
}
// ReSharper restore IdentifierTypo
