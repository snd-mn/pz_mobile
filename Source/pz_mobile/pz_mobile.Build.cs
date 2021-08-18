// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class pz_mobile : ModuleRules
{
	public pz_mobile(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[] { "VaRest" });

		PrivateIncludePathModuleNames.AddRange(new string[] { "VaRest" });

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Http",
			"Json", "JsonUtilities", "VaRest"
		});
	}
}