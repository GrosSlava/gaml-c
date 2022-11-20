// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "GeneratorBase.h"




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
};