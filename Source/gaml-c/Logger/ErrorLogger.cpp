// Copyright 2022 - 2023 GrosSlava.

#include "ErrorLogger.h"

#include "../Token/Token.h"

#include <fstream>





// clang-format off
void FErrorLogger::Raise
(
	EErrorMessageType MessageType, 
	const std::string& File, size_t Line, size_t Pos, size_t UnderlineLength, 
	const FCompileOptions& CompileOptions
)
// clang-format on
{
	FErrorInfo LErrorInfo = GetErrorInfo(MessageType);


	if( CompileOptions.ConvertWarningsToErrors )
	{
		LErrorInfo.ErrorType = EErrorType::ERROR;
	}

	// clang-format off
	if( 
		LErrorInfo.ErrorType == EErrorType::WARNING && 
		(CompileOptions.WarningLevel == EWarningLevel::NoWarnings || LErrorInfo.WarningLevel > CompileOptions.WarningLevel)
	   ) return;
	// clang-format on

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

			FCompileLogger::MessageError(LLineStr);

			if( Pos > 0 )
			{
				std::string LPosStr = "";
				LPosStr.resize(std::max(LLineStr.size(), Pos), ' ');
				LPosStr[Pos - 1] = '^'; // we are indexing position in row from 1

				for( size_t i = Pos; i < Pos + UnderlineLength && i < LPosStr.size(); ++i )
				{
					LPosStr[i] = '~';
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

void FErrorLogger::Raise(EErrorMessageType MessageType, const Token& CTXToken, const FCompileOptions& CompileOptions)
{
	Raise(MessageType, CTXToken.GetFileInfo().GetFileFullPath(), CTXToken.GetLine(), CTXToken.GetPos(), CTXToken.GetLexeme().size() - 1, CompileOptions);
}

FErrorInfo FErrorLogger::GetErrorInfo(EErrorMessageType MessageType)
{
#define CASE_ERROR(Type) case EErrorMessageType::Type

	// clang-format off
	switch( MessageType )
	{
	// Initialization
	CASE_ERROR(NO_PATH_TO_COMPILER):						return FErrorInfo(EErrorStage::INITIALIZATION, EErrorType::WARNING, EWarningLevel::SeriousWarning, "No path to compiler.");
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
	CASE_ERROR(STATE_STACK_EMPTY):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "State stack is empty.");
	CASE_ERROR(UNEXPECTED_EXPRESSION):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Unexpected expression.");
	CASE_ERROR(UNEXPECTED_IDENTIFIER):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Unexpected identifier.");
	CASE_ERROR(EXPECTED_IDENTIFIER):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected identifier.");
	CASE_ERROR(EXPECTED_SEMICOLON):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected ';'.");
	CASE_ERROR(EXPECTED_ASSIGN):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '='.");
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
	CASE_ERROR(EXPECTED_DESCRIPTION_BLOCK):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected '***'.");
	CASE_ERROR(EXPECTED_FUNCTION_RETURN_TYPE):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected return type.");
	CASE_ERROR(EXPECTED_FUNCTION_NAME):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected function name.");
	CASE_ERROR(EXPECTED_ARGUMENT_TYPE):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected argument type.");
	CASE_ERROR(EXPECTED_ARGUMENT_NAME):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected argument name.");
	CASE_ERROR(EXPECTED_ALIAS_NAME):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected alias name.");
	CASE_ERROR(EXPECTED_CLASS_NAME):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected class name.");
	CASE_ERROR(EXPECTED_CONTROL_OPERATOR):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Expected control operator.");
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
	CASE_ERROR(IMPORTING_MAIN_MODULE):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Main module can't be imported.");
	CASE_ERROR(IMPORTING_IMPLEMENT_MODULE):					return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Implement module can only main module.");
	CASE_ERROR(MODULE_ALIAS_CONTAINS_INVALID_CHAR):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Module alias name contains invalid char.");
	CASE_ERROR(DOUBLE_MODIFIER):							return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Double modifier.");
	CASE_ERROR(RETURN_TYPE_DOUBLE_MODIFIER):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Return type double modifier.");
	CASE_ERROR(MEMBER_DOUBLE_MODIFIER):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Member double modifier.");
	CASE_ERROR(FUNCTION_DECLARATION_NOT_FOUND):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function declaration not found.");
	CASE_ERROR(FUNCTION_ARGUMENT_NAME_MISMATCH):			return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Mismatch of the function declaration argument name.");
	CASE_ERROR(FUNCTION_DESCRIPTION_MISMATCH):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Mismatch of the function description.");
	CASE_ERROR(FUNCTION_STATIC_CODE_OVERRIDE):				return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Function static code override.");
	CASE_ERROR(CLASS_NAME_NOT_FOUND):						return FErrorInfo(EErrorStage::PARSER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Class name was not found.");
	
	//Code generator
	CASE_ERROR(NO_DEFAULT_COMPILER_FOR_CURRENT_PLATFORM):	return FErrorInfo(EErrorStage::CODE_GENERATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "No default compiler for current platform.");
	CASE_ERROR(UNSUPPORTED_CODE_GENERATOR):					return FErrorInfo(EErrorStage::CODE_GENERATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "Unsupported code generator.");
	CASE_ERROR(INVALID_ARCH_FOR_GENERATE):					return FErrorInfo(EErrorStage::CODE_GENERATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid architecture type for default compiler.");
	CASE_ERROR(INVALID_GENERATION_EXTENSION):				return FErrorInfo(EErrorStage::CODE_GENERATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid generation file extension.");

	// Linker
	CASE_ERROR(NO_DEFAULT_LINKER_FOR_CURRENT_PLATFORM):		return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "No default linker for current platform.");
	CASE_ERROR(INVALID_SUBSYSTEM):							return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid subsystem type.");
	CASE_ERROR(INVALID_ARCH_FOR_LINK):						return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Invalid architecture type for default linker.");
	CASE_ERROR(CANT_LINK_TO_TARGET_PLATFORM):				return FErrorInfo(EErrorStage::LINKER, EErrorType::ERROR, EWarningLevel::NoWarnings, "Default linker can't create executable for target platform. Try to link on selected platform with native linker or with custom cross-compiler.");
	
	}
	// clang-format on

	return FErrorInfo(EErrorStage::INITIALIZATION, EErrorType::ERROR, EWarningLevel::NoWarnings, "!!!EMPTY MESSAGE!!!");
}
