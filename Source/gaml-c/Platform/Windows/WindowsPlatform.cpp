// Copyright 2022 - 2023 GrosSlava.

#include "../../CoreMinimal.h"
#if WINDOWS_32 || WINDOWS_64

#include "WindowsPlatform.h"
#include "../PlatformHelperLibrary.h"





// clang-format off
int FGenericPlatform::RunMSVC
(
	const FGamlFileInfo& OriginalFile, const FCompileOptions& CompileOptions,
	const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
)
// clang-format on
{
	std::string ConsoleCommand = "";
	ConsoleCommand.reserve(256);

	ConsoleCommand += '\"' + GetMSVCHostDirectory();

	// for compiling to target platform use native tools command prompt for VS
	switch( CompileOptions.TargetArch )
	{
	case ETargetArch::x86:
	{
		ConsoleCommand += "\\x86\\cl.exe\" -arch:SSE2";
		break;
	}
	case ETargetArch::x86_64:
	{
		ConsoleCommand += "\\x64\\cl.exe\" -arch:AVX2";
		break;
	}
	case ETargetArch::arm:
	{
		ConsoleCommand += "\\arm\\cl.exe\" -arch:VFPv4";
		break;
	}
	case ETargetArch::arm_64:
	{
		ConsoleCommand += "\\arm64\\cl.exe\" -arch:armv8.0";
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
		ConsoleCommand += " -Od";
		break;
	}
	case EOptimizationLevel::SizeOptimization:
	{
		ConsoleCommand += " -O1 -Os";
		break;
	}
	case EOptimizationLevel::SpeedOptimization:
	{
		ConsoleCommand += " -O2 -Ot";
		break;
	}
	}

	// clang-format off
	if( CompileOptions.IsDebug )                    { ConsoleCommand += ""; }
	if( CompileOptions.ConvertWarningsToErrors )    { ConsoleCommand += " -WX"; }
	if( CompileOptions.DumpAssembly )               { ConsoleCommand += " -FAcs -Fa" + OutputDirectoryPath; }
	if( CompileOptions.NoBuiltin )                  { ConsoleCommand += ""; }
	if( CompileOptions.Freestanding )               { ConsoleCommand += ""; }
	if( CompileOptions.NoStackProtection )          { ConsoleCommand += " -GS-"; }
	if( CompileOptions.NoRedZone )                  { ConsoleCommand += ""; }
	// clang-format on

	ConsoleCommand += " -TC -Gd -c -nologo -Wall -Qspectre- -source-charset:utf-8 -execution-charset:utf-8 -fp:precise";
	ConsoleCommand += " -Fo" + CompiledObjectFilePath;
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

	ConsoleCommand += '\"' + GetMSVCHostDirectory();

	switch( CompileOptions.TargetArch )
	{
	case ETargetArch::x86:
	{
		ConsoleCommand += "\\x86\\link.exe\" -MACHINE:X86";
		break;
	}
	case ETargetArch::x86_64:
	{
		ConsoleCommand += "\\x64\\link.exe\" -MACHINE:X64";
		break;
	}
	case ETargetArch::arm:
	{
		ConsoleCommand += "\\arm\\link.exe\" -MACHINE:ARM";
		break;
	}
	case ETargetArch::arm_64:
	{
		ConsoleCommand += "\\arm64\\link.exe\"-MACHINE:ARM64";
		break;
	}
	default:
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_LINK, "", 0, 0, 0, CompileOptions);
		break;
	}
	}

	switch( CompileOptions.SubsystemType )
	{
	case ESubsystemType::Console:
	{
		ConsoleCommand += " -SUBSYSTEM:CONSOLE";
		break;
	}
	case ESubsystemType::Window:
	{
		ConsoleCommand += " -SUBSYSTEM:WINDOWS";
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
		ConsoleCommand += " -LIBPATH:" + LLibSearchPath;
	}
	for( const std::string& LLibFilePath : LibsFilesPaths )
	{
		if( LLibFilePath.empty() )
		{
			continue;
		}
		ConsoleCommand += " " + LLibFilePath;
	}

	// clang-format off
	if( CompileOptions.Freestanding )           { ConsoleCommand += " -NODEFAULTLIB"; }
	if( !CompileOptions.EntryPoint.empty() )    { ConsoleCommand += " -ENTRY:" + CompileOptions.EntryPoint; }
	if( CompileOptions.IsDebug )                { ConsoleCommand += " -DEBUG:FULL"; }
	if( CompileOptions.IsDLL )                  { ConsoleCommand += " -DLL"; }
	// clang-format on

	ConsoleCommand += " -NOLOGO -DYNAMICBASE -INCREMENTAL";
	ConsoleCommand += " -OUT:" + OutputFilePath;

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
