// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// Adapted from "BlueprintGraph/Classes/K2Node_ComponentBoundEvent.h" (Unreal Engine 5.1), which is Copyright
// Epic Games, Inc. Licensed only for use with Unreal Engine.

#pragma once

#include <K2Node.h>
#include <K2Node_Event.h>

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2K2Node_EventEmitterBoundEvent.generated.h"

/**
 * A Blueprint node for binding logic to an event exposed by the Events Object of an Event Emitter.
 *
 * In an event graph, this looks identical to a normal event binding node, but under the hood this actually eliminates
 * the friction of exposing delegates through an interface by allowing the desired delegate properties to be exposed by
 * each interface via a concrete Events Object. Then, the OpenPF2 Editor Support module automatically exposes the
 * delegate properties of such events objects as though they were events on the Event Emitter (the object implementing
 * the interfaces and exposing the events object). When a game designer elects to bind to such an event, it creates a
 * node of this special type so that at run time the event graph knows how to bind to the appropriate delegate property
 * of the events object.
 *
 * @see IPF2EventEmitterInterface
 */
UCLASS(MinimalAPI)
class UPF2K2Node_EventEmitterBoundEvent : public UK2Node_Event, public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Protected Static Fields
	// =================================================================================================================
	/**
	 * Creates a new instance of this node in the specified Blueprint for the specified emitter, delegate, and event.
	 *
	 * @param Blueprint
	 *	The blueprint containing the event graph into which the new node should be placed.
	 * @param EmitterVariable
	 *	The property of the Blueprint that contains the event emitter object implementing the IPF2EventEmitterInterface.
	 * @param EmitterClass
	 *	The type of object in EmitterVariable.
	 * @param EventName
	 *	The internal name to create for the event. This must be unique within the graph.
	 */
	OPENPF2BLUEPRINTNODES_API static UPF2K2Node_EventEmitterBoundEvent* CreateNew(const UBlueprint* Blueprint,
	                                                                              FObjectProperty*  EmitterVariable,
	                                                                              const UClass*     EmitterClass,
	                                                                              const FName       EventName);

	/**
	 * Locates an existing instance of this node in the specified Blueprint having the specified emitter and event name.
	 *
	 * @param Blueprint
	 *	The blueprint containing the event graph into which the new node should be placed.
	 * @param EmitterVariableName
	 *	The name of the property in the Blueprint that contains the event emitter object implementing the
	 *	IPF2EventEmitterInterface.
	 * @param EventName
	 *	The internal, unique name of the event to locate.
	 */
	OPENPF2BLUEPRINTNODES_API static UPF2K2Node_EventEmitterBoundEvent* FindExisting(
		const UBlueprint* Blueprint,
		const FName       EmitterVariableName,
		const FName       EventName);

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The name of the property in the Blueprint that contains the event emitter object.
	 *
	 * This object must implement the IPF2EventEmitterInterface.
	 */
	UPROPERTY()
	FName EmitterVariableName;

	/**
	 * The class that authoritatively owns the delegate property.
	 */
	UPROPERTY()
	TObjectPtr<UClass> DelegateOwnerClass;

	/**
	 * The name of the delegate property in the events object.
	 */
	UPROPERTY()
	FName DelegatePropertyName;

	/**
	 * The cached name of this node.
	 *
	 * This is cached to avoid the cost of constructing FText strings on repaints of the event graph. This is
	 * invalidated any time that this node is reconstructed.
	 */
	FNodeTextCache CachedNodeTitle;

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Initializes this instance for a particular emitter and delegate property.
	 *
	 * @param EmitterVariable
	 *	The property of the Blueprint that contains the event emitter object implementing the IPF2EventEmitterInterface.
	 * @param DelegateProperty
	 *	The target event delegate property of the events object.
	 */
	OPENPF2BLUEPRINTNODES_API void Initialize(
		FObjectProperty const*            EmitterVariable,
		const FMulticastDelegateProperty* DelegateProperty);

	// =================================================================================================================
	// Public Methods - UObject Overrides
	// =================================================================================================================
	virtual bool Modify(const bool bAlwaysMarkDirty = true) override;

	// =================================================================================================================
	// Public Methods - UEdGraphNode Overrides
	// =================================================================================================================
	virtual void ReconstructNode() override;

	virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual FText GetTooltipText() const override;

	virtual bool HasDeprecatedReference() const override;

	virtual FEdGraphNodeDeprecationResponse GetDeprecationResponse(
		EEdGraphNodeDeprecationType DeprecationType) const override;

	// =================================================================================================================
	// Public Methods - K2Node Overrides
	// =================================================================================================================
	virtual bool NodeCausesStructuralBlueprintChange() const override
	{
		return true;
	}

	virtual UClass* GetDynamicBindingClass() const override;

	virtual void RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const override;

	virtual void HandleVariableRenamed(UBlueprint*  InBlueprint,
	                                   UClass*      InVariableClass,
	                                   UEdGraph*    InGraph,
	                                   const FName& InOldVarName,
	                                   const FName& InNewVarName) override;

	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;

	// =================================================================================================================
	// Public Methods - K2Node_Event Overrides
	// =================================================================================================================
	virtual bool IsUsedByAuthorityOnlyDelegate() const override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;

protected:
	/**
	 * Checks if the Blueprint still contains the event emitter, and the event emitter still has the delegate property.
	 *
	 * @return
	 *	True if the Blueprint has a variable with the name that this event was bound with, that variable is an event
	 *	emitter, and that event emitter has a delegate property with the name that this event was bound with; or false,
	 *	otherwise.
	 */
	bool IsDelegateValid() const;

	/**
	 * Gets the delegate property of the events object in the event emitter property of the blueprint.
	 *
	 * @return
	 *	Either the pointer to the target delegate property of the events object; or null if the delegate property cannot
	 *	be found.
	 */
	FMulticastDelegateProperty* GetTargetDelegateProperty() const;

	/**
	 * Gets either the delegate property of the events object, or what it was remapped to by config.
	 *
	 * @return
	 *	Either the pointer to the target delegate property of the events object; or null if the delegate property cannot
	 *	be found, even after applying remapping.
	 */
	FMulticastDelegateProperty* GetTargetOrRemappedDelegateProperty() const;

	/**
	 * Gets the name to display for the delegate property.
	 *
	 * @return
	 *	The display name of the delegate property.
	 */
	FText GetDelegateDisplayName() const;
};
