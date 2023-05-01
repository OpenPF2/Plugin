// Portions adapted from Unreal Engine 5.1, which is Copyright Epic Games, Inc.
// Licensed only for use with Unreal Engine.

#include "Utilities/PF2BlueprintUtilities.h"

#include <EdGraphSchema_K2.h>

#include <EdGraph/EdGraphPin.h>

#define LOCTEXT_NAMESPACE "BlueprintSnapNodes"

namespace PF2BlueprintUtilities
{
	FEdGraphPinType InvertMapPinType(const FEdGraphPinType& PinType)
	{
		if (PinType.IsMap())
		{
			FEdGraphPinType InversePinType = FEdGraphPinType::GetPinTypeForTerminalType(PinType.PinValueType);

			InversePinType.ContainerType = PinType.ContainerType;
			InversePinType.PinValueType  = FEdGraphTerminalType::FromPinType(PinType);
			InversePinType.bIsConst      = PinType.bIsConst;
			InversePinType.bIsReference  = PinType.bIsReference;

			// BUGBUG: Unreal doesn't have a way to track the constness of a map key separately from the constness of
			// the map itself. So, we must force const to "false" in the value type.
			InversePinType.PinValueType.bTerminalIsConst = false;

			return InversePinType;
		}
		else
		{
			UE_LOG(
				LogPf2CoreBlueprintNodes,
				Error,
				TEXT("Only Map pin types can be inverted (given \"%s\")."),
				*(PF2BlueprintUtilities::GetTypeDescription(PinType).ToString())
			);

			return PinType;
		}
	}

	// Adapted from BlueprintSnapNodes/Private/SGraphSnapContainerRow.cpp.
	FText GetTypeDescription(const FEdGraphPinType& PinType)
	{
		FText       Description;
		const FText ValueTypeText = DescribePinType(PinType.PinValueType),
		            KeyTypeText   = DescribePinType(PinType);

		switch (PinType.ContainerType)
		{
			default:
				break;

			case EPinContainerType::Array:
				Description = FText::Format(LOCTEXT("PinTypeIsArray", "TArray<{0}>"), KeyTypeText);
				break;

			case EPinContainerType::Set:
				Description = FText::Format(LOCTEXT("PinTypeIsSet", "TSet<{0}>"), KeyTypeText);
				break;

			case EPinContainerType::Map:
				Description = FText::Format(LOCTEXT("PinTypeIsMap", "TMap<{0}, {1}>"), KeyTypeText, ValueTypeText);
				break;
		}

		if (PinType.bIsConst)
		{
			Description = FText::Format(LOCTEXT("PinTypeIsConst", "const {0}"), Description);
		}

		if (PinType.bIsReference)
		{
			Description = FText::Format(LOCTEXT("PinTypeIsReference", "{0}&"), Description);
		}

		return Description;
	}

	FText DescribePinType(const FEdGraphTerminalType& TerminalPinType)
	{
		const FEdGraphPinType PinType     = FEdGraphPinType::GetPinTypeForTerminalType(TerminalPinType);
		FText                 Description = DescribePinType(PinType);

		if (TerminalPinType.bTerminalIsConst)
		{
			Description = FText::Format(LOCTEXT("PinTypeIsConst", "const {0}"), Description);
		}

		return Description;
	}

	// Adapted from BlueprintSnapNodes/Private/SGraphSnapContainerRow.cpp.
	FText DescribePinType(const FEdGraphPinType& PinType)
	{
		FText          Description;
		const FName    PinSubCategory       = PinType.PinSubCategory;
		const UObject* PinSubCategoryObject = PinType.PinSubCategoryObject.Get();

		if ((PinSubCategory != UEdGraphSchema_K2::PSC_Bitmask) && (PinSubCategoryObject != nullptr))
		{
			if (const UField* Field = Cast<const UField>(PinSubCategoryObject))
			{
				Description = Field->GetDisplayNameText();
			}
			else
			{
				Description = FText::AsCultureInvariant(PinSubCategoryObject->GetName());
			}
		}
		else
		{
			Description = UEdGraphSchema_K2::GetCategoryText(PinType.PinCategory, true);
		}

		return Description;
	}
}

#undef LOCTEXT_NAMESPACE
