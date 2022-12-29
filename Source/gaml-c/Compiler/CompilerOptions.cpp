// Copyright 2022 GrosSlava.

#include "CompilerOptions.h"
#include "CompilerConfig.h"
#include "CompilerHelperLibrary.h"

#include "../Platform/PlatformHelperLibrary.h"

#include "../Logger/ErrorLogger.h"





struct FOptionInfo
{
public:

	FOptionInfo() = delete;

	// clang-format off
	FOptionInfo
	(
		const std::string& InShortOption, const std::string& InLongOption, const std::string& InDescription, bool InHasArgument,
		void (*InFunction)(const std::string&, FCompileOptions&, std::vector<FGamlFileInfo>&, std::vector<std::string>&, std::vector<std::string>&)
	) :
		ShortOption(InShortOption), LongOption(InLongOption), Description(InDescription), HasArgument(InHasArgument), Function(InFunction)
	{

	}
	// clang-format on


public:

	// clang-format off
	inline bool Process
	(
		const std::string& OptionStr, 
		FCompileOptions& OutCompileOptions, std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths
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
	inline std::string GetHelpStr() const
	{ 
		return ShortOption + std::string(4 - ShortOption.size(), ' ') + LongOption + std::string(25 - LongOption.size(), ' ') + " --- " + Description;
	}
	// clang-format on



private:

	std::string ShortOption = "";
	std::string LongOption = "";
	std::string Description = "";
	bool HasArgument = false;

	void (*Function)(const std::string&, FCompileOptions&, std::vector<FGamlFileInfo>&, std::vector<std::string>&, std::vector<std::string>&) = nullptr;
};




// clang-format off
#define OPTION_FUNCTION(Name) \
	void Name \
	( \
		const std::string& Argument, \
		FCompileOptions& OutCompileOptions, std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths \
	)
// clang-format on

OPTION_FUNCTION(HelpOption);
OPTION_FUNCTION(VersionOption);
OPTION_FUNCTION(PackageOption);
OPTION_FUNCTION(StaticLinkOption);
OPTION_FUNCTION(LinkLibraryOption);
OPTION_FUNCTION(OutputOption);
OPTION_FUNCTION(ProgramNameOption);
OPTION_FUNCTION(OptimizationLevelOption);
OPTION_FUNCTION(WarningLevelOption);
OPTION_FUNCTION(CodeGenerationTypeOption);
OPTION_FUNCTION(SubsystemTypeOption);
OPTION_FUNCTION(TargetPlatformOption);
OPTION_FUNCTION(TargetArchOption);
OPTION_FUNCTION(EntryPointOption);
OPTION_FUNCTION(LibsSearchingOption);
OPTION_FUNCTION(DebugOption);
OPTION_FUNCTION(DLLOption);
OPTION_FUNCTION(WarningToErrorsOption);
OPTION_FUNCTION(NoBuiltinOption);
OPTION_FUNCTION(FreestandingOption);
OPTION_FUNCTION(NoStackProtectionOption);
OPTION_FUNCTION(NoRedZonesOption);
OPTION_FUNCTION(NoTranslationOption);
OPTION_FUNCTION(DumpLexemeOption);
OPTION_FUNCTION(DumpModulesOption);
OPTION_FUNCTION(DumpCOption);
OPTION_FUNCTION(DumpASMOption);
OPTION_FUNCTION(NoLinkingOption);
OPTION_FUNCTION(QuietOption);
OPTION_FUNCTION(NoContextOption);
OPTION_FUNCTION(ShowProgressOption);

// clang-format off
static const std::vector<FOptionInfo> Options = 
{
	FOptionInfo("-h",	"--help",					"help information",										false,	HelpOption),
	FOptionInfo("-v",	"--version",				"compiler version",										false,	VersionOption),

	FOptionInfo("-p",	"--package=",				"compiling package dir with gaml files",				true,	PackageOption),
	FOptionInfo("-b",	"",							"static link package dir with object files",			true,	StaticLinkOption),
	FOptionInfo("-l",	"--lib=",					"link library",											true,	LinkLibraryOption),
	FOptionInfo("-o",	"--output=",				"output directory",										true,	OutputOption),
	FOptionInfo("",		"--name=",					"compiled program name",								true,	ProgramNameOption),
	FOptionInfo("-O",	"",							"optimization level [0 - 2]",							true,	OptimizationLevelOption),
	FOptionInfo("-W",	"",							"warning level [0 - 3]",								true,	WarningLevelOption),
	FOptionInfo("",		"--code_type=",				"code generation type [ReduceC, LLVM]",					true,	CodeGenerationTypeOption),
	FOptionInfo("",		"--subsystem=",				"type of subsystem [Console, Window]",					true,	SubsystemTypeOption),
	FOptionInfo("",		"--platform=",				"[Undefined, Windows, Linux]",							true,	TargetPlatformOption),
	FOptionInfo("",		"--arch=",					"[x86, x86_64, ARM, ARM_64]",							true,	TargetArchOption),
	FOptionInfo("-e",	"--entry=",					"entry point name",										true,	EntryPointOption),
	FOptionInfo("-L",	"--libpath=",				"add libs searching dir",								true,	LibsSearchingOption),

	FOptionInfo("",		"--debug",					"include debug information",							false,	DebugOption),
	FOptionInfo("",		"--DLL",					"output result will be in dll",							false,	DLLOption),
	FOptionInfo("",		"--w2e",					"warnings to errors",									false,	WarningToErrorsOption),
	FOptionInfo("",		"--no_builtin",				"no builtin content",									false,	NoBuiltinOption), 
	FOptionInfo("",		"--freestanding",			"generate freestanding code",							false,	FreestandingOption),
	FOptionInfo("",		"--no_stack_protector",		"disable stack protection",								false,	NoStackProtectionOption),
	FOptionInfo("",		"--no_red_zone",			"disable red zones",									false,	NoRedZonesOption),

	FOptionInfo("",		"--no_translate",			"do not translate the generated code",					false,	NoTranslationOption),
	FOptionInfo("",		"--dump_lexeme",			"dump lexemes to file",									false,	DumpLexemeOption),
	FOptionInfo("",		"--dump_modules",			"dump modules dependencies to file",					false,	DumpModulesOption),
	FOptionInfo("",		"--dump_c",					"dump generated code to file",							false,	DumpCOption), 
	FOptionInfo("-S",	"--dump_asm",				"dump assembler to file",								false,	DumpASMOption),
	FOptionInfo("-c",	"",							"no linking, only compile",								false,	NoLinkingOption),

	FOptionInfo("-q",	"--quiet",					"no compiler messages",									false,	QuietOption),
	FOptionInfo("",		"--no_context",				"no context string with errors",						false,	NoContextOption),
	FOptionInfo("",		"--progress",				"show compilation progress",							false,	ShowProgressOption), 
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
	FCompilerHelperLibrary::GetAllFilesWithExtensionsInFolder(Argument, {"o", "obj"}, LPackegeFilesInfo);

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

OPTION_FUNCTION(CodeGenerationTypeOption)
{
	if( Argument == "ReduceC" )
	{
		OutCompileOptions.CodeGenerationType = ECodeGenerationType::ReduceC;
	}
	else if( Argument == "LLVM" )
	{
		OutCompileOptions.CodeGenerationType = ECodeGenerationType::LLVM;
	}
	else
	{
		FCompileLogger::MessageError("Invalid code generation type: " + Argument);
		exit(0);
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
	if( Argument == "x86" )
	{
		OutCompileOptions.TargetArch = ETargetArch::x86;
	}
	else if( Argument == "x86_64" )
	{
		OutCompileOptions.TargetArch = ETargetArch::x86_64;
	}
	else if( Argument == "ARM" )
	{
		OutCompileOptions.TargetArch = ETargetArch::arm;
	}
	else if( Argument == "ARM_64" )
	{
		OutCompileOptions.TargetArch = ETargetArch::arm_64;
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

OPTION_FUNCTION(DLLOption)
{
	OutCompileOptions.IsDLL = true;
}

OPTION_FUNCTION(WarningToErrorsOption)
{
	OutCompileOptions.ConvertWarningsToErrors = true;
}

OPTION_FUNCTION(NoBuiltinOption)
{
	OutCompileOptions.NoBuiltin = true;
}

OPTION_FUNCTION(FreestandingOption)
{
	OutCompileOptions.Freestanding = true;
}

OPTION_FUNCTION(NoStackProtectionOption)
{
	OutCompileOptions.NoStackProtection = true;
}

OPTION_FUNCTION(NoRedZonesOption)
{
	OutCompileOptions.NoRedZone = true;
}

OPTION_FUNCTION(NoTranslationOption)
{
	OutCompileOptions.NoTranslation = true;
}

OPTION_FUNCTION(DumpLexemeOption)
{
	OutCompileOptions.DumpLexemes = true;
}

OPTION_FUNCTION(DumpModulesOption)
{
	OutCompileOptions.DumpModuleDependencies = true;
}

OPTION_FUNCTION(DumpCOption)
{
	OutCompileOptions.DumpGeneratedCode = true;
}

OPTION_FUNCTION(DumpASMOption)
{
	OutCompileOptions.DumpAssembly = true;
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




// clang-format off
void ParseInputOptions
(
	int argc, char** argv, FCompileOptions& OutCompileOptions, 
	std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths
)
// clang-format on
{
	for( int i = 0; i < argc; ++i )
	{
		if( argv[i][0] != '-' )
		{
			const FGamlFileInfo LFileInfo = FCompilerHelperLibrary::SplitFilePath(argv[i]);

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