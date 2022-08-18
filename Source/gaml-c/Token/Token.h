// Copyright 2022 GrosSlava.

#pragma once

#include "TokenType.h"
#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"

#include <string>




/*
	Base lexeme from source code.
	@see ETokenType, FTokenHelperLibrary.
*/
class Token final
{
public:

	Token() = delete;
	inline Token(const FGamlFileInfo& InFileInfo, const std::string& InLexeme, size_t InLine, size_t InPos, const FCompileOptions& CompileOptions) : 
		LexemeStr(InLexeme), FileInfo(InFileInfo), Line(InLine), Pos(InPos)
	{
		DetermineTokenType(CompileOptions);
	}



public:

	std::string GetTypeAsStr() const noexcept;
	inline ETokenType GetType() const noexcept { return Type; }
	inline const std::string& GetLexeme() const noexcept { return LexemeStr; }
	inline const FGamlFileInfo& GetFileInfo() const noexcept { return FileInfo; }
	inline size_t GetLine() const noexcept { return Line; }
	inline size_t GetPos() const noexcept { return Pos; }

private:

	void DetermineTokenType(const FCompileOptions& CompileOptions);


	inline bool IsStringLexeme(const std::string& Lexeme) const noexcept
	{ 
		return Lexeme.size() >= 2 && Lexeme.front() == '"' && Lexeme.back() == '"'; 
	}

	inline bool IsCharLexeme(const std::string& Lexeme) const noexcept
	{ 
		return Lexeme.size() >= 2 && Lexeme.front() == '\'' && Lexeme.back() == '\''; 
	}

	bool IsIntegerLexeme(const std::string& Lexeme) const noexcept;
	bool IsDoubleLexeme(const std::string& Lexeme) const noexcept;
	bool IsFloatLexeme(const std::string& Lexeme) const noexcept;



private:

	/*
		Token type.
	*/
	ETokenType Type;
	/*
		Token value from source code.
	*/
	std::string LexemeStr = "";

	/*
		Original file info.
	*/
	FGamlFileInfo FileInfo;
	/*
		Token line index.
	*/
	size_t Line = 0;
	/*
		Token position in text file line.
	*/
	size_t Pos = 0;
};