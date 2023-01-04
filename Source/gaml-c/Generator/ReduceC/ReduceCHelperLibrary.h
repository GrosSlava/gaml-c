// Copyright 2022 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"

#include "../../Parser/ProgramSymbols.h"
#include "../../Compiler/CompilerOptions.h"




/*
    Helper library to generate ReduceC code.
*/
struct FReduceCHelperLibrary
{
	static inline std::string GetStandardTypeNameCStr(int TypeID)
	{
		// clang-format off
		switch( static_cast<EStandardTypesID>(TypeID) )
		{
		case EStandardTypesID::VOID_ID: 	return "void";
		case EStandardTypesID::UINT8_ID: 	return "unsigned char";
		case EStandardTypesID::UINT16_ID: 	return "unsigned short int";
		case EStandardTypesID::UINT32_ID: 	return "unsigned int";
		case EStandardTypesID::UINT64_ID: 	return "unsigned long long int";
		case EStandardTypesID::INT8_ID: 	return "signed char";
		case EStandardTypesID::INT16_ID: 	return "signed short int";
		case EStandardTypesID::INT32_ID: 	return "signed int";
		case EStandardTypesID::INT64_ID: 	return "signed long long int";
		case EStandardTypesID::ADDR_T_ID: 	return "signed long long int";
		case EStandardTypesID::FLOAT_ID: 	return "float";
		case EStandardTypesID::DOUBLE_ID: 	return "double";
		case EStandardTypesID::BOOL_ID: 	return "signed char";
		case EStandardTypesID::CHAR_ID: 	return "unsigned short int";
		case EStandardTypesID::STRING_ID: 	return "string";
		case EStandardTypesID::VECTOR4D_ID: return "vector4d";
		case EStandardTypesID::VECTOR3D_ID: return "vector3d";
		case EStandardTypesID::VECTOR2D_ID: return "vector2d";
		}
		// clang-format on

		return "";
	}

	static inline std::string GetCallingConventionCStr(EFunctionCallingConvention CallingConvention, ETargetPlatform TargetPlatform)
	{
		switch( CallingConvention )
		{
		case EFunctionCallingConvention::CDECL:
		{
			if( TargetPlatform == ETargetPlatform::Windows )
			{
				return "__cdecl";
			}
			else
			{
				return "__attribute__((cdecl))";
			}
		}
		case EFunctionCallingConvention::STDCALL:
		{
			if( TargetPlatform == ETargetPlatform::Windows )
			{
				return "__stdcall";
			}
			else
			{
				return "__attribute__((stdcall))";
			}
		}
		case EFunctionCallingConvention::FASTCALL:
		{
			if( TargetPlatform == ETargetPlatform::Windows )
			{
				return "__fastcall";
			}
			else
			{
				return "__attribute__((__fastcall))";
			}
		}
		}

		return "";
	}




	// clang-format off
	static std::string GetFunctionSignatureCStr
	(
		const std::string& FunctionCompileName, const FFunctionSignatureInfo& FunctionInfo, 
		ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
	);
	// clang-format on

	// clang-format off
	static std::string GetFunctionPointerCStr
	(
		const std::string& Name, const FFunctionSignatureInfo& FunctionInfo, bool IncludeConst, 
		ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
	);
	// clang-format on
	
	// clang-format off
	static std::string GetFunctionImplementationBodyCStr
	(
		const std::string& FunctionCompileName, const FCompilingFunctionInfo& FunctionCompileInfo, 
		const FProgramInfo& ProgramInfo
	);
	// clang-format on




	// clang-format off
	static std::string GetClassDeclarationCStr
	(
		const std::string& ClassCompileName, const FClassInfo& ClassInfo, 
		ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
	);
	// clang-format on

	static std::string GetClassVariablesCStr(const FClassInfo& ClassInfo, ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo);




	// clang-format off
	static std::string GetVariableDeclarationCStr
	(
		const FVariableInfo& VariableInfo, bool IncludeConst, bool IncludeName, bool IsFunctionArgument, 
		ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
	);
	// clang-format on
};