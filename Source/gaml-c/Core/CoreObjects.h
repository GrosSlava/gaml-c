// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CompilerOptions.h"
#include "CompilerConfig.h"




/**
	All project global objects for easy access.
	Must be inited in main.
*/
struct FCoreObjects
{
	/*
		Compiler options for all subsystems.
	*/
	static FCompileOptions CompileOptions;
};
