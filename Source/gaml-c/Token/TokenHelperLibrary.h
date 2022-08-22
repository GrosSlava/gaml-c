// Copyright 2022 GrosSlava.

#pragma once

#include <string>




/*
	Helper library for tokens char/string operations.
	@see ETokenType.
*/
struct FTokenHelperLibrary
{
public:
	
	static inline bool IsWhitespace(const char c) noexcept
	{
		return  (' ' == c) || ('\n' == c) ||
				('\r' == c) || ('\t' == c) ||
				('\b' == c) || ('\v' == c) ||
				('\f' == c);
	}

	static inline bool IsOperatorChar(const char c) noexcept
	{
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
				('|' == c) || (';' == c);
	}
	
	static inline bool IsComplex(const char c1, const char c2) noexcept
	{
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

		return false;
	}

	static inline bool IsComplex(const char c1, const char c2, const char c3) noexcept
	{
		switch( c1 )
		{
		case '^': return (c2 == '^' && c3 == '=');
		case '<': return (c2 == '<' && c3 == '=');
		case '>': return (c2 == '>' && c3 == '=');
		case '.': return (c2 == '.' && c3 == '.');
		}

		return false;
	}

	static inline bool IsComplexToken(const std::string& s) noexcept
	{
		return (s.size() == 2 && IsComplex(s[0], s[1])) || (s.size() == 3 && IsComplex(s[0], s[1], s[2]));
	}

	static inline bool IsSeparateSymbol(char c) noexcept
	{
		return IsWhitespace(c) || IsOperatorChar(c);
	}

	static inline bool IsLetter(const char c) noexcept
	{
		return (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z'));
	}

	static inline bool IsDigit(const char c) noexcept
	{
		return ('0' <= c) && (c <= '9');
	}

	static inline bool IsLetterOrDigit(const char c) noexcept
	{
		return IsLetter(c) || IsDigit(c);
	}

	static inline bool IsLeftBracket(const char c) noexcept
	{
		return ('(' == c) || ('[' == c) || ('{' == c);
	}

	static inline bool IsRightBracket(const char c) noexcept
	{
		return (')' == c) || (']' == c) || ('}' == c);
	}

	static inline bool IsBracket(const char c) noexcept
	{
		return IsLeftBracket(c) || IsRightBracket(c);
	}

	static inline bool IsSign(const char c) noexcept
	{
		return ('+' == c) || ('-' == c);
	}
	


	static inline bool IsInvalidChar(const char c) noexcept
	{
		return  !IsWhitespace(c)	&&
				!IsOperatorChar(c)	&&
				!IsLetter(c)		&&
				!IsDigit(c)			&&
				!IsBracket(c)		&&
				!IsSign(c)			&&
				(c != '_')			&&
				(c != '$')			&&
				(c != '#')			&&
				(c != '"')			&&
				(c != '\'');
	}

	static inline bool IsCorrectIdentifier(const std::string& s) noexcept
	{
		if( !IsLetter(s[0]) && s[0] != '_' ) return false;

		for( const char& c : s )
		{
			if( !IsLetter(c) && !IsDigit(c) && c != '_' )
			{
				return false;
			}
		}

		return true;
	}
};