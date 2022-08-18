// Copyright 2022 GrosSlava.

#pragma once

#include "CompilerFileInfo.h"
#include "CompilerOptions.h"
#include "CompilerHelperLibrary.h"
#include "../Token/Token.h"
#include "../Parser/ProgramSymbols.h"
#include "../Logger/ErrorLogger.h"
#include "../Generator/GeneratorBase.h"

#include <string>
#include <vector>




/*
	Main class for compilation pipeline.
*/
class Compiler final
{
public:

	inline Compiler() { }



public:

	std::string Process(const std::string& FilePath, const FCompileOptions& Options);
	std::string Process(const FGamlFileInfo& InFileInfo, const FCompileOptions& Options);
	
	
	inline void LogError(EErrorStage ErrorStage, EErrorType ErrorType, const std::string& FileName, const std::string& Message, size_t Line, size_t Pos) const
	{
		if( CurrentOptions.Silent ) return;

		FCompileLogger::Raise(ErrorStage, ErrorType, FileName, Message, Line, Pos);
	}

	inline std::string GetCompilerOutputDir(const std::string& FileName) const
	{
		std::string LFilePath = "";
		if( CurrentOptions.OutputDir.empty() )
		{
			LFilePath = FileInfo.PathToFileOnly;
		}
		else
		{
			LFilePath = CurrentOptions.OutputDir;
		}

		return FCompilerHelperLibrary::CatPaths(LFilePath, FileName);
	}

private:

	bool Open(std::string& OutCode);
	bool ProcessLexer(const std::string& Code, std::vector<Token>& OutTokens);
	bool ProcessParser(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo);
	bool ProcessSemantic(FProgramInfo& ProgramInfo);
	bool GenerateCode(const FProgramInfo& ProgramInfo, std::string& OutCompiledObjectFilePath);


	void DumpLexemes(const std::vector<Token>& Tokens);
	void DumpModuleDependencies(const FProgramInfo& ProgramInfo);


	BaseGenerator* CreateCodeGenerator() const;



private:

	/*
		Information about compiling file.
	*/
	FGamlFileInfo FileInfo;

	/*
		Cached compiler options.
	*/
	FCompileOptions CurrentOptions;
};