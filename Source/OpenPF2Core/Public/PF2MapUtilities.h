// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "UObject/ObjectMacros.h"

/**
 * Various utilities for functional programming with maps and similar structures.
 */
namespace PF2MapUtilities
{
	/**
	 * Inverts the keys and values of a map, so that for each pair the key becomes the value and vice-versa.
	 *
	 * @param InputMap
	 *	The map to invert.
	 *
	 * @return
	 *	The inverted map.
	 */
	template<typename Key, typename Value>
	TMap<Value, Key> Invert(const TMap<Key, Value> InputMap)
	{
		TMap<Value, Key> OutputMap;

		for (const auto& Pair : InputMap)
		{
			OutputMap.Add(Pair.Value, Pair.Key);
		}

		return OutputMap;
	}
}
