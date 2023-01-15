// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CompilerOptions.h"
#include "GamlFileInfo.h"
#include "CompilerHelperLibrary.h"

#include "Logger/ErrorLogger.h"




/*
	Object for linking compiled object files.
*/
struct FLinker
{
public:

	inline FLinker() { }



public:

	/*
		Start linking.

		@param ObjectFilesPaths - Array of object files to link.
		@param LibsFilesPaths - Array of paths to libraries.
		@param Options - Compilation options.
	*/
	void Process(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths, const FCompileOptions& Options);

private:

	/*
		@return path to result directory.
	*/
	inline std::string GetOutputDirectoryPath() const noexcept
	{
		return CurrentCompileOptions.OutputDir.empty() ? FirstFileInfo.PathToFileOnly : CurrentCompileOptions.OutputDir;
	}
	/*
		@return path to resulting file.
	*/
	inline std::string GetOutputFilePath(const std::string& Extension) const noexcept
	{
		const std::string LProgramName = CurrentCompileOptions.ProgramName.empty() ? FirstFileInfo.FileNameOnly : CurrentCompileOptions.ProgramName;
		return FCompilerHelperLibrary::CatPaths(GetOutputDirectoryPath(), LProgramName + "." + Extension);
	}


	/*
		Raise error based on linker context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType, const std::string& ObjectFilePath) const
	{
		FErrorLogger::Raise(ErrorMessageType, ObjectFilePath, 0, 0, 0, CurrentCompileOptions);
	}

private:

	/*
		Run platform specific linker.
	*/
	void RunThirdPartyLinker(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths);




private:

	/*
		Cached compiler options.
	*/
	FCompileOptions CurrentCompileOptions;
	/*
		Cached name of first passed file.
	*/
	FGamlFileInfo FirstFileInfo;
};