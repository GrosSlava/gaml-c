// Copyright 2022 GrosSlava.

#pragma once

#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"
#include "../Compiler/CompilerConfig.h"
#include "../Compiler/CompilerHelperLibrary.h"
#include "GeneratorHelperLibrary.h"
#include "../Parser/ProgramSymbols.h"
#include "../Logger/ErrorLogger.h"

#include <string>
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

	virtual bool GenerateCode(const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, const FProgramInfo& ProgramInfo, std::string& OutCompiledObjectFilePath)
	{
		CurrentFileInfo = FileInfo;
		CurrentCompileOptions = CompileOptions;
		GeneratedCodeStr.clear();

		OutCompiledObjectFilePath.clear(); 

		const std::string LOutFilePath = GetOutputFilePath(GetOutFileExtension());
		if( LOutFilePath.empty() ) return false;

		std::ofstream LFile(LOutFilePath);
		if( !LFile.is_open() )
		{
			FCompileLogger::Raise(EErrorStage::INITIALIZATION, EErrorType::ERROR, FileInfo.FileNameOnly, "Can't create file '" + LOutFilePath + "'!", 0, 0);
			return false;
		}


		ProcessGeneration(ProgramInfo);
		LFile.write(GeneratedCodeStr.c_str(), GeneratedCodeStr.size());
		LFile.close();

		if( !CurrentCompileOptions.NoTranslation )
		{
			RunThirdPartyCompiler(LOutFilePath, OutCompiledObjectFilePath);
		}
		
		if( !CurrentCompileOptions.DumpGeneratedCode )
		{
			std::remove(LOutFilePath.c_str());
		}

		return true;
	}

protected:

	virtual std::string GetOutFileExtension() const { return ""; }
	virtual void ProcessGeneration(const FProgramInfo& ProgramInfo) { }
	virtual int RunThirdPartyCompiler(const std::string& FilePath, std::string& OutCompiledObjectFilePath) { return 0; }

	inline std::string GetOutputDirectoryPath() const
	{
		if( CurrentCompileOptions.OutputDir.empty() )
		{
			return CurrentFileInfo.PathToFileOnly;
		}

		return CurrentCompileOptions.OutputDir;
	}

	inline std::string GetOutputFilePath(const std::string& ExtensionOnlyStr) const
	{
		return FCompilerHelperLibrary::CatPaths(GetOutputDirectoryPath(), CurrentFileInfo.FileNameOnly + "." + ExtensionOnlyStr);
	}

	inline std::string GetCompilerIdentifier() const
	{
		return std::string(FCompilerConfig::COMPILER_NAME) + " v" + std::string(FCompilerConfig::COMPILER_VERSION);
	}

	inline void RaiseError(EErrorMessageType ErrorMessageType, size_t Line, size_t Pos) const 
	{ 
		FErrorLogger::Raise(ErrorMessageType, CurrentFileInfo.GetFileFullPath(), Line, Pos, CurrentCompileOptions); 
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