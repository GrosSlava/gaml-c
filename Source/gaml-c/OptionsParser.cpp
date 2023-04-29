// Copyright 2022 - 2023 GrosSlava.

#include "OptionsParser.h"

#include "CompilerOptions.h"
#include "GamlFileInfo.h"
#include "CompilerHelperLibrary.h"

#include "Platform/PlatformHelperLibrary.h"

#include "Logger/ErrorLogger.h"





// clang-format off
bool FOptionInfo::Process
(
	const std::string& OptionStr, FCompileOptions& OutCompileOptions, 
	std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths
) const
// clang-format on
{
	if( HasArgument )
	{
		if( !ShortOption.empty() && OptionStr.substr(0, ShortOption.size()) == ShortOption )
		{
			Function(OptionStr.substr(ShortOption.size()), OutCompileOptions, OutSourceFilePaths, OutObjectFiles, OutLibsFilesPaths);
			return true;
		}
		else if( !LongOption.empty() && OptionStr.substr(0, LongOption.size()) == LongOption )
		{
			Function(OptionStr.substr(LongOption.size()), OutCompileOptions, OutSourceFilePaths, OutObjectFiles, OutLibsFilesPaths);
			return true;
		}
	}
	else if( OptionStr == ShortOption || OptionStr == LongOption )
	{
		Function("", OutCompileOptions, OutSourceFilePaths, OutObjectFiles, OutLibsFilesPaths);
		return true;
	}

	return false;
}





// clang-format off
static const std::vector<FOptionInfo> Options = 
{
	FOptionInfo("-h",	"--help",					"help information",										false,	HelpOption),
	FOptionInfo("-v",	"--version",				"compiler version",										false,	VersionOption),

	FOptionInfo("-p",	"--package=",				"compiling package dir with gaml files",				true,	PackageOption),
	FOptionInfo("-P",	"--link_package=",			"static link package dir with object files",			true,	StaticLinkOption),
	FOptionInfo("-l",	"--lib=",					"link library",											true,	LinkLibraryOption),
	FOptionInfo("-o",	"--output=",				"set output directory",									true,	OutputOption),
	FOptionInfo("-n",	"--name=",					"set result name",										true,	ProgramNameOption),
	FOptionInfo("-O",	"",							"set optimization level [0 - 2]",						true,	OptimizationLevelOption),
	FOptionInfo("-W",	"",							"set warning level [0 - 3]",							true,	WarningLevelOption),
	FOptionInfo("",		"--subsystem=",				"set type of subsystem [Console, Window]",				true,	SubsystemTypeOption),
	FOptionInfo("",		"--build=",					"set type of program build [lib, dlib, exe]",			true,	BuildTypeOption),
	FOptionInfo("",		"--platform=",				"set target platform (Undefined, Windows, Linux)",		true,	TargetPlatformOption),
	FOptionInfo("",		"--arch=",					"set target arch (x86_64, AArch64)",			        true,	TargetArchOption),
	FOptionInfo("-e",	"--entry=",					"set entry point name",									true,	EntryPointOption),
	FOptionInfo("-L",	"--libpath=",				"add libs searching dir",								true,	LibsSearchingOption),

	FOptionInfo("",		"--debug",					"include debug information",							false,	DebugOption),
	FOptionInfo("",		"--w2e",					"convert warnings to errors",							false,	WarningToErrorsOption),
	FOptionInfo("",		"--no_reflection",			"disable reflection code generation",					false,	NoReflectionOption),

	FOptionInfo("-q",	"--quiet",					"no compiler messages",									false,	QuietOption),
	FOptionInfo("",		"--no_context",				"no context string with errors",						false,	NoContextOption),
	FOptionInfo("",		"--progress",				"show compilation progress",							false,	ShowProgressOption), 
	FOptionInfo("-t",	"--time",					"show total compilation time",							false,	ShowCompileTimeOption),

	FOptionInfo("",		"--dump_lexeme",			"dump lexemes to file",									false,	DumpLexemeOption),
	FOptionInfo("",		"--dump_ast",				"dump all ast to file",									false,	DumpASTOption),
	FOptionInfo("",		"--dump_modules",			"dump modules dependencies to file",					false,	DumpModulesOption),
	FOptionInfo("",		"--dump_ir",				"dump IR to file",										false,	DumpIROption),
	FOptionInfo("",		"--dump_code",				"dump generated code to file",							false,	DumpGeneratedCodeOption),
	FOptionInfo("-c",	"",							"no linking, only compile",								false,	NoLinkingOption),
};
// clang-format on

