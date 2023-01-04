// Copyright 2022 GrosSlava.

#include "../../CoreMinimal.h"
#if LINUX

#include "LinuxPlatform.h"
#include "../PlatformHelperLibrary.h"





// clang-format off
int FGenericPlatform::RunGCC
(
    const FGamlFileInfo& OriginalFile, const FCompileOptions& CompileOptions,
    const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
)
// clang-format on
{
	std::string ConsoleCommand = "";
	ConsoleCommand.reserve(256);

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

	// clang-format off
	if( CompileOptions.IsDebug ) 					{ ConsoleCommand += " -g"; }
	if( CompileOptions.ConvertWarningsToErrors ) 	{ ConsoleCommand += " -Werror"; }
	if( CompileOptions.DumpAssembly ) 				{ ConsoleCommand += " -S"; }
	if( CompileOptions.NoBuiltin ) 					{ ConsoleCommand += " -fno-builtin"; }
	if( CompileOptions.Freestanding ) 				{ ConsoleCommand += " -ffreestanding"; }
	if( CompileOptions.NoStackProtection ) 			{ ConsoleCommand += " -fno-stack-protector"; }
	if( CompileOptions.NoRedZone ) 					{ ConsoleCommand += " -mno-red-zone"; }
	// clang-format on

	ConsoleCommand += " -c -Wextra -Wall -fexec-charset=UTF-8 -finput-charset=UTF-8 -masm=intel";
	ConsoleCommand += " -o" + CompiledObjectFilePath;
	ConsoleCommand += " " + FilePath;

	return FPlatformHelperLibrary::RunConsoleCommand(ConsoleCommand);
}

// clang-format off
int FGenericPlatform::RunLLC
(
    const FGamlFileInfo& OriginalFile, const FCompileOptions& CompileOptions,
    const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
)
// clang-format on
{
	//TODO
	return 0;
}





// clang-format off
int FGenericPlatform::RunThirdPartyLinker
(
    const FCompileOptions& CompileOptions, const std::string& OutputFilePath,
    const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths
)
// clang-format on
{
	std::string ConsoleCommand = "";
	ConsoleCommand.reserve(256);

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
		if( LLibSearchPath.empty() )
		{
			continue;
		}
		ConsoleCommand += " -L" + LLibSearchPath;
	}
	for( const std::string& LLibFilePath : LibsFilesPaths )
	{
		if( LLibFilePath.empty() )
		{
			continue;
		}
		ConsoleCommand += " -l" + LLibFilePath;
	}

	// clang-format off
	if( CompileOptions.Freestanding ) 			{ ConsoleCommand += " -nostdlib"; }
	if( !CompileOptions.EntryPoint.empty() ) 	{ ConsoleCommand += " -nostartfiles -e" + CompileOptions.EntryPoint; }
	if( CompileOptions.IsDebug ) 				{ ConsoleCommand += ""; }
	if( CompileOptions.IsDLL ) 					{ ConsoleCommand += " -shared -fPIC"; }
	// clang-format on

	ConsoleCommand += " -o" + OutputFilePath;

	for( const std::string& LObjectFilePath : ObjectFilesPaths )
	{
		if( LObjectFilePath.empty() )
		{
			continue;
		}
		ConsoleCommand += " " + LObjectFilePath;
	}

	return FPlatformHelperLibrary::RunConsoleCommand(ConsoleCommand);
}

#endif
