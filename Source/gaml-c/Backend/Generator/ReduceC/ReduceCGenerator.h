// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "Generator/GeneratorBase.h"




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
	virtual void ProcessGeneration(std::string& GeneratedCodeStr, const FIRInfo& IRInfo) override;
};
