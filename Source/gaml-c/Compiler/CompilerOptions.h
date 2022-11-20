// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "CompilerConfig.h"
#include "CompilerFileInfo.h"




/*
	Types of code optimization.
*/
enum class EOptimizationLevel
{
	NoOptimization = 0,
	SizeOptimization = 1,
	SpeedOptimization = 2
};

/*
	Types of severity of the warning.
*/
enum class EWarningLevel
{
	NoWarnings = 0,
	SeriousWarning = 1,
	CommonWarning = 2,
	MinorWarning = 3
};

/*
	Types of available code generations.
*/
enum class ECodeGenerationType
{
	ReduceC,
	LLVM,
	NASM
};

/*
	Type of subsystem for which the executable file is intended.
*/
enum class ESubsystemType
{
	Console,
	Window
};



/*
	All compilation options. 
	Will be filled in from the console options.
*/
struct FCompileOptions
{
	/*
		Path to current running compiler.
	*/
	std::string PathToCompiler = "";

	/*
		Directory for compiler output.
	*/
	std::string OutputDir = "";
	/*
		Name of compiled program. By default name of first file.
	*/
	std::string ProgramName = "";
	/*
		Level of optimization.
	*/
	EOptimizationLevel OptimizationLevel = EOptimizationLevel::SpeedOptimization;
	/*
		Level of warning.
	*/
	EWarningLevel WarningLevel = EWarningLevel::CommonWarning;
	/*
		Type of code generation.
	*/
	ECodeGenerationType CodeGenerationType = ECodeGenerationType::ReduceC;
	/*
		Type of program subsystem.
	*/
	ESubsystemType SubsystemType = ESubsystemType::Console;
	/*
		Target platform for code generation.
	*/
	ETargetPlatform TargetPlatform = FCompilerConfig::DEFAULT_TARGET_PLATFORM;
	/*
		Target architecture for code generation.
	*/
	ETargetArch TargetArch = FCompilerConfig::DEFAULT_TARGET_ARCH;
	/*
		Name of entry function. Empty means default.
	*/
	std::string EntryPoint = "";
	/*
		Array of addtional paths where linker will search libs.
	*/
	std::vector<std::string> AdditionalLibsSearchingDirs;

	/*
		Include debug information or not.
	*/
	bool IsDebug = false;
	/*
		Is compiling dll.
	*/
	bool IsDLL = false;
	/*
		All warnings will be errors.
	*/
	bool ConvertWarningsToErrors = false;
	/*
		No all builtin content like string, dynamic array...
	*/
	bool NoBuiltin = false;
	/*
		Generate freestanding code without platform libraries, etc.
	*/
	bool Freestanding = false;
	/*
		Disable stack protection.
	*/
	bool NoStackProtection = false;
	/*
		Disable red zones.
	*/
	bool NoRedZone = false;

	/*
		Do not translate the generated code to a machine code using a third-party compiler.
	*/
	bool NoTranslation = false;
	/*
		Dump LEXER stage to file.
	*/
	bool DumpLexemes = false;
	/*
		Dump all used modules dependencies to file.
	*/
	bool DumpModuleDependencies = false;
	/*
		Dump generated code to file.
	*/
	bool DumpGeneratedCode = false;
	/*
		Dump assembler stage to file.
	*/
	bool DumpAssembly = false;
	/*
		Stop on obj file stage.
	*/
	bool NoLinking = false;

	/*
		No compiler prints.
	*/
	bool Silent = false;
	/*
		Print context string with errors or not.
	*/
	bool IncludeContextIntoErrors = true;
	/*
		Show compilation progress. Useful when compiling multiple files.
	*/
	bool ShowProgress = false;
};



// clang-format off
void ParseInputOptions
(
	int argc, char** argv, FCompileOptions& OutCompileOptions, 
	std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths
);
// clang-format on