// Copyright 2022 - 2023 GrosSlava.

#include "Token.h"
#include "TokenHelperLibrary.h"

#include "../Compiler/CompilerOptions.h"
#include "../Logger/ErrorLogger.h"





void Token::DetermineTokenType(const FCompileOptions& CompileOptions)
{
	/*
		Table for token type hashing.
		Key - hash of token lexeme.
		Value - token type.
	*/
	static std::unordered_map<size_t, ETokenType> TokenTypeCache;


	// clang-format off
	if( FTokenHelperLibrary::IsIntegerLexeme(LexemeStr) )	{ Type = ETokenType::INTEGER_CONST;	return;	}
	if( FTokenHelperLibrary::IsFloatLexeme(LexemeStr) )		{ Type = ETokenType::FLOAT_CONST;	return; }
	if( FTokenHelperLibrary::IsDoubleLexeme(LexemeStr) )	{ Type = ETokenType::DOUBLE_CONST;	return; }
	if( FTokenHelperLibrary::IsCharLexeme(LexemeStr) )		{ Type = ETokenType::CHAR_CONST;	return; }
	if( FTokenHelperLibrary::IsStringLexeme(LexemeStr) )	{ Type = ETokenType::STRING_CONST;	return; }
	// clang-format on

	const size_t LLexemeHash = GetHash();
	auto LTokenTypeCacheIter = TokenTypeCache.find(LLexemeHash);
	if( LTokenTypeCacheIter != TokenTypeCache.end() )
	{
		Type = LTokenTypeCacheIter->second;
		return;
	}


	// clang-format off

#define CASE_LEXEME(Lexeme, TokenType) if( LexemeStr == Lexeme ) { Type = ETokenType::TokenType; TokenTypeCache.insert(std::pair(LLexemeHash, Type)); return; }

	CASE_LEXEME("<",						LESS)
	CASE_LEXEME(">",						GREATER)
	CASE_LEXEME("<=",						LESS_EQUAL)
	CASE_LEXEME(">=",						GREATER_EQUAL)
	CASE_LEXEME("==",						EQUAL)
	CASE_LEXEME("!=",						NOT_EQUAL)

	CASE_LEXEME("&&",						AND)
	CASE_LEXEME("||",						OR)
	CASE_LEXEME("!",						EXCLAMATION)

	CASE_LEXEME("&",						BINARY_AND)
	CASE_LEXEME("|",						BINARY_OR)
	CASE_LEXEME("~",						BINARY_INVERSE)
	CASE_LEXEME("^",						BINARY_XOR)
	CASE_LEXEME("<<",						BINARY_SHL)
	CASE_LEXEME(">>",						BINARY_SHR)

	CASE_LEXEME("+",						PLUS)
	CASE_LEXEME("-",						MINUS)
	CASE_LEXEME("*",						STAR)
	CASE_LEXEME("/",						SLASH)
	CASE_LEXEME("++",						INC)
	CASE_LEXEME("--",						DEC)
	CASE_LEXEME("%",						MOD)
	CASE_LEXEME("^^",						POW)

	CASE_LEXEME("sizeof",					SIZE_OF)
	CASE_LEXEME("typeof",					TYPE_OF)
	CASE_LEXEME("nameof",					NAME_OF)
	CASE_LEXEME("alignof",					ALIGN_OF)
	CASE_LEXEME("isfunction",				IS_FUNCTION)
	CASE_LEXEME("isstruct",					IS_STRUCT)
	CASE_LEXEME("isenum",					IS_ENUM)
	CASE_LEXEME("isinterface",				IS_INTERFACE)
	CASE_LEXEME("isobject",					IS_OBJECT)
	CASE_LEXEME("iscomponent",				IS_COMPONENT)
	CASE_LEXEME("issubclass",				IS_SUBCLASS)
	CASE_LEXEME("isinstance",				IS_INSTANCE)
	CASE_LEXEME("islambda",					IS_LAMBDA)
	CASE_LEXEME("isiterable",				IS_ITERABLE)
	CASE_LEXEME("isenumerable",				IS_ENUMERABLE)
	CASE_LEXEME("isabstract",				IS_ABSTRACT)
	CASE_LEXEME("isalias",					IS_ALIAS)
	CASE_LEXEME("in",						IN)
	CASE_LEXEME("is",						IS)
	CASE_LEXEME("as",						AS)
	CASE_LEXEME("addr",						ADDR)

	CASE_LEXEME("::",						NAMESPACE_ACCESS_OPERATOR)
	CASE_LEXEME("->",						RIGHT_ARROW)
	CASE_LEXEME("=>",						RIGHT_FAT_ARROW)
	CASE_LEXEME("~>",						RIGHT_WAVE_ARROW)

	CASE_LEXEME("{",						LBRA)
	CASE_LEXEME("}",						RBRA)
	CASE_LEXEME("(",						LPAR)
	CASE_LEXEME(")",						RPAR)
	CASE_LEXEME("[",						LSQR)
	CASE_LEXEME("]",						RSQR)
	CASE_LEXEME("<|",						LTRI)
	CASE_LEXEME("|>",						RTRI)

	CASE_LEXEME("=",						ASSIGN)
	CASE_LEXEME("+=",						ADD_ASSIGN)
	CASE_LEXEME("-=",						SUB_ASSIGN)
	CASE_LEXEME("*=",						MUL_ASSIGN)
	CASE_LEXEME("/=",						DIV_ASSIGN)
	CASE_LEXEME("%=",						MOD_ASSIGN)
	CASE_LEXEME("^^=",						POW_ASSIGN)
	CASE_LEXEME("&=",						BINARY_AND_ASSIGN)
	CASE_LEXEME("|=",						BINARY_OR_ASSIGN)
	CASE_LEXEME("~=",						BINARY_INVERSE_ASSIGN)
	CASE_LEXEME("^=",						BINARY_XOR_ASSIGN)
	CASE_LEXEME("<<=",						BINARY_SHL_ASSIGN)
	CASE_LEXEME(">>=",						BINARY_SHR_ASSIGN)

	CASE_LEXEME("//",						LINE_COMMENT)
	CASE_LEXEME("/*",						BLOCK_COMMENT_START)
	CASE_LEXEME("*/",						BLOCK_COMMENT_END)
	CASE_LEXEME("***",						DESCRIPTION_BLOCK)

	CASE_LEXEME(";",						SEMICOLON)
	CASE_LEXEME(":",						COLON)
	CASE_LEXEME(",",						COMMA)
	CASE_LEXEME(".",						POINT)
	CASE_LEXEME("?",						QUESTION)
	CASE_LEXEME("...",						VARIADIC)
	CASE_LEXEME("$",						DOLLAR)
	CASE_LEXEME("#",						SHARP)
	CASE_LEXEME("@",						DOG)

	CASE_LEXEME("true",						TRUE_CONST)
	CASE_LEXEME("false",					FALSE_CONST)
	
	CASE_LEXEME("class",					CLASS)
	CASE_LEXEME("uint8",					UINT8)
	CASE_LEXEME("uint16",					UINT16)
	CASE_LEXEME("uint32",					UINT32)
	CASE_LEXEME("uint64",					UINT64)
	CASE_LEXEME("int8",						INT8)
	CASE_LEXEME("int16",					INT16)
	CASE_LEXEME("int32",					INT32)
	CASE_LEXEME("int64",					INT64)
	CASE_LEXEME("addr_t",					ADDR_T)
	CASE_LEXEME("float",					FLOAT)
	CASE_LEXEME("double",					DOUBLE)
	CASE_LEXEME("bool",						BOOL)
	CASE_LEXEME("char",						CHAR)
	CASE_LEXEME("string",					STRING)
	CASE_LEXEME("array",					ARRAY)
	CASE_LEXEME("vector4d",					VECTOR4D)
	CASE_LEXEME("vector3d",					VECTOR3D)
	CASE_LEXEME("vector2d",					VECTOR2D)

	CASE_LEXEME("cast",						CAST)
	CASE_LEXEME("unsafe_cast",				UNSAFE_CAST)

	CASE_LEXEME("assert",					ASSERT)
	CASE_LEXEME("static_assert",			STATIC_ASSERT)
	CASE_LEXEME("static_error",				STATIC_ERROR)
	CASE_LEXEME("static_warning",			STATIC_WARNING)
	CASE_LEXEME("static_message",			STATIC_MESSAGE)

	CASE_LEXEME("do",						DO)
	CASE_LEXEME("while",					WHILE)
	CASE_LEXEME("for",						FOR)
	CASE_LEXEME("foreach",					FOREACH)
	CASE_LEXEME("break",					BREAK)
	CASE_LEXEME("continue",					CONTINUE)

	CASE_LEXEME("if",						IF)
	CASE_LEXEME("elif",						ELIF)
	CASE_LEXEME("else",						ELSE)
	CASE_LEXEME("switch",					SWITCH)
	CASE_LEXEME("switch_all",				SWITCH_ALL)
	CASE_LEXEME("case",						CASE)
	CASE_LEXEME("default",					DEFAULT)

	CASE_LEXEME("const",					CONST)
	CASE_LEXEME("mut",						MUTABLE)
	CASE_LEXEME("static",					STATIC)
	CASE_LEXEME("virtual",					VIRTUAL)
	CASE_LEXEME("override",					OVERRIDE)
	CASE_LEXEME("abstract",					ABSTRACT)
	CASE_LEXEME("final",					FINAL)
	CASE_LEXEME("deprecated",				DEPRECATED)
	CASE_LEXEME("unimplemented",			UNIMPLEMENTED)
	CASE_LEXEME("align",					ALIGN)

	CASE_LEXEME("func",						FUNCTION)
	CASE_LEXEME("lambda",					LAMBDA)
	CASE_LEXEME("param",					PARAM)
	CASE_LEXEME("return",					RETURN)
	CASE_LEXEME("extern_c",					EXTERN_C)
	CASE_LEXEME("cdecl",					CDECL)
	CASE_LEXEME("stdcall",					STDCALL)
	CASE_LEXEME("fastcall",					FASTCALL)

	CASE_LEXEME("var",						VAR)

	CASE_LEXEME("struct",					STRUCT)
	CASE_LEXEME("enum",						ENUM)
	CASE_LEXEME("interface",				INTERFACE)
	CASE_LEXEME("object",					OBJECT)
	CASE_LEXEME("component",				COMPONENT)
	CASE_LEXEME("this",						THIS)
	CASE_LEXEME("super",					SUPER)
	CASE_LEXEME("None",						NONE)
	CASE_LEXEME("using",					USING)

	CASE_LEXEME("public",					PUBLIC)
	CASE_LEXEME("protected",				PROTECTED)
	CASE_LEXEME("private",					PRIVATE)

	CASE_LEXEME("import",					IMPORT)
	CASE_LEXEME("module",					MODULE)
	CASE_LEXEME("implement",				IMPLEMENT)

	if( FTokenHelperLibrary::IsCorrectIdentifier(LexemeStr) ) { Type = ETokenType::IDENTIFIER; return; }
	// clang-format on

	if( LexemeStr.empty() )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_LEXEME, FileInfo.GetFileFullPath(), Line, Pos, 0, CompileOptions);
	}
	else
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_LEXEME, FileInfo.GetFileFullPath(), Line, Pos, LexemeStr.size() - 1, CompileOptions);
	}
}

