// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ViewExtendSystem : ModuleRules
{
	public ViewExtendSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateIncludePaths.AddRange(
            new string[] {
				//Used in ColorCorrectRegionsPostProcessMaterial.h
				Path.Combine(GetModuleDirectory("Renderer"), "Private"),
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "DisplayClusterLightCardExtender",
                 "EditorWidgets",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "RHI",
                "Renderer",
                "Projects",
                "RenderCore",
                "EditorWidgets",
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
            PrivateDependencyModuleNames.Add("EditorWidgets");
        }
    }
}
