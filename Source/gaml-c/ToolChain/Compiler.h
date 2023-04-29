// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CoreObjects.h"
#include "GamlFileInfo.h"
#include "CompilerHelperLibrary.h"

#include "Logger/ErrorLogger.h"




struct Token;
class BaseGenerator;

struct FProgramInfo;
struct FIRInfo;



/**
	Main object for compilation pipeline.
*/
struct FCompiler
{
public:

	inline FCompiler() { }



public:

	/**
		Start compilation pipeline.
	*/
	inline std::string Process(const std::string& FilePath) { return Process(FGamlFileInfo(FilePath)); }
	std::string Process(const FGamlFileInfo& InFileInfo);

private:

	/**
		@return path to result directory.
	*/
	inline std::string GetCompilerOutputDir(const std::string& FileName) const noexcept
	{
		const std::string LFilePath = FCoreObjects::CompileOptions.OutputDir.empty() ? FileInfo.PathToFileOnly : FCoreObjects::CompileOptions.OutputDir;
		return FCompilerHelperLibrary::CatPaths(LFilePath, FileName);
	}


	/**
		Log error based on compiler context.
	*/
	inline void LogError(EErrorType ErrorType, const std::string& FileName, const std::string& Message, size_t Line, size_t Pos) const
	{
		if( FCoreObjects::CompileOptions.Silent ) return;

		FCompileLogger::Raise(ErrorType, FileName, Message, Line, Pos);
	}

private:

	//.....................Translation pipeline.....................//

	bool Open(std::string& OutCode);
	bool ProcessLexer(const std::string& Code, std::vector<Token>& OutTokens);
	bool ProcessParser(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo);
	bool ProcessSemantic(FProgramInfo& ProgramInfo);
	bool ProcessIR(FProgramInfo& ProgramInfo, FIRInfo& OutIR);
	bool GenerateCode(const FIRInfo& IRInfo, std::string& OutCompiledObjectFilePath);

	//..............................................................//


	/**
		Save translation unit lexemes into file.
	*/
	void DumpLexemes(const std::vector<Token>& Tokens);
	/**
		Save translation unit AST into file.
	*/
	void DumpAST(const FProgramInfo& ProgramInfo);
	/**
		Save translation unit dependencies into file.
	*/
	void DumpModuleDependencies(const FProgramInfo& ProgramInfo);
	/**
		Save translation unit IR into file.
	*/
	void DumpIR(const FIRInfo& IRInfo);




private:

	/*
		Information about compiling file.
	*/
	FGamlFileInfo FileInfo;
};