// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// Adapted from "BlueprintGraph/Classes/K2Node_ComponentBoundEvent.cpp" and
// "Editor/UnrealEd/Private/Kismet2/Kismet2.cpp" (Unreal Engine 5.1), which are Copyright Epic Games, Inc. Licensed only
// for use with Unreal Engine.

#include "PF2K2Node_EventEmitterBoundEvent.h"

#include <EdGraphSchema_K2_Actions.h>

#include <Kismet2/BlueprintEditorUtils.h>
#include <Kismet2/CompilerResultsLog.h>
#include <Kismet2/KismetEditorUtilities.h>

#include <Logging/MessageLog.h>

#include "OpenPF2GameFramework.h"
#include "PF2EventEmitterDelegateBinding.h"
#include "PF2EventEmitterInterface.h"

#define LOCTEXT_NAMESPACE "PF2K2Node"

UPF2K2Node_EventEmitterBoundEvent* UPF2K2Node_EventEmitterBoundEvent::CreateNew(const UBlueprint* Blueprint,
                                                                                FObjectProperty*  EmitterVariable,
                                                                                const UClass*     EmitterClass,
                                                                                const FName       EventName)
{
	UPF2K2Node_EventEmitterBoundEvent* NewNode = nullptr;

	if ((Blueprint != nullptr) && (EmitterVariable != nullptr) && (EmitterClass != nullptr) &&
	    (EventName != NAME_None))
	{
		const UClass* EventsObjectClass = IPF2EventEmitterInterface::GetEventsClassOfCDO(EmitterClass);

		// Find the delegate property we want to bind to.
		FMulticastDelegateProperty* DelegateProperty =
			FindFProperty<FMulticastDelegateProperty>(EventsObjectClass, EventName);

		if (DelegateProperty != nullptr)
		{
			UEdGraph* TargetGraph = Blueprint->GetLastEditedUberGraph();

			if (TargetGraph != nullptr)
			{
				// Figure out a decent place to stick the node
				const FVector2D NewNodePos = TargetGraph->GetGoodPlaceForNewNode();

				// Create a new event node.
				NewNode = FEdGraphSchemaAction_K2NewNode::SpawnNode<UPF2K2Node_EventEmitterBoundEvent>(
					TargetGraph,
					NewNodePos,
					EK2NewNodeFlags::SelectNewNode,
					[EmitterVariable, DelegateProperty](UPF2K2Node_EventEmitterBoundEvent* NewInstance)
					{
						NewInstance->Initialize(EmitterVariable, DelegateProperty);
					}
				);

				// Finally, bring up kismet and jump to the new node.
				if (NewNode != nullptr)
				{
					FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(NewNode);
				}
			}
		}
	}

	return NewNode;
}

UPF2K2Node_EventEmitterBoundEvent* UPF2K2Node_EventEmitterBoundEvent::FindExisting(
	const UBlueprint* Blueprint,
	const FName       EmitterVariableName,
	const FName       EventName)
{
	UPF2K2Node_EventEmitterBoundEvent* Node = nullptr;

	if ((Blueprint != nullptr) && (EmitterVariableName != NAME_None) && (EventName != NAME_None))
	{
		TArray<UPF2K2Node_EventEmitterBoundEvent*> EventNodes;

		FBlueprintEditorUtils::GetAllNodesOfClass(Blueprint, EventNodes);

		for (auto NodeIter = EventNodes.CreateIterator(); NodeIter; ++NodeIter)
		{
			const UPF2K2Node_EventEmitterBoundEvent* BoundEvent = *NodeIter;

			if ((BoundEvent->EmitterVariableName == EmitterVariableName) &&
			    (BoundEvent->DelegatePropertyName == EventName))
			{
				Node = *NodeIter;
				break;
			}
		}
	}

	return Node;
}

void UPF2K2Node_EventEmitterBoundEvent::Initialize(
	FObjectProperty const*            EmitterVariable,
	const FMulticastDelegateProperty* DelegateProperty)
{
	if ((EmitterVariable != nullptr) && (DelegateProperty != nullptr))
	{
		this->EmitterVariableName  = EmitterVariable->GetFName();
		this->DelegatePropertyName = DelegateProperty->GetFName();

		this->DelegateOwnerClass =
			CastChecked<UClass>(DelegateProperty->GetOwner<UObject>())->GetAuthoritativeClass();

		this->EventReference.SetFromField<UFunction>(DelegateProperty->SignatureFunction, false);

		this->CustomFunctionName = FName(
			*FString::Printf(TEXT("BndEventEmitterEvt__%s_%s_%s_%s"),
			*this->GetBlueprint()->GetName(),
			*EmitterVariable->GetName(),
			*this->GetName(),
			*this->EventReference.GetMemberName().ToString())
		);

		this->bOverrideFunction = false;
		this->bInternalEvent    = true;

		this->CachedNodeTitle.MarkDirty();
	}
}

