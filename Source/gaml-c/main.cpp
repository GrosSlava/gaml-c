// Copyright 2022 - 2023 GrosSlava.

#include "GamlFileInfo.h"
#include "OptionsParser.h"
#include "CoreObjects.h"
#include "ToolChain/ToolChain.h"





/*
	gaml-c entry point.
*/
int main(int argc, char** argv)
{
	// Parse console input
	FCompileOptions LCompileOptions;
	std::vector<FGamlFileInfo> LSourceFilePaths;
	std::vector<std::string> LObjectFilesPaths;
	std::vector<std::string> LLibsFilesPaths;
	ParseInputOptions(argc, argv, LCompileOptions, LSourceFilePaths, LObjectFilesPaths, LLibsFilesPaths);

	// Set global objects
	FCoreObjects::CompileOptions = LCompileOptions;

	// Run tool chain
	FToolChain LToolChain;
	LToolChain.Process(LSourceFilePaths, LObjectFilesPaths, LLibsFilesPaths);

	return 0;
}