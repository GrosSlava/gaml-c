// Copyright 2022 GrosSlava.

#include "CompileLogger.h"

#include <iostream>





void FCompileLogger::Raise(EErrorStage ErrorStage, EErrorType ErrorType, const std::string& File, const std::string& Message, size_t Line, size_t Pos)
{
	std::string LErrorMessage = "";
	LErrorMessage.reserve(64 + File.size() + Message.size());

	if( !File.empty() )
	{
		LErrorMessage += "\"" + File + "\" ";
	}

	if( ErrorStage != EErrorStage::INITIALIZATION && Line + Pos != 0 )
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

	switch( ErrorStage )
	{
	case EErrorStage::INITIALIZATION:	{ LErrorMessage += "Initialization: ";				break; }
	case EErrorStage::LEXER:			{ LErrorMessage += "Lexer: ";						break; }
	case EErrorStage::PARSER:			{ LErrorMessage += "Parser: ";						break; }
	case EErrorStage::SEMANTIC:			{ LErrorMessage += "Analizer: ";					break; }
	case EErrorStage::CODE_GENERATION:	{ LErrorMessage += "Compiler: ";					break; }
	case EErrorStage::LINKER:			{ LErrorMessage += "Linker: ";						break; }
	default:							{ LErrorMessage += "INVALIID STAGE: ";				break; }
	}
	// clang-format on

	LErrorMessage += Message;

	FCompileLogger::MessageError(LErrorMessage);
}

void FCompileLogger::MessageError(const std::string& Message)
{
	if( Message.empty() ) return;

	std::cerr << Message << std::endl;
}

void FCompileLogger::MessageText(const std::string& Message)
{
	if( Message.empty() ) return;

	std::cout << Message << std::endl;
}