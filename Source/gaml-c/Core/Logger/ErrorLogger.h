// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CompileLogger.h"
#include "ErrorName.h"




struct Token;



/*
	Helper struct to raise warnings and errors from compiler.
	@see FCompileLogger.
*/
class FErrorLogger
{
public:

	// clang-format off
	/*
		@param MessageType - Type of error.
		@param File - Context file.
		@param Line - Context line.
		@param Pos - Context line.
		@param UnderlineLength - Length of underline after Pos.
	*/
	static void Raise
	(
		EErrorMessageType MessageType, 
		const std::string& File, size_t Line, size_t Pos, size_t UnderlineLength
	);
	// clang-format on

	/*
		@param MessageType - Type of error.
		@param CTXToken - Context token.
	*/
	static void Raise(EErrorMessageType MessageType, const Token& CTXToken);
};