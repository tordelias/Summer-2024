// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Summer_2024/Summer_2024Character.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSummer_2024Character() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
SUMMER_2024_API UClass* Z_Construct_UClass_ASummer_2024Character();
SUMMER_2024_API UClass* Z_Construct_UClass_ASummer_2024Character_NoRegister();
UPackage* Z_Construct_UPackage__Script_Summer_2024();
// End Cross Module References

// Begin Class ASummer_2024Character
void ASummer_2024Character::StaticRegisterNativesASummer_2024Character()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASummer_2024Character);
UClass* Z_Construct_UClass_ASummer_2024Character_NoRegister()
{
	return ASummer_2024Character::StaticClass();
}
struct Z_Construct_UClass_ASummer_2024Character_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Summer_2024Character.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Summer_2024Character.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TopDownCameraComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Top down camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Summer_2024Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Top down camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera above the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Summer_2024Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera above the character" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TopDownCameraComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASummer_2024Character>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASummer_2024Character_Statics::NewProp_TopDownCameraComponent = { "TopDownCameraComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASummer_2024Character, TopDownCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TopDownCameraComponent_MetaData), NewProp_TopDownCameraComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASummer_2024Character_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASummer_2024Character, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASummer_2024Character_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASummer_2024Character_Statics::NewProp_TopDownCameraComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASummer_2024Character_Statics::NewProp_CameraBoom,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASummer_2024Character_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASummer_2024Character_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Summer_2024,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASummer_2024Character_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASummer_2024Character_Statics::ClassParams = {
	&ASummer_2024Character::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASummer_2024Character_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASummer_2024Character_Statics::PropPointers),
	0,
	0x008000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASummer_2024Character_Statics::Class_MetaDataParams), Z_Construct_UClass_ASummer_2024Character_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASummer_2024Character()
{
	if (!Z_Registration_Info_UClass_ASummer_2024Character.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASummer_2024Character.OuterSingleton, Z_Construct_UClass_ASummer_2024Character_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASummer_2024Character.OuterSingleton;
}
template<> SUMMER_2024_API UClass* StaticClass<ASummer_2024Character>()
{
	return ASummer_2024Character::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASummer_2024Character);
ASummer_2024Character::~ASummer_2024Character() {}
// End Class ASummer_2024Character

// Begin Registration
struct Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024Character_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASummer_2024Character, ASummer_2024Character::StaticClass, TEXT("ASummer_2024Character"), &Z_Registration_Info_UClass_ASummer_2024Character, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASummer_2024Character), 2584085696U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024Character_h_330877793(TEXT("/Script/Summer_2024"),
	Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024Character_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Github_Github_UE_summer_projects_Summer_2024_Summer_2024_Source_Summer_2024_Summer_2024Character_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
