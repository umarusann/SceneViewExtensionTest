// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "MaterialShader.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "RHI.h"
#include "RHIStaticStates.h"
#include "RenderGraphResources.h"

#include "RenderResource.h"
#include "SceneManagement.h"
#include "ShaderParameterUtils.h"
#include "UObject/ConstructorHelpers.h"

#include "ScreenPass.h"
#include "SceneTexturesConfig.h"



/**
 * 
 */
BEGIN_SHADER_PARAMETER_STRUCT(MSVEShaderInputParameters,)
SHADER_PARAMETER_RDG_TEXTURE(Texture2D<uint>, MergedStencilTexture)
	SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
	SHADER_PARAMETER_STRUCT_INCLUDE(FSceneTextureShaderParameters, SceneTextures)
	SHADER_PARAMETER_STRUCT_REF(FWorkingColorSpaceShaderParameters, WorkingColorSpace)
	SHADER_PARAMETER_STRUCT(FScreenPassTextureViewportParameters, PostProcessOutput)
	SHADER_PARAMETER_STRUCT_ARRAY(FScreenPassTextureInput, PostProcessInput, [1])
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class VIEWEXTENDSYSTEM_API FMySceneViewExtensionMaterialShader:public  FGlobalShader
{
public:
	using FParameters = MSVEShaderInputParameters;
	SHADER_USE_PARAMETER_STRUCT_WITH_LEGACY_BASE(FMySceneViewExtensionMaterialShader,FGlobalShader);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return !IsMobilePlatform(Parameters.Platform);
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,FShaderCompilerEnvironment& OutEnvironment)
	{
		FMaterialShader::ModifyCompilationEnvironment(Parameters,OutEnvironment);
	}
};

class FMySceneViewExtensionMaterialVS:public FMySceneViewExtensionMaterialShader
{
public:
	DECLARE_GLOBAL_SHADER(FMySceneViewExtensionMaterialVS);
	FMySceneViewExtensionMaterialVS()=default;
	FMySceneViewExtensionMaterialVS(const ShaderMetaType::CompiledShaderInitializerType & Initializer): FMySceneViewExtensionMaterialShader(Initializer)
	{}

	void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FSceneView& View)
	{
		FGlobalShader::SetParameters<FViewUniformShaderParameters>(BatchedParameters, View.ViewUniformBuffer);
	}

	UE_DEPRECATED(5.3, "SetParameters with FRHIBatchedShaderParameters should be used.")
	void SetParameters(FRHICommandList& RHICmdList, const FSceneView& View)
	{
		FRHIBatchedShaderParameters& BatchedParameters = RHICmdList.GetScratchShaderParameters();
		SetParameters(BatchedParameters, View);
		RHICmdList.SetBatchedShaderParameters(RHICmdList.GetBoundVertexShader(), BatchedParameters);
	}
};

class FMySceneViewExtensionGenericPS:public FMySceneViewExtensionMaterialShader
{
public:
	FMySceneViewExtensionGenericPS()=default;
	FMySceneViewExtensionGenericPS(const ShaderMetaType::CompiledShaderInitializerType & Initializer):FMySceneViewExtensionMaterialShader(Initializer)
	{}
	void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FSceneView& View)
	{
		FGlobalShader::SetParameters<FViewUniformShaderParameters>(BatchedParameters, View.ViewUniformBuffer);
	}

	UE_DEPRECATED(5.3, "SetParameters with FRHIBatchedShaderParameters should be used.")
	void SetParameters(FRHICommandList& RHICmdList, const FSceneView& View)
	{
		FRHIBatchedShaderParameters& BatchedParameters = RHICmdList.GetScratchShaderParameters();
		SetParameters(BatchedParameters, View);
		RHICmdList.SetBatchedShaderParameters(RHICmdList.GetBoundPixelShader(), BatchedParameters);
	}
};

class FMySceneViewExtensionMaterialPS:public FMySceneViewExtensionGenericPS
{
public:
	DECLARE_GLOBAL_SHADER(FMySceneViewExtensionMaterialPS);
	//class FShaderType : SHADER_PERMUTATION_ENUM_CLASS()

	FMySceneViewExtensionMaterialPS()=default;
	FMySceneViewExtensionMaterialPS(const ShaderMetaType::CompiledShaderInitializerType & Initializer):FMySceneViewExtensionGenericPS(Initializer)
	{}
};

//vertex shader to draw rectangle
class FMySceneViewExtensionScreenPassVS:public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FMySceneViewExtensionScreenPassVS);

	FMySceneViewExtensionScreenPassVS()=default;
	FMySceneViewExtensionScreenPassVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer):FGlobalShader(Initializer)
	{}
};