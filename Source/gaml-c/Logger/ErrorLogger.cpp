// Copyright 2022 GrosSlava.

#include "ErrorLogger.h"

#include <fstream>





void FErrorLogger::Raise(EErrorMessageType MessageType, const std::string& File, size_t Line, size_t Pos, const FCompileOptions& CompileOptions)
{
	FErrorInfo LErrorInfo = GetErrorInfo(MessageType);


	if( CompileOptions.ConvertWarningsToErrors )
	{
		LErrorInfo.ErrorType = EErrorType::ERROR;
	}

	if( LErrorInfo.ErrorType == EErrorType::WARNING && (CompileOptions.WarningLevel == EWarningLevel::NoWarnings || LErrorInfo.WarningLevel > CompileOptions.WarningLevel) ) return;

	if( !LErrorInfo.Message.empty() && !CompileOptions.Silent )
	{
		FCompileLogger::Raise(LErrorInfo.ErrorStage, LErrorInfo.ErrorType, File, LErrorInfo.Message, Line, Pos);
	}

	if( !File.empty() && CompileOptions.IncludeContextIntoErrors && !CompileOptions.Silent && Line > 0 )
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

			FCompileLogger::Message(LLineStr);

			if( Pos > 0 )
			{
				std::string LPosStr = "";
				LPosStr.resize(std::max(LLineStr.size(), Pos), ' ');
				LPosStr[Pos - 1] = '^'; // we are indexing position in row from 1

				FCompileLogger::Message(LPosStr);
			}
		}
	}


	if( LErrorInfo.ErrorType == EErrorType::ERROR )
	{
		exit(1);
	}
}

