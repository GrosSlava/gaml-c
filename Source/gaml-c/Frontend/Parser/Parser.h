// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "ProgramSymbols.h"
#include "GamlFileInfo.h"

#include "Logger/ErrorLogger.h"




struct Token;



/*
	Main object for checking syntax and generating AST.
	@see Token.
*/
struct FParser
{
public:

	inline FParser() { }



public:

	// clang-format off
	/*
		Start parse.

		@param Tokens - Array of tokens to parse.
		@param FileInfo - Original file info.
		@param InIsMainModule - Indicate that we parsing main module or importing.
		@param OutProgramInfo - Result of parsing.
	*/
	void Process
	(
		const std::vector<Token>& Tokens, const FGamlFileInfo& FileInfo, bool InIsMainModule,
		FProgramInfo& OutProgramInfo
	);
	// clang-format on

private:

	void CheckPairs(const std::vector<Token>& Tokens);
	void ProcessSymbolsScanning(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo);




private:

	/*
		Info of file from which we take tokens.
	*/
	FGamlFileInfo CurrentFileInfo;
	/*
		Is parsing main module or importing.
	*/
	bool IsMainModule = false;
};