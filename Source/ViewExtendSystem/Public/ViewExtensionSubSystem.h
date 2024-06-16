// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMySceneViewExtension.h"
#include "MySceneViewExtensionSetting.h"
#include "Subsystems/WorldSubsystem.h"

#include "ViewExtensionSubSystem.generated.h"

/**
 * 
 */
#if WITH_EDITOR
class FViewExtensionEditorUndoClient : public FEditorUndoClient
{
};
#else
class FColorCorrectRegionsEditorUndoClient
{
};
#endif


UCLASS()
class VIEWEXTENDSYSTEM_API UViewExtensionSubSystem : public UWorldSubsystem,public FViewExtensionEditorUndoClient
{
	GENERATED_BODY()
public:

	// Subsystem Init/Deinit
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Undo/redo is only supported by editor.
#if WITH_EDITOR
	// FEditorUndoClient pure virtual methods.
	virtual void PostUndo(bool bSuccess) override { RefreshRegions(); };
	virtual void PostRedo(bool bSuccess) override { RefreshRegions(); }
#endif
	
	void SortExtensionSettingByDistance(const FVector& ViewLocation);

private:

	/** Repopulates array of region actors. */
	void RefreshRegions();
public:
	void OnLevelsChanged() { RefreshRegions(); };
	TArray<AMySceneViewExtensionSetting*> SettingsDistanceBased;

private:
	TSharedPtr<class FMySceneViewExtension,ESPMode::ThreadSafe> MySceneViewExtension;
	FCriticalSection MySceneViewAccessCriticalSection;

public:
	friend class FMySceneViewExtension;
};