OPTION_FUNCTION(HelpOption)
{
	for( const FOptionInfo& LOptionInfo : Options )
	{
		FCompileLogger::MessageText(LOptionInfo.GetHelpStr());
	}
	exit(0);
}

OPTION_FUNCTION(VersionOption)
{
	FCompileLogger::MessageText(std::string(FCompilerConfig::COMPILER_NAME) + std::string(" ") + std::string(FCompilerConfig::COMPILER_VERSION));
	exit(0);
}

OPTION_FUNCTION(PackageOption)
{
	std::vector<FGamlFileInfo> LPackegeFilesInfo;
	FCompilerHelperLibrary::GetAllFilesWithExtensionsInFolder(Argument, {FCompilerConfig::COMPILE_FILE_EXTENSION}, LPackegeFilesInfo);

	if( LPackegeFilesInfo.empty() )
	{
		FCompileLogger::MessageError("Package '" + Argument + "' hasn't got any compilable files.");
		exit(0);
	}

	for( const FGamlFileInfo& LFileInfo : LPackegeFilesInfo )
	{
		OutSourceFilePaths.push_back(LFileInfo);
	}
}

OPTION_FUNCTION(StaticLinkOption)
{
	std::vector<FGamlFileInfo> LPackegeFilesInfo;
	FCompilerHelperLibrary::GetAllFilesWithExtensionsInFolder(Argument, FPlatformHelperLibrary::GetAllObjectFileExtensions(), LPackegeFilesInfo);

	if( LPackegeFilesInfo.empty() )
	{
		FCompileLogger::MessageError("Package '" + Argument + "' hasn't got any object files.");
		exit(0);
	}

	for( const FGamlFileInfo& LFileInfo : LPackegeFilesInfo )
	{
		OutObjectFiles.push_back(LFileInfo.GetFileFullPath());
	}
}

OPTION_FUNCTION(LinkLibraryOption)
{
	OutLibsFilesPaths.push_back(Argument);
}

OPTION_FUNCTION(OutputOption)
{
	OutCompileOptions.OutputDir = Argument;
}

OPTION_FUNCTION(ProgramNameOption)
{
	OutCompileOptions.ProgramName = Argument;
}

OPTION_FUNCTION(OptimizationLevelOption)
{
	if( Argument.empty() || std::isdigit(Argument[0]) ) return;

	switch( static_cast<int>(Argument[0] - '0') )
	{
	case 0:
	{
		OutCompileOptions.OptimizationLevel = EOptimizationLevel::NoOptimization;
		break;
	}
	case 1:
	{
		OutCompileOptions.OptimizationLevel = EOptimizationLevel::SizeOptimization;
		break;
	}
	case 2:
	{
		OutCompileOptions.OptimizationLevel = EOptimizationLevel::SpeedOptimization;
		break;
	}
	default:
	{
		FCompileLogger::MessageError("Invalid optimization level: " + Argument[0]);
		exit(0);
	}
	}
}

OPTION_FUNCTION(WarningLevelOption)
{
	if( Argument.empty() || std::isdigit(Argument[0]) ) return;

	switch( static_cast<int>(Argument[0] - '0') )
	{
	case 0:
	{
		OutCompileOptions.WarningLevel = EWarningLevel::NoWarnings;
		break;
	}
	case 1:
	{
		OutCompileOptions.WarningLevel = EWarningLevel::MinorWarning;
		break;
	}
	case 2:
	{
		OutCompileOptions.WarningLevel = EWarningLevel::CommonWarning;
		break;
	}
	case 3:
	{
		OutCompileOptions.WarningLevel = EWarningLevel::SeriousWarning;
		break;
	}
	default:
	{
		FCompileLogger::MessageError("Invalid warning level: " + Argument[0]);
		exit(0);
	}
	}
}

OPTION_FUNCTION(SubsystemTypeOption)
{
	if( Argument == "Console" )
	{
		OutCompileOptions.SubsystemType = ESubsystemType::Console;
	}
	else if( Argument == "Window" )
	{
		OutCompileOptions.SubsystemType = ESubsystemType::Window;
	}
	else
	{
		FCompileLogger::MessageError("Invalid subsystem type: " + Argument);
		exit(0);
	}
}

OPTION_FUNCTION(BuildTypeOption)
{
	if( Argument == "lib" )
	{
		OutCompileOptions.BuildType = EBuildType::StaticLibrary;
	}
	else if( Argument == "dlib" )
	{
		OutCompileOptions.BuildType = EBuildType::SharedLibrary;
	}
	else if( Argument == "exe" )
	{
		OutCompileOptions.BuildType = EBuildType::Executable;
	}
	else
	{
		FCompileLogger::MessageError("Invalid build type: " + Argument);
		exit(0);
	}
}

