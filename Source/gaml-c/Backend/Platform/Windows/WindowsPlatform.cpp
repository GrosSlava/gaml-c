// Copyright 2022 - 2023 GrosSlava.

#include "CoreMinimal.h"
#if WINDOWS_32 || WINDOWS_64

#include "WindowsPlatform.h"
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

	ConsoleCommand += '\"' + GetMSVCHostDirectory();

	switch( FCoreObjects::CompileOptions.TargetArch )
	{
	case ETargetArch::x86_64:
	{
		ConsoleCommand += "\\x64\\link.exe\" -MACHINE:X64";
		break;
	}
	case ETargetArch::AArch64:
	{
		ConsoleCommand += "\\arm64\\link.exe\"-MACHINE:ARM64";
		break;
	}
	default:
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_LINK, "", 0, 0, 0);
		break;
	}
	}

	switch( FCoreObjects::CompileOptions.SubsystemType )
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
	if( true /* Freestanding */ )												{ ConsoleCommand += " -NODEFAULTLIB"; }
	if( !FCoreObjects::CompileOptions.EntryPoint.empty() )						{ ConsoleCommand += " -ENTRY:" + FCoreObjects::CompileOptions.EntryPoint; }
	if( FCoreObjects::CompileOptions.IsDebug )									{ ConsoleCommand += " -DEBUG:FULL"; }
	if( FCoreObjects::CompileOptions.BuildType == EBuildType::SharedLibrary )	{ ConsoleCommand += " -DLL"; }
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

	return FCompilerHelperLibrary::RunConsoleCommand(ConsoleCommand);
}

#endif
