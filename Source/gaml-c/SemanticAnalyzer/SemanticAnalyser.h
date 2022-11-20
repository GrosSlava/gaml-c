// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"
#include "../Parser/ProgramSymbols.h"




class SemanticAnalyser final
{
public:

	inline SemanticAnalyser() { }



public:

	void Process(const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, FProgramInfo& ProgramInfo);
};