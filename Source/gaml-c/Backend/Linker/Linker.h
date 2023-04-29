// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CoreObjects.h"
#include "GamlFileInfo.h"
#include "CompilerHelperLibrary.h"

#include "Logger/ErrorLogger.h"




/**
	Object for linking compiled object files.
*/
struct FLinker
{
public:

	inline FLinker() { }



public:

	/**
		Start linking.

		@param ObjectFilesPaths - Array of object files to link.
		@param LibsFilesPaths - Array of paths to libraries.
	*/
	void Process(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths);

private:

	/**
		@return path to result directory.
	*/
	inline std::string GetOutputDirectoryPath() const noexcept
	{
		return FCoreObjects::CompileOptions.OutputDir.empty() ? FirstFileInfo.PathToFileOnly : FCoreObjects::CompileOptions.OutputDir;
	}
	/**
		@return path to resulting file.
	*/
	inline std::string GetOutputFilePath(const std::string& Extension) const noexcept
	{
		// clang-format off
		const std::string LProgramName =	FCoreObjects::CompileOptions.ProgramName.empty() ? 
											FirstFileInfo.FileNameOnly : FCoreObjects::CompileOptions.ProgramName;
		// clang-format on
		return FCompilerHelperLibrary::CatPaths(GetOutputDirectoryPath(), LProgramName + "." + Extension);
	}


	/**
		Raise error based on linker context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType, const std::string& ObjectFilePath) const
	{
		FErrorLogger::Raise(ErrorMessageType, ObjectFilePath, 0, 0, 0);
	}

private:

	/**
		Run platform specific linker.
	*/
	void RunThirdPartyLinker(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths);




private:

	/**
		Cached name of first passed file.
	*/
	FGamlFileInfo FirstFileInfo;
};