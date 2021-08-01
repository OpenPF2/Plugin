// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

using UnrealBuildTool;

public class TeenWolfRpg : ModuleRules
{
	// ReSharper disable once InconsistentNaming
	public TeenWolfRpg(ReadOnlyTargetRules Target)
		: base(Target)
	{
		PrivatePCHHeaderFile = "Public/TeenWolfRpg.h";

		PCHUsage = PCHUsageMode.UseSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayAbilities",
				"GameplayTags",
				"ActionRPG",
			}
		);
	}
}
