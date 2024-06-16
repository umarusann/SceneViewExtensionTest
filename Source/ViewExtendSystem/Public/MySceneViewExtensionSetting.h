// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySceneViewExtensionSetting.generated.h"

// store a copy of MysceneViewExtension Properties to be used on render thread
struct FMySceneViewExtensionRenderProxy
{
	bool Invert;
	FVector BoxOrigin;
	bool bIsActiveThisFrame;
};

typedef TSharedPtr<FMySceneViewExtensionRenderProxy,ESPMode::ThreadSafe> FMySceneViewExtensionRenderProxyPtr;

UCLASS()
class VIEWEXTENDSYSTEM_API AMySceneViewExtensionSetting : public AActor
{
	GENERATED_BODY()

public:
	
	// Sets default values for this actor's properties
	AMySceneViewExtensionSetting();
	FMySceneViewExtensionRenderProxyPtr MySceneViewExtensionRenderProxy;

	FMySceneViewExtensionRenderProxyPtr GetMSVEProxy_RenderThread()
	{
		check(IsInRenderingThread());
		return  MySceneViewExtensionRenderProxy;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
