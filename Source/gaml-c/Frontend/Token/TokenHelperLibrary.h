// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"




/*
	Helper library for tokens char/string operations.
	Operate only with char/string. For token types see ParserHelperLibrary.
	@see ETokenType. @FParserHelperLibrary.
*/
struct FTokenHelperLibrary
{
	/*
		Chech that c is whitespace or special not visible symbol.
	*/
	static inline bool IsWhitespace(const char c) noexcept
	{
		// clang-format off
		return  (' ' == c) || ('\n' == c) ||
				('\r' == c) || ('\t' == c) ||
				('\b' == c) || ('\v' == c) ||
				('\f' == c);
		// clang-format on
	}

	/*
		Chech that c is single-symbol operator.
	*/
	static inline bool IsOperatorChar(const char c) noexcept
	{
		// clang-format off
		return  ('+' == c) || ('-' == c) ||
				('*' == c) || ('/' == c) ||
				('^' == c) || ('~' == c) ||
				('<' == c) || ('>' == c) ||
				('=' == c) || ('!' == c) ||
				(',' == c) || ('.' == c) ||
				('(' == c) || (')' == c) ||
				('[' == c) || (']' == c) ||
				('{' == c) || ('}' == c) ||
				('%' == c) || (':' == c) ||
				('?' == c) || ('&' == c) ||
				('|' == c) || (';' == c) || 
				('@' == c) || ('#' == c) || ('$' == c);
		// clang-format on
	}

	/*
		Check that c is letter.
	*/
	static inline bool IsLetter(const char c) noexcept { return (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')); }
	/*
		Check that c is digit.
	*/
	static inline bool IsDigit(const char c) noexcept { return ('0' <= c) && (c <= '9'); }
	/*
		Check that c is letter or digit.
	*/
	static inline bool IsLetterOrDigit(const char c) noexcept { return IsLetter(c) || IsDigit(c); }

	/*
		Check that c is left bracket like '(' or '[' ...
	*/
	static inline bool IsLeftBracket(const char c) noexcept { return ('(' == c) || ('[' == c) || ('{' == c); }
	/*
		Check that c is right bracket like ')' or ']' ...
	*/
	static inline bool IsRightBracket(const char c) noexcept { return (')' == c) || (']' == c) || ('}' == c); }
	/*
		Check that c is any single-symbol bracket.
	*/
	static inline bool IsBracket(const char c) noexcept { return IsLeftBracket(c) || IsRightBracket(c); }

	/*
		Check that c is sign.
	*/
	static inline bool IsSign(const char c) noexcept { return ('+' == c) || ('-' == c); }

	/*
		Check that c is symbol which separate tokens.
	*/
	static inline bool IsSeparateSymbol(const char c) noexcept { return IsWhitespace(c) || IsOperatorChar(c); }



	/*
		Check that c1 and c2 are two-symbols operator. 
	*/
	static inline bool IsComplex(const char c1, const char c2) noexcept
	{
		// clang-format off
		switch( c1 )
		{
		case '<': return c2 == '=' || c2 == '<' || c2 == '|';
		case '>': return c2 == '=' || c2 == '>';
		case '=': return c2 == '=' || c2 == '>';
		case '!': return c2 == '=';
		case '&': return c2 == '&' || c2 == '=';
		case '|': return c2 == '|' || c2 == '>' || c2 == '=';
		case '+': return c2 == '+' || c2 == '=';
		case '-': return c2 == '-' || c2 == '>' || c2 == '=';
		case '^': return c2 == '^' || c2 == '=';
		case ':': return c2 == ':';
		case '*': return c2 == '=' || c2 == '/';
		case '/': return c2 == '=' || c2 == '/' || c2 == '*';
		case '%': return c2 == '=';
		case '~': return c2 == '>' || c2 == '=';
		}
		// clang-format on

		return false;
	}
	/*
		Check that c1, c2, c3 are three-symbols operator. 
	*/
	static inline bool IsComplex(const char c1, const char c2, const char c3) noexcept
	{
		// clang-format off
		switch( c1 )
		{
		case '^': return (c2 == '^' && c3 == '=');
		case '<': return (c2 == '<' && c3 == '=');
		case '>': return (c2 == '>' && c3 == '=');
		case '.': return (c2 == '.' && c3 == '.');
		case '*': return (c2 == '*' && c3 == '*');
		}
		// clang-format on

		return false;
	}
	/*
		Check that c1, c2 are potential two-symbols or three-symbols operator. 
	*/
	static inline bool IsPotentialComplex(const char c1, const char c2) noexcept
	{
		return IsComplex(c1, c2) || IsComplex(c1, c2, '=') || IsComplex(c1, c2, '.') || IsComplex(c1, c2, '*');
	}
	/*
		Check that s is complex token operator.
	*/
	static inline bool IsComplexToken(const std::string& s) noexcept
	{
		return (s.size() == 2 && IsComplex(s[0], s[1])) || (s.size() == 3 && IsComplex(s[0], s[1], s[2]));
	}



	/*
		Check that c is incorrect char.
	*/
	static inline bool IsInvalidChar(const char c) noexcept
	{
		// clang-format off
		return  !IsWhitespace(c)	&&
				!IsOperatorChar(c)	&&
				!IsLetter(c)		&&
				!IsDigit(c)			&&
				!IsBracket(c)		&&
				!IsSign(c)			&&
				(c != '_')			&&
				(c != '"')			&&
				(c != '\'');
		// clang-format on
	}
	/*
		Check that identifier is named correctly.
	*/
	static inline bool IsCorrectIdentifier(const std::string& s) noexcept
	{
		if( s.empty() || (!IsLetter(s[0]) && s[0] != '_') ) return false;

		for( const char c : s )
		{
			if( !IsLetter(c) && !IsDigit(c) && c != '_' )
			{
				return false;
			}
		}

		return true;
	}



	/*
		Check that Lexeme is wrapped by '"'.

		@param Lexeme - Lexeme str to check.
	*/
	static inline bool IsStringLexeme(const std::string& Lexeme) noexcept { return Lexeme.size() >= 2 && Lexeme.front() == '"' && Lexeme.back() == '"'; }

	/*
		Check that Lexeme is wrapped by '\''.

		@param Lexeme - Lexeme str to check.
	*/
	static inline bool IsCharLexeme(const std::string& Lexeme) noexcept { return Lexeme.size() >= 2 && Lexeme.front() == '\'' && Lexeme.back() == '\''; }

	/*
		Check that Lexeme is integer.

		@param Lexeme - Lexeme str to check.
	*/
	static bool IsIntegerLexeme(const std::string& Lexeme) noexcept;

	/*
		Check that Lexeme is double.

		@param Lexeme - Lexeme str to check.
	*/
	static bool IsDoubleLexeme(const std::string& Lexeme) noexcept;

	/*
		Check that Lexeme is float.

		@param Lexeme - Lexeme str to check.
	*/
	static bool IsFloatLexeme(const std::string& Lexeme) noexcept;
};