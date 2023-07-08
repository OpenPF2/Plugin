// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <K2Node.h>

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2K2Node_ForEachMapPair.generated.h"

class FBlueprintActionDatabaseRegistrar;
class FName;
class UEdGraph;
class UObject;
struct FLinearColor;

/**
 * A Blueprint node for iterating over each key and value of a map.
 */
UCLASS(MinimalAPI)
class UPF2K2Node_ForEachMapPair : public UK2Node, public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - UEdGraphNode Overrides
	// =================================================================================================================
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
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

	virtual int32 GetNodeRefreshPriority() const override
	{
		// ReSharper disable once CppRedundantQualifier
		return EBaseNodeRefreshPriority::Low_UsesDependentWildcard;
	}

	virtual bool IsNodePure() const override
	{
		return false;
	}

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;

protected:
	/**
	 * The name of the pin that provides the map over which to iterate.
	 */
	static const FName MapInputPinName;

	/**
	 * The name of the exec pin that is invoked for each pair of the map.
	 */
	static const FName InsideLoopPinName;

	/**
	 * The name of the pin that provides the key in each pair to logic inside the loop.
	 */
	static const FName CurrentKeyPinName;

	/**
	 * The name of the pin that provides the value in each pair to logic inside the loop.
	 */
	static const FName CurrentValuePinName;

	/**
	 * Gets the map input pin object.
	 *
	 * @return
	 *	The input graph pin from this node instance.
	 */
	FORCEINLINE UEdGraphPin* GetMapInputPin() const
	{
		return this->FindPinChecked(MapInputPinName, EGPD_Input);
	}

	/**
	 * Gets the exec pin object for logic inside the loop.
	 *
	 * @return
	 *	The exec graph pin for inside the loop from this node instance.
	 */
	FORCEINLINE UEdGraphPin* GetInsideLoopPin() const
	{
		return this->FindPinChecked(InsideLoopPinName, EGPD_Output);
	}

	/**
	 * Gets the key output pin object.
	 *
	 * @return
	 *	The key output graph pin from this node instance.
	 */
	FORCEINLINE UEdGraphPin* GetCurrentKeyPin() const
	{
		return this->FindPinChecked(CurrentKeyPinName, EGPD_Output);
	}

	/**
	 * Gets the value output pin object.
	 *
	 * @return
	 *	The value output graph pin from this node instance.
	 */
	FORCEINLINE UEdGraphPin* GetCurrentValuePin() const
	{
		return this->FindPinChecked(CurrentValuePinName, EGPD_Output);
	}

	/**
	 * Gets the "Completed" execution pin object.
	 *
	 * @return
	 *	The graph pin from this node instance that is executed when the loop is complete.
	 */
	FORCEINLINE UEdGraphPin* GetLoopCompletedPin() const
	{
		return this->GetThenPin();
	}

	/**
	 * Updates the specified pin of this node to match the type of the pin to which it is connected.
	 *
	 * This method only needs to be called on one of the pins of this node, as one call will affect all input and output
	 * pins accordingly. The pins of this node start out as wildcard pins, so this is how the wildcard pins on
	 * this node assume the desired types from pins in other nodes in the graph.
	 *
	 * If the specified pin is not connected to another node yet, calling this method has no effect.
	 *
	 * @param LocalPin
	 *	The pin in this node that should be updated to match the type of any pin to which it is connected.
	 */
	void PropagateLinkedPinType(UEdGraphPin* LocalPin);

	/**
	 * Updates the pins of this node to match the type of the given other input pin.
	 *
	 * If the given other pin is a wildcard pin, calling this method has no effect.
	 *
	 * @param OtherPin
	 *	The pin in the other node that will provide the type for the local input pin.
	 */
	void PropagateInputPinType(const UEdGraphPin* OtherPin);

	/**
	 * Resets the specified pin of this node to accepting a wildcard type.
	 *
	 * @param TargetPin
	 *	The pin to reset to being a wildcard type.
	 */
	void ResetPinToWildcard(UEdGraphPin* TargetPin);
};
