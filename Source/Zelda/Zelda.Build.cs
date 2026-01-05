// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Zelda : ModuleRules
{
	public Zelda(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"MediaAssets",
			"Http",
			"Json",
			"JsonUtilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Zelda",
			"Zelda/Variant_Platforming",
			"Zelda/Variant_Platforming/Animation",
			"Zelda/Variant_Combat",
			"Zelda/Variant_Combat/AI",
			"Zelda/Variant_Combat/Animation",
			"Zelda/Variant_Combat/Gameplay",
			"Zelda/Variant_Combat/Interfaces",
			"Zelda/Variant_Combat/UI",
			"Zelda/Variant_SideScrolling",
			"Zelda/Variant_SideScrolling/AI",
			"Zelda/Variant_SideScrolling/Gameplay",
			"Zelda/Variant_SideScrolling/Interfaces",
			"Zelda/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
