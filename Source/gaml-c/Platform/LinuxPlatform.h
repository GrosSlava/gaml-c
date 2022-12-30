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
		ConsoleCommand.reserve(128);

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
			FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_GENERATE, OriginalFile.GetFileFullPath(), 0, 0, 0, CompileOptions);
			break;
		}
		}

		ConsoleCommand += " -c -Wextra -Wall -fexec-charset=UTF-8 -finput-charset=UTF-8 -masm=intel";

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

	// clang-format off
	static int RunThirdPartyLinker
	(
		const FCompileOptions& CompileOptions, const std::string& OutputFilePath,
		const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths
	)
	// clang-format on
	{
		std::string ConsoleCommand = "";
		ConsoleCommand.reserve(128);

		if( CompileOptions.TargetArch != FCompilerConfig::DEFAULT_TARGET_ARCH )
		{
			FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_LINK, "", 0, 0, 0, CompileOptions);
		}

		ConsoleCommand += "gcc";

		switch( CompileOptions.SubsystemType )
		{
		case ESubsystemType::Console:
		{
			ConsoleCommand += "";
			break;
		}
		case ESubsystemType::Window:
		{
			ConsoleCommand += "";
			break;
		}
		default:
		{
			FErrorLogger::Raise(EErrorMessageType::INVALID_SUBSYSTEM, "", 0, 0, 0, CompileOptions);
			break;
		}
		}

		for( const std::string& LLibSearchPath : CompileOptions.AdditionalLibsSearchingDirs )
		{
			ConsoleCommand += " -L" + LLibSearchPath;
		}
		for( const std::string& LLibFilePath : LibsFilesPaths )
		{
			if( LLibFilePath.empty() ) continue;
			ConsoleCommand += " -l" + LLibFilePath;
		}

		if( CompileOptions.Freestanding ) ConsoleCommand += " -nostdlib";
		if( !CompileOptions.EntryPoint.empty() )
		{
			ConsoleCommand += " -e" + CompileOptions.EntryPoint;
		}
		else
		{
			ConsoleCommand += " -nostartfiles";
		}
		if( CompileOptions.IsDebug ) ConsoleCommand += "";
		if( CompileOptions.IsDLL ) ConsoleCommand += " -shared -fPIC";

		ConsoleCommand += " -o" + OutputFilePath;

		for( const std::string& LObjectFilePath : ObjectFilesPaths )
		{
			if( LObjectFilePath.empty() ) continue;
			ConsoleCommand += " " + LObjectFilePath;
		}

		return system(ConsoleCommand.c_str());
	}
};
