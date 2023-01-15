// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "GamlFileInfo.h"
#include "CompilerOptions.h"
#include "CompilerHelperLibrary.h"

#include "Logger/ErrorLogger.h"




struct Token;
class BaseGenerator;
struct FProgramInfo;



/*
	Main object for compilation pipeline.
*/
struct FCompiler
{
public:

	inline FCompiler() { }



public:

	/*
		Start compilation pipeline.
	*/
	std::string Process(const std::string& FilePath, const FCompileOptions& Options);
	std::string Process(const FGamlFileInfo& InFileInfo, const FCompileOptions& Options);

private:

	/*
		@return path to result directory.
	*/
	inline std::string GetCompilerOutputDir(const std::string& FileName) const noexcept
	{
		const std::string LFilePath = CurrentOptions.OutputDir.empty() ? FileInfo.PathToFileOnly : CurrentOptions.OutputDir;
		return FCompilerHelperLibrary::CatPaths(LFilePath, FileName);
	}


	/*
		Log error based on compiler context.
	*/
	inline void LogError(EErrorStage ErrorStage, EErrorType ErrorType, const std::string& FileName, const std::string& Message, size_t Line, size_t Pos) const
	{
		if( CurrentOptions.Silent ) return;

		FCompileLogger::Raise(ErrorStage, ErrorType, FileName, Message, Line, Pos);
	}

private:

	//.....................Translation pipeline.....................//

	bool Open(std::string& OutCode);
	bool ProcessLexer(const std::string& Code, std::vector<Token>& OutTokens);
	bool ProcessParser(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo);
	bool ProcessSemantic(FProgramInfo& ProgramInfo);
	bool GenerateCode(const FProgramInfo& ProgramInfo, std::string& OutCompiledObjectFilePath);

	//..............................................................//


	/*
		Save translation unit lexemes into file.
	*/
	void DumpLexemes(const std::vector<Token>& Tokens);
	/*
		Save translation unit dependencies into file.
	*/
	void DumpModuleDependencies(const FProgramInfo& ProgramInfo);


	/*
		Construct code generator based on current compilation options.

		@return generated code generator.
	*/
	BaseGenerator* CreateCodeGenerator() const noexcept;




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