// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "Parser/ProgramSymbols.h"
#include "CoreEnums.h"




/*
	Helper library to generate ReduceC code.
*/
struct FReduceCHelperLibrary
{
	static std::string GetStandardTypeNameCStr(const std::string& TypeName);

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