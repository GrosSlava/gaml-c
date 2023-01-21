// Copyright 2022 - 2023 GrosSlava.

#include "CompileLogger.h"

#include <iostream>





void FCompileLogger::Raise(EErrorType ErrorType, const std::string& File, const std::string& Message, size_t Line, size_t Pos)
{
	std::string LErrorMessage = "";
	LErrorMessage.reserve(64 + File.size() + Message.size());

	if( !File.empty() )
	{
		LErrorMessage += "\"" + File + "\" ";
	}

	if( Line + Pos != 0 )
	{
		LErrorMessage += "[";
		LErrorMessage += std::to_string(Line);
		LErrorMessage += "][";
		LErrorMessage += std::to_string(Pos);
		LErrorMessage += "] ";
	}

	// clang-format off
	switch( ErrorType )
	{
	case EErrorType::WARNING:			{ LErrorMessage += "WARNING ";						break; }
	case EErrorType::ERROR:				{ LErrorMessage += "ERROR ";						break; }
	default:							{ LErrorMessage += "INVALIID ERROR TYPE ";			break; }
	}
	// clang-format on

	LErrorMessage += Message;

	FCompileLogger::MessageError(LErrorMessage);
}

void FCompileLogger::MessageError(const std::string& Message)
{
	if( !Message.empty() )
	{
		std::cerr << Message << std::endl;
	}
}

void FCompileLogger::MessageText(const std::string& Message)
{
	if( !Message.empty() )
	{
		std::cout << Message << std::endl;
	}
}