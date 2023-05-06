// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Libraries/PF2K2Node_ForEachMapPair.h"

#include <BlueprintActionDatabaseRegistrar.h>
#include <BlueprintNodeSpawner.h>
#include <EdGraphSchema_K2.h>
#include <K2Node_AssignmentStatement.h>
#include <K2Node_CallFunction.h>
#include <K2Node_ExecutionSequence.h>
#include <K2Node_IfThenElse.h>
#include <K2Node_TemporaryVariable.h>
#include <KismetCompiler.h>

#include <Styling/AppStyle.h>

#include <Textures/SlateIcon.h>

#include "Libraries/PF2MapLibrary.h"

#include "Utilities/PF2BlueprintUtilities.h"

// ReSharper disable once IdentifierTypo
#define LOCTEXT_NAMESPACE "K2Node_ForEachMapPair"

const FName UPF2K2Node_ForEachMapPair::MapInputPinName(TEXT("Map"));
const FName UPF2K2Node_ForEachMapPair::InsideLoopPinName(TEXT("LoopBody"));
const FName UPF2K2Node_ForEachMapPair::CurrentKeyPinName(TEXT("CurrentKey"));
const FName UPF2K2Node_ForEachMapPair::CurrentValuePinName(TEXT("CurrentValue"));

FSlateIcon UPF2K2Node_ForEachMapPair::GetIconAndTint(FLinearColor& OutColor) const
{
	static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "GraphEditor.Macro.Loop_16x");

	return Icon;
}

FText UPF2K2Node_ForEachMapPair::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("ForEachMapPairTitle", "For Each Map Pair");
}

FText UPF2K2Node_ForEachMapPair::GetTooltipText() const
{
	return LOCTEXT(
		"ForEachMapPairTooltip",
		"Loops over each key and value pair in a map."
	);
}

void UPF2K2Node_ForEachMapPair::AllocateDefaultPins()
{
	FCreatePinParams MapInputPinParams;

	this->CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	MapInputPinParams.ContainerType = EPinContainerType::Map;
	this->CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, MapInputPinName, MapInputPinParams);

	this->CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, InsideLoopPinName);
	this->CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, CurrentKeyPinName);
	this->CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, CurrentValuePinName);

	if (UEdGraphPin* CompletedPin = this->CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then))
	{
		CompletedPin->PinFriendlyName = LOCTEXT("Completed", "Completed");
	}
}

FText UPF2K2Node_ForEachMapPair::GetMenuCategory() const
{
	return LOCTEXT("MapMenuCategory", "OpenPF2|Utility|Map");
}

void UPF2K2Node_ForEachMapPair::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* Action = this->GetClass();

	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(Action);
		check(Spawner != nullptr);

		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UPF2K2Node_ForEachMapPair::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	this->PropagateLinkedPinType(Pin);
}

void UPF2K2Node_ForEachMapPair::PostReconstructNode()
{
	Super::PostReconstructNode();

	this->PropagateLinkedPinType(this->GetMapInputPin());
}

