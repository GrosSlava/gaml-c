// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CompilerOptions.h"




struct FGamlFileInfo;




/*
	Main object for organizing tools.
*/
struct FToolChain final
{
public:

	FToolChain() { }



public:

	// clang-format off
	/*
		Process tool chain pipeline.

		@param SourceFilePaths - Array of source files to compile.
		@param ObjectFilesPaths - Array of additional object files for linking.
		@param LibsFilesPaths - Array of additional libraries for linking.
		@param CompileOptions - Compilation options.
	*/
	void Process
	(
		const std::vector<FGamlFileInfo>& SourceFilePaths, 
		const std::vector<std::string>& ObjectFilesPaths,
		const std::vector<std::string>& LibsFilesPaths, 
		const FCompileOptions& CompileOptions
	);
	// clang-format on

private:

	//...............Tool chain pipeline................//

	void CompileSourceFiles(const std::vector<FGamlFileInfo>& SourceFilePaths, std::vector<std::string>& OutObjectFilesPaths);
	void LinkProgram(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths);

	//..................................................//




private:

	/*
		Cached compile options.
	*/
	FCompileOptions CurrentCompileOptions;
};
