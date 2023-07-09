// Portions adapted from Unreal Engine 5.1, which is Copyright Epic Games, Inc.
// Licensed only for use with Unreal Engine.

#include "Utilities/PF2BlueprintEditorUtilities.h"

#include <Engine/Blueprint.h>

namespace PF2BlueprintEditorUtilities
{
	UBlueprint* GetBlueprintContainingObject(const UObject* Object)
	{
		UBlueprint* ContainingBlueprint = nullptr;

		if (Object != nullptr)
		{
			const UClass* OutermostClass = Object->GetOutermostObject()->GetClass();

			if (OutermostClass != nullptr)
			{
				ContainingBlueprint = UBlueprint::GetBlueprintFromClass(OutermostClass);
			}
		}

		return ContainingBlueprint;
	}

	FSubobjectEditorTreeNode* GetSelectedTreeNodeInBlueprint(UBlueprint* Blueprint)
	{
		FSubobjectEditorTreeNode*          SelectedNode    = nullptr;
		const TSharedPtr<SSubobjectEditor> SubobjectEditor = GetSubobjectEditorForBlueprint(Blueprint);

		if (SubobjectEditor.IsValid())
		{
			TArray<FSubobjectEditorTreeNodePtrType> SelectedNodes = SubobjectEditor->GetSelectedNodes();

			if (SelectedNodes.Num() == 1)
			{
				const FSubobjectEditorTreeNodePtrType SelectedNodePtr = SelectedNodes[0];

				SelectedNode = SelectedNodePtr.Get();
			}
		}

		return SelectedNode;
	}

	TSharedPtr<SSubobjectEditor> GetSubobjectEditorForBlueprint(UBlueprint* Blueprint)
	{
		TSharedPtr<SSubobjectEditor> SubobjectEditor = nullptr;
		const FBlueprintEditor*      BlueprintEditor = GetBlueprintEditorForBlueprint(Blueprint);

		if (BlueprintEditor != nullptr)
		{
			SubobjectEditor = BlueprintEditor->GetSubobjectEditor();
		}

		return SubobjectEditor;
	}

	FBlueprintEditor* GetBlueprintEditorForBlueprint(UBlueprint* Blueprint)
	{
		FBlueprintEditor* Editor = nullptr;

		if (Blueprint != nullptr)
		{
			UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();

			if ((Blueprint != nullptr) && (AssetEditorSubsystem != nullptr))
			{
				IAssetEditorInstance* AssetEditor = AssetEditorSubsystem->FindEditorForAsset(Blueprint, false);

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
}
