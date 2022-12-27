// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#if !WINDOWS_32 && !WINDOWS_64
#error "WINDOWS platform not defined!"
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
			FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_GENERATE, OriginalFile.GetFileFullPath(), 0, 0, CompileOptions);
			break;
		}
		}

		ConsoleCommand += " -TC -Gd -c -nologo -Wall -Qspectre-";
		ConsoleCommand += " -source-charset:utf-8 -execution-charset:utf-8"; // set charset
		ConsoleCommand += " -fp:precise";									 // set floating point behaviour
		ConsoleCommand += "";												 // set assembler syntax (intel syntax is by default, no option to set directly)
		ConsoleCommand += "";												 // disable exceptions (not pass argument for exception)

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

		if( CompileOptions.IsDebug ) ConsoleCommand += "";
		if( CompileOptions.ConvertWarningsToErrors ) ConsoleCommand += " -WX";
		if( CompileOptions.DumpAssembly ) ConsoleCommand += " -FAcs -Fa" + OutputDirectoryPath;
		if( CompileOptions.NoBuiltin ) ConsoleCommand += "";
		if( CompileOptions.Freestanding ) ConsoleCommand += "";
		if( CompileOptions.NoStackProtection ) ConsoleCommand += " -GS-";
		if( CompileOptions.NoRedZone ) ConsoleCommand += "";

		ConsoleCommand += " -Fo" + CompiledObjectFilePath;

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
			FErrorLogger::Raise(EErrorMessageType::INVALID_ARCH_FOR_LINK, "", 0, 0, CompileOptions);
			break;
		}
		}

		ConsoleCommand += " -NOLOGO -DYNAMICBASE -INCREMENTAL";

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
			FErrorLogger::Raise(EErrorMessageType::INVALID_SUBSYSTEM, "", 0, 0, CompileOptions);
			break;
		}
		}

		for( const std::string& LLibSearchPath : CompileOptions.AdditionalLibsSearchingDirs )
		{
			ConsoleCommand += " -LIBPATH:" + LLibSearchPath;
		}
		for( const std::string& LLibFilePath : LibsFilesPaths )
		{
			if( LLibFilePath.empty() ) continue;
			ConsoleCommand += " " + LLibFilePath;
		}

		if( CompileOptions.Freestanding ) ConsoleCommand += " -NODEFAULTLIB";
		if( !CompileOptions.EntryPoint.empty() ) ConsoleCommand += " -ENTRY:" + CompileOptions.EntryPoint;
		if( CompileOptions.IsDebug ) ConsoleCommand += " -DEBUG:FULL";
		if( CompileOptions.IsDLL ) ConsoleCommand += " -DLL";

		ConsoleCommand += " -OUT:" + OutputFilePath;

		for( const std::string& LObjectFilePath : ObjectFilesPaths )
		{
			if( LObjectFilePath.empty() ) continue;
			ConsoleCommand += " " + LObjectFilePath;
		}

		return system(ConsoleCommand.c_str());
	}




	static std::string GetMSVCRootDirectory() noexcept
	{
		std::string LResult = "";

		LResult += "C:\\Program Files\\Microsoft Visual Studio\\";
		const std::string LVisualStudioYearVersion = FCompilerHelperLibrary::GetBestFolderName("C:/Program Files/Microsoft Visual Studio", {"2022", "2019", "2017"});
		LResult += LVisualStudioYearVersion;
		LResult += "\\";
		const std::string LVisualStudioType = FCompilerHelperLibrary::GetBestFolderName("C:/Program Files/Microsoft Visual Studio/" + LVisualStudioYearVersion, {"Professional", "Community"});
		LResult += LVisualStudioType;
		LResult += "\\VC\\Tools\\MSVC\\";
		LResult += FCompilerHelperLibrary::GetFirstFolderName("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC");

		return LResult;
	}

	static inline std::string GetMSVCHostDirectory() noexcept
	{
		std::string LResult = GetMSVCRootDirectory() + "\\bin\\";
#if WINDOWS_64
		LResult += "Hostx64";
#elif WINDOWS_32
		LResult += "Hostx86";
#endif
		return LResult;
	}
};
