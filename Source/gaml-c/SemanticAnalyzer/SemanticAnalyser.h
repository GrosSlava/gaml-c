// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"




struct FProgramInfo;



class SemanticAnalyser final
{
public:

	inline SemanticAnalyser() { }



public:

	void Process(const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, FProgramInfo& ProgramInfo);




private:

	/*
		Information about compiling file.
	*/
	FGamlFileInfo FileInfo;

	/*
		Cached compiler options.
	*/
	FCompileOptions CurrentOptions;
};