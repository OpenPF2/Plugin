// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
using UnrealBuildTool;

// ReSharper disable once InconsistentNaming
public class OpenPF2Core : ModuleRules
{
	public OpenPF2Core(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivatePCHHeaderFile = "Public/OpenPF2Core.h";

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"AIModule",
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"EnhancedInput",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"GameplayAbilities",
				"Slate",
				"SlateCore",
			}
		);
	}
}
