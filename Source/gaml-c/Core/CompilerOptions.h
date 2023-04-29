// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CoreEnums.h"
#include "CompilerConfig.h"




/**
	All compilation options. 
	Will be filled in from the console options.
*/
struct FCompileOptions
{
	/**
		Path to current running compiler.
	*/
	std::string PathToCompiler = "";

	/**
		Directory for compiler output.
	*/
	std::string OutputDir = "";
	/**
		Name of compiled program. By default name of first file.
	*/
	std::string ProgramName = "";
	/**
		Level of optimization.
	*/
	EOptimizationLevel OptimizationLevel = EOptimizationLevel::SpeedOptimization;
	/**
		Level of warning.
	*/
	EWarningLevel WarningLevel = EWarningLevel::CommonWarning;
	/**
		Type of program subsystem.
	*/
	ESubsystemType SubsystemType = ESubsystemType::Console;
	/**
		Type of program build.
	*/
	EBuildType BuildType = EBuildType::Executable;
	/**
		Target platform for code generation.
	*/
	ETargetPlatform TargetPlatform = FCompilerConfig::DEFAULT_TARGET_PLATFORM;
	/**
		Target architecture for code generation.
	*/
	ETargetArch TargetArch = FCompilerConfig::DEFAULT_TARGET_ARCH;
	/**
		Name of entry function. Empty means default.
	*/
	std::string EntryPoint = "";
	/**
		Array of addtional paths where linker will search libs.
	*/
	std::vector<std::string> AdditionalLibsSearchingDirs;

	/**
		Include debug information or not.
	*/
	bool IsDebug = false;
	/**
		All warnings will be errors.
	*/
	bool ConvertWarningsToErrors = false;
	/**
		Disable reflection code generation.
	*/
	bool NoReflection = false;

	/**
		No compiler prints.
	*/
	bool Silent = false;
	/**
		Print context string with errors or not.
	*/
	bool IncludeContextIntoErrors = true;
	/**
		Show compilation progress. Useful when compiling multiple files.
	*/
	bool ShowProgress = false;
	/**
		Show total compilation time.
	*/
	bool ShowCompileTime = false;

	/**
		Dump LEXER stage to file.
	*/
	bool DumpLexemes = false;
	/**
		Dump PARSER stage to file.
	*/
	bool DumpAST = false;
	/**
		Dump all used modules dependencies to file.
	*/
	bool DumpModuleDependencies = false;
	/**
		Dump program IR to file.
	*/
	bool DumpIR = false;
	/**
		Dump generated code to file.
	*/
	bool DumpGeneratedCode = false;
	/**
		Stop on obj file stage.
	*/
	bool NoLinking = false;
};
