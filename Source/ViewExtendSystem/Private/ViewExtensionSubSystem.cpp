// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewExtensionSubSystem.h"

#include "MySceneViewExtensionSetting.h"

void UViewExtensionSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
	// In some cases (like nDisplay nodes) EndPlay is not guaranteed to be called when level is removed.
	GetWorld()->OnLevelsChanged().AddUObject(this, &UViewExtensionSubSystem::OnLevelsChanged);
	// Initializing Scene view extension responsible for rendering regions.
	MySceneViewExtension = FSceneViewExtensions::NewExtension<FMySceneViewExtension>(this);
}
void UViewExtensionSubSystem::Deinitialize()
{
	
}
void UViewExtensionSubSystem::RefreshRegions()
{
	
}
void UViewExtensionSubSystem::SortExtensionSettingByDistance(const FVector& ViewLocation)
{
	FScopeLock SettingsScopeLock(&MySceneViewAccessCriticalSection);
	TMap<AMySceneViewExtensionSetting*,double> DistanceMap;
	for(AMySceneViewExtensionSetting* Setting :SettingsDistanceBased)
	{
		FMySceneViewExtensionRenderProxyPtr State = Setting->GetMSVEProxy_RenderThread();
		FVector CameraToSettingVec=(State->BoxOrigin = ViewLocation);
		DistanceMap.Add(Setting,CameraToSettingVec.Dot(CameraToSettingVec));
	}
	SettingsDistanceBased.Sort([&DistanceMap](const AMySceneViewExtensionSetting& A,const AMySceneViewExtensionSetting& B)
	{
		return DistanceMap[&A] > DistanceMap[&B];
	});
}


