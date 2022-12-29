// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "ProgramSymbols.h"
#include "../Token/Token.h"

#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"

#include "../Logger/ErrorLogger.h"




/*
	Main object for checking syntax and generating AST.
	@see Token.
*/
class Parser final
{
public:

	inline Parser() { }



public:

	// clang-format off
	/*
		Start parse.

		@param Tokens - array of tokens to parse.
		@param FileInfo - original file info.
		@param CompileOptions - Current compiling options.
		@param InIsMainModule - Indicate that we parsing main module or importing.
		@param OutProgramInfo - result of parsing.
	*/
	void Process
	(
		const std::vector<Token>& Tokens, const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, bool InIsMainModule,
		FProgramInfo& OutProgramInfo
	);
	// clang-format on

	/*
		Raise error based on parser context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType, const Token& Token) const
	{
		// clang-format off
		FErrorLogger::Raise
		(
			ErrorMessageType, 
			CurrentFileInfo.GetFileFullPath(), 
			Token.GetLine(), Token.GetPos(), Token.GetLexeme().size() - 1, 
			CurrentCompileOptions
		);
		// clang-format on
	}

private:

	void CheckPairs(const std::vector<Token>& Tokens);
	void ProcessSymbolsScanning(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo);




private:

	/*
		Info of file from which we take tokens.
	*/
	FGamlFileInfo CurrentFileInfo;
	/*
		Cached compiler options.
	*/
	FCompileOptions CurrentCompileOptions;
	/*
		Is parsing main module or importing.
	*/
	bool IsMainModule = false;
};