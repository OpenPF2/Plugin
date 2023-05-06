// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <K2Node.h>

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2K2Node_MapInvert.generated.h"

class UEdGraphPin;

/**
 * A custom Blueprint node for inverting maps.
 *
 * During inversion, the keys and values of a map, so that for each pair the key becomes the value and vice-versa.
 */
UCLASS(MinimalAPI)
class UPF2K2Node_MapInvert : public UK2Node, public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - UEdGraphNode Overrides
	// =================================================================================================================
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void AllocateDefaultPins() override;

	// =================================================================================================================
	// Public Methods - UK2Node Overrides
	// =================================================================================================================
	virtual FText GetMenuCategory() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PostReconstructNode() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

	virtual bool ShouldDrawCompact() const override
	{
		return true;
	};

	virtual int32 GetNodeRefreshPriority() const override
	{
		// ReSharper disable once CppRedundantQualifier
		return EBaseNodeRefreshPriority::Low_UsesDependentWildcard;
	}

	virtual bool IsNodePure() const override
	{
		return true;
	}

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;

protected:
	/**
	 * The name of the pin on Invert nodes that passes in the original map.
	 */
	static const FName InputPinName;

	/**
	 * The name of the pin on Invert nodes that receives the inverse map output.
	 */
	static const FName OutputPinName;

	/**
	 * Gets the input pin object.
	 *
	 * @return
	 *	The input graph pin from this node instance.
	 */
	UEdGraphPin* GetInputPin() const;

	/**
	 * Gets the output pin object.
	 *
	 * @return
	 *	The output graph pin from this node instance.
	 */
	UEdGraphPin* GetOutputPin() const;

	/**
	 * Updates the specified pin of this node to match the type of the pin to which it is connected.
	 *
	 * This method only needs to be called on one of the pins of this node, as one call will affect both the input and
	 * output pins accordingly. The pins of this node start out as wildcard pins, so this is how the wildcard pins on
	 * this node assume the desired types from pins in other nodes in the graph.
	 *
	 * If the specified pin is not connected to another node yet, calling this method has no effect.
	 *
	 * @param LocalPin
	 *	The pin in this node that should be updated to match the type of any pin to which it is connected.
	 */
	void PropagateLinkedPinType(UEdGraphPin* LocalPin);

	/**
	 * Updates the specified pin of this node to match the type of the given other pin.
	 *
	 * This method only needs to be called on one of the pins of this node, as one call will affect both the input and
	 * output pins accordingly. The pins of this node start out as wildcard pins, so this is how the wildcard pins on
	 * this node assume the desired types from pins in other nodes in the graph.
	 *
	 * If the given other pin is a wildcard pin, calling this method has no effect.
	 *
	 * @param OtherPin
	 *	The pin in the other node that will provide the type for the local pin.
	 * @param LocalPin
	 *	The pin in this node that should be updated to match the type of the pin in the other node.
	 */
	void PropagatePinType(const UEdGraphPin* OtherPin, const UEdGraphPin* LocalPin);

	/**
	 * Updates the specified pins of this node to match the specified pin type.
	 *
	 * The "Regular" target pin will be updated to match the given pin type, while the "Inverse" target pin will receive
	 * its inverse. In other words, if the given pin type is "Map<String, Int>", then the regular target pin will be set
	 * to "Map<String, Int>" while the inverse target pin will be set to "Map<Int, String>".
	 *
	 * If the given pin type is a wildcard pin, calling this method has no effect.
	 *
	 * @param PinType
	 *	The type to apply to the specified pins.
	 * @param RegularTargetPin
	 *	The pin in this node that should be updated to match the given pin type.
	 * @param InverseTargetPin
	 *	The pin in this node that should be updated to match the inverse of the given pin type.
	 */
	void PropagatePinType(const FEdGraphPinType& PinType,
	                      UEdGraphPin*           RegularTargetPin,
	                      UEdGraphPin*           InverseTargetPin);

	/**
	 * Validates that the key type of the inverse map is valid according to Blueprint business rules.
	 *
	 * Map keys must support GetTypeHash(), so some types that are allowed for values cannot be used as keys (e.g.,
	 * booleans).
	 *
	 * If an invalid type is supplied, this node will disconnect itself from the graph and an appropriate message will
	 * be shown to the user.
	 */
	void ValidateKeyType();

	/**
	 * Resets the specified pin of this node to accepting a wildcard type.
	 *
	 * @param TargetPin
	 *	The pin to reset to being a wildcard type.
	 */
	void ResetPinToWildcard(UEdGraphPin* TargetPin);
};
