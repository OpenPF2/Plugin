// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Libraries/PF2K2Node_MapInvert.h"

#include <BlueprintActionDatabaseRegistrar.h>
#include <BlueprintNodeSpawner.h>
#include <EdGraphSchema_K2.h>
#include <K2Node_CallFunction.h>
#include <KismetCompiler.h>

#include <Framework/Notifications/NotificationManager.h>

#include <Kismet2/BlueprintEditorUtils.h>

#include <Widgets/Notifications/SNotificationList.h>

#include "Libraries/PF2MapLibrary.h"

#include "Utilities/PF2BlueprintUtilities.h"

// ReSharper disable once IdentifierTypo
#define LOCTEXT_NAMESPACE "K2Node_MapInvert"

const FName UPF2K2Node_MapInvert::InputPinName  = TEXT("Map");
const FName UPF2K2Node_MapInvert::OutputPinName = TEXT("InvertedMap");

FText UPF2K2Node_MapInvert::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
	if (TitleType == ENodeTitleType::MenuTitle)
	{
		return LOCTEXT("InvertMapTitle", "Invert");
	}
	else
	{
		return LOCTEXT("InvertMapTitle", "INVERT");
	}
}

FText UPF2K2Node_MapInvert::GetTooltipText() const
{
	return LOCTEXT(
		"InvertMapTooltip",
		"Inverts the keys and values of a map, so that for each pair the key becomes the value and vice-versa."
	);
}

void UPF2K2Node_MapInvert::AllocateDefaultPins()
{
	FCreatePinParams InputParams,
					 OutputParams;

	// Input pin.
	InputParams.ContainerType = EPinContainerType::Map;
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, InputPinName, InputParams);

	// Output pin.
	OutputParams.ContainerType = EPinContainerType::Map;
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, OutputPinName, OutputParams);
}

FText UPF2K2Node_MapInvert::GetMenuCategory() const
{
	return LOCTEXT("MapMenuCategory", "OpenPF2|Utility|Map");
}

void UPF2K2Node_MapInvert::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* Action = this->GetClass();

	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(Action);
		check(Spawner != nullptr);

		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UPF2K2Node_MapInvert::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	this->PropagateLinkedPinType(Pin);
}

void UPF2K2Node_MapInvert::PostReconstructNode()
{
	Super::PostReconstructNode();

	// We only propagate type changes that originate from the input pin (see PropagateLinkedPinType() for why).
	this->PropagateLinkedPinType(this->GetInputPin());
}

void UPF2K2Node_MapInvert::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UEdGraphPin          *InputPin  = this->GetInputPin(),
	                     *OutputPin = this->GetOutputPin();
	UK2Node_CallFunction *PinCallFunction;
	const UFunction      *Function;
	UEdGraphPin          *InvertInputMap,
	                     *InvertOutputMap;

	Super::ExpandNode(CompilerContext, SourceGraph);

	PinCallFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

	Function =
		UPF2MapLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UPF2MapLibrary, InvertMap));

	PinCallFunction->SetFromFunction(Function);
	PinCallFunction->AllocateDefaultPins();

	InvertInputMap  = PinCallFunction->FindPinChecked(TEXT("InputMap"));
	InvertOutputMap = PinCallFunction->FindPinChecked(TEXT("OutputMap"));

	check((InvertInputMap != nullptr) && (InvertOutputMap != nullptr));

	InvertInputMap->PinType  = InputPin->PinType;
	InvertOutputMap->PinType = OutputPin->PinType;

	UE_LOG(
		LogPf2CoreBlueprintNodes,
		VeryVerbose,
		TEXT("[%s] Populated nested input pin (%s) as \"%s\" and nested output pin (%s) to \"%s\"."),
		*(this->GetIdForLogs()),
		*(InvertInputMap->GetName()),
		*(PF2BlueprintUtilities::GetTypeDescription(InvertInputMap->PinType).ToString()),
		*(InvertOutputMap->GetName()),
		*(PF2BlueprintUtilities::GetTypeDescription(InvertOutputMap->PinType).ToString())
	);

	CompilerContext.MovePinLinksToIntermediate(*InputPin,  *InvertInputMap);
	CompilerContext.MovePinLinksToIntermediate(*OutputPin, *InvertOutputMap);

	// Break any links to the expanded node, now that we've replaced it with a call to the real thing.
	this->BreakAllNodeLinks();
}

FString UPF2K2Node_MapInvert::GetIdForLogs() const
{
	return this->GetFullName();
}

UEdGraphPin* UPF2K2Node_MapInvert::GetInputPin() const
{
	return this->FindPinChecked(InputPinName, EGPD_Input);
}

UEdGraphPin* UPF2K2Node_MapInvert::GetOutputPin() const
{
	return this->FindPinChecked(OutputPinName, EGPD_Output);
}

