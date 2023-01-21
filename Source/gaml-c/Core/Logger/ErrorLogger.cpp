// Copyright 2022 - 2023 GrosSlava.

#include "ErrorLogger.h"

#include "Token/Token.h"
#include "CoreObjects.h"

#include <fstream>





// clang-format off
void FErrorLogger::Raise
(
	EErrorMessageType MessageType, 
	const std::string& File, size_t Line, size_t Pos, size_t UnderlineLength
)
// clang-format on
{
	FErrorInfo LErrorInfo = GetErrorInfo(MessageType);


	if( FCoreObjects::CompileOptions.ConvertWarningsToErrors )
	{
		LErrorInfo.ErrorType = EErrorType::ERROR;
	}

	// clang-format off
	if( 
		LErrorInfo.ErrorType == EErrorType::WARNING && 
		(FCoreObjects::CompileOptions.WarningLevel == EWarningLevel::NoWarnings || LErrorInfo.WarningLevel > FCoreObjects::CompileOptions.WarningLevel)
	   ) return;
	// clang-format on

	if( !LErrorInfo.Message.empty() && !FCoreObjects::CompileOptions.Silent )
	{
		FCompileLogger::Raise(LErrorInfo.ErrorType, File, LErrorInfo.Message, Line, Pos);
	}

	if( !File.empty() && FCoreObjects::CompileOptions.IncludeContextIntoErrors && !FCoreObjects::CompileOptions.Silent && Line > 0 )
	{
		std::ifstream LFile(File);
		if( LFile.is_open() )
		{
			size_t LLineIndex = 0;
			std::string LLineStr = "";

			// we are indexing rows from 1, so the last row read will be the one we are looking for
			while( LLineIndex < Line )
			{
				std::getline(LFile, LLineStr);
				++LLineIndex;
			}

			LFile.close();

			FCompileLogger::MessageError(LLineStr);

			if( Pos > 0 )
			{
				std::string LPosStr = "";
				LPosStr.resize(std::max(LLineStr.size(), Pos), ' ');
				LPosStr[Pos - 1] = '^'; // we are indexing position in row from 1

				for( size_t i = 0; i < Pos + UnderlineLength && i < LPosStr.size(); ++i )
				{
					if( i < Pos )
					{
						if( LLineStr[i] == '\t' )
						{
							LPosStr[i] = '\t';
						}
					}
					else
					{
						if( LLineStr[i] == '\t' )
						{
							LPosStr[i] = '\t';
						}
						else
						{
							LPosStr[i] = '~';
						}
					}
				}

				FCompileLogger::MessageError(LPosStr);
			}
		}
	}


	if( LErrorInfo.ErrorType == EErrorType::ERROR )
	{
		exit(1);
	}
}

void FErrorLogger::Raise(EErrorMessageType MessageType, const Token& CTXToken)
{
	Raise(MessageType, CTXToken.GetFileInfo().GetFileFullPath(), CTXToken.GetLine(), CTXToken.GetPos(), CTXToken.GetLexeme().size() - 1);
}
