// Copyright 2022 GrosSlava.

#include "Linker.h"
#include "../Compiler/CompilerConfig.h"
#include "../Generator/GeneratorHelperLibrary.h"

#include <cstdio>





void Linker::Process(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths, const FCompileOptions& Options)
{
	if( ObjectFilesPaths.empty() ) return;

	CurrentCompileOptions = Options;
	FirstFileInfo = FCompilerHelperLibrary::SplitFilePath(ObjectFilesPaths[0]);


	RunThirdPartyLinker(ObjectFilesPaths, LibsFilesPaths);
}



void Linker::RunThirdPartyLinker(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths)
{
	std::string ConsoleCommand = "";

	std::string ExecutableFileExtension = "";
	std::string LibraryFileExtension = "";
	switch( CurrentCompileOptions.TargetPlatform )
	{
	case ETargetPlatform::Windows:
	{
		ExecutableFileExtension = "exe";
		LibraryFileExtension = "dll";
		break;
	}
	case ETargetPlatform::Linux:
	{
		ExecutableFileExtension = "out";
		LibraryFileExtension = "so";
		break;
	}
	default:
	{
		RaiseError(EErrorMessageType::CANT_LINK_TO_TARGET_PLATFORM, "");
		break;
	}
	}
	


#if WINDOWS_32 || WINDOWS_64
	ConsoleCommand += '\"' + FGeneratorHelperLibrary::GetMSVCHostDirectory();

	switch( CurrentCompileOptions.TargetArch )
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
	case ETargetArch::Arm:
	{
		ConsoleCommand += "\\arm\\link.exe\" -MACHINE:ARM";
		break;
	}
	case ETargetArch::Arm_64:
	{
		ConsoleCommand += "\\arm64\\link.exe\"-MACHINE:ARM64";
		break;
	}
	default:
	{
		RaiseError(EErrorMessageType::INVALID_ARCH_FOR_LINK, "");
		break;
	}
	}

	ConsoleCommand += " -NOLOGO -DYNAMICBASE -INCREMENTAL";
	
	switch( CurrentCompileOptions.SubsystemType )
	{
	case ESubsystemType::Boot:
	{
		ConsoleCommand += " -SUBSYSTEM:BOOT_APPLICATION";
		break;
	}
	case ESubsystemType::Native:
	{
		ConsoleCommand += " -SUBSYSTEM:NATIVE";
		break;
	}
	case ESubsystemType::Console:
	{
		ConsoleCommand += " -SUBSYSTEM:CONSOLE";
		break;
	}
	case ESubsystemType::Windows:
	{
		ConsoleCommand += " -SUBSYSTEM:WINDOWS";
		break;
	}
	default:
	{
		RaiseError(EErrorMessageType::INVALID_SUBSYSTEM, "");
		break;
	}
	}

	for( const std::string& LLibSearchPath : CurrentCompileOptions.AdditionalLibsSearchingDirs )
	{
		ConsoleCommand += " -LIBPATH:" + LLibSearchPath;
	}
	for( const std::string& LLibFilePath : LibsFilesPaths )
	{
		if( LLibFilePath.empty() ) continue;
		ConsoleCommand += " " + LLibFilePath;
	}

	if( CurrentCompileOptions.Freestanding )
	{
		ConsoleCommand += " -NODEFAULTLIB";
	}
	else
	{
		// use native tools command prompt for VS
	}
	if( !CurrentCompileOptions.EntryPoint.empty() )
	{
		ConsoleCommand += " -ENTRY:" + CurrentCompileOptions.EntryPoint;
	}
	if( CurrentCompileOptions.IsDLL )
	{
		ConsoleCommand += " -DLL";
	}

	ConsoleCommand += " -OUT:" + GetOutputFilePath(CurrentCompileOptions.IsDLL ? LibraryFileExtension : ExecutableFileExtension);
#elif LINUX
	if( CurrentCompileOptions.TargetArch != FCompilerConfig::DEFAULT_TARGET_ARCH )
	{
		RaiseError(EErrorMessageType::INVALID_ARCH_FOR_LINK, "");
	}

	ConsoleCommand += "ld";

	switch( CurrentCompileOptions.SubsystemType )
	{
	case ESubsystemType::Boot:
	{
		ConsoleCommand += "-mcmodel=kernel";
		break;
	}
	case ESubsystemType::Native:
	{
		ConsoleCommand += "-mcmodel=kernel";
		break;
	}
	case ESubsystemType::Console:
	{
		ConsoleCommand += "";
		break;
	}
	case ESubsystemType::Windows:
	{
		ConsoleCommand += "";
		break;
	}
	default:
	{
		RaiseError(EErrorMessageType::INVALID_SUBSYSTEM, "");
		break;
	}
	}

	for( const std::string& LLibSearchPath : CurrentCompileOptions.AdditionalLibsSearchingDirs )
	{
		ConsoleCommand += " -L" + LLibSearchPath;
	}
	for( const std::string& LLibFilePath : LibsFilesPaths )
	{
		if( LLibFilePath.empty() ) continue;
		ConsoleCommand += " -l" + LLibFilePath;
	}

	if( CurrentCompileOptions.Freestanding )
	{
		ConsoleCommand += " -nostdlib";
	}
	else
	{
		ConsoleCommand += " -lm -lc -lgcc";
	}
	if( !CurrentCompileOptions.EntryPoint.empty() )
	{
		ConsoleCommand += " -e" + CurrentCompileOptions.EntryPoint;
	}
	if( CurrentCompileOptions.IsDLL )
	{
		ConsoleCommand += " -shared -fPIC";
	}

	ConsoleCommand += " -o" + GetOutputFilePath(CurrentCompileOptions.IsDLL ? LibraryFileExtension : ExecutableFileExtension);
#else
	RaiseError(EErrorMessageType::NO_DEFAULT_LINKER_FOR_CURRENT_PLATFORM, "");
#endif

	for( const std::string& LObjectFilePath : ObjectFilesPaths )
	{
		if( LObjectFilePath.empty() ) continue;
		ConsoleCommand += " " + LObjectFilePath;
	}

	system(ConsoleCommand.c_str());
}