void UPF2K2Node_ForEachMapPair::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* Schema  = CompilerContext.GetSchema();
	bool                     bResult = true;

	UK2Node_CallFunction *       GetIteratorNode,
	                     *       IteratorHasPairNode;
	UK2Node_AssignmentStatement* IteratorAssignNode;
	UK2Node_IfThenElse*          BranchNode;
	UK2Node_ExecutionSequence*   SequenceInsideLoop;
	UEdGraphPin*                 IteratorVariablePin;

	// =================================================================================================================
	// Loop Initialization
	// =================================================================================================================
	{
		// Declare a temporary local variable to hold the pair iterator.
		//
		// "UK2Node_TemporaryVariable" Pins:
		//	- Variable (Output): A reference to the new local variable.
		UK2Node_TemporaryVariable* IteratorVariableNode =
			CompilerContext.SpawnIntermediateNode<UK2Node_TemporaryVariable>(this, SourceGraph);

		IteratorVariableNode->VariableType.PinCategory = UEdGraphSchema_K2::PC_Struct;
		IteratorVariableNode->VariableType.PinSubCategoryObject = MakeWeakObjectPtr(FPF2MapPairIterator::StaticStruct());
		IteratorVariableNode->AllocateDefaultPins();

		IteratorVariablePin = IteratorVariableNode->GetVariablePin();
	}
	{
		// Get the pair iterator.
		//
		// "UK2Node_CallFunction" Pins for GetMapPairIterator():
		//	- Map (Input): The map for which an iterator is desired.
		//	- Iterator (Return Value): The new iterator.
		UEdGraphPin *MapInputPin         = this->GetMapInputPin(),
		            *IteratorMapInputPin;

		GetIteratorNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

		GetIteratorNode->SetFromFunction(
			UPF2MapLibrary::StaticClass()->FindFunctionByName(
				GET_FUNCTION_NAME_CHECKED(UPF2MapLibrary, GetMapPairIterator)
			)
		);

		GetIteratorNode->AllocateDefaultPins();

		IteratorMapInputPin = GetIteratorNode->FindPinChecked(TEXT("Map"));
		IteratorMapInputPin->PinType = MapInputPin->PinType;

		// This Node: "Map" --> GetMapPairIterator Node: "Map"
		CompilerContext.MovePinLinksToIntermediate(*MapInputPin, *IteratorMapInputPin);
	}
	{
		// Assign temporary local "iterator" variable to the pair iterator.
		//
		// "UK2Node_AssignmentStatement" Pins:
		//	- Execute (Input)
		//	- Variable (Input): The variable being assigned.
		//	- Value (Input): The value being assigned to the variable.
		//	- Then (Output)
		IteratorAssignNode = CompilerContext.SpawnIntermediateNode<UK2Node_AssignmentStatement>(this, SourceGraph);

		IteratorAssignNode->AllocateDefaultPins();

		// This Node:                      "Exec"     --> UK2Node_AssignmentStatement Node: "Exec"
		// UK2Node_TemporaryVariable Node: "Variable" --> UK2Node_AssignmentStatement Node: "Variable"
		// GetMapPairIterator Node:        "Iterator" --> UK2Node_AssignmentStatement Node: "Value"
		CompilerContext.MovePinLinksToIntermediate(*this->GetExecPin(), *IteratorAssignNode->GetExecPin());
		bResult &= Schema->TryCreateConnection(IteratorVariablePin, IteratorAssignNode->GetVariablePin());
		bResult &= Schema->TryCreateConnection(GetIteratorNode->GetReturnValuePin(), IteratorAssignNode->GetValuePin());
	}

	// =================================================================================================================
	// Inside the Loop
	// =================================================================================================================
	{
		// Fetch loop condition: "Iterator.HasPair()"
		//
		// "UK2Node_CallFunction" Pins for DoesMapPairIteratorHavePair():
		//	- Iterator (Input): The iterator for which a pair is desired.
		//	- Has Pair (Return Value): Whether the iterator is pointing at a valid pair.
		IteratorHasPairNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

		IteratorHasPairNode->SetFromFunction(
			UPF2MapLibrary::StaticClass()->FindFunctionByName(
				GET_FUNCTION_NAME_CHECKED(UPF2MapLibrary, DoesMapPairIteratorHavePair)
			)
		);

		IteratorHasPairNode->AllocateDefaultPins();

		// UK2Node_TemporaryVariable Node: "Variable" --> DoesMapPairIteratorHavePair Node: "Iterator"
		bResult &=
			Schema->TryCreateConnection(IteratorVariablePin, IteratorHasPairNode->FindPinChecked(TEXT("Iterator")));
	}
	{
		// Evaluate loop condition: "if Iterator.HasPair() then ... else ..."
		//
		// "UK2Node_IfThenElse" Pins:
		//	- Execute (Input)
		//	- Condition (Input)
		//	- Then (Output)
		//	- Else (Output)
		BranchNode = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
		BranchNode->AllocateDefaultPins();

		// UK2Node_AssignmentStatement Node: "Then"     --> UK2Node_IfThenElse Node: "Exec"
		// DoesMapPairIteratorHavePair Node: "Has Pair" --> UK2Node_IfThenElse Node: "Condition"
		bResult &= Schema->TryCreateConnection(IteratorAssignNode->GetThenPin(), BranchNode->GetExecPin());
		bResult &= Schema->TryCreateConnection(IteratorHasPairNode->GetReturnValuePin(), BranchNode->GetConditionPin());
	}
	{
		// Execute a sequence inside each loop iteration.
		//
		// This allows the Blueprint VM to clean-up the stack between iterations of the loop. Otherwise, each iteration
		// of the loop would add another stack frame, which would needlessly use up memory.
		//
		// "UK2Node_ExecutionSequence" Pins:
		//	- Execute (Input)
		//	- Then 0 (Output)
		//	- Then 1 (Output)
		SequenceInsideLoop = CompilerContext.SpawnIntermediateNode<UK2Node_ExecutionSequence>(this, SourceGraph);

		SequenceInsideLoop->AllocateDefaultPins();
		SequenceInsideLoop->AddInputPin();

		// UK2Node_IfThenElse Node: "Then"          --> UK2Node_ExecutionSequence Node: "Exec"
		// UK2Node_ExecutionSequence Node: "Then 0" --> This Node: "Loop Body"
		// UK2Node_IfThenElse Node: "Else"          --> This Node: "Loop Completed"
		bResult &= Schema->TryCreateConnection(BranchNode->GetThenPin(), SequenceInsideLoop->GetExecPin());
		CompilerContext.MovePinLinksToIntermediate(*this->GetInsideLoopPin(), *SequenceInsideLoop->GetThenPinGivenIndex(0));
		CompilerContext.MovePinLinksToIntermediate(*this->GetLoopCompletedPin(), *BranchNode->GetElsePin());
	}
	{
		// "UK2Node_CallFunction" Pins for GetKeyFromMapPairIterator():
		//	- Iterator (Input): The iterator for which a key is desired.
		//	- Key (Return Value): The key from the current pair.
		UK2Node_CallFunction* GetPairKeyNode =
			CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

		UEdGraphPin *LoopKeyPin = this->GetCurrentKeyPin(),
		            *PairKeyPin;

		GetPairKeyNode->SetFromFunction(
			UPF2MapLibrary::StaticClass()->FindFunctionByName(
				GET_FUNCTION_NAME_CHECKED(UPF2MapLibrary, GetKeyFromMapPairIterator)
			)
		);

		GetPairKeyNode->AllocateDefaultPins();

		PairKeyPin = GetPairKeyNode->FindPinChecked(TEXT("Key"));

		// Ensure that the pin type returned by "Get Key from Map Pair Iterator" matches the map keys.
		PairKeyPin->PinType = LoopKeyPin->PinType;

		// UK2Node_TemporaryVariable Node: "Variable" --> GetKeyFromMapPairIterator Node: "Iterator"
		// GetKeyFromMapPairIterator Node: "Key"      --> This Node: "Current Key"
		bResult &= Schema->TryCreateConnection(IteratorVariablePin, GetPairKeyNode->FindPinChecked(TEXT("Iterator")));
		CompilerContext.MovePinLinksToIntermediate(*LoopKeyPin, *PairKeyPin);
	}
	{
		// "UK2Node_CallFunction" Pins for GetValueFromMapPairIterator():
		//	- Iterator (Input): The iterator for which a key is desired.
		//	- Value (Return Value): The value from the current pair.
		UK2Node_CallFunction* GetPairValueNode =
			CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

		UEdGraphPin *LoopValuePin = this->GetCurrentValuePin(),
		            *PairValuePin;

		GetPairValueNode->SetFromFunction(
			UPF2MapLibrary::StaticClass()->FindFunctionByName(
				GET_FUNCTION_NAME_CHECKED(UPF2MapLibrary, GetValueFromMapPairIterator)
			)
		);

		GetPairValueNode->AllocateDefaultPins();

		PairValuePin = GetPairValueNode->FindPinChecked(TEXT("Value"));

		// Ensure that the pin type returned by "Get Value from Map Pair Iterator" matches the map values.
		PairValuePin->PinType = LoopValuePin->PinType;

		// UK2Node_TemporaryVariable Node: "Variable" --> GetValueFromMapPairIterator Node: "Iterator"
		// GetValueFromMapPairIterator Node: "Value"  --> This Node: "Current Value"
		bResult &= Schema->TryCreateConnection(IteratorVariablePin, GetPairValueNode->FindPinChecked(TEXT("Iterator")));
		CompilerContext.MovePinLinksToIntermediate(*LoopValuePin, *PairValuePin);
	}

	// =================================================================================================================
	// Loop Iterator Increment
	// =================================================================================================================
	{
		// Increment the pair iterator.
		//
		// "UK2Node_CallFunction" Pins for IncrementMapPairIterator():
		//	- Execute (Input)
		//	- Iterator (Input): The iterator to increment.
		//	- Then (Output)
		UK2Node_CallFunction* IncrementMapPairIteratorNode =
				CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

		IncrementMapPairIteratorNode->SetFromFunction(
			UPF2MapLibrary::StaticClass()->FindFunctionByName(
				GET_FUNCTION_NAME_CHECKED(UPF2MapLibrary, IncrementMapPairIterator)
			)
		);

		IncrementMapPairIteratorNode->AllocateDefaultPins();

		// UK2Node_ExecutionSequence Node: "Then 1"   --> IncrementMapPairIterator Node: "Exec"
		// UK2Node_TemporaryVariable Node: "Variable" --> IncrementMapPairIterator Node: "Iterator"
		// IncrementMapPairIterator Node: "Then"      --> UK2Node_IfThenElse Node: "Exec"
		bResult &= Schema->TryCreateConnection(
			SequenceInsideLoop->GetThenPinGivenIndex(1),
			IncrementMapPairIteratorNode->GetExecPin()
		);

		bResult &= Schema->TryCreateConnection(
			IteratorVariablePin,
			IncrementMapPairIteratorNode->FindPinChecked(TEXT("Iterator"))
		);

		bResult &= Schema->TryCreateConnection(
			IncrementMapPairIteratorNode->GetThenPin(), BranchNode->GetExecPin()
		);
	}

	if (!bResult)
	{
		CompilerContext.MessageLog.Error(*NSLOCTEXT("K2Node", "ForEachMapPair", "Expand error in @@").ToString(), this);
	}

	this->BreakAllNodeLinks();
}

