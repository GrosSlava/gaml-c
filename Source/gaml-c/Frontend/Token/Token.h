// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "TokenType.h"
#include "GamlFileInfo.h"




/*
	Base lexeme from source code.
	@see ETokenType, FTokenHelperLibrary.
*/
struct Token
{
public:

	Token() = delete;
	inline Token(const FGamlFileInfo& InFileInfo, const std::string& InLexeme, size_t InLine, size_t InPos) :
		LexemeStr(InLexeme), FileInfo(InFileInfo), Line(InLine), Pos(InPos)
	{
		DetermineTokenType();
	}
	Token(const Token& Other) : Type(Other.Type), LexemeStr(Other.LexemeStr), FileInfo(Other.FileInfo), Line(Other.Line), Pos(Other.Pos) { }
	Token(Token&& Other) noexcept :
		Type(Other.Type), LexemeStr(std::move(Other.LexemeStr)), FileInfo(std::move(Other.FileInfo)), Line(Other.Line), Pos(Other.Pos)
	{
		Other.Type = ETokenType::IDENTIFIER;
		Other.Line = 0;
		Other.Pos = 0;
	}

public:

	Token& operator=(const Token& Other)
	{
		if( this == &Other )
		{
			return *this;
		}

		Type = Other.Type;
		LexemeStr = Other.LexemeStr;
		FileInfo = Other.FileInfo;
		Line = Other.Line;
		Pos = Other.Pos;

		return *this;
	}
	Token& operator=(Token&& Other) noexcept
	{
		Type = Other.Type;
		LexemeStr = std::move(Other.LexemeStr);
		FileInfo = std::move(Other.FileInfo);
		Line = Other.Line;
		Pos = Other.Pos;

		Other.Type = ETokenType::IDENTIFIER;
		Other.Line = 0;
		Other.Pos = 0;

		return *this;
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
	*/
	void DetermineTokenType();




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