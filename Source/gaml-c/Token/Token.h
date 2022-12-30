// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "TokenType.h"

#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"




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

	/*
		@return token type in str.
	*/
	std::string GetTypeAsStr() const noexcept;
	/*
		@return token type.
	*/
	inline ETokenType GetType() const noexcept { return Type; }
	/*
		@return original lexeme str.
	*/
	inline const std::string& GetLexeme() const noexcept { return LexemeStr; }
	/*
		@return information about token's file.
	*/
	inline const FGamlFileInfo& GetFileInfo() const noexcept { return FileInfo; }
	/*
		@return token line index in file.
	*/
	inline size_t GetLine() const noexcept { return Line; }
	/*
		@return token position in line.
	*/
	inline size_t GetPos() const noexcept { return Pos; }
	/*
		@return hash from current lexeme str.
	*/
	inline size_t GetHash() const noexcept { return std::hash<std::string> {}(LexemeStr); }

private:

	/*
		Set Type based on LexemeStr.

		@param CompileOptions - Compile options to use in errors.
	*/
	void DetermineTokenType(const FCompileOptions& CompileOptions);




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
		Token start position in text file line.
	*/
	size_t Pos = 0;
};