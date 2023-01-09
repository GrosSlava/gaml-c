// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "CompileLogger.h"
#include "../Compiler/CompilerOptions.h"




class Token;



/*
	Error/Warning message identifier.
*/
enum class EErrorMessageType
{
	/* Initialization */
	NO_PATH_TO_COMPILER,
	NO_FILES_TO_COMPILE,


	/* Lexer */
	INVALID_SYMBOL,
	INVALID_LEXEME,
	EXTRA_DIGIT_AFTER_NUMBER_END,
	EXTRA_DOT_INSIDE_NUMBER,
	EXTRA_E_INSIDE_NUMBER,
	EXTRA_SIGN_INSIDE_NUMBER,
	EXTRA_F_INSIDE_NUMBER,


	/* Parser */
	INVALID_STATE,
	STATE_STACK_EMPTY,

	UNEXPECTED_EXPRESSION,
	UNEXPECTED_IDENTIFIER,

	EXPECTED_IDENTIFIER,
	EXPECTED_SEMICOLON,
	EXPECTED_ASSIGN,
	EXPECTED_COLON,
	EXPECTED_COMMA,
	EXPECTED_POINT,
	EXPECTED_QUESTION,
	EXPECTED_LBRA,
	EXPECTED_RBRA,
	EXPECTED_LPAR,
	EXPECTED_RPAR,
	EXPECTED_LSQR,
	EXPECTED_RSQR,
	EXPECTED_LTRI,
	EXPECTED_RTRI,
	EXPECTED_DESCRIPTION_BLOCK,
	EXPECTED_FUNCTION_RETURN_TYPE,
	EXPECTED_FUNCTION_NAME,
	EXPECTED_ARGUMENT_TYPE,
	EXPECTED_ARGUMENT_NAME,
	EXPECTED_ALIAS_NAME,
	EXPECTED_CLASS_NAME,

	INVALID_CLOSE_PAIR,
	OPEN_PAIR_SHOULD_HAVE_CLOSE,

	MODULE_NAME_REDEFINITION,
	MODULE_ALIAS_NAME_REDEFINITION,
	FUNCTION_NAME_REDEFINITION,
	FUNCTION_IMPLEMENTATION_NAME_REDEFINITION,
	CLASS_NAME_REDEFINITION,
	VARIABLE_NAME_REDEFINITION,
	ARGUMENT_NAME_REDEFINITION,
	ALIAS_NAME_REDEFINITION,
	TEMPLATE_CODE_NAME_REDEFINITION,

	MODULE_NAME_GENERATION_PROBLEM,
	FUNCTION_NAME_GENERATION_PROBLEM,
	VARIABLE_NAME_GENERATION_PROBLEM,
	CLASS_NAME_GENERATION_PROBLEM,
	ALIAS_NAME_GENERATION_PROBLEM,

	MODULE_NOT_FOUND,
	NO_NAME_NOT_MAIN_MODULE,
	MODULE_DOUBLE_IMPORT,
	INVALID_IMPORTING_MODULE_NAME,
	IMPORTING_PACKAGE_PROBLEM,
	MODULE_NAME_NOT_MATCH_FILE_NAME,
	IMPORTING_MAIN_MODULE,
	IMPORTING_IMPLEMENT_MODULE,
	MODULE_ALIAS_CONTAINS_INVALID_CHAR,

	DOUBLE_MODIFIER,
	RETURN_TYPE_DOUBLE_MODIFIER,
	MEMBER_DOUBLE_MODIFIER,
	FUNCTION_DECLARATION_NOT_FOUND,
	FUNCTION_ARGUMENT_NAME_MISMATCH,
	FUNCTION_DESCRIPTION_MISMATCH,
	FUNCTION_STATIC_CODE_OVERRIDE,

	CLASS_NAME_NOT_FOUND,


	/* Code generator */
	NO_DEFAULT_COMPILER_FOR_CURRENT_PLATFORM,
	UNSUPPORTED_CODE_GENERATOR,
	INVALID_ARCH_FOR_GENERATE,
	INVALID_GENERATION_EXTENSION,


	/* Linker */
	NO_DEFAULT_LINKER_FOR_CURRENT_PLATFORM,
	INVALID_SUBSYSTEM,
	INVALID_ARCH_FOR_LINK,
	CANT_LINK_TO_TARGET_PLATFORM
};



/*
	Helper struct for information about error.
*/
struct FErrorInfo
{
public:

	inline FErrorInfo() { }
	inline FErrorInfo(EErrorStage InErrorStage, EErrorType InErrorType, EWarningLevel InWarningLevel, const std::string& InMessage) :
		ErrorStage(InErrorStage), ErrorType(InErrorType), WarningLevel(InWarningLevel), Message(InMessage)
	{
	}


public:

	/*
		Error stage in compilation pipeline.
	*/
	EErrorStage ErrorStage = EErrorStage::INITIALIZATION;
	/*
		Severity of the error.
	*/
	EErrorType ErrorType = EErrorType::WARNING;
	/*
		Level of warning.
	*/
	EWarningLevel WarningLevel = EWarningLevel::NoWarnings;
	/*
		Message for this error.
	*/
	std::string Message = "";
};



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
		@param CompileOptions - Current compilation options.
	*/
	static void Raise
	(
		EErrorMessageType MessageType, 
		const std::string& File, size_t Line, size_t Pos, size_t UnderlineLength, 
		const FCompileOptions& CompileOptions
	);
	// clang-format on

	/*
		@param MessageType - Type of error.
		@param CTXToken - Context token.
		@param CompileOptions - Current compilation options.
	*/
	static void Raise(EErrorMessageType MessageType, const Token& CTXToken, const FCompileOptions& CompileOptions);

private:

	/*
		@return predefined error info based on MessageType.
	*/
	static FErrorInfo GetErrorInfo(EErrorMessageType MessageType);
};