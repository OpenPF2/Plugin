// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

/**
 * Utility logic for working with Enums.
 */
namespace PF2EnumUtilities
{
	/**
	 * Convert the value of an enum to a string.
	 *
	 * @param EnumValue
	 *	The enumerated type value to convert to a string.
	 *
	 * @return
	 *	The key/name that corresponds to the value in the enumerated type.
	 */
	template<typename T>
	FString ToString(const T EnumValue)
	{
		FString Name = StaticEnum<T>()->GetNameStringByValue(static_cast<__underlying_type(T)>(EnumValue));

		check(Name.Len() != 0);

		return Name;
	}
}
