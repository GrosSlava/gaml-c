// Copyright 2022 GrosSlava.

#include "Lexer.h"

#include "../Token/TokenHelperLibrary.h"





void Lexer::Process(const std::string& Code, const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, std::vector<Token>& OutTokens)
{
	OutTokens.clear();

	CurrentFileInfo = FileInfo;
	CurrentCompileOptions = CompileOptions;

	CurrentLine = 1; // we are indexing rows from 1
	CurrentPos = 0;
	CurrentLexeme = "";

	Split(Code, OutTokens);
	Merge(OutTokens);
}




enum class ESpiltCommentState : unsigned char
{
	DEFAULT,
	PossibleInComment,
	InLineComment,
	InBlockComment,
	PossibleOutBlockComment,
	CommentEnd
};

enum class ESpiltStringState : unsigned char
{
	DEFAULT,
	CharOpen,
	StringOpen
};

enum class ESpiltNumberState : unsigned char
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
	ESpiltCommentState SplitCommentState = ESpiltCommentState::DEFAULT;
	ESpiltStringState SpiltStringState = ESpiltStringState::DEFAULT;
	ESpiltNumberState SpiltNumberState = ESpiltNumberState::DEFAULT;


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

		if( SplitCommentState == ESpiltCommentState::CommentEnd )
		{
			SplitCommentState = ESpiltCommentState::DEFAULT;
		}

		if( LSymbol == '\n' )
		{
			if( SplitCommentState == ESpiltCommentState::PossibleInComment )
			{
				SplitCommentState = ESpiltCommentState::DEFAULT;
			}
			else if( SplitCommentState == ESpiltCommentState::InLineComment )
			{
				SplitCommentState = ESpiltCommentState::CommentEnd;
			}
			else if( SplitCommentState == ESpiltCommentState::PossibleOutBlockComment )
			{
				SplitCommentState = ESpiltCommentState::InBlockComment;
			}
		}
		else if( LSymbol == '/' )
		{
			if( SplitCommentState == ESpiltCommentState::DEFAULT )
			{
				SplitCommentState = ESpiltCommentState::PossibleInComment;
			}
			else if( SplitCommentState == ESpiltCommentState::PossibleInComment )
			{
				SplitCommentState = ESpiltCommentState::InLineComment;
				CurrentLexeme.resize(CurrentLexeme.size() - 1);
				PushCurrentLexeme(OutTokens, 2);
			}
			else if( SplitCommentState == ESpiltCommentState::PossibleOutBlockComment )
			{
				SplitCommentState = ESpiltCommentState::CommentEnd;
			}
		}
		else if( LSymbol == '*' )
		{
			if( SplitCommentState == ESpiltCommentState::PossibleInComment )
			{
				SplitCommentState = ESpiltCommentState::InBlockComment;
				CurrentLexeme.resize(CurrentLexeme.size() - 1);
				// not push current lexeme because we can have comment inside any expression
			}
			else if( SplitCommentState == ESpiltCommentState::InBlockComment )
			{
				SplitCommentState = ESpiltCommentState::PossibleOutBlockComment;
			}
		}
		else
		{
			if( SplitCommentState == ESpiltCommentState::PossibleInComment )
			{
				SplitCommentState = ESpiltCommentState::DEFAULT;
			}
			else if( SplitCommentState == ESpiltCommentState::PossibleOutBlockComment )
			{
				SplitCommentState = ESpiltCommentState::InBlockComment;
			}
		}

		// clang-format off
		if( 
			SplitCommentState == ESpiltCommentState::InLineComment || 
			SplitCommentState == ESpiltCommentState::InBlockComment || 
			SplitCommentState == ESpiltCommentState::PossibleOutBlockComment ||
			SplitCommentState == ESpiltCommentState::CommentEnd 
		  )
		// clang-format on
		{
			continue;
		}

		//.......................................................//


		//......................String/char......................//

		if( LSymbol == '\'' )
		{
			if( SpiltStringState == ESpiltStringState::DEFAULT )
			{
				SpiltStringState = ESpiltStringState::CharOpen;
				PushCurrentLexeme(OutTokens, 1);
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltStringState == ESpiltStringState::CharOpen )
			{
				SpiltStringState = ESpiltStringState::DEFAULT;
				CurrentLexeme += LSymbol;
				PushCurrentLexeme(OutTokens);
				continue;
			}
			else if( SpiltStringState == ESpiltStringState::StringOpen )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
		}
		else if( LSymbol == '"' )
		{
			if( SpiltStringState == ESpiltStringState::DEFAULT )
			{
				SpiltStringState = ESpiltStringState::StringOpen;
				PushCurrentLexeme(OutTokens, 1);
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltStringState == ESpiltStringState::CharOpen )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltStringState == ESpiltStringState::StringOpen )
			{
				SpiltStringState = ESpiltStringState::DEFAULT;
				CurrentLexeme += LSymbol;
				PushCurrentLexeme(OutTokens);
				continue;
			}
		}
		else if( LSymbol == '\n' )
		{
			SpiltStringState = ESpiltStringState::DEFAULT;
		}

		if( SpiltStringState == ESpiltStringState::CharOpen || SpiltStringState == ESpiltStringState::StringOpen )
		{
			CurrentLexeme += LSymbol;
			continue;
		}

		//.......................................................//


		//......................Numbers..........................//

		if( FTokenHelperLibrary::IsDigit(LSymbol) )
		{
			if( SpiltNumberState == ESpiltNumberState::DEFAULT )
			{
				if( (CurrentLexeme.size() == 1 && FTokenHelperLibrary::IsOperatorChar(CurrentLexeme[0])) || FTokenHelperLibrary::IsComplexToken(CurrentLexeme) )
				{
					PushCurrentLexeme(OutTokens, 1);
				}

				if( CurrentLexeme.empty() )
				{
					SpiltNumberState = ESpiltNumberState::HasNumber;
					CurrentLexeme += LSymbol;
					continue;
				}
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumber )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnDot )
			{
				SpiltNumberState = ESpiltNumberState::HasNumberAfterDot;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterDot )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnE )
			{
				SpiltNumberState = ESpiltNumberState::HasNumberAfterE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnSignAfterE )
			{
				SpiltNumberState = ESpiltNumberState::HasNumberAfterE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterE )
			{
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_DIGIT_AFTER_NUMBER_END);
			}
		}
		else if( LSymbol == '.' )
		{
			if( SpiltNumberState == ESpiltNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumber )
			{
				SpiltNumberState = ESpiltNumberState::OnDot;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnDot )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterDot )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnE )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_DOT_INSIDE_NUMBER);
			}
		}
		else if( LSymbol == 'e' || LSymbol == 'E' )
		{
			if( SpiltNumberState == ESpiltNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumber )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnDot )
			{
				SpiltNumberState = ESpiltNumberState::OnE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterDot )
			{
				SpiltNumberState = ESpiltNumberState::OnE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnE )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_E_INSIDE_NUMBER);
			}
		}
		else if( FTokenHelperLibrary::IsSign(LSymbol) )
		{
			if( SpiltNumberState == ESpiltNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumber )
			{
				// no include sign in number lexeme
				SpiltNumberState = ESpiltNumberState::DEFAULT;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnDot )
			{
				RaiseError(EErrorMessageType::EXTRA_SIGN_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterDot )
			{
				SpiltNumberState = ESpiltNumberState::DEFAULT;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnE )
			{
				SpiltNumberState = ESpiltNumberState::OnSignAfterE;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_SIGN_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterE )
			{
				SpiltNumberState = ESpiltNumberState::DEFAULT;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnF )
			{
				SpiltNumberState = ESpiltNumberState::DEFAULT;
			}
		}
		else if( LSymbol == 'f' || LSymbol == 'F' )
		{
			if( SpiltNumberState == ESpiltNumberState::DEFAULT )
			{
				// no operation
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumber )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnDot )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterDot )
			{
				SpiltNumberState = ESpiltNumberState::OnF;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnE )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::OnSignAfterE )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
			else if( SpiltNumberState == ESpiltNumberState::HasNumberAfterE )
			{
				SpiltNumberState = ESpiltNumberState::OnF;
				CurrentLexeme += LSymbol;
				continue;
			}
			else if( SpiltNumberState == ESpiltNumberState::OnF )
			{
				RaiseError(EErrorMessageType::EXTRA_F_INSIDE_NUMBER);
			}
		}
		else
		{
			SpiltNumberState = ESpiltNumberState::DEFAULT;
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
