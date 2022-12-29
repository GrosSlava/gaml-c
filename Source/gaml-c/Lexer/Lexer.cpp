// Copyright 2022 GrosSlava.

#include "Lexer.h"

#include "../Token/TokenHelperLibrary.h"





void Lexer::Process(const std::string& Code, const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, std::vector<Token>& OutTokens)
{
	OutTokens.clear();

	CurrentFileInfo = FileInfo;
	CurrentCompileOptions = CompileOptions;

	CurrentLine = 1; // we are indexing rows from 1
	CurrentPos = 1;	 // we are indexing position in row from 1
	CurrentLexeme = "";

	Split(Code, OutTokens);
	Merge(OutTokens);
}




enum class ESplitCommentState : unsigned char
{
	DEFAULT,
	PossibleInComment,
	InLineComment,
	InBlockComment,
	PossibleOutBlockComment,
	CommentEnd
};

enum class ESplitStringState : unsigned char
{
	DEFAULT,
	CharOpen,
	StringOpen
};

enum class ESplitNumberState : unsigned char
{
	DEFAULT,
	HasNumber,
	OnDot,
	HasNumberAfterDot,
	OnE,
	OnSignAfterE,
	HasNumberAfterE,
	OnF
};

void Lexer::Split(const std::string& Code, std::vector<Token>& OutTokens)
{
	ESplitCommentState SplitCommentState = ESplitCommentState::DEFAULT;
	ESplitStringState SplitStringState = ESplitStringState::DEFAULT;
	ESplitNumberState SplitNumberState = ESplitNumberState::DEFAULT;


	for( const char& LSymbol : Code )
	{
		if( LSymbol == '\n' )
		{
			++CurrentLine;
			CurrentPos = 0;
		}
		++CurrentPos; // we are indexing position in row from 1


		//.....................Comments..........................//

		// NOTE! Construction: /* /* */ - second '/*' not open new block.
		// NOTE! Construction: /* /* */ */ - second '*/' will be not in comment block.

		if( SplitCommentState == ESplitCommentState::CommentEnd )
		{
			SplitCommentState = ESplitCommentState::DEFAULT;
		}

		if( LSymbol == '\n' )
		{
			if( SplitCommentState == ESplitCommentState::PossibleInComment )
			{
				SplitCommentState = ESplitCommentState::DEFAULT;
			}
			else if( SplitCommentState == ESplitCommentState::InLineComment )
			{
				SplitCommentState = ESplitCommentState::CommentEnd;
			}
			else if( SplitCommentState == ESplitCommentState::PossibleOutBlockComment )
			{
				SplitCommentState = ESplitCommentState::InBlockComment;
			}
		}
		else if( LSymbol == '/' )
		{
			if( SplitCommentState == ESplitCommentState::DEFAULT )
			{
				SplitCommentState = ESplitCommentState::PossibleInComment;
			}
			else if( SplitCommentState == ESplitCommentState::PossibleInComment )
			{
				SplitCommentState = ESplitCommentState::InLineComment;
				CurrentLexeme.resize(CurrentLexeme.size() - 1);
				PushCurrentLexeme(OutTokens, 2);
			}
			else if( SplitCommentState == ESplitCommentState::PossibleOutBlockComment )
			{
				SplitCommentState = ESplitCommentState::CommentEnd;
			}
		}
		else if( LSymbol == '*' )
		{
			if( SplitCommentState == ESplitCommentState::PossibleInComment )
			{
				SplitCommentState = ESplitCommentState::InBlockComment;
				CurrentLexeme.resize(CurrentLexeme.size() - 1);
				// not push current lexeme because we can have comment inside any expression
			}
			else if( SplitCommentState == ESplitCommentState::InBlockComment )
			{
				SplitCommentState = ESplitCommentState::PossibleOutBlockComment;
			}
		}
		else
		{
			if( SplitCommentState == ESplitCommentState::PossibleInComment )
			{
				SplitCommentState = ESplitCommentState::DEFAULT;
			}
			else if( SplitCommentState == ESplitCommentState::PossibleOutBlockComment )
			{
				SplitCommentState = ESplitCommentState::InBlockComment;
			}
		}

		// clang-format off
		if( 
			SplitCommentState == ESplitCommentState::InLineComment || 
			SplitCommentState == ESplitCommentState::InBlockComment || 
			SplitCommentState == ESplitCommentState::PossibleOutBlockComment ||
			SplitCommentState == ESplitCommentState::CommentEnd 
		  )
		// clang-format on
		{
			continue;
		}

		//.......................................................//


		//......................String/char......................//

		if( LSymbol == '\'' )
		{
			if( SplitStringState == ESplitStringState::DEFAULT )
			{
				SplitStringState = ESplitStringState::CharOpen;
				PushCurrentLexeme(OutTokens, 1);
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitStringState == ESplitStringState::CharOpen )
			{
				SplitStringState = ESplitStringState::DEFAULT;
				CurrentLexeme += LSymbol;
				PushCurrentLexeme(OutTokens);
				continue;
			}
			else if( SplitStringState == ESplitStringState::StringOpen )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
		}
		else if( LSymbol == '"' )
		{
			if( SplitStringState == ESplitStringState::DEFAULT )
			{
				SplitStringState = ESplitStringState::StringOpen;
				PushCurrentLexeme(OutTokens, 1);
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitStringState == ESplitStringState::CharOpen )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitStringState == ESplitStringState::StringOpen )
			{
				SplitStringState = ESplitStringState::DEFAULT;
				CurrentLexeme += LSymbol;
				PushCurrentLexeme(OutTokens);
				continue;
			}
		}
		else if( LSymbol == '\n' )
		{
			SplitStringState = ESplitStringState::DEFAULT;
		}

		if( SplitStringState == ESplitStringState::CharOpen || SplitStringState == ESplitStringState::StringOpen )
		{
			CurrentLexeme += LSymbol;
			continue;
		}

		//.......................................................//


		//......................Numbers..........................//

		if( FTokenHelperLibrary::IsDigit(LSymbol) )
		{
			if( SplitNumberState == ESplitNumberState::DEFAULT )
			{
				if( (CurrentLexeme.size() == 1 && FTokenHelperLibrary::IsOperatorChar(CurrentLexeme[0])) || FTokenHelperLibrary::IsComplexToken(CurrentLexeme) )
				{
					PushCurrentLexeme(OutTokens, 1);
				}

				if( CurrentLexeme.empty() )
				{
					SplitNumberState = ESplitNumberState::HasNumber;
					CurrentLexeme += LSymbol;
					continue;
				}
			}
			else if( SplitNumberState == ESplitNumberState::HasNumber )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnDot )
			{
				SplitNumberState = ESplitNumberState::HasNumberAfterDot;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterDot )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnE )
			{
				SplitNumberState = ESplitNumberState::HasNumberAfterE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnSignAfterE )
			{
				SplitNumberState = ESplitNumberState::HasNumberAfterE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterE )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_DIGIT_AFTER_NUMBER_END);
			}
		}
		else if( LSymbol == '.' )
		{
			if( SplitNumberState == ESplitNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SplitNumberState == ESplitNumberState::HasNumber )
			{
				SplitNumberState = ESplitNumberState::OnDot;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnDot )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterDot )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnE )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
		}
		else if( LSymbol == 'e' || LSymbol == 'E' )
		{
			if( SplitNumberState == ESplitNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SplitNumberState == ESplitNumberState::HasNumber )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnDot )
			{
				SplitNumberState = ESplitNumberState::OnE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterDot )
			{
				SplitNumberState = ESplitNumberState::OnE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnE )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
		}
		else if( FTokenHelperLibrary::IsSign(LSymbol) )
		{
			if( SplitNumberState == ESplitNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SplitNumberState == ESplitNumberState::HasNumber )
			{
				// no include sign in number lexeme
				SplitNumberState = ESplitNumberState::DEFAULT;
			}
			else if( SplitNumberState == ESplitNumberState::OnDot )
			{
				RaiseError(EErrorMessageType::EXTRA_SIGN_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterDot )
			{
				SplitNumberState = ESplitNumberState::DEFAULT;
			}
			else if( SplitNumberState == ESplitNumberState::OnE )
			{
				SplitNumberState = ESplitNumberState::OnSignAfterE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_SIGN_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterE )
			{
				SplitNumberState = ESplitNumberState::DEFAULT;
			}
			else if( SplitNumberState == ESplitNumberState::OnF )
			{
				SplitNumberState = ESplitNumberState::DEFAULT;
			}
		}
		else if( LSymbol == 'f' || LSymbol == 'F' )
		{
			if( SplitNumberState == ESplitNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SplitNumberState == ESplitNumberState::HasNumber )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnDot )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterDot )
			{
				SplitNumberState = ESplitNumberState::OnF;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnE )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SplitNumberState == ESplitNumberState::HasNumberAfterE )
			{
				SplitNumberState = ESplitNumberState::OnF;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SplitNumberState == ESplitNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
		}
		else
		{
			SplitNumberState = ESplitNumberState::DEFAULT;
		}

		//.......................................................//


		if( FTokenHelperLibrary::IsInvalidChar(LSymbol) )
		{
			RaiseError(EErrorMessageType::INVALID_SYMBOL);
		}



		if( FTokenHelperLibrary::IsSeparateSymbol(LSymbol) )
		{
			if( FTokenHelperLibrary::IsWhitespace(LSymbol) )
			{
				PushCurrentLexeme(OutTokens, 1);
			}
			else if( FTokenHelperLibrary::IsOperatorChar(LSymbol) )
			{
				if( CurrentLexeme.size() == 0 )
				{
					CurrentLexeme += LSymbol;
					// push on next iteration
				}
				else if( CurrentLexeme.size() == 1 && FTokenHelperLibrary::IsPotentialComplex(CurrentLexeme[0], LSymbol) )
				{
					CurrentLexeme += LSymbol;
					// push on next iteration
				}
				else if( CurrentLexeme.size() == 2 && FTokenHelperLibrary::IsComplex(CurrentLexeme[0], CurrentLexeme[1], LSymbol) )
				{
					CurrentLexeme += LSymbol;
					PushCurrentLexeme(OutTokens);
				}
				else
				{
					if( CurrentLexeme.size() == 3 )
					{
						if( FTokenHelperLibrary::IsComplex(CurrentLexeme[0], CurrentLexeme[1], CurrentLexeme[2]) )
						{
							PushCurrentLexeme(OutTokens, 1);
						}
						else if( FTokenHelperLibrary::IsComplex(CurrentLexeme[0], CurrentLexeme[1]) )
						{
							const std::string Tmp = CurrentLexeme;

							CurrentLexeme = Tmp.substr(0, 2);
							PushCurrentLexeme(OutTokens, 2);

							CurrentLexeme = Tmp.substr(2, 1);
							PushCurrentLexeme(OutTokens, 1);
						}
						else if( FTokenHelperLibrary::IsComplex(CurrentLexeme[1], CurrentLexeme[2]) )
						{
							const std::string Tmp = CurrentLexeme;

							CurrentLexeme = Tmp.substr(0, 1);
							PushCurrentLexeme(OutTokens, 3);

							CurrentLexeme = Tmp.substr(1, 2);
							PushCurrentLexeme(OutTokens, 1);
						}
						else
						{
							PushCurrentLexeme(OutTokens, 1);
						}
					}
					else
					{
						PushCurrentLexeme(OutTokens, 1);
					}


					CurrentLexeme += LSymbol;
					// push on next iteration
				}
			}
			else
			{
				PushCurrentLexeme(OutTokens, 1);
				CurrentLexeme += LSymbol;
				PushCurrentLexeme(OutTokens);
			}
		}
		else
		{
			if( (CurrentLexeme.size() == 1 && FTokenHelperLibrary::IsOperatorChar(CurrentLexeme[0])) || FTokenHelperLibrary::IsComplexToken(CurrentLexeme) )
			{
				PushCurrentLexeme(OutTokens, 1);
			}

			CurrentLexeme += LSymbol;
		}
	}

	PushCurrentLexeme(OutTokens);
}

void Lexer::Merge(std::vector<Token>& OutTokens)
{
	std::vector<Token> LTokens;

	//Example
	/*
	//.......................Merge access modifier block.....................//

	for( size_t i = 0; i < OutTokens.size(); ++i )
	{
		// clang-format off
		while( 
				(i + 1 < OutTokens.size()) && 
				(OutTokens[i].GetType() == ETokenType::PUBLIC || OutTokens[i].GetType() == ETokenType::PROTECTED || OutTokens[i].GetType() == ETokenType::PRIVATE) &&
				OutTokens[i + 1].GetType() == ETokenType::COLON
			 )
		// clang-format on
		{
			Token LToken(CurrentFileInfo, OutTokens[i].GetLexeme() + OutTokens[i + 1].GetLexeme(), OutTokens[i].GetLine(), OutTokens[i].GetPos(), CurrentCompileOptions);
			LTokens.push_back(LToken);
			i += 2;
		}

		if( i >= OutTokens.size() ) break;
		LTokens.push_back(OutTokens[i]);
	}

	OutTokens = LTokens;
	LTokens.clear();

	//.......................................................................//
	*/
}