bool UPF2K2Node_EventEmitterBoundEvent::Modify(const bool bAlwaysMarkDirty)
{
	this->CachedNodeTitle.MarkDirty();

	return Super::Modify(bAlwaysMarkDirty);
}

void UPF2K2Node_EventEmitterBoundEvent::ReconstructNode()
{
	// We need to fix up our event reference as it may have changed or been redirected.
	const FMulticastDelegateProperty* TargetDelegateProp = this->GetTargetOrRemappedDelegateProperty();

	this->DelegatePropertyName = TargetDelegateProp->GetFName();

	if ((TargetDelegateProp != nullptr) && (TargetDelegateProp->SignatureFunction != nullptr))
	{
		this->EventReference.SetFromField<UFunction>(TargetDelegateProp->SignatureFunction, false);
	}

	this->CachedNodeTitle.MarkDirty();

	Super::ReconstructNode();
}

bool UPF2K2Node_EventEmitterBoundEvent::CanPasteHere(const UEdGraph* TargetGraph) const
{
	// By default, to be safe, we don't allow events to be pasted, except under special circumstances (see below)
	bool bAllowPaste = Super::CanPasteHere(TargetGraph);

	if (bAllowPaste)
	{
		const UK2Node_Event* PreExistingNode =
			FindExisting(
				FBlueprintEditorUtils::FindBlueprintForGraph(TargetGraph),
				this->EmitterVariableName,
				this->DelegatePropertyName
			);

		if (PreExistingNode != nullptr)
		{
			UE_LOG(
				LogPf2BlueprintNodes,
				Log,
				TEXT("Cannot paste event node (%s) because an event of this type already exists in this graph."),
				*this->GetFName().ToString()
			);

			bAllowPaste = false;
		}
	}

	return bAllowPaste;
}

FText UPF2K2Node_EventEmitterBoundEvent::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (this->CachedNodeTitle.IsOutOfDate(this))
	{
		FFormatNamedArguments Args;

		Args.Add(TEXT("DelegatePropertyName"), this->GetDelegateDisplayName());
		Args.Add(TEXT("ComponentPropertyName"), FText::FromName(this->EmitterVariableName));

		// FText::Format() is slow, so we cache this to save on performance.
		this->CachedNodeTitle.SetCachedText(
			FText::Format(
				LOCTEXT("EventEmitterBoundEvent_Title", "{DelegatePropertyName} ({ComponentPropertyName})"),
				Args
			),
			this);
	}

	return this->CachedNodeTitle;
}

FText UPF2K2Node_EventEmitterBoundEvent::GetTooltipText() const
{
	const FMulticastDelegateProperty* TargetDelegateProp = this->GetTargetDelegateProperty();

	if (TargetDelegateProp == nullptr)
	{
		return FText::FromName(this->DelegatePropertyName);
	}
	else
	{
		return TargetDelegateProp->GetToolTipText();
	}
}

bool UPF2K2Node_EventEmitterBoundEvent::HasDeprecatedReference() const
{
	const FMulticastDelegateProperty* DelegateProperty = this->GetTargetDelegateProperty();

	if (DelegateProperty == nullptr)
	{
		return false;
	}
	else
	{
		return DelegateProperty->HasAnyPropertyFlags(CPF_Deprecated);
	}
}

FEdGraphNodeDeprecationResponse UPF2K2Node_EventEmitterBoundEvent::GetDeprecationResponse(
	const EEdGraphNodeDeprecationType DeprecationType) const
{
	FEdGraphNodeDeprecationResponse Response = Super::GetDeprecationResponse(DeprecationType);

	if (DeprecationType == EEdGraphNodeDeprecationType::NodeHasDeprecatedReference)
	{
		const UFunction* Function = this->EventReference.ResolveMember<UFunction>(GetBlueprintClassFromNode());

		if (ensureMsgf(Function != nullptr, TEXT("If function reference cannot be resolved, how do we know it is deprecated?")))
		{
			const FText DetailedMessage =
				FText::FromString(Function->GetMetaData(FBlueprintMetadata::MD_DeprecationMessage));

			Response.MessageType = EEdGraphNodeDeprecationMessageType::Warning;

			Response.MessageText =
				FBlueprintEditorUtils::GetDeprecatedMemberUsageNodeWarning(
					this->GetDelegateDisplayName(),
					DetailedMessage);
		}
	}

	return Response;
}

UClass* UPF2K2Node_EventEmitterBoundEvent::GetDynamicBindingClass() const
{
	return UPF2EventEmitterDelegateBinding::StaticClass();
}