FString UPF2K2Node_ForEachMapPair::GetIdForLogs() const
{
	return this->GetFullName();
}

void UPF2K2Node_ForEachMapPair::PropagateLinkedPinType(UEdGraphPin* LocalPin)
{
	UEdGraphPin* MapInputPin     = this->GetMapInputPin();
	UEdGraphPin* CurrentKeyPin   = this->GetCurrentKeyPin();
	UEdGraphPin* CurrentValuePin = this->GetCurrentValuePin();

	if ((LocalPin == MapInputPin) ||
		(LocalPin == CurrentKeyPin) ||
		(LocalPin == CurrentValuePin))
	{
		const UEdGraphPin* ConnectedToPin         = (LocalPin->LinkedTo.Num() > 0) ? LocalPin->LinkedTo[0] : nullptr;
		const bool         IsInputConnected       = (MapInputPin->LinkedTo.Num() != 0);
		const bool         IsOutputKeyConnected   = (CurrentKeyPin->LinkedTo.Num() != 0);
		const bool         IsOutputValueConnected = (CurrentValuePin->LinkedTo.Num() != 0);

		if (ConnectedToPin == nullptr)
		{
			// If all input and output pins are unlinked, then reset all types to wildcard.
			if (!IsInputConnected && !IsOutputKeyConnected && !IsOutputValueConnected)
			{
				this->ResetPinToWildcard(MapInputPin);
				this->ResetPinToWildcard(CurrentKeyPin);
				this->ResetPinToWildcard(CurrentValuePin);
			}
		}
		// We only propagate type changes that originate from the input pin.
		else if (LocalPin == MapInputPin)
		{
			this->PropagateInputPinType(ConnectedToPin);
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPF2K2Node_ForEachMapPair::PropagateInputPinType(const UEdGraphPin* OtherPin)
{
	UEdGraphPin*          MapInputPin      = this->GetMapInputPin();
	UEdGraphPin*          CurrentKeyPin    = this->GetCurrentKeyPin();
	UEdGraphPin*          CurrentValuePin  = this->GetCurrentValuePin();
	const FEdGraphPinType ConnectedPinType = OtherPin->PinType;

	if ((ConnectedPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) &&
		(ConnectedPinType.PinValueType.TerminalCategory != UEdGraphSchema_K2::PC_Wildcard))
	{
		check(OtherPin != MapInputPin);

		MapInputPin->PinType = OtherPin->PinType;

		CurrentKeyPin->PinType               = OtherPin->PinType;
		CurrentKeyPin->PinType.ContainerType = EPinContainerType::None;

		CurrentValuePin->PinType = FEdGraphPinType::GetPinTypeForTerminalType(OtherPin->PinType.PinValueType);

		UE_LOG(
			LogPf2CoreBlueprintNodes,
			VeryVerbose,
			TEXT("[%s] Changed input pin (%s) type to \"%s\", key pin (%s) type to \"%s\"), and value pin (%s) type to \"%s\"."),
			*(this->GetIdForLogs()),
			*(MapInputPin->GetName()),
			*(PF2BlueprintUtilities::GetTypeDescription(MapInputPin->PinType).ToString()),
			*(CurrentKeyPin->GetName()),
			*(PF2BlueprintUtilities::GetTypeDescription(CurrentKeyPin->PinType).ToString()),
			*(CurrentValuePin->GetName()),
			*(PF2BlueprintUtilities::GetTypeDescription(CurrentValuePin->PinType).ToString())
		);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPF2K2Node_ForEachMapPair::ResetPinToWildcard(UEdGraphPin* TargetPin)
{
	const EPinContainerType ContainerType = TargetPin->PinType.ContainerType;

	UE_LOG(
		LogPf2CoreBlueprintNodes,
		VeryVerbose,
		TEXT("[%s] Resetting pin (%s) to being a wildcard."),
		*(this->GetIdForLogs()),
		*(TargetPin->GetName())
	);

	TargetPin->BreakAllPinLinks();

	TargetPin->PinType.ResetToDefaults();
	TargetPin->PinType.ContainerType = ContainerType;
	TargetPin->PinType.PinCategory   = UEdGraphSchema_K2::PC_Wildcard;
}

#undef LOCTEXT_NAMESPACE