FErrorInfo FErrorLogger::GetErrorInfo(EErrorMessageType MessageType)
{
	#define CASE_ERROR(Type) case EErrorMessageType::Type

	switch( MessageType )
	{
	// Initialization
	CASE_ERROR(NO_FILES_TO_COMPILE):						return FErrorInfo(EErrorStage::INITIALIZATION, EErrorType::WARNING, EWarningLevel::SeriousWarning, "No files to compile.");

	//Lexer
	CASE_ERROR(INVALID_SYMBOL):								return FErrorInfo(EErrorStage::LEXER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid symbol.");
	CASE_ERROR(INVALID_LEXEME):								return FErrorInfo(EErrorStage::LEXER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid lexeme.");
	CASE_ERROR(EXTRA_DIGIT_AFTER_NUMBER_END):				return FErrorInfo(EErrorStage::LEXER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Extra digit after expected end of number.");
	CASE_ERROR(EXTRA_DOT_INSIDE_NUMBER):					return FErrorInfo(EErrorStage::LEXER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Extra dot inside number.");
	CASE_ERROR(EXTRA_E_INSIDE_NUMBER):						return FErrorInfo(EErrorStage::LEXER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Extra e inside number.");
	CASE_ERROR(EXTRA_SIGN_INSIDE_NUMBER):					return FErrorInfo(EErrorStage::LEXER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Extra sign inside number.");
	CASE_ERROR(EXTRA_F_INSIDE_NUMBER):						return FErrorInfo(EErrorStage::LEXER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Extra f inside number.");

	// Parser
	CASE_ERROR(INVALID_STATE):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid state.");
	CASE_ERROR(UNEXPECTED_EXPRESSION):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Unexpected expression.");
	CASE_ERROR(UNEXPECTED_IDENTIFIER):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Unexpected identifier.");
	CASE_ERROR(EXPECTED_IDENTIFIER):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected identifier.");
	CASE_ERROR(EXPECTED_SEMICOLON):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected ';'.");
	CASE_ERROR(EXPECTED_COLON):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected ':'.");
	CASE_ERROR(EXPECTED_COMMA):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected ','.");
	CASE_ERROR(EXPECTED_POINT):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '.'.");
	CASE_ERROR(EXPECTED_QUESTION):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '?'.");
	CASE_ERROR(EXPECTED_LBRA):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '{'.");
	CASE_ERROR(EXPECTED_RBRA):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '}'.");
	CASE_ERROR(EXPECTED_LPAR):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '('.");
	CASE_ERROR(EXPECTED_RPAR):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected ')'.");
	CASE_ERROR(EXPECTED_LSQR):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '['.");
	CASE_ERROR(EXPECTED_RSQR):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected ']'.");
	CASE_ERROR(EXPECTED_LTRI):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '<|'.");
	CASE_ERROR(EXPECTED_RTRI):								return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '|>'.");
	CASE_ERROR(INVALID_CLOSE_PAIR):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid close pair.");
	CASE_ERROR(OPEN_PAIR_SHOULD_HAVE_CLOSE):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Open pair should have close.");
	CASE_ERROR(MODULE_NAME_REDEFINITION):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Module name redefinition.");
	CASE_ERROR(MODULE_ALIAS_NAME_REDEFINITION):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Module alias name redefinition.");
	CASE_ERROR(FUNCTION_NAME_REDEFINITION):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function implementation name redefinition.");
	CASE_ERROR(FUNCTION_IMPLEMENTATION_NAME_REDEFINITION):	return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function name redefinition.");
	CASE_ERROR(CLASS_NAME_REDEFINITION):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Class name redefinition.");
	CASE_ERROR(VARIABLE_NAME_REDEFINITION):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Variable name redefinition.");
	CASE_ERROR(ARGUMENT_NAME_REDEFINITION):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Argument name redefinition.");
	CASE_ERROR(ALIAS_NAME_REDEFINITION):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Alias name redefinition.");
	CASE_ERROR(TEMPLATE_CODE_NAME_REDEFINITION):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Template class name redefinition.");
	CASE_ERROR(MODULE_NAME_GENERATION_PROBLEM):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Module name generation problem.");
	CASE_ERROR(FUNCTION_NAME_GENERATION_PROBLEM):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function name generation problem.");
	CASE_ERROR(VARIABLE_NAME_GENERATION_PROBLEM):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Variable name generation problem.");
	CASE_ERROR(CLASS_NAME_GENERATION_PROBLEM):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Class name generation problem.");
	CASE_ERROR(ALIAS_NAME_GENERATION_PROBLEM):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Alias name generation problem.");
	CASE_ERROR(MODULE_NOT_FOUND):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Module not found.");
	CASE_ERROR(NO_NAME_NOT_MAIN_MODULE):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "An unnamed module can only be the main module.");
	CASE_ERROR(MODULE_DOUBLE_IMPORT):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Detected module double import.");
	CASE_ERROR(INVALID_IMPORTING_MODULE_NAME):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid importing module name.");
	CASE_ERROR(IMPORTING_PACKAGE_PROBLEM):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Importing package problem.");
	CASE_ERROR(MODULE_NAME_NOT_MATCH_FILE_NAME):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Module name does not match the file name.");
	CASE_ERROR(IMPORTING_IMPLEMENT_MODULE):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Implement module can only main module.");
	CASE_ERROR(FUNCTION_DOUBLE_SPECIFIER):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function double specifier.");
	CASE_ERROR(FUNCTION_RETURN_TYPE_DOUBLE_CPECIFIER):		return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function return type double specifier.");
	CASE_ERROR(FUNCTION_MEMBER_DOUBLE_SPECIFIER):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function member double specifier.");
	CASE_ERROR(EXPECTED_FUNCTION_RETURN_TYPE):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected return type.");
	CASE_ERROR(EXPECTED_FUNCTION_NAME):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected function name.");
	CASE_ERROR(EXPECTED_ARGUMENT_TYPE):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected argument type.");
	CASE_ERROR(EXPECTED_ARGUMENT_NAME):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected argument name.");
	CASE_ERROR(FUNCTION_DECLARATION_NOT_FOUND):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function declaration not found.");
	CASE_ERROR(FUNCTION_ARGUMENT_NAME_MISMATCH):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Mismatch of the function declaration argument name.");
	CASE_ERROR(FUNCTION_STATIC_CODE_OVERRIDE):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function static code override.");

	//Code generator
	CASE_ERROR(NO_DEFAULT_COMPILER_FOR_CURRENT_PLATFORM):	return FErrorInfo(EErrorStage::CODE_GENERATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "No default compiler for current platform.");
	CASE_ERROR(INVALID_ARCH_FOR_GENERATE):					return FErrorInfo(EErrorStage::CODE_GENERATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid architecture type for default compiler.");

	// Linker
	CASE_ERROR(NO_DEFAULT_LINKER_FOR_CURRENT_PLATFORM):		return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "No default linker for current platform.");
	CASE_ERROR(INVALID_SUBSYSTEM):							return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid subsystem type.");
	CASE_ERROR(INVALID_ARCH_FOR_LINK):						return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid architecture type for default linker.");
	CASE_ERROR(CANT_LINK_TO_TARGET_PLATFORM):				return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Default linker can't create executable for target platform. Try to link on selected platform with native linker or with custom cross-compiler.");
	
	}

	return FErrorInfo(EErrorStage::INITIALIZATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "!!!EMPTY MESSAGE!!!");
}
