// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "InterfaceEventsDetailCustomization.h"

#include <DetailCategoryBuilder.h>
#include <DetailLayoutBuilder.h>
#include <DetailWidgetRow.h>
#include <K2Node_ComponentBoundEvent.h>

#include <Engine/Blueprint.h>

#include <Kismet2/BlueprintEditorUtils.h>
#include <Kismet2/KismetEditorUtilities.h>

#include <Widgets/Input/SButton.h>
#include <Widgets/Layout/SWidgetSwitcher.h>

#include "OpenPF2EditorSupport.h"
#include "PF2EventEmitterInterface.h"

#define LOCTEXT_NAMESPACE "InterfaceEventsDetailCustomization"

void FInterfaceEventsDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> SelectedObjects;

	SelectedObjects = DetailBuilder.GetSelectedObjects();

	if ((SelectedObjects.Num() == 1) && SelectedObjects[0].IsValid())
	{
		const UObject*                        SelectedObject      = SelectedObjects[0].Get();
		UBlueprint*                           ContainingBlueprint = GetBlueprintContainingObject(SelectedObject);
		const FSubobjectEditorTreeNodePtrType SelectedTreeNode    = GetSelectedTreeNodeInBlueprint(ContainingBlueprint);

		if ((ContainingBlueprint != nullptr) && (SelectedTreeNode.IsValid()))
		{
			this->Blueprint = ContainingBlueprint;

			this->AddEventsCategory(DetailBuilder, SelectedObject, SelectedTreeNode.Get()->GetVariableName());
		}
	}
}

void FInterfaceEventsDetailCustomization::AddEventsCategory(IDetailLayoutBuilder& DetailBuilder,
															const UObject*        SelectedObject,
                                                            const FName           SelectedVariableName) const
{
	UClass*                    SelectedObjectClass = SelectedObject->GetClass();
	const IPF2EventEmitterInterface* SelectedEventsIntf  = Cast<IPF2EventEmitterInterface>(SelectedObject);

	const UBlueprint* BlueprintObj = this->GetBlueprint();
	check(BlueprintObj != nullptr);

	if ((SelectedObjectClass != nullptr) && (SelectedEventsIntf != nullptr) && BlueprintObj->AllowsDynamicBinding())
	{
		// If the object property can't be resolved for the property or it has a null events object, we can't use its
		// events.
		const FObjectProperty* VariableProperty =
			FindFProperty<FObjectProperty>(BlueprintObj->SkeletonGeneratedClass, SelectedVariableName);

		const UObject* EventsObject = SelectedEventsIntf->GetGenericEventsObject();

		if ((VariableProperty != nullptr) && (EventsObject != nullptr))
		{
			const UClass* EventsObjectClass = EventsObject->GetClass();

			if ((EventsObjectClass != nullptr) && FBlueprintEditorUtils::CanClassGenerateEvents(EventsObjectClass))
			{
				for (TFieldIterator<FMulticastDelegateProperty> PropertyIt(EventsObjectClass, EFieldIteratorFlags::IncludeSuper); PropertyIt; ++PropertyIt)
				{
					const FMulticastDelegateProperty* Property = *PropertyIt;

					static const FName HideInDetailPanelName("HideInDetailPanel");

					// Check for multicast delegates that we can safely assign
					if (!Property->HasAnyPropertyFlags(CPF_Parm) && Property->HasAllPropertyFlags(CPF_BlueprintAssignable) &&
						!Property->HasMetaData(HideInDetailPanelName))
					{
						const FName EventName = Property->GetFName();
						const FText EventText = Property->GetDisplayNameText();

						IDetailCategoryBuilder& EventCategory =
							DetailBuilder.EditCategory(
								TEXT("Events"),
								LOCTEXT("Events", "Events"),
								ECategoryPriority::Uncommon
							);

						EventCategory
							.AddCustomRow(EventText)
							.WholeRowContent()
							[
								SNew(SHorizontalBox)
								.ToolTipText(Property->GetToolTipText())

								+ SHorizontalBox::Slot()
								.AutoWidth()
								.VAlign(VAlign_Center)
								.Padding(0.0f, 0.0f, 5.0f, 0.0f)
								[
									SNew(SImage)
									.Image(FAppStyle::Get().GetBrush("GraphEditor.Event_16x"))
								]

								+ SHorizontalBox::Slot()
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Font(IDetailLayoutBuilder::GetDetailFont())
									.Text(EventText)
								]

								+ SHorizontalBox::Slot()
								.HAlign(HAlign_Left)
								.VAlign(VAlign_Center)
								.Padding(0.0f)
								[
									SNew(SButton)
									.ContentPadding(FMargin(3.0, 2.0))
									.OnClicked(
										this,
										&FInterfaceEventsDetailCustomization::HandleAddOrViewEventForVariable,
										EventName,
										SelectedVariableName,
										MakeWeakObjectPtr(SelectedObjectClass))
									[
										SNew(SWidgetSwitcher)
										.WidgetIndex(
											this,
											&FInterfaceEventsDetailCustomization::GetAddOrViewIndexForButton,
											EventName,
											SelectedVariableName)

										+ SWidgetSwitcher::Slot()
										[
											SNew(SImage)
											.ColorAndOpacity(FSlateColor::UseForeground())
											.Image(FAppStyle::Get().GetBrush("Icons.SelectInViewport"))
										]

										+ SWidgetSwitcher::Slot()
										[
											SNew(SImage)
											.ColorAndOpacity(FSlateColor::UseForeground())
											.Image(FAppStyle::Get().GetBrush("Icons.Plus"))
										]
									]
								]
							];
					}
				}
			}
		}
	}
}

