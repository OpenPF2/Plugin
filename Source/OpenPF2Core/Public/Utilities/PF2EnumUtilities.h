// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

/**
 * Utility logic for working with static enums.
 */
namespace PF2EnumUtilities
{
	/**
	 * Convert the value of an enum to a name.
	 *
	 * @tparam E The enum type.
	 *
	 * @param EnumValue
	 *	The enumerated type value to convert to a name.
	 *
	 * @return
	 *	The key/name that corresponds to the value in the enumerated type.
	 */
	template<typename E>
	OPENPF2CORE_API FName ToName(const E EnumValue)
	{
		const FName Name = StaticEnum<E>()->GetNameByValue(static_cast<__underlying_type(E)>(EnumValue));

		check(Name.IsValid());

		return Name;
	}

	/**
	 * Convert the value of an enum to a string.
	 *
	 * @tparam E The enum type.
	 *
	 * @param EnumValue
	 *	The enumerated type value to convert to a string.
	 *
	 * @return
	 *	The key/name that corresponds to the value in the enumerated type.
	 */
	template<typename E>
	OPENPF2CORE_API FString ToString(const E EnumValue)
	{
		FString Name = StaticEnum<E>()->GetNameStringByValue(static_cast<__underlying_type(E)>(EnumValue));

		check(Name.Len() != 0);

		return Name;
	}
}
