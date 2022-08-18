// Copyright 2022 GrosSlava.

#pragma once

#include "GeneratorBase.h"

#include <string>





/*
	Generator for LLVM code.
	@see BaseGenerator.
*/
class LLVMGenerator : public BaseGenerator
{
public:

	inline LLVMGenerator() { }



protected:

	virtual std::string GetOutFileExtension() const override { return "ll"; }
	virtual void ProcessGeneration(const FProgramInfo& ProgramInfo) override;
	virtual int RunThirdPartyCompiler(const std::string& FilePath, std::string& OutCompiledObjectFilePath) override;
};