FReply FInterfaceEventsDetailCustomization::HandleAddOrViewEventForVariable(
	const FName                  EventName,
	const FName                  PropertyName,
	const TWeakObjectPtr<UClass> PropertyClass) const
{
	UBlueprint* BlueprintObj = this->GetBlueprint();
	check(BlueprintObj != nullptr);

	// Find the corresponding variable property in the Blueprint
	// ReSharper disable once CppTooWideScope
	FObjectProperty* VariableProperty =
		FindFProperty<FObjectProperty>(BlueprintObj->SkeletonGeneratedClass, PropertyName);

	if (VariableProperty)
	{
		if (!FKismetEditorUtilities::FindBoundEventForComponent(BlueprintObj, EventName, VariableProperty->GetFName()))
		{
			FKismetEditorUtilities::CreateNewBoundEventForClass(PropertyClass.Get(), EventName, BlueprintObj, VariableProperty);
		}
		else
		{
			// ReSharper disable once CppTooWideScope
			const UK2Node_ComponentBoundEvent* ExistingNode =
				FKismetEditorUtilities::FindBoundEventForComponent(
					BlueprintObj,
					EventName,
					VariableProperty->GetFName()
				);

			if ( ExistingNode )
			{
				FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(ExistingNode);
			}
		}
	}

	return FReply::Handled();
}


int32 FInterfaceEventsDetailCustomization::GetAddOrViewIndexForButton(const FName EventName,
                                                                      const FName PropertyName) const
{
	const UBlueprint* BlueprintObj = this->GetBlueprint();
	check(BlueprintObj != nullptr);

	if (FKismetEditorUtilities::FindBoundEventForComponent(BlueprintObj, EventName, PropertyName))
	{
		// View
		return 0;
	}
	else
	{
		// Add
		return 1;
	}
}

UBlueprint* FInterfaceEventsDetailCustomization::GetBlueprintContainingObject(const UObject* SelectedObject)
{
	UBlueprint* ContainingBlueprint = nullptr;

	if (SelectedObject != nullptr)
	{
		const UClass* OutermostClass = SelectedObject->GetOutermostObject()->GetClass();

		if (OutermostClass != nullptr)
		{
			ContainingBlueprint = UBlueprint::GetBlueprintFromClass(OutermostClass);
		}
	}

	return ContainingBlueprint;
}

FSubobjectEditorTreeNodePtrType FInterfaceEventsDetailCustomization::GetSelectedTreeNodeInBlueprint(
	const UBlueprint* Blueprint)
{
	FSubobjectEditorTreeNodePtrType    SelectedNode    = nullptr;
	const TSharedPtr<SSubobjectEditor> SubobjectEditor = GetSubobjectEditorForBlueprint(Blueprint);

	if (SubobjectEditor.IsValid())
	{
		TArray<FSubobjectEditorTreeNodePtrType> SelectedNodes = SubobjectEditor->GetSelectedNodes();

		if (SelectedNodes.Num() == 1)
		{
			SelectedNode = SelectedNodes[0];
		}
	}

	return SelectedNode;
}

TSharedPtr<SSubobjectEditor> FInterfaceEventsDetailCustomization::GetSubobjectEditorForBlueprint(
	const UBlueprint* Blueprint)
{
	TSharedPtr<SSubobjectEditor> SubobjectEditor = nullptr;
	const FBlueprintEditor*      BlueprintEditor = GetBlueprintEditorForBlueprint(Blueprint);

	if (BlueprintEditor != nullptr)
	{
		SubobjectEditor = BlueprintEditor->GetSubobjectEditor();
	}

	return SubobjectEditor;
}

FBlueprintEditor* FInterfaceEventsDetailCustomization::GetBlueprintEditorForBlueprint(const UBlueprint* Blueprint)
{
	FBlueprintEditor* Editor = nullptr;

	if (Blueprint != nullptr)
	{
		const UEdGraph* EditorGraph = Blueprint->GetLastEditedUberGraph();

		Editor = GetBlueprintEditorForGraph(EditorGraph);
	}

	return Editor;
}

FBlueprintEditor* FInterfaceEventsDetailCustomization::GetBlueprintEditorForGraph(const UEdGraph* Graph)
{
	FBlueprintEditor* Editor = nullptr;

	if (Graph != nullptr)
	{
		UBlueprint*            OuterBlueprint       = Cast<UBlueprint>(Graph->GetOuter());
		UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();

		if ((OuterBlueprint != nullptr) && (AssetEditorSubsystem != nullptr))
		{
			IAssetEditorInstance* AssetEditor = AssetEditorSubsystem->FindEditorForAsset(OuterBlueprint, false);

			if (AssetEditor != nullptr)
			{
				FAssetEditorToolkit* AssetEditorToolkit = static_cast<FAssetEditorToolkit*>(AssetEditor);

				if (AssetEditorToolkit->IsBlueprintEditor())
				{
					Editor = static_cast<FBlueprintEditor*>(AssetEditorToolkit);
				}
			}
		}
	}

	return Editor;
}

#undef LOCTEXT_NAMESPACE
