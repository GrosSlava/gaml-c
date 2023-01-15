// Copyright 2022 - 2023 GrosSlava.

#include "GamlFileInfo.h"
#include "OptionsParser.h"
#include "ToolChain/ToolChain.h"





/*
	gaml-c entry point.
*/
int main(int argc, char** argv)
{
	FCompileOptions LCompileOptions;
	std::vector<FGamlFileInfo> LSourceFilePaths;
	std::vector<std::string> LObjectFilesPaths;
	std::vector<std::string> LLibsFilesPaths;

	ParseInputOptions(argc, argv, LCompileOptions, LSourceFilePaths, LObjectFilesPaths, LLibsFilesPaths);

	FToolChain LToolChain;
	LToolChain.Process(LSourceFilePaths, LObjectFilesPaths, LLibsFilesPaths, LCompileOptions);

	return 0;
}