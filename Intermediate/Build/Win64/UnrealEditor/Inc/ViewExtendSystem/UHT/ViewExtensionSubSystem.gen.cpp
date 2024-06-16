// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ViewExtendSystem/Public/ViewExtensionSubSystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeViewExtensionSubSystem() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem();
	UPackage* Z_Construct_UPackage__Script_ViewExtendSystem();
	VIEWEXTENDSYSTEM_API UClass* Z_Construct_UClass_UViewExtensionSubSystem();
	VIEWEXTENDSYSTEM_API UClass* Z_Construct_UClass_UViewExtensionSubSystem_NoRegister();
// End Cross Module References
	void UViewExtensionSubSystem::StaticRegisterNativesUViewExtensionSubSystem()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UViewExtensionSubSystem);
	UClass* Z_Construct_UClass_UViewExtensionSubSystem_NoRegister()
	{
		return UViewExtensionSubSystem::StaticClass();
	}
	struct Z_Construct_UClass_UViewExtensionSubSystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UViewExtensionSubSystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UWorldSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_ViewExtendSystem,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UViewExtensionSubSystem_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UViewExtensionSubSystem_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ViewExtensionSubSystem.h" },
		{ "ModuleRelativePath", "Public/ViewExtensionSubSystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UViewExtensionSubSystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UViewExtensionSubSystem>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UViewExtensionSubSystem_Statics::ClassParams = {
		&UViewExtensionSubSystem::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UViewExtensionSubSystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UViewExtensionSubSystem_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UViewExtensionSubSystem()
	{
		if (!Z_Registration_Info_UClass_UViewExtensionSubSystem.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UViewExtensionSubSystem.OuterSingleton, Z_Construct_UClass_UViewExtensionSubSystem_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UViewExtensionSubSystem.OuterSingleton;
	}
	template<> VIEWEXTENDSYSTEM_API UClass* StaticClass<UViewExtensionSubSystem>()
	{
		return UViewExtensionSubSystem::StaticClass();
	}
	UViewExtensionSubSystem::UViewExtensionSubSystem() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UViewExtensionSubSystem);
	UViewExtensionSubSystem::~UViewExtensionSubSystem() {}
	struct Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_ViewExtensionSubSystem_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_ViewExtensionSubSystem_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UViewExtensionSubSystem, UViewExtensionSubSystem::StaticClass, TEXT("UViewExtensionSubSystem"), &Z_Registration_Info_UClass_UViewExtensionSubSystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UViewExtensionSubSystem), 1834424493U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_ViewExtensionSubSystem_h_1285830642(TEXT("/Script/ViewExtendSystem"),
		Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_ViewExtensionSubSystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UEPRJ_SceneTest_Plugins_ViewExtendSystem_Source_ViewExtendSystem_Public_ViewExtensionSubSystem_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
