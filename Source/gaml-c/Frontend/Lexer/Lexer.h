// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "GamlFileInfo.h"

#include "Logger/ErrorLogger.h"




struct Token;



/*
	Main object for extracting tokens from the source code.
	@see Token.
*/
struct FLexer
{
public:

	inline FLexer() { }



public:

	/*
		Start transform source code into lexemes.

		@param Code - Source code str.
		@param FileInfo - Original file info.
		@param OutTokens - Extracted tokens result.
	*/
	void Process(const std::string& Code, const FGamlFileInfo& FileInfo, std::vector<Token>& OutTokens);

private:

	/*
		Raise error based on lexer context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType) const
	{
		FErrorLogger::Raise(ErrorMessageType, CurrentFileInfo.GetFileFullPath(), CurrentLine, CurrentPos - 1, 0);
	}

private:

	//.......................Process pipeline..........................//

	void Split(const std::string& Code, std::vector<Token>& OutTokens);
	void Merge(std::vector<Token>& OutTokens);

	//.................................................................//

	/*
		Save current lexeme as token.
	*/
	void PushCurrentLexeme(std::vector<Token>& OutTokens, size_t PosBack = 0);




private:

	/*
		Info of file from which we take tokens.
	*/
	FGamlFileInfo CurrentFileInfo;

	/*
		Current token line.
	*/
	size_t CurrentLine = 1;
	/*
		Current token position in line.
	*/
	size_t CurrentPos = 1;
	/*
		Current lexeme string.
	*/
	std::string CurrentLexeme = "";
};