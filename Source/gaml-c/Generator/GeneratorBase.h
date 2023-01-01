// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "GeneratorHelperLibrary.h"

#include "../Platform/PlatformHelperLibrary.h"
#include "../Platform/GenericPlatform.h"

#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"
#include "../Compiler/CompilerConfig.h"
#include "../Compiler/CompilerHelperLibrary.h"

#include "../Parser/ProgramSymbols.h"
#include "../Logger/ErrorLogger.h"




/*
	Base class for code generators.
	Generators should generate code based only on given information in ProgramInfo.
	All optimizations and platform specifics are produced in SemanticAnalyser or in third party compiler.

	@see FProgramInfo.
*/
class BaseGenerator
{
public:

	inline BaseGenerator() { }
	virtual ~BaseGenerator() { }



public:

	// clang-format off
	/*
		Translate code to object file.

		@param FileInfo - original file info.
		@param CompileOptions - Current compile options.
		@param ProgramInfo - Program abstract view.
		@param OutCompiledObjectFilePath - Result path to generated object file.
		@return success.
	*/
	virtual bool GenerateCode
	(
		const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, const FProgramInfo& ProgramInfo, 
		std::string& OutCompiledObjectFilePath
	);
	// clang-format on

protected:

	/*
		@return low-level language extension.
	*/
	virtual std::string GetOutFileExtension() const { return ""; }
	/*
		Translate code to other language.
	*/
	virtual void ProcessGeneration(std::string& GeneratedCodeStr, const FProgramInfo& ProgramInfo) { }

protected:

	/*
		Raise error based on compiler context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType, size_t Line, size_t Pos, size_t UnderlineLength) const
	{
		FErrorLogger::Raise(ErrorMessageType, CurrentFileInfo.GetFileFullPath(), Line, Pos, UnderlineLength, CurrentCompileOptions);
	}


	/*
		@return path to output folder.
	*/
	inline std::string GetOutputDirectoryPath() const noexcept
	{
		return CurrentCompileOptions.OutputDir.empty() ? CurrentFileInfo.PathToFileOnly : CurrentCompileOptions.OutputDir;
	}
	/*
		@param ExtensionOnlyStr - file extension wihout '.'
		@return path to output file with specific extension.
	*/
	inline std::string GetOutputFilePath(const std::string& ExtensionOnlyStr) const noexcept
	{
		return FCompilerHelperLibrary::CatPaths(GetOutputDirectoryPath(), CurrentFileInfo.FileNameOnly + "." + ExtensionOnlyStr);
	}




protected:

	/*
		Info of file from which we take tokens.
	*/
	FGamlFileInfo CurrentFileInfo;
	/*
		Cached compiler options.
	*/
	FCompileOptions CurrentCompileOptions;
};