std::string Token::GetTypeAsStr() const noexcept
{
	// clang-format off
#define CASE_TOKEN(TokenType, Str) case ETokenType::TokenType: return Str;

	switch( Type )
	{
	CASE_TOKEN(IDENTIFIER,					"identifier")
	
	CASE_TOKEN(LESS,						"less")
	CASE_TOKEN(GREATER,						"greater")
	CASE_TOKEN(LESS_EQUAL,					"less equal")
	CASE_TOKEN(GREATER_EQUAL,				"greater equal")
	CASE_TOKEN(EQUAL,						"equal")
	CASE_TOKEN(NOT_EQUAL,					"not equal")

	CASE_TOKEN(AND,							"and")
	CASE_TOKEN(OR,							"or")
	CASE_TOKEN(EXCLAMATION,					"exclamation")

	CASE_TOKEN(BINARY_AND,					"binary_and")
	CASE_TOKEN(BINARY_OR,					"binary_or")
	CASE_TOKEN(BINARY_INVERSE,				"binary_inverse")
	CASE_TOKEN(BINARY_XOR,					"binary_xor")
	CASE_TOKEN(BINARY_SHL,					"binary_shl")
	CASE_TOKEN(BINARY_SHR,					"binary_shr")

	CASE_TOKEN(PLUS,						"plus")
	CASE_TOKEN(MINUS,						"minus")
	CASE_TOKEN(STAR,						"star")
	CASE_TOKEN(SLASH,						"slash")
	CASE_TOKEN(INC,							"inc")
	CASE_TOKEN(DEC,							"dec")
	CASE_TOKEN(MOD,							"mod")
	CASE_TOKEN(POW,							"pow")

	CASE_TOKEN(SIZE_OF,						"size_of")
	CASE_TOKEN(TYPE_OF,						"type_of")
	CASE_TOKEN(NAME_OF,						"name_of")
	CASE_TOKEN(ALIGN_OF,					"align_of")
	CASE_TOKEN(IS_FUNCTION,					"is_function")
	CASE_TOKEN(IS_STRUCT,					"is_struct")
	CASE_TOKEN(IS_ENUM,						"is_enum")
	CASE_TOKEN(IS_INTERFACE,				"is_interface")
	CASE_TOKEN(IS_OBJECT,					"is_object")
	CASE_TOKEN(IS_COMPONENT,				"is_component")
	CASE_TOKEN(IS_SUBCLASS,					"isvsubclass")
	CASE_TOKEN(IS_INSTANCE,					"is_instance")
	CASE_TOKEN(IS_LAMBDA,					"is_lambda")
	CASE_TOKEN(IS_ITERABLE,					"is_iterable")
	CASE_TOKEN(IS_ENUMERABLE,				"is_enumerable")
	CASE_TOKEN(IS_ABSTRACT,					"is_abstract")
	CASE_TOKEN(IS_ALIAS,					"is_alias")
	CASE_TOKEN(IN,							"in")
	CASE_TOKEN(IS,							"is")
	CASE_TOKEN(AS,							"as")
	CASE_TOKEN(ADDR,						"addr")

	CASE_TOKEN(NAMESPACE_ACCESS_OPERATOR,	"namespace_access_operator")
	CASE_TOKEN(RIGHT_ARROW,					"right_arrow")
	CASE_TOKEN(RIGHT_FAT_ARROW,				"right_fat_arrow")
	CASE_TOKEN(RIGHT_WAVE_ARROW,			"right_wavevarrow")

	CASE_TOKEN(LBRA,						"lbra")
	CASE_TOKEN(RBRA,						"rbra")
	CASE_TOKEN(LPAR,						"lpar")
	CASE_TOKEN(RPAR,						"rpar")
	CASE_TOKEN(LSQR,						"lsqr")
	CASE_TOKEN(RSQR,						"rsqr")
	CASE_TOKEN(LTRI,						"ltri")
	CASE_TOKEN(RTRI,						"rtri")

	CASE_TOKEN(ASSIGN,						"assign")
	CASE_TOKEN(ADD_ASSIGN,					"add_assign")
	CASE_TOKEN(SUB_ASSIGN,					"sub_assign")
	CASE_TOKEN(MUL_ASSIGN,					"mul_assign")
	CASE_TOKEN(DIV_ASSIGN,					"div_assign")
	CASE_TOKEN(MOD_ASSIGN,					"mod_assign")
	CASE_TOKEN(POW_ASSIGN,					"pow_assign")
	CASE_TOKEN(BINARY_AND_ASSIGN,			"binary_'and'_assign")
	CASE_TOKEN(BINARY_OR_ASSIGN,			"binary_'or'_assign")
	CASE_TOKEN(BINARY_INVERSE_ASSIGN,		"binary_'inverse'_assign")
	CASE_TOKEN(BINARY_XOR_ASSIGN,			"binary_'xor'_assign")
	CASE_TOKEN(BINARY_SHL_ASSIGN,			"binary_'shl'_assign")
	CASE_TOKEN(BINARY_SHR_ASSIGN,			"binary_'shr'_assign")

	CASE_TOKEN(LINE_COMMENT,				"line_comment")
	CASE_TOKEN(BLOCK_COMMENT_START,			"block_comment_start")
	CASE_TOKEN(BLOCK_COMMENT_END,			"block_comment_end")
	CASE_TOKEN(DESCRIPTION_BLOCK,			"description_block")

	CASE_TOKEN(SEMICOLON,					"semicolon")
	CASE_TOKEN(COLON,						"colon")
	CASE_TOKEN(COMMA,						"comma")
	CASE_TOKEN(POINT,						"point")
	CASE_TOKEN(QUESTION,					"question")
	CASE_TOKEN(VARIADIC,					"variadic")
	CASE_TOKEN(DOLLAR,						"dollar")
	CASE_TOKEN(SHARP,						"sharp")
	CASE_TOKEN(DOG,							"dog")

	CASE_TOKEN(INTEGER_CONST,				"integer_const")
	CASE_TOKEN(FLOAT_CONST,					"float_const")
	CASE_TOKEN(DOUBLE_CONST,				"double_const")
	CASE_TOKEN(CHAR_CONST,					"char_const")
	CASE_TOKEN(STRING_CONST,				"string_const")
	CASE_TOKEN(TRUE_CONST,					"true_const")
	CASE_TOKEN(FALSE_CONST,					"false_const")

	CASE_TOKEN(CLASS,						"class")
	CASE_TOKEN(UINT8,						"uint8")
	CASE_TOKEN(UINT16,						"uint16")
	CASE_TOKEN(UINT32,						"uint32")
	CASE_TOKEN(UINT64,						"uint64")
	CASE_TOKEN(INT8,						"int8")
	CASE_TOKEN(INT16,						"int16")
	CASE_TOKEN(INT32,						"int32")
	CASE_TOKEN(INT64,						"int64")
	CASE_TOKEN(ADDR_T,						"addr_t")
	CASE_TOKEN(FLOAT,						"float")
	CASE_TOKEN(DOUBLE,						"double")
	CASE_TOKEN(BOOL,						"bool")
	CASE_TOKEN(CHAR,						"char")
	CASE_TOKEN(STRING,						"string")
	CASE_TOKEN(ARRAY,						"array")
	CASE_TOKEN(VECTOR4D,					"vector4d")
	CASE_TOKEN(VECTOR3D,					"vector3d")
	CASE_TOKEN(VECTOR2D,					"vector2d")

	CASE_TOKEN(CAST,						"cast")
	CASE_TOKEN(UNSAFE_CAST,					"unsafe_cast")

	CASE_TOKEN(ASSERT,						"assert")
	CASE_TOKEN(STATIC_ASSERT,				"static_assert")
	CASE_TOKEN(STATIC_ERROR,				"static_error")
	CASE_TOKEN(STATIC_WARNING,				"static_warning")
	CASE_TOKEN(STATIC_MESSAGE,				"static_message")
		
	CASE_TOKEN(DO,							"do")
	CASE_TOKEN(WHILE,						"while")
	CASE_TOKEN(FOR,							"for")
	CASE_TOKEN(FOREACH,						"foreach")
	CASE_TOKEN(BREAK,						"break")
	CASE_TOKEN(CONTINUE,					"continue")

	CASE_TOKEN(IF,							"if")
	CASE_TOKEN(ELIF,						"elif")
	CASE_TOKEN(ELSE,						"else")
	CASE_TOKEN(SWITCH,						"switch")
	CASE_TOKEN(SWITCH_ALL,					"switch all")
	CASE_TOKEN(CASE,						"case")
	CASE_TOKEN(DEFAULT,						"default")

	CASE_TOKEN(CONST,						"const")
	CASE_TOKEN(MUTABLE,						"mutable")
	CASE_TOKEN(STATIC,						"static")
	CASE_TOKEN(VIRTUAL,						"virtual")
	CASE_TOKEN(OVERRIDE,					"override")
	CASE_TOKEN(ABSTRACT,					"abstract")
	CASE_TOKEN(FINAL,						"final")
	CASE_TOKEN(DEPRECATED,					"deprecated")
	CASE_TOKEN(UNIMPLEMENTED,				"unimplemented")
	CASE_TOKEN(ALIGN,						"align")

	CASE_TOKEN(FUNCTION,					"function")
	CASE_TOKEN(LAMBDA,						"lambda")
	CASE_TOKEN(PARAM,						"param")
	CASE_TOKEN(RETURN,						"return")
	CASE_TOKEN(EXTERN_C,					"extern_c")
	CASE_TOKEN(CDECL,						"cdecl")
	CASE_TOKEN(STDCALL,						"stdcall")
	CASE_TOKEN(FASTCALL,					"fastcall")

	CASE_TOKEN(VAR,							"var")

	CASE_TOKEN(STRUCT,						"struct")
	CASE_TOKEN(ENUM,						"enum")
	CASE_TOKEN(INTERFACE,					"interface")
	CASE_TOKEN(OBJECT,						"object")
	CASE_TOKEN(COMPONENT,					"component")
	CASE_TOKEN(THIS,						"this")
	CASE_TOKEN(SUPER,						"super")
	CASE_TOKEN(NONE,						"none")
	CASE_TOKEN(USING,						"using")

	CASE_TOKEN(PUBLIC,						"public")
	CASE_TOKEN(PROTECTED,					"protected")
	CASE_TOKEN(PRIVATE,						"private")

	CASE_TOKEN(IMPORT,						"import")
	CASE_TOKEN(MODULE,						"module")
	CASE_TOKEN(IMPLEMENT,					"implement")
	}
	// clang-format on

	return "";
}