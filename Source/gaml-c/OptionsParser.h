// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"




struct FCompileOptions;
struct FGamlFileInfo;



/*
	Option handler signature.
*/
using OptionHandlerSign = void (*)(const std::string&, FCompileOptions&, std::vector<FGamlFileInfo>&, std::vector<std::string>&, std::vector<std::string>&);

/*
	Helper struct for handling option info.
*/
struct FOptionInfo
{
public:

	FOptionInfo() = delete;

	// clang-format off
	FOptionInfo
	(
		const std::string& InShortOption, const std::string& InLongOption, const std::string& InDescription, bool InHasArgument,
		OptionHandlerSign InFunction
	) :
		ShortOption(InShortOption), LongOption(InLongOption), Description(InDescription), HasArgument(InHasArgument), Function(InFunction)
	// clang-format on
	{
	}



public:

	// clang-format off
	bool Process
	(
		const std::string& OptionStr, FCompileOptions& OutCompileOptions, 
		std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths
	) const;
	// clang-format on

	/*
		@return option help str.
	*/
	inline std::string GetHelpStr() const noexcept
	{
		return ShortOption + std::string(4 - ShortOption.size(), ' ') + LongOption + std::string(25 - LongOption.size(), ' ') + " --- " + Description;
	}




private:

	/*
		Option short version key.
	*/
	std::string ShortOption = "";
	/*
		Option long version key.
	*/
	std::string LongOption = "";
	/*
		Option help description.
	*/
	std::string Description = "";
	/*
		Can have argument after option or not.
	*/
	bool HasArgument = false;
	/*
		Option handler.
	*/
	OptionHandlerSign Function = nullptr;
};




//................................................Handlers..........................................................//

#define OPTION_FUNCTION(Name)                                                                                                  \
	void Name(const std::string& Argument, FCompileOptions& OutCompileOptions, std::vector<FGamlFileInfo>& OutSourceFilePaths, \
		std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths)

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
OPTION_FUNCTION(NoReflectionOption);
OPTION_FUNCTION(FreestandingOption);
OPTION_FUNCTION(NoStackProtectionOption);
OPTION_FUNCTION(NoRedZonesOption);
OPTION_FUNCTION(NoTranslationOption);
OPTION_FUNCTION(DumpLexemeOption);
OPTION_FUNCTION(DumpASTOption);
OPTION_FUNCTION(DumpModulesOption);
OPTION_FUNCTION(DumpIROption);
OPTION_FUNCTION(DumpCOption);
OPTION_FUNCTION(DumpASMOption);
OPTION_FUNCTION(NoLinkingOption);
OPTION_FUNCTION(QuietOption);
OPTION_FUNCTION(NoContextOption);
OPTION_FUNCTION(ShowProgressOption);
OPTION_FUNCTION(ShowCompileTimeOption);

//..................................................................................................................//




// clang-format off
/*
	Main function for parsing program input line.

	@param argc - Count of options.
	@param argv - Array of C-strings.
	@param OutCompileOptions - Filled compile options.
	@param OutSourceFilePaths - Resulting array of files to compile.
	@param OutObjectFiles - Resulting array of additional object files for linking.
	@param OutLibsFilesPaths - Resulting array of additional libraries for linking.
*/
void ParseInputOptions
(
	int argc, char** argv, FCompileOptions& OutCompileOptions, 
	std::vector<FGamlFileInfo>& OutSourceFilePaths, std::vector<std::string>& OutObjectFiles, std::vector<std::string>& OutLibsFilesPaths
);
// clang-format on