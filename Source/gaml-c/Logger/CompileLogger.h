// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"




/*
	Stage of compilation where error raised.
*/
enum class EErrorStage
{
	INITIALIZATION,
	LEXER,
	PARSER,
	SEMANTIC,
	CODE_GENERATION,
	LINKER
};

/*
	Severity of the error.
*/
enum class EErrorType
{
	ERROR,
	WARNING
};


/*
	Helper object for logging from compiler.
*/
struct FCompileLogger
{
	/*
		Log formatted message.

		@param ErrorStage - Compilation stage.
		@param ErrorType - Severity of the error.
		@param File - Context file.
		@param Message - Message to log.
		@param Line - Context line.
		@param Pos - Context line position.
	*/
	static void Raise(EErrorStage ErrorStage, EErrorType ErrorType, const std::string& File, const std::string& Message, size_t Line, size_t Pos);
	/*
		Log message.

		@param Message - Message to log.
	*/
	static void Message(const std::string& Message);
};