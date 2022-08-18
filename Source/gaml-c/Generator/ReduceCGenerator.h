// Copyright 2022 GrosSlava.

#pragma once

#include "GeneratorBase.h"

#include <string>




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
	virtual int RunThirdPartyCompiler(const std::string& FilePath, std::string& OutCompiledObjectFilePath) override;

private:

	std::string GetClassDeclarationCStr(const std::string& ClassCompileName, const FClassInfo& ClassInfo, const FProgramInfo& ProgramInfo) const;
	std::string GetFunctionSignatureCStr(const std::string& FunctionCompileName, const FFunctionSignatureInfo& FunctionInfo, const FProgramInfo& ProgramInfo) const;
	std::string GetFunctionImplementationBodyCStr(const std::string& FunctionCompileName, const FCompilingFunctionInfo& FunctionCompileInfo, const FProgramInfo& ProgramInfo) const;

	std::string GetVariableDeclarationCStr(const FVariableInfo& VariableInfo, bool IncludeConst, bool IncludeName, bool IsFunctionArgument, const FProgramInfo& ProgramInfo) const;
	std::string GetStandardTypeNameCStr(int TypeID) const;
	std::string GetFunctionPointerCStr(const std::string& Name, const FFunctionSignatureInfo& FunctionInfo, bool IncludeConst, const FProgramInfo& ProgramInfo) const;
	std::string GetClassVariablesCStr(const FClassInfo& ClassInfo, const FProgramInfo& ProgramInfo) const;

	std::string GetCallingConventionCStr(EFunctionCallingConvention CallingConvention) const;
};