// Copyright 2022 GrosSlava.

#pragma once

#include "GeneratorBase.h"

#include <string>





/*
	Generator for NASM code.
	@see BaseGenerator.
*/
class NASMGenerator : public BaseGenerator
{
public:

	inline NASMGenerator() { }



protected:

	virtual std::string GetOutFileExtension() const override { return "asm"; }
	virtual void ProcessGeneration(const FProgramInfo& ProgramInfo) override;
	virtual int RunThirdPartyCompiler(const std::string& FilePath, std::string& OutCompiledObjectFilePath) override;
};