void UPF2K2Node_EventEmitterBoundEvent::RegisterDynamicBinding(UDynamicBlueprintBinding* BindingObject) const
{
	UPF2EventEmitterDelegateBinding* ComponentBindingObject = CastChecked<UPF2EventEmitterDelegateBinding>(BindingObject);

	FBlueprintComponentDelegateBinding Binding;

	Binding.ComponentPropertyName = this->EmitterVariableName;
	Binding.DelegatePropertyName  = this->DelegatePropertyName;
	Binding.FunctionNameToBind    = this->CustomFunctionName;

	this->CachedNodeTitle.MarkDirty();

	ComponentBindingObject->AddBinding(Binding);
}

void UPF2K2Node_EventEmitterBoundEvent::HandleVariableRenamed(UBlueprint*  InBlueprint,
                                                              UClass*      InVariableClass,
                                                              UEdGraph*    InGraph,
                                                              const FName& InOldVarName,
                                                              const FName& InNewVarName)
{
	if ((InVariableClass != nullptr) && InVariableClass->IsChildOf(InBlueprint->GeneratedClass))
	{
		// This could be the case if the component that this was originally bound to was removed, and a new one was
		// added in its place. @see UE-88511
		if (InNewVarName == this->EmitterVariableName)
		{
			FCompilerResultsLog LogResults;
			FMessageLog MessageLog("BlueprintLog");
			LogResults.Error(*LOCTEXT("ComponentBoundEvent_Rename_Error", "There can only be one event node bound to this component! Delete @@ or the other bound event").ToString(), this);

			MessageLog.NewPage(LOCTEXT("ComponentBoundEvent_Rename_Error_Label", "Rename Component Error"));
			MessageLog.AddMessages(LogResults.Messages);
			MessageLog.Notify(LOCTEXT("OnConvertEventToFunctionErrorMsg", "Renaming a component"));
			FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(this);
		}
		else if (InOldVarName == this->EmitterVariableName)
		{
			this->Modify();

			this->EmitterVariableName = InNewVarName;
		}
	}
}

void UPF2K2Node_EventEmitterBoundEvent::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const
{
	if (!this->IsDelegateValid())
	{
		MessageLog.Warning(*LOCTEXT("ComponentBoundEvent_Error", "@@ does not have a valid matching component!").ToString(), this);
	}

	Super::ValidateNodeDuringCompilation(MessageLog);
}

bool UPF2K2Node_EventEmitterBoundEvent::IsUsedByAuthorityOnlyDelegate() const
{
	const FMulticastDelegateProperty* TargetDelegateProp = this->GetTargetDelegateProperty();

	return ((TargetDelegateProp != nullptr) && TargetDelegateProp->HasAnyPropertyFlags(CPF_BlueprintAuthorityOnly));
}

FString UPF2K2Node_EventEmitterBoundEvent::GetIdForLogs() const
{
	return this->GetFullName();
}

bool UPF2K2Node_EventEmitterBoundEvent::IsDelegateValid() const
{
	const UBlueprint* const BP = this->GetBlueprint();

	// Validate that the property has not been renamed or deleted via the SCS tree.
	return BP && FindFProperty<FObjectProperty>(BP->GeneratedClass, this->EmitterVariableName)
		// Validate that the actual declaration for this event has not been deleted
		// either from a native base class or a BP multicast delegate. The Delegate could have been
		// renamed/redirected, so also check for a remapped field if we need to
		&& (this->GetTargetOrRemappedDelegateProperty() != nullptr);
}

FMulticastDelegateProperty* UPF2K2Node_EventEmitterBoundEvent::GetTargetDelegateProperty() const
{
	return FindFProperty<FMulticastDelegateProperty>(this->DelegateOwnerClass, this->DelegatePropertyName);
}

FMulticastDelegateProperty* UPF2K2Node_EventEmitterBoundEvent::GetTargetOrRemappedDelegateProperty() const
{
	FMulticastDelegateProperty* TargetDelegateProp = this->GetTargetDelegateProperty();

	// If we couldn't find the target delegate, try to find it in the property remap table.
	if (TargetDelegateProp == nullptr)
	{
		FMulticastDelegateProperty* NewProperty =
			FMemberReference::FindRemappedField<FMulticastDelegateProperty>(
				this->DelegateOwnerClass,
				this->DelegatePropertyName);

		if (NewProperty != nullptr)
		{
			// We found a remapped property, so redirect our target.
			TargetDelegateProp = NewProperty;
		}
	}

	return TargetDelegateProp;
}

FText UPF2K2Node_EventEmitterBoundEvent::GetDelegateDisplayName() const
{
	const FMulticastDelegateProperty* TargetProperty = this->GetTargetDelegateProperty();

	if (TargetProperty == nullptr)
	{
		return FText::FromName(this->DelegatePropertyName);
	}
	else
	{
		return TargetProperty->GetDisplayNameText();
	}
}

#undef LOCTEXT_NAMESPACE
