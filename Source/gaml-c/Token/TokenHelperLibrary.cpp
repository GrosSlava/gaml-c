// Copyright 2022 - 2023 GrosSlava.

#include "TokenHelperLibrary.h"





bool FTokenHelperLibrary::IsIntegerLexeme(const std::string& Lexeme) noexcept
{
	bool IsHex = false;
	bool IsBinary = false;
	if( Lexeme.size() >= 2 && Lexeme[0] == '0' && (Lexeme[1] == 'x' || Lexeme[1] == 'X') )
	{
		IsHex = true;
	}
	if( !IsHex && (Lexeme.back() == 'b' || Lexeme.back() == 'B') )
	{
		IsBinary = true;
	}

	if( (IsHex && Lexeme.size() < 3) || (IsBinary && Lexeme.size() < 2) )
	{
		return false;
	}


	bool LHasFirstDigit = false;
	bool LHasX = false;
	bool LHasDigitAfterX = false;
	bool LHasB = false;
	for( const char c : Lexeme )
	{
		if( IsBinary && LHasB )
		{
			return false;
		}

		if( c == 'x' || c == 'X' )
		{
			if( !LHasFirstDigit || !IsHex || LHasX )
			{
				return false;
			}
			LHasX = true;
			continue;
		}

		if( c == 'b' || c == 'B' )
		{
			if( !LHasFirstDigit )
			{
				return false;
			}
			LHasB = true;
			continue;
		}

		if( (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') )
		{
			if( !LHasX )
			{
				return false;
			}
			LHasDigitAfterX = true;
			continue;
		}

		if( !IsDigit(c) )
		{
			return false;
		}

		LHasFirstDigit = true;
		if( LHasX )
		{
			LHasDigitAfterX = true;
		}
	}

	if( IsHex && !LHasDigitAfterX )
	{
		return false;
	}
	return LHasFirstDigit;
}

bool FTokenHelperLibrary::IsDoubleLexeme(const std::string& Lexeme) noexcept
{
	bool LHasFirstDigit = false;
	bool LHasPoint = false;
	bool LHasDigitAfterPoint = false;
	bool LHasE = false;
	bool LHasSignAfterE = false;
	bool LHasDigitAfterE = false;

	for( const char c : Lexeme )
	{
		if( c == '.' )
		{
			if( !LHasFirstDigit || LHasPoint || LHasE )
			{
				return false;
			}
			LHasPoint = true;
			continue;
		}

		if( c == 'e' || c == 'E' )
		{
			if( !LHasFirstDigit || LHasE || !LHasPoint )
			{
				return false;
			}
			LHasE = true;
			continue;
		}

		if( IsSign(c) )
		{
			if( !LHasE || LHasSignAfterE || LHasDigitAfterE )
			{
				return false;
			}
			LHasSignAfterE = true;
			continue;
		}

		if( !IsDigit(c) )
		{
			return false;
		}

		LHasFirstDigit = true;
		if( LHasPoint )
		{
			LHasDigitAfterPoint = true;
		}
		if( LHasE )
		{
			LHasDigitAfterE = true;
		}
	}

	if( LHasE && !LHasDigitAfterE )
	{
		return false;
	}
	return LHasFirstDigit && LHasPoint && LHasDigitAfterPoint;
}

bool FTokenHelperLibrary::IsFloatLexeme(const std::string& Lexeme) noexcept
{
	bool LHasFirstDigit = false;
	bool LHasPoint = false;
	bool LHasDigitAfterPoint = false;
	bool LHasE = false;
	bool LHasSignAfterE = false;
	bool LHasDigitAfterE = false;
	bool LHasF = false;

	for( const char c : Lexeme )
	{
		if( LHasF )
		{
			return false;
		}

		if( c == '.' )
		{
			if( !LHasFirstDigit || LHasPoint || LHasE )
			{
				return false;
			}
			LHasPoint = true;
			continue;
		}

		if( c == 'e' || c == 'E' )
		{
			if( !LHasFirstDigit || LHasE || !LHasPoint )
			{
				return false;
			}
			LHasE = true;
			continue;
		}

		if( IsSign(c) )
		{
			if( !LHasE || LHasSignAfterE || LHasDigitAfterE )
			{
				return false;
			}
			LHasSignAfterE = true;
			continue;
		}

		if( c == 'f' || c == 'F' )
		{
			if( !LHasFirstDigit || !LHasPoint || !LHasDigitAfterPoint )
			{
				return false;
			}
			LHasF = true;
			continue;
		}

		if( !IsDigit(c) )
		{
			return false;
		}

		LHasFirstDigit = true;
		if( LHasPoint )
		{
			LHasDigitAfterPoint = true;
		}
		if( LHasE )
		{
			LHasDigitAfterE = true;
		}
	}

	if( LHasE && !LHasDigitAfterE )
	{
		return false;
	}
	return LHasFirstDigit && LHasPoint && LHasDigitAfterPoint && LHasF;
}
