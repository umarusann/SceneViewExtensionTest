// Fill out your copyright notice in the Description page of Project Settings.


#include "FMySceneViewExtension.h"

#include "CommonRenderResources.h"
#include "Containers/DynamicRHIResourceArray.h"
#include "DynamicResolutionState.h"
#include "FMySceneViewExtensionMaterialShader.h"
#include "Engine/World.h"
#include "RHI.h"
#include "ScreenPass.h"
#include "SceneView.h"
#include "PostProcess/PostProcessing.h"
#include "SceneRendering.h"


DECLARE_GPU_STAT_NAMED(MySceneViewExtension, TEXT("MySceneViewExtension"));
FMySceneViewExtension::FMySceneViewExtension(const FAutoRegister& AutoRegister, UViewExtensionSubSystem* InWorldSubsystem):FSceneViewExtensionBase(AutoRegister),WorldSubsystem(InWorldSubsystem)
{
	
}

FScreenPassTextureViewportParameters GetTextureViewportParameters(const FScreenPassTextureViewport& InViewport)
{
	const FVector2f Extent(InViewport.Extent);
	const FVector2f ViewportMin(InViewport.Rect.Min.X, InViewport.Rect.Min.Y);
	const FVector2f ViewportMax(InViewport.Rect.Max.X, InViewport.Rect.Max.Y);
	const FVector2f ViewportSize = ViewportMax - ViewportMin;

	FScreenPassTextureViewportParameters Parameters;

	if (!InViewport.IsEmpty())
	{
		Parameters.Extent = FVector2f(Extent);
		Parameters.ExtentInverse = FVector2f(1.0f / Extent.X, 1.0f / Extent.Y);

		Parameters.ScreenPosToViewportScale = FVector2f(0.5f, -0.5f) * ViewportSize;	
		Parameters.ScreenPosToViewportBias = (0.5f * ViewportSize) + ViewportMin;	

		Parameters.ViewportMin = InViewport.Rect.Min;
		Parameters.ViewportMax = InViewport.Rect.Max;

		Parameters.ViewportSize = ViewportSize;
		Parameters.ViewportSizeInverse = FVector2f(1.0f / Parameters.ViewportSize.X, 1.0f / Parameters.ViewportSize.Y);

		Parameters.UVViewportMin = ViewportMin * Parameters.ExtentInverse;
		Parameters.UVViewportMax = ViewportMax * Parameters.ExtentInverse;

		Parameters.UVViewportSize = Parameters.UVViewportMax - Parameters.UVViewportMin;
		Parameters.UVViewportSizeInverse = FVector2f(1.0f / Parameters.UVViewportSize.X, 1.0f / Parameters.UVViewportSize.Y);

		Parameters.UVViewportBilinearMin = Parameters.UVViewportMin + 0.5f * Parameters.ExtentInverse;
		Parameters.UVViewportBilinearMax = Parameters.UVViewportMax - 0.5f * Parameters.ExtentInverse;
	}

	return Parameters;
}

bool RenderMySceneViewExtension
	(FRDGBuilder& GraphBuilder
	,const FSceneView& View
	,const FSceneViewFamily& ViewFamily
	,AMySceneViewExtensionSetting* Setting
	,const FIntRect& PrimaryViewRect
	,const FScreenPassRenderTarget& SceneColorRenderTarget
	,const float ScreenPercentage
	,FScreenPassRenderTarget& BackBufferRenderTarget
	,const FScreenPassTextureViewportParameters& SceneTextureviewportParams
	,const FScreenPassTextureInput& SceneTextureInput
	,const FSceneTextureShaderParameters& SceneTextures
	,FGlobalShaderMap* GlobalShaderMap
	,FRHIBlendState* DefaultBlendState)
{
	SCOPED_GPU_STAT(GraphBuilder.RHICmdList, MySceneViewExtension);
	FRHIDepthStencilState* DepthStencilState = FScreenPassPipelineState::FDefaultDepthStencilState::GetRHI();
	FMySceneViewExtensionRenderProxyPtr SceneViewExtensionSetting= Setting->GetMSVEProxy_RenderThread();
	
	FIntRect Viewport;
	Viewport = PrimaryViewRect;

	const FScreenPassTextureViewport MSVEViewport(SceneColorRenderTarget.Texture,Viewport);
	TShaderMapRef<FMySceneViewExtensionMaterialVS> VertexShader(GlobalShaderMap);
	TShaderRef<FMySceneViewExtensionGenericPS> PixelShader;
	MSVEShaderInputParameters* PostProcessMaterialParameters=GraphBuilder.AllocParameters<MSVEShaderInputParameters>();
	PostProcessMaterialParameters->RenderTargets[0] = BackBufferRenderTarget.GetRenderTargetBinding();

	PostProcessMaterialParameters->WorkingColorSpace=GDefaultWorkingColorSpaceUniformBuffer.GetUniformBufferRef();
	PostProcessMaterialParameters->PostProcessOutput=SceneTextureviewportParams;
	PostProcessMaterialParameters->PostProcessInput[0]=SceneTextureInput;
	PostProcessMaterialParameters->SceneTextures=SceneTextures;
	PostProcessMaterialParameters->View=View.ViewUniformBuffer;
	
	GraphBuilder.AddPass
		(RDG_EVENT_NAME("MySceneViewExtension")
		,PostProcessMaterialParameters
		,ERDGPassFlags::Raster
		,[&View,
			MSVEViewport,
			VertexShader,
			PixelShader,
			DefaultBlendState,
			DepthStencilState,
			PostProcessMaterialParameters
			](FRHICommandList& RHICmdList)
		{
			FRHIBatchedShaderParameters& BatchedParameters = RHICmdList.GetScratchShaderParameters();
			PixelShader->SetParameters(BatchedParameters, View);
						SetShaderParameters(BatchedParameters, PixelShader, *PostProcessMaterialParameters);

						RHICmdList.SetBatchedShaderParameters(PixelShader.GetPixelShader(), BatchedParameters);

						BatchedParameters.Reset();

						VertexShader->SetParameters(BatchedParameters, View);
						SetShaderParameters(BatchedParameters, VertexShader, *PostProcessMaterialParameters);

						RHICmdList.SetBatchedShaderParameters(VertexShader.GetVertexShader(), BatchedParameters);
		});
	BackBufferRenderTarget.LoadAction = ERenderTargetLoadAction::ELoad;

	FCopyRectPS::FParameters* Parameters = GraphBuilder.AllocParameters<FCopyRectPS::FParameters>();
	Parameters->InputTexture = BackBufferRenderTarget.Texture;
	Parameters->InputSampler = TStaticSamplerState<>::GetRHI();
	Parameters->RenderTargets[0] = SceneColorRenderTarget.GetRenderTargetBinding();

	TShaderMapRef<FCopyRectPS> CopyPixelShader(GlobalShaderMap);
	TShaderMapRef<FMySceneViewExtensionScreenPassVS> ScreenPassVS(GlobalShaderMap);
	FRHIBlendState* CopyBlendState = TStaticBlendState<CW_RGB, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha, BO_Add, BF_Zero, BF_One>::GetRHI();
	GraphBuilder.AddPass(
			RDG_EVENT_NAME("ColorCorrectRegions_CopyViewport"),
			Parameters,
			ERDGPassFlags::Raster,
			[&View, ScreenPassVS, CopyPixelShader,MSVEViewport, Parameters, CopyBlendState](FRHICommandList& RHICmdList)
			{
				DrawScreenPass(
					RHICmdList,
					View,
					MSVEViewport,
					MSVEViewport,
					FScreenPassPipelineState(ScreenPassVS, CopyPixelShader, CopyBlendState),
					EScreenPassDrawFlags::None,
					[&](FRHICommandList&)
					{
						SetShaderParameters(RHICmdList, CopyPixelShader, CopyPixelShader.GetPixelShader(), *Parameters);
					});
			});
	return true;
	
}

void FMySceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	const FSceneViewFamily& ViewFamily = *View.Family;
	DynamicRenderScaling::TMap<float> UpperBounds = ViewFamily.GetScreenPercentageInterface()->GetResolutionFractionsUpperBound();
	const auto FeatureLevel = View.GetFeatureLevel();
	const float ScreenPercentage = UpperBounds[GDynamicPrimaryResolutionFraction] * ViewFamily.SecondaryViewFraction;
	
	// We need to make sure to take Windows and Scene scale into account.

	checkSlow(View.bIsViewInfo); // can't do dynamic_cast because FViewInfo doesn't have any virtual functions.
	const FIntRect PrimaryViewRect = static_cast<const FViewInfo&>(View).ViewRect;

	FScreenPassTexture SceneColor((*Inputs.SceneTextures)->SceneColorTexture, PrimaryViewRect);
	
	{
		// Getting material data for the current view.
		FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

		// Reusing the same output description for our back buffer as SceneColor
		FRDGTextureDesc MySceneViewOutputDesc = SceneColor.Texture->Desc;

		MySceneViewOutputDesc.Format = PF_FloatRGBA;
		FLinearColor ClearColor(0., 0., 0., 0.);
		MySceneViewOutputDesc.ClearValue = FClearValueBinding(ClearColor);

		FRDGTexture* BackBufferRenderTargetTexture = GraphBuilder.CreateTexture(MySceneViewOutputDesc, TEXT("BackBufferRenderTargetTexture"));
		FScreenPassRenderTarget BackBufferRenderTarget = FScreenPassRenderTarget(BackBufferRenderTargetTexture, SceneColor.ViewRect, ERenderTargetLoadAction::EClear);
		FScreenPassRenderTarget SceneColorRenderTarget(SceneColor, ERenderTargetLoadAction::ELoad);
		const FScreenPassTextureViewport SceneColorTextureViewport(SceneColor);

		FRHIBlendState* DefaultBlendState = FScreenPassPipelineState::FDefaultBlendState::GetRHI();

		RDG_EVENT_SCOPE(GraphBuilder, "MySceneViewExtension %dx%d", SceneColorTextureViewport.Rect.Width(), SceneColorTextureViewport.Rect.Height());

		FRHISamplerState* PointClampSampler = TStaticSamplerState<SF_Point, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
		const FScreenPassTextureViewportParameters SceneTextureViewportParams = GetTextureViewportParameters(SceneColorTextureViewport);
		FScreenPassTextureInput SceneTextureInput;
		{
			SceneTextureInput.Viewport = SceneTextureViewportParams;
			SceneTextureInput.Texture = SceneColorRenderTarget.Texture;
			SceneTextureInput.Sampler = PointClampSampler;
		}

		// Because we are not using proxy material, but plain global shader, we need to setup Scene textures ourselves.
		// We don't need to do this per region.
		check(View.bIsViewInfo);
		FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::All);

		WorldSubsystem->SortExtensionSettingByDistance(View.ViewLocation);
		{
			FScopeLock SettingsScopeLock(&WorldSubsystem->MySceneViewAccessCriticalSection);
			for(auto It=WorldSubsystem->SettingsDistanceBased.CreateConstIterator();It;++It)
			{
				AMySceneViewExtensionSetting* Setting = *It;
				RenderMySceneViewExtension(GraphBuilder,View,ViewFamily,Setting,PrimaryViewRect,SceneColorRenderTarget,ScreenPercentage,BackBufferRenderTarget,SceneTextureViewportParams,SceneTextureInput,SceneTextures,GlobalShaderMap,DefaultBlendState);
			}
		}
	}
}


