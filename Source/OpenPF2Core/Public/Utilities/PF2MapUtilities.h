// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

/**
 * Various utilities for functional programming with maps and similar structures.
 */
namespace PF2MapUtilities
{
	/**
	 * Gets all of the keys of the given map, in the order they appear when iterating over the map.
	 *
	 * @param Map
	 *	The map from which keys are desired.
	 *
	 * @return
	 *	The keys of the map.
	 */
	template<typename Key, typename Value>
	OPENPF2CORE_API TArray<Key> GetKeys(const TMap<Key, Value> Map)
	{
		TArray<Key> Keys;

		for (const auto& Pair : Map)
		{
			Keys.Add(Pair.Key);
		}

		return Keys;
	}

	/**
	 * Gets all of the keys of the given multi-map, in the order they appear when iterating over the map.
	 *
	 * @param Map
	 *	The multi-map from which keys are desired.
	 *
	 * @return
	 *	The keys of the map.
	 */
	template<typename Key, typename Value>
	OPENPF2CORE_API TArray<Key> GetKeys(const TMultiMap<Key, Value> Map)
	{
		TArray<Key> Keys;

		for (const auto& Pair : Map)
		{
			Keys.Add(Pair.Key);
		}

		return Keys;
	}

	/**
	 * Gets all of the values of the given map, in the order they appear when iterating over the map.
	 *
	 * @param Map
	 *	The map from which values are desired.
	 *
	 * @return
	 *	The values of the map.
	 */
	template<typename Key, typename Value>
	OPENPF2CORE_API TArray<Value> GetValues(const TMap<Key, Value> Map)
	{
		TArray<Value> Values;

		for (const auto& Pair : Map)
		{
			Values.Add(Pair.Value);
		}

		return Values;
	}

	/**
	 * Gets all of the values of the given multi-map, in the order they appear when iterating over the map.
	 *
	 * @param Map
	 *	The multi-map from which values are desired.
	 *
	 * @return
	 *	The values of the map.
	 */
	template<typename Key, typename Value>
	OPENPF2CORE_API TArray<Value> GetValues(const TMultiMap<Key, Value> Map)
	{
		TArray<Value> Values;

		for (const auto& Pair : Map)
		{
			Values.Add(Pair.Value);
		}

		return Values;
	}

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
	OPENPF2CORE_API TMap<Value, Key> Invert(const TMap<Key, Value> InputMap)
	{
		TMap<Value, Key> OutputMap;

		for (const auto& Pair : InputMap)
		{
			OutputMap.Add(Pair.Value, Pair.Key);
		}

		return OutputMap;
	}
}
