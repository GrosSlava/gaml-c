// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "GamlFileInfo.h"




struct FProgramInfo;



struct FSemanticAnalyser
{
public:

	inline FSemanticAnalyser() { }



public:

	void Process(const FGamlFileInfo& FileInfo, FProgramInfo& ProgramInfo);




private:

	/*
		Information about compiling file.
	*/
	FGamlFileInfo FileInfo;
};