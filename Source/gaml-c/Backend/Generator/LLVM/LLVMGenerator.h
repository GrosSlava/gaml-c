// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "Generator/GeneratorBase.h"




/**
	Generator for LLVM code.
	@see BaseGenerator.
*/
class LLVMGenerator : public BaseGenerator
{
public:

	inline LLVMGenerator() { }



protected:

	virtual std::string GetOutFileExtension() const override { return "ll"; }
	virtual void ProcessGeneration(std::string& GeneratedCodeStr, const FIRInfo& IRInfo) override;
	virtual void CompileToBinary(const std::string& FilePath, const std::string& OutCompiledObjectFilePath) override;
};