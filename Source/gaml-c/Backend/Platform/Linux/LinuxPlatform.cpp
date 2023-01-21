// Copyright 2022 - 2023 GrosSlava.

#include "CoreMinimal.h"
#if LINUX

#include "LinuxPlatform.h"
#include "Platform/PlatformHelperLibrary.h"





// clang-format off
int FGenericPlatform::RunGCC
(
	const FGamlFileInfo& OriginalFile,
	const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
)
// clang-format on
{
	std::string ConsoleCommand = "";
	ConsoleCommand.reserve(256);

	switch( FCoreObjects::CompileOptions.TargetArch )
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
		FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_GENERATE, OriginalFile.GetFileFullPath(), 0, 0, 0);
		break;
	}
	}

	switch( FCoreObjects::CompileOptions.OptimizationLevel )
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
	if( FCoreObjects::CompileOptions.IsDebug )                    { ConsoleCommand += " -g"; }
	if( FCoreObjects::CompileOptions.ConvertWarningsToErrors )    { ConsoleCommand += " -Werror"; }
	if( FCoreObjects::CompileOptions.DumpAssembly )               { ConsoleCommand += " -S"; }
	if( FCoreObjects::CompileOptions.NoBuiltin )                  { ConsoleCommand += " -fno-builtin"; }
	if( FCoreObjects::CompileOptions.Freestanding )               { ConsoleCommand += " -ffreestanding"; }
	if( FCoreObjects::CompileOptions.NoStackProtection )          { ConsoleCommand += " -fno-stack-protector"; }
	if( FCoreObjects::CompileOptions.NoRedZone )                  { ConsoleCommand += " -mno-red-zone"; }
	// clang-format on

	ConsoleCommand += " -c -Wextra -Wall -fexec-charset=UTF-8 -finput-charset=UTF-8 -masm=intel";
	ConsoleCommand += " -o" + CompiledObjectFilePath;
	ConsoleCommand += " " + FilePath;

	return FCompilerHelperLibrary::RunConsoleCommand(ConsoleCommand);
}

// clang-format off
int FGenericPlatform::RunLLC
(
	const FGamlFileInfo& OriginalFile,
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
	const std::string& OutputFilePath,
	const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths
)
// clang-format on
{
	std::string ConsoleCommand = "";
	ConsoleCommand.reserve(256);

	if( FCoreObjects::CompileOptions.TargetArch != FCompilerConfig::DEFAULT_TARGET_ARCH )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_LINK, "", 0, 0, 0);
	}

	ConsoleCommand += "gcc";

	switch( FCoreObjects::CompileOptions.SubsystemType )
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
		FErrorLogger::Raise(EErrorMessageType::INVALID_SUBSYSTEM, "", 0, 0, 0);
		break;
	}
	}

	for( const std::string& LLibSearchPath : FCoreObjects::CompileOptions.AdditionalLibsSearchingDirs )
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
	if( FCoreObjects::CompileOptions.Freestanding )           { ConsoleCommand += " -nostdlib"; }
	if( !FCoreObjects::CompileOptions.EntryPoint.empty() )    { ConsoleCommand += " -nostartfiles -e" + FCoreObjects::CompileOptions.EntryPoint; }
	if( FCoreObjects::CompileOptions.IsDebug )                { ConsoleCommand += ""; }
	if( FCoreObjects::CompileOptions.IsDLL )                  { ConsoleCommand += " -shared -fPIC"; }
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

	return FCompilerHelperLibrary::RunConsoleCommand(ConsoleCommand);
}

#endif
