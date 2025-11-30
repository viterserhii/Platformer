// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Platformer : ModuleRules
{
	public Platformer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "Paper2D",
            "InteractionSystem",
        });
	}
}
