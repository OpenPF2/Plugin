// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <EdGraph/EdGraphPin.h>

#include <Internationalization/Text.h>

/**
 * Various utility methods for simplifying the logic of Blueprint nodes.
 */
namespace PF2BlueprintNodeUtilities
{
	/**
	 * Inverts the key and value types of a map graph pin, so that the key type becomes the value type and vice-versa.
	 *
	 * If the original pin is const, the inverse is const.
	 * If the original pin is a reference, the inverse is a reference.
	 *
	 * The const-ness of the value of the original pin is ignored.
	 *
	 * This can only be used on map pin types.
	 *
	 * @param PinType
	 *	The map pin type to invert.
	 *
	 * @return
	 *	The invert map pin type. The key type matches the value type of PinType, and the value type matches the
	 *	key type of PinType.
	 */
	OPENPF2BLUEPRINTNODES_API FEdGraphPinType InvertMapPinType(const FEdGraphPinType& PinType);

	/**
	 * Gets a human-friendly description of a blueprint pin.
	 *
	 * @param PinType
	 *	The type of blueprint pin.
	 *
	 * @return
	 *	The human-friendly description.
	 */
	OPENPF2BLUEPRINTNODES_API FText GetTypeDescription(const FEdGraphPinType& PinType);

	/**
	 * Gets a human-friendly description of the type of a terminal graph pin.
	 *
	 * @param TerminalPinType
	 *	The type of the terminal pin.
	 *
	 * @return
	 *	The human-friendly description of the pin type.
	 */
	OPENPF2BLUEPRINTNODES_API FText DescribePinType(const FEdGraphTerminalType& TerminalPinType);

	/**
	 * Gets a human-friendly description of the type of a node graph pin.
	 *
	 * @param PinType
	 *	The type of the graph pin.
	 *
	 * @return
	 *	The human-friendly description of the pin type.
	 */
	OPENPF2BLUEPRINTNODES_API FText DescribePinType(const FEdGraphPinType& PinType);
}