void UPF2K2Node_MapInvert::PropagateLinkedPinType(UEdGraphPin* LocalPin)
{
	UEdGraphPin* InputPin  = this->GetInputPin();
	UEdGraphPin* OutputPin = this->GetOutputPin();

	if ((LocalPin == InputPin) || (LocalPin == OutputPin))
	{
		const UEdGraphPin* ConnectedToPin    = (LocalPin->LinkedTo.Num() > 0) ? LocalPin->LinkedTo[0] : nullptr;
		const bool         IsInputConnected  = (InputPin->LinkedTo.Num() != 0);
		const bool         IsOutputConnected = (OutputPin->LinkedTo.Num() != 0);

		if (ConnectedToPin == nullptr)
		{
			// If both input and output pins are unlinked, then reset the types of both to wildcard.
			if (!IsInputConnected && !IsOutputConnected)
			{
				this->ResetPinToWildcard(InputPin);
				this->ResetPinToWildcard(OutputPin);
			}
		}
		else
		{
			// We only propagate type changes that originate from the input pin.
			//
			// In an earlier draft, we propagated type changes from the output pins the same way that we do for the
			// input pins, but this created a "constness" conflict if the output pin of this node was connected to a
			// const input pin in another node, since that would force the input pin of this node to be const when it
			// didn't need to be.
			if (LocalPin == InputPin)
			{
				this->PropagatePinType(ConnectedToPin, LocalPin);
			}
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPF2K2Node_MapInvert::PropagatePinType(const UEdGraphPin* OtherPin, const UEdGraphPin* LocalPin)
{
	UEdGraphPin*          InputPin         = this->GetInputPin();
	UEdGraphPin*          OutputPin        = this->GetOutputPin();
	const FEdGraphPinType ConnectedPinType = OtherPin->PinType;

	if ((ConnectedPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) &&
		(ConnectedPinType.PinValueType.TerminalCategory != UEdGraphSchema_K2::PC_Wildcard))
	{
		check(OtherPin != InputPin);

		if (LocalPin == InputPin)
		{
			this->PropagatePinType(ConnectedPinType, InputPin, OutputPin);
		}

		if (LocalPin == OutputPin)
		{
			this->PropagatePinType(ConnectedPinType, OutputPin, InputPin);
		}

		this->ValidateKeyType();
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPF2K2Node_MapInvert::PropagatePinType(const FEdGraphPinType& PinType,
                                            UEdGraphPin*           RegularTargetPin,
                                            UEdGraphPin*           InverseTargetPin)
{
	RegularTargetPin->PinType = PinType;
	InverseTargetPin->PinType = PF2BlueprintUtilities::InvertMapPinType(PinType);

	UE_LOG(
		LogPf2CoreBlueprintNodes,
		VeryVerbose,
		TEXT("[%s] Changed local pin (%s) to \"%s\" and local pin (%s) to \"%s\"."),
		*(this->GetIdForLogs()),
		*(RegularTargetPin->GetName()),
		*(PF2BlueprintUtilities::GetTypeDescription(RegularTargetPin->PinType).ToString()),
		*(InverseTargetPin->GetName()),
		*(PF2BlueprintUtilities::GetTypeDescription(InverseTargetPin->PinType).ToString())
	);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPF2K2Node_MapInvert::ValidateKeyType()
{
	UEdGraphPin*          InputPin  = this->GetInputPin();
	UEdGraphPin*          OutputPin = this->GetOutputPin();
	const FEdGraphPinType PinType   = OutputPin->PinType;

	if (!FBlueprintEditorUtils::HasGetTypeHash(PinType))
	{
		// Inform user via toast why the type change was exceptional and clear the pin because the key type
		// cannot be hashed.
		const FText NotificationText =
			FText::Format(
				LOCTEXT(
					"TypeCannotBeHashed",
					"A map of type '{0}' cannot be inverted because the value type does not have a GetTypeHash function. Maps require a hash function to insert and find elements"
				),
				UEdGraphSchema_K2::TypeToText(PinType)
			);

		FNotificationInfo Info(NotificationText);

		Info.FadeInDuration  = 0.0f;
		Info.FadeOutDuration = 0.0f;
		Info.ExpireDuration  = 10.0f;

		InputPin->BreakAllPinLinks();
		OutputPin->BreakAllPinLinks();
		this->NotifyPinConnectionListChanged(OutputPin);

		FSlateNotificationManager::Get().AddNotification(Info);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPF2K2Node_MapInvert::ResetPinToWildcard(UEdGraphPin* TargetPin)
{
	UE_LOG(
		LogPf2CoreBlueprintNodes,
		VeryVerbose,
		TEXT("[%s] Resetting pin (%s) on Invert node to being a wildcard."),
		*(this->GetIdForLogs()),
		*(TargetPin->GetName())
	);

	TargetPin->BreakAllPinLinks();

	TargetPin->PinType.ResetToDefaults();
	TargetPin->PinType.ContainerType = EPinContainerType::Map;
	TargetPin->PinType.PinCategory   = UEdGraphSchema_K2::PC_Wildcard;
}

#undef LOCTEXT_NAMESPACE
