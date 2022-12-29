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

#include <fstream>




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
	)
	// clang-format on
	{
		// set context
		CurrentFileInfo = FileInfo;
		CurrentCompileOptions = CompileOptions;
		GeneratedCodeStr.clear();

		OutCompiledObjectFilePath.clear();


		// generate code for low-level language
		ProcessGeneration(ProgramInfo);


		// create other language file
		const std::string LOutFilePath = GetOutputFilePath(GetOutFileExtension());
		if( LOutFilePath.empty() ) return false;

		std::ofstream LFile(LOutFilePath);
		if( !LFile.is_open() )
		{
			FCompileLogger::Raise(EErrorStage::INITIALIZATION, EErrorType::ERROR, FileInfo.FileNameOnly, "Can't create file '" + LOutFilePath + "'!", 0, 0);
			return false;
		}

		LFile.write(GeneratedCodeStr.c_str(), GeneratedCodeStr.size());
		LFile.close();


		// compile generated code by native compiler
		if( !CurrentCompileOptions.NoTranslation )
		{
			const std::string LFileExtension = FPlatformHelperLibrary::GetPlatformObjectFileExtension(CurrentCompileOptions.TargetPlatform);
			if( LFileExtension.empty() )
			{
				RaiseError(EErrorMessageType::INVALID_GENERATION_EXTENSION, 0, 0, 0);
				return false;
			}

			OutCompiledObjectFilePath = GetOutputFilePath(LFileExtension);
			FGenericPlatform::RunThirdPartyCompiler(CurrentFileInfo, CurrentCompileOptions, LOutFilePath, GetOutputDirectoryPath(), OutCompiledObjectFilePath);
		}

		// remove generated low-level code if needed
		if( !CurrentCompileOptions.DumpGeneratedCode )
		{
			std::remove(LOutFilePath.c_str());
		}

		return true;
	}

protected:

	/*
		@return low-level language extension.
	*/
	virtual std::string GetOutFileExtension() const { return ""; }
	/*
		Translate code to other language.
	*/
	virtual void ProcessGeneration(const FProgramInfo& ProgramInfo) { }

protected:

	/*
		@return path to output folder.
	*/
	inline std::string GetOutputDirectoryPath() const noexcept
	{
		if( CurrentCompileOptions.OutputDir.empty() )
		{
			return CurrentFileInfo.PathToFileOnly;
		}

		return CurrentCompileOptions.OutputDir;
	}
	/*
		@param ExtensionOnlyStr - file extension wihout '.'
		@return path to output file with specific extension.
	*/
	inline std::string GetOutputFilePath(const std::string& ExtensionOnlyStr) const noexcept
	{
		return FCompilerHelperLibrary::CatPaths(GetOutputDirectoryPath(), CurrentFileInfo.FileNameOnly + "." + ExtensionOnlyStr);
	}


	/*
		Raise error based on compiler context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType, size_t Line, size_t Pos, size_t UnderlineLength) const
	{
		FErrorLogger::Raise(ErrorMessageType, CurrentFileInfo.GetFileFullPath(), Line, Pos, UnderlineLength, CurrentCompileOptions);
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
	/*
		Result of generating the code to write to the file.
	*/
	std::string GeneratedCodeStr = "";
};