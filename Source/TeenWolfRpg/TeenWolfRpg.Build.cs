// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
//
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.

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
				"Engine"
			}
		);
	}
}