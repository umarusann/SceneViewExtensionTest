// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ViewExtendSystem/Public/MySceneViewExtensionSetting.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMySceneViewExtensionSetting() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ViewExtendSystem();
	VIEWEXTENDSYSTEM_API UClass* Z_Construct_UClass_AMySceneViewExtensionSetting();
	VIEWEXTENDSYSTEM_API UClass* Z_Construct_UClass_AMySceneViewExtensionSetting_NoRegister();
// End Cross Module References
	void AMySceneViewExtensionSetting::StaticRegisterNativesAMySceneViewExtensionSetting()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMySceneViewExtensionSetting);
	UClass* Z_Construct_UClass_AMySceneViewExtensionSetting_NoRegister()
	{
		return AMySceneViewExtensionSetting::StaticClass();
	}
	struct Z_Construct_UClass_AMySceneViewExtensionSetting_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ViewExtendSystem,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "MySceneViewExtensionSetting.h" },
		{ "ModuleRelativePath", "Public/MySceneViewExtensionSetting.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMySceneViewExtensionSetting>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::ClassParams = {
		&AMySceneViewExtensionSetting::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::Class_MetaDataParams), Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AMySceneViewExtensionSetting()
	{
		if (!Z_Registration_Info_UClass_AMySceneViewExtensionSetting.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMySceneViewExtensionSetting.OuterSingleton, Z_Construct_UClass_AMySceneViewExtensionSetting_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AMySceneViewExtensionSetting.OuterSingleton;
	}
	template<> VIEWEXTENDSYSTEM_API UClass* StaticClass<AMySceneViewExtensionSetting>()
	{
		return AMySceneViewExtensionSetting::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMySceneViewExtensionSetting);
	AMySceneViewExtensionSetting::~AMySceneViewExtensionSetting() {}
	struct Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_MySceneViewExtensionSetting_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_MySceneViewExtensionSetting_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AMySceneViewExtensionSetting, AMySceneViewExtensionSetting::StaticClass, TEXT("AMySceneViewExtensionSetting"), &Z_Registration_Info_UClass_AMySceneViewExtensionSetting, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMySceneViewExtensionSetting), 2181972795U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_MySceneViewExtensionSetting_h_2740342408(TEXT("/Script/ViewExtendSystem"),
		Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_MySceneViewExtensionSetting_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_MySceneViewExtensionSetting_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
