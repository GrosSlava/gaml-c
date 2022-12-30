// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Token/Token.h"

#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"

#include "../Logger/ErrorLogger.h"




/*
	Main object for extracting tokens from the source code.
	@see Token.
*/
class Lexer final
{
public:

	inline Lexer() { }



public:

	/*
		Start transform source code into lexemes.

		@param Code - Source code str.
		@param FileInfo - original file info.
		@param CompileOptions - Current compiling options.
		@param OutTokens - Extracted tokens result.
	*/
	void Process(const std::string& Code, const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, std::vector<Token>& OutTokens);

	/*
		Raise error based on lexer context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType) const
	{
		FErrorLogger::Raise(ErrorMessageType, CurrentFileInfo.GetFileFullPath(), CurrentLine, CurrentPos - 1, 0, CurrentCompileOptions);
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
		Cached compiler options.
	*/
	FCompileOptions CurrentCompileOptions;

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