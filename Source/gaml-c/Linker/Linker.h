// Copyright 2022 GrosSlava.

#pragma once

#include "../Compiler/CompilerOptions.h"
#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerHelperLibrary.h"
#include "../Logger/ErrorLogger.h"

#include <vector>
#include <string>




/*
	Object for linking compiled object files.
*/
class Linker final
{
public:

	inline Linker() { }



public:

	void Process(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths, const FCompileOptions& Options);

	inline void RaiseError(EErrorMessageType ErrorMessageType, const std::string& ObjectFilePath) const 
	{ 
		FErrorLogger::Raise(ErrorMessageType, ObjectFilePath, 0, 0, CurrentCompileOptions); 
	}

protected:

	void RunThirdPartyLinker(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths);


	inline std::string GetOutputDirectoryPath() const
	{
		if( CurrentCompileOptions.OutputDir.empty() )
		{
			return FirstFileInfo.PathToFileOnly;
		}

		return CurrentCompileOptions.OutputDir;
	}

	inline std::string GetOutputFilePath(const std::string& Extension) const
	{
		std::string LProgramName = "";
		if( CurrentCompileOptions.ProgramName.empty() )
		{
			LProgramName = FirstFileInfo.FileNameOnly;
		}
		else
		{
			LProgramName = CurrentCompileOptions.ProgramName;
		}

		return FCompilerHelperLibrary::CatPaths(GetOutputDirectoryPath(), LProgramName + "." + Extension);
	}



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