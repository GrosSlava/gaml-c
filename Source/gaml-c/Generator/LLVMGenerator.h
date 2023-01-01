// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "GeneratorBase.h"




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
	virtual void ProcessGeneration(std::string& GeneratedCodeStr, const FProgramInfo& ProgramInfo) override;
};