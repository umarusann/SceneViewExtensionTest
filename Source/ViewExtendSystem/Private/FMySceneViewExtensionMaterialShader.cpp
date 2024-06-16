// Fill out your copyright notice in the Description page of Project Settings.


#include "FMySceneViewExtensionMaterialShader.h"


IMPLEMENT_GLOBAL_SHADER(FMySceneViewExtensionMaterialVS,"/ViewExtendSystemShader/Private/MyShader.ufs","MainVS",SF_Vertex);
IMPLEMENT_GLOBAL_SHADER(FMySceneViewExtensionScreenPassVS,"/ViewExtendSystemShader/Private/MyShaderScreenPassVS.usf","MainVS",SF_Vertex);