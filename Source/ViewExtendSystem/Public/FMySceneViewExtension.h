// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneViewExtension.h"
#include "ViewExtensionSubSystem.h"

class UViewExtensionSubSystem;
/**
 * 
 */
class VIEWEXTENDSYSTEM_API FMySceneViewExtension:public FSceneViewExtensionBase
{
public:
	FMySceneViewExtension(const FAutoRegister& AutoRegister, UViewExtensionSubSystem* InWorldSubsystem);
	
	//~ Begin FSceneViewExtensionBase Interface
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
	//~ End FSceneViewExtensionBase Interface
public:
	// Called when owning subsystem needs to release this extension.
	void Invalidate();
private:
	UViewExtensionSubSystem* WorldSubsystem;
};
