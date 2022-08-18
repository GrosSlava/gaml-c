// Copyright 2022 GrosSlava.

#pragma once

#include <string>




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
public:

	static void Raise(EErrorStage ErrorStage, EErrorType ErrorType, const std::string& File, const std::string& Message, size_t Line, size_t Pos);
	static void Message(const std::string& Message);
};