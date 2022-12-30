// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "GeneratorBase.h"




/*
	Generator for reduce c code.
	@see BaseGenerator.
*/
class ReduceCGenerator : public BaseGenerator
{
public:

	inline ReduceCGenerator() { }



protected:

	virtual std::string GetOutFileExtension() const override { return "c"; }
	virtual void ProcessGeneration(const FProgramInfo& ProgramInfo) override;

private:

	// clang-format off
	std::string GetClassDeclarationCStr
	(
		const std::string& ClassCompileName, const FClassInfo& ClassInfo, 
		const FProgramInfo& ProgramInfo
	) const;
	// clang-format on

	// clang-format off
	std::string GetFunctionSignatureCStr
	(
		const std::string& FunctionCompileName, const FFunctionSignatureInfo& FunctionInfo, 
		const FProgramInfo& ProgramInfo
	) const;
	// clang-format on

	// clang-format off
	std::string GetFunctionImplementationBodyCStr
	(
		const std::string& FunctionCompileName, const FCompilingFunctionInfo& FunctionCompileInfo, 
		const FProgramInfo& ProgramInfo
	) const;
	// clang-format on

	// clang-format off
	std::string GetVariableDeclarationCStr
	(
		const FVariableInfo& VariableInfo, bool IncludeConst, bool IncludeName, bool IsFunctionArgument, 
		const FProgramInfo& ProgramInfo
	) const;
	// clang-format on

	std::string GetStandardTypeNameCStr(int TypeID) const;

	// clang-format off
	std::string GetFunctionPointerCStr
	(
		const std::string& Name, const FFunctionSignatureInfo& FunctionInfo, bool IncludeConst, 
		const FProgramInfo& ProgramInfo
	) const;
	// clang-format on
	
	std::string GetClassVariablesCStr(const FClassInfo& ClassInfo, const FProgramInfo& ProgramInfo) const;

	std::string GetCallingConventionCStr(EFunctionCallingConvention CallingConvention) const;
};