// Copyright (c) 2026. MIT License.

using UnrealBuildTool;

public class UnrealBuiltInGuide : ModuleRules
{
	public UnrealBuiltInGuide(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"DeveloperSettings"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"ToolMenus",
			"Projects"
		});
	}
}
