// Copyright 2022 - 2023 GrosSlava.

#include "CoreMinimal.h"
#if LINUX

#include "LinuxPlatform.h"
#include "Platform/PlatformHelperLibrary.h"





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
	if( true /* Freestanding */ )												{ ConsoleCommand += " -nostdlib"; }
	if( !FCoreObjects::CompileOptions.EntryPoint.empty() )						{ ConsoleCommand += " -nostartfiles -e" + FCoreObjects::CompileOptions.EntryPoint; }
	if( FCoreObjects::CompileOptions.IsDebug )									{ ConsoleCommand += ""; }
	if( FCoreObjects::CompileOptions.BuildType == EBuildType::SharedLibrary )	{ ConsoleCommand += " -shared -fPIC"; }
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