OPTION_FUNCTION(TargetPlatformOption)
{
	if( Argument == "Undefined" )
	{
		OutCompileOptions.TargetPlatform = ETargetPlatform::Undefined;
	}
	else if( Argument == "Windows" )
	{
		OutCompileOptions.TargetPlatform = ETargetPlatform::Windows;
	}
	else if( Argument == "Linux" )
	{
		OutCompileOptions.TargetPlatform = ETargetPlatform::Linux;
	}
	else
	{
		FCompileLogger::MessageError("Invalid platform type: " + Argument);
		exit(0);
	}
}

OPTION_FUNCTION(TargetArchOption)
{
	if( Argument == "x86_64" )
	{
		OutCompileOptions.TargetArch = ETargetArch::x86_64;
	}
	else if( Argument == "AArch64" )
	{
		OutCompileOptions.TargetArch = ETargetArch::AArch64;
	}
	else
	{
		FCompileLogger::MessageError("Invalid architecture type: " + Argument);
		exit(0);
	}
}

OPTION_FUNCTION(EntryPointOption)
{
	OutCompileOptions.EntryPoint = Argument;
}

OPTION_FUNCTION(LibsSearchingOption)
{
	OutCompileOptions.AdditionalLibsSearchingDirs.push_back(Argument);
}

OPTION_FUNCTION(DebugOption)
{
	OutCompileOptions.IsDebug = true;
}

OPTION_FUNCTION(WarningToErrorsOption)
{
	OutCompileOptions.ConvertWarningsToErrors = true;
}

OPTION_FUNCTION(NoReflectionOption)
{
	OutCompileOptions.NoReflection = true;
}

OPTION_FUNCTION(DumpLexemeOption)
{
	OutCompileOptions.DumpLexemes = true;
}

OPTION_FUNCTION(DumpASTOption)
{
	OutCompileOptions.DumpAST = true;
}

OPTION_FUNCTION(DumpModulesOption)
{
	OutCompileOptions.DumpModuleDependencies = true;
}

OPTION_FUNCTION(DumpIROption)
{
	OutCompileOptions.DumpIR = true;
}

OPTION_FUNCTION(DumpGeneratedCodeOption)
{
	OutCompileOptions.DumpGeneratedCode = true;
}

OPTION_FUNCTION(NoLinkingOption)
{
	OutCompileOptions.NoLinking = true;
}

OPTION_FUNCTION(QuietOption)
{
	OutCompileOptions.Silent = true;
}

OPTION_FUNCTION(NoContextOption)
{
	OutCompileOptions.IncludeContextIntoErrors = false;
}

OPTION_FUNCTION(ShowProgressOption)
{
	OutCompileOptions.ShowProgress = true;
}

OPTION_FUNCTION(ShowCompileTimeOption)
{
	OutCompileOptions.ShowCompileTime = true;
}





// clang-format off
void ParseInputOptions
(
	int argc, char** argv, FCompileOptions& OutCompileOptions, 
	std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths
)
// clang-format on
{
	if( argc <= 0 )
	{
		FCompileLogger::MessageError("No path to compiler!");
		exit(0);
	}

	OutCompileOptions.PathToCompiler = argv[0];

	for( int i = 1; i < argc; ++i )
	{
		if( argv[i][0] != '-' )
		{
			const FGamlFileInfo LFileInfo(argv[i]);

			if( FPlatformHelperLibrary::IsObjectFileExtension(LFileInfo.ExtensionOnly) )
			{
				OutObjectFiles.push_back(LFileInfo.GetFileFullPath());
			}
			else if( LFileInfo.ExtensionOnly == FCompilerConfig::COMPILE_FILE_EXTENSION )
			{
				OutSourceFilePaths.push_back(LFileInfo);
			}
			else
			{
				FCompileLogger::MessageError("File with extension '" + LFileInfo.ExtensionOnly + "' can't be compiled!");
			}

			continue;
		}


		const std::string LOptionName = argv[i];
		if( LOptionName.empty() ) continue;

		bool LFindOption = false;
		for( const FOptionInfo& LOptionInfo : Options )
		{
			if( LOptionInfo.Process(LOptionName, OutCompileOptions, OutSourceFilePaths, OutObjectFiles, OutLibsFilesPaths) )
			{
				LFindOption = true;
				break;
			}
		}

		if( !LFindOption )
		{
			FCompileLogger::MessageError("Option '" + LOptionName + "' not found!\nUse --help for details.");
			exit(0);
		}
	}
}