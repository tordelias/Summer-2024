// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Summer_2024/Summer_2024GameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSummer_2024GameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
SUMMER_2024_API UClass* Z_Construct_UClass_ASummer_2024GameMode();
SUMMER_2024_API UClass* Z_Construct_UClass_ASummer_2024GameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_Summer_2024();
// End Cross Module References

// Begin Class ASummer_2024GameMode
void ASummer_2024GameMode::StaticRegisterNativesASummer_2024GameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASummer_2024GameMode);
UClass* Z_Construct_UClass_ASummer_2024GameMode_NoRegister()
{
	return ASummer_2024GameMode::StaticClass();
}
struct Z_Construct_UClass_ASummer_2024GameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Summer_2024GameMode.h" },
		{ "ModuleRelativePath", "Summer_2024GameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASummer_2024GameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ASummer_2024GameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Summer_2024,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASummer_2024GameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASummer_2024GameMode_Statics::ClassParams = {
	&ASummer_2024GameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASummer_2024GameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASummer_2024GameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASummer_2024GameMode()
{
	if (!Z_Registration_Info_UClass_ASummer_2024GameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASummer_2024GameMode.OuterSingleton, Z_Construct_UClass_ASummer_2024GameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASummer_2024GameMode.OuterSingleton;
}
template<> SUMMER_2024_API UClass* StaticClass<ASummer_2024GameMode>()
{
	return ASummer_2024GameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASummer_2024GameMode);
ASummer_2024GameMode::~ASummer_2024GameMode() {}
// End Class ASummer_2024GameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024GameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASummer_2024GameMode, ASummer_2024GameMode::StaticClass, TEXT("ASummer_2024GameMode"), &Z_Registration_Info_UClass_ASummer_2024GameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASummer_2024GameMode), 3617613817U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024GameMode_h_2331692573(TEXT("/Script/Summer_2024"),
	Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024GameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024GameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
