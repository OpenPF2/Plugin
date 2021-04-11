// Copyright 2021 Teen Wolf RPG. All Rights Reserved.

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