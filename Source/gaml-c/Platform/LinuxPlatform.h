// Copyright 2022 GrosSlava.

#pragma once

#if !LINUX
#error "LINUX platform not defined!"
#endif


#include "../Compiler/CompilerOptions.h"
#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerHelperLibrary.h"

#include "../Logger/ErrorLogger.h"

#include <cstdio>




struct FGenericPlatform
{
	// clang-format off
	static int RunThirdPartyCompiler
	(
		const FGamlFileInfo& OriginalFile, const FCompileOptions& CompileOptions,
		const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
	)
	// clang-format on
	{ 
		std::string ConsoleCommand = "";

		switch( CompileOptions.TargetArch )
		{
		case ETargetArch::x86:
		{
			ConsoleCommand += "gcc -m32";
			break;
		}
		case ETargetArch::x86_64:
		{
			ConsoleCommand += "gcc -m64";
			break;
		}
		case ETargetArch::arm:
		{
			ConsoleCommand += "gcc -marm";
			break;
		}
		case ETargetArch::arm_64:
		{
			ConsoleCommand += "gcc -marm";
			break;
		}
		default:
		{
			FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_GENERATE, OriginalFile.GetFileFullPath(), 0, 0, CompileOptions);
			break;
		}
		}

		ConsoleCommand += " -c -Wextra -Wall";
		ConsoleCommand += " -fexec-charset=UTF-8 -finput-charset=UTF-8"; // set charset
		ConsoleCommand += "";											 // set floating point behaviour (use default options)
		ConsoleCommand += " -masm=intel";								 // set assembler syntax
		ConsoleCommand += "";											 // disable exceptions(gcc does not support exceptions because it is compiler for C)

		switch( CompileOptions.OptimizationLevel )
		{
		case EOptimizationLevel::NoOptimization:
		{
			ConsoleCommand += " -O0";
			break;
		}
		case EOptimizationLevel::SizeOptimization:
		{
			ConsoleCommand += " -Os";
			break;
		}
		case EOptimizationLevel::SpeedOptimization:
		{
			ConsoleCommand += " -Ofast";
			break;
		}
		}

		if( CompileOptions.IsDebug ) ConsoleCommand += " -g";
		if( CompileOptions.ConvertWarningsToErrors ) ConsoleCommand += " -Werror";
		if( CompileOptions.DumpAssembly ) ConsoleCommand += " -S";
		if( CompileOptions.NoBuiltin ) ConsoleCommand += " -fno-builtin";
		if( CompileOptions.Freestanding ) ConsoleCommand += " -ffreestanding";
		if( CompileOptions.NoStackProtection ) ConsoleCommand += " -fno-stack-protector";
		if( CompileOptions.NoRedZone ) ConsoleCommand += " -mno-red-zone";

		ConsoleCommand += " -o" + CompiledObjectFilePath;

		ConsoleCommand += " ";
		ConsoleCommand += FilePath;

		return system(ConsoleCommand.c_str());
	}
};
