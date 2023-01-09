// Copyright 2022 - 2023 GrosSlava.

#include "Parser.h"
#include "States/ParserStates.h"
#include "ParserHelperLibrary.h"

#include "../Token/Token.h"





// clang-format off
void Parser::Process
(
	const std::vector<Token>& Tokens, const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, bool InIsMainModule, 
	FProgramInfo& OutProgramInfo
)
// clang-format on
{
	CurrentFileInfo = FileInfo;
	CurrentCompileOptions = CompileOptions;
	IsMainModule = InIsMainModule;


	// NOTE: comments was already removed
	CheckPairs(Tokens);
	ProcessSymbolsScanning(Tokens, OutProgramInfo);
}




void Parser::CheckPairs(const std::vector<Token>& Tokens)
{
	std::vector<Token> LPairTokensStack;

	for( const Token& LToken : Tokens )
	{
		if( LToken.GetType() == ETokenType::DESCRIPTION_BLOCK )
		{
			if( LPairTokensStack.empty() || LPairTokensStack.back().GetType() != ETokenType::DESCRIPTION_BLOCK )
			{
				LPairTokensStack.push_back(LToken);
				continue;
			}
			else
			{
				LPairTokensStack.pop_back();
				continue;
			}
		}

		if( FParserHelperLibrary::IsOpenPairToken(LToken) )
		{
			LPairTokensStack.push_back(LToken);
			continue;
		}

		if( FParserHelperLibrary::IsClosePairToken(LToken) )
		{
			if( LPairTokensStack.empty() )
			{
				switch( FParserHelperLibrary::GetMatchOpenPairType(LToken) )
				{
				case ETokenType::LBRA:
				{
					RaiseError(EErrorMessageType::EXPECTED_LBRA, LToken);
					return;
				}
				case ETokenType::LPAR:
				{
					RaiseError(EErrorMessageType::EXPECTED_LPAR, LToken);
					return;
				}
				case ETokenType::LSQR:
				{
					RaiseError(EErrorMessageType::EXPECTED_LSQR, LToken);
					return;
				}
				case ETokenType::LTRI:
				{
					RaiseError(EErrorMessageType::EXPECTED_LTRI, LToken);
					return;
				}
				}

				RaiseError(EErrorMessageType::INVALID_CLOSE_PAIR, LToken);
				return;
			}
			else if( !FParserHelperLibrary::DoesPairTokensMatch(LPairTokensStack.back(), LToken) )
			{
				switch( FParserHelperLibrary::GetMatchClosePairType(LPairTokensStack.back()) )
				{
				case ETokenType::RBRA:
				{
					RaiseError(EErrorMessageType::EXPECTED_RBRA, LToken);
					return;
				}
				case ETokenType::RPAR:
				{
					RaiseError(EErrorMessageType::EXPECTED_RPAR, LToken);
					return;
				}
				case ETokenType::RSQR:
				{
					RaiseError(EErrorMessageType::EXPECTED_RSQR, LToken);
					return;
				}
				case ETokenType::RTRI:
				{
					RaiseError(EErrorMessageType::EXPECTED_RTRI, LToken);
					return;
				}
				}

				RaiseError(EErrorMessageType::INVALID_CLOSE_PAIR, LToken);
				return;
			}
			else
			{
				LPairTokensStack.pop_back();
			}
		}
	}

	if( !LPairTokensStack.empty() )
	{
		RaiseError(EErrorMessageType::OPEN_PAIR_SHOULD_HAVE_CLOSE, LPairTokensStack.back());
		return;
	}
}

void Parser::ProcessSymbolsScanning(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo)
{
	FParserStates LParserStates(CurrentFileInfo, CurrentCompileOptions, IsMainModule);
	std::shared_ptr<IParserState> LState = LParserStates.GDefault_ParserState;

	for( const Token& LToken : Tokens )
	{
		LState = LState->Process(LParserStates, LToken, OutProgramInfo);
		if( LState == nullptr )
		{
			RaiseError(EErrorMessageType::INVALID_STATE, LToken);
			return;
		}
	}
	if( LState != LParserStates.GDefault_ParserState || !LParserStates.IsStateStackEmpty() )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, CurrentFileInfo.GetFileFullPath(), 0, 0, 0, CurrentCompileOptions);
		return;
	}
}
