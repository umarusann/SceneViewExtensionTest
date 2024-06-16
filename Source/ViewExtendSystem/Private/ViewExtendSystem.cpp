// Copyright Epic Games, Inc. All Rights Reserved.

#include "ViewExtendSystem.h"

#if WITH_EDITOR

#include "Filters/CustomClassFilterData.h"
#include "LevelEditor.h"
#endif

#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FViewExtendSystemModule"

void FViewExtendSystemModule::StartupModule()
{
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("ViewExtendSystem"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/ViewExtendSystemShader"), PluginShaderDir);
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FViewExtendSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FViewExtendSystemModule, ViewExtendSystem)