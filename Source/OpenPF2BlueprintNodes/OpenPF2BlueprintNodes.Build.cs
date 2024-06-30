// OpenPF2 Game Framework for Unreal Engine, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

using UnrealBuildTool;

// ReSharper disable once InconsistentNaming
public class OpenPF2BlueprintNodes : ModuleRules
{
	public OpenPF2BlueprintNodes(ReadOnlyTargetRules Target) : base(Target)
	{
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"OpenPF2GameFramework",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"BlueprintGraph",
				"Engine",
				"GraphEditor",
				"KismetCompiler",
				"PropertyEditor",
				"Slate",
				"SlateCore",
				"UnrealEd",
			}
		);
	}
}
