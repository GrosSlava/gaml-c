// Copyright 2022 GrosSlava.

#pragma once




/*
	All language tokens.
*/
enum class ETokenType
{
	IDENTIFIER,

	// relationship operators
	LESS,                       // <
	GREATER,                    // >
	LESS_EQUAL,                 // <=
	GREATER_EQUAL,              // >=
	EQUAL,                      // ==
	NOT_EQUAL,                  // !=

	// logical operators
	AND,                        // &&
	OR,                         // ||
	EXCLAMATION,                // !

	// binary operators
	BINARY_AND,                 // &
	BINARY_OR,                  // |
	BINARY_INVERSE,             // ~
	BINARY_XOR,                 // ^
	BINARY_SHL,                 // <<
	BINARY_SHR,                 // >>

	// math operators
	PLUS,                       // +
	MINUS,                      // -
	STAR,                       // *
	SLASH,                      // /
	INC,                        // ++
	DEC,                        // --
	MOD,                        // %
	POW,						// ^^

	// algorithm operators
	SIZE_OF,                    // sizeof
	TYPE_OF,                    // typeof
	NAME_OF,                    // nameof
	ALIGN_OF,                   // alignof
	ALIGN_AS,					// alignas
	IS_FUNCTION,                // isfunction
	IS_STRUCT,					// isstruct
	IS_ENUM,					// isenum
	IS_INTERFACE,				// isinterface
	IS_OBJECT,					// isobject
	IS_COMPONENT,				// iscomponent
	IS_SUBCLASS,                // issubclass
	IS_INSTANCE,                // isinstance
	IN,                         // in
	IS,                         // is
	AS,							// as
	ADDR,                       // addr

	// code access operators
	NAMESPACE_ACCESS_OPERATOR,  // ::
	RIGHT_ARROW,				// ->

	// brackets
	LBRA,                       // {
	RBRA,                       // }
	LPAR,                       // (
	RPAR,                       // )
	LSQR,                       // [
	RSQR,                       // ]
	LTRI,						// <|
	RTRI,						// |>

	// assign operators
	ASSIGN,                     // =
	ADD_ASSIGN,                 // +=
	SUB_ASSIGN,                 // -=
	MUL_ASSIGN,                 // *=
	DIV_ASSIGN,                 // /=
	MOD_ASSIGN,                 // %=
	POW_ASSIGN,                 // ^^=
	BINARY_AND_ASSIGN,          // &=
	BINARY_OR_ASSIGN,           // |=
	BINARY_XOR_ASSIGN,          // ^=
	BINARY_SHL_ASSIGN,          // <<=
	BINARY_SHR_ASSIGN,          // >>=



	// comment
	LINE_COMMENT,               // //
	BLOCK_COMMENT_START,        // /*
	BLOCK_COMMENT_END,          // */

	// other symbols
	SEMICOLON,                  // ;
	COLON,                      // :
	COMMA,                      // ,
	POINT,                      // .
	QUESTION,                   // ?
	VARIADIC,                   // ...
	DOLLAR,						// $
	SHARP,						// #



	// code constants
	INTEGER_CONST,              // 1, 2, 3..., 0xff, 11101b
	FLOAT_CONST,                // 1.34f, 0.110f, 123.456e3f, 123.456E3f, 123.456e+3f, 123.456E+3f, 123.456e-3f, 123.456E-3f
	DOUBLE_CONST,               // 1.34, 0.110, 123.456e3, 123.456E3, 123.456e+3, 123.456E+3, 123.456e-3, 123.456E-3
	CHAR_CONST,                 // 'a'
	STRING_CONST,               // "abcd"
	TRUE_CONST,                 // true
	FALSE_CONST,                // false

	// types
	VOID,                       // void
	ANY,						// any
	CLASS,						// class
	UINT8,                      // uint8
	UINT16,                     // uint16
	UINT32,                     // uint32
	UINT64,                     // uint64
	INT8,                       // int8
	INT16,                      // int16
	INT32,                      // int32
	INT64,                      // int64
	ADDR_T,						// addr_t
	FLOAT,                      // float
	DOUBLE,                     // double
	BOOL,                       // bool
	CHAR,                       // char
	STRING,                     // string
	ARRAY,                      // array
	VECTOR4D,                   // vector4d
	VECTOR3D,                   // vector3d
	VECTOR2D,                   // vector2d



	// cycles
	DO,							// do
	WHILE,                      // while
	FOR,                        // for
	FOREACH,                    // foreach
	BREAK,                      // break
	CONTINUE,                   // continue

	// conditions
	IF,                         // if
	ELSE,                       // else
	SWITCH,                     // switch
	SWITCH_ALL,					// switch_all
	CASE,                       // case
	DEFAULT,                    // default

	// function
	FUNCTION,                   // func
	LAMBDA,                     // lambda
	RETURN,                     // return
	EXTERN_C,					// extern_c
	CDECL,						// cdecl
	STDCALL,					// stdcall
	FASTCALL,					// fastcall
	THISCALL,					// thiscall

	// specifiers
	CONST,                      // const
	MUTABLE,					// mut
	STATIC,                     // static
	INLINE,                     // inline         
	VIRTUAL,                    // virtual
	OVERRIDE,                   // override
	ABSTRACT,					// abstract
	FINAL,                      // final
	TEMPLATE,                   // template
	DEPRECATED,					// deprecated
	UNIMPLEMENTED,				// unimplemented

	// casts
	CAST,                       // cast
	UNSAFE_CAST,                // unsafe_cast

	// asserts
	ASSERT,                     // assert
	STATIC_ASSERT,              // static_assert
	STATIC_ERROR,				// static_error
	STATIC_WARNING,				// static_warning
	STATIC_MESSAGE,				// static_message

	// objects
	STRUCT,                     // struct
	ENUM,                       // enum
	INTERFACE,                  // interface
	OBJECT,                     // object
	COMPONENT,                  // component
	THIS,                       // this
	SUPER,                      // super
	NONE,						// None
	USING,						// using

	// access modifiers
	PUBLIC,                     // public
	PROTECTED,                  // protected
	PRIVATE,                    // private
	PUBLIC_BLOCK,               // public:
	PROTECTED_BLOCK,            // protected:
	PRIVATE_BLOCK,              // private:

	// modules
	IMPORT,                     // import
	MODULE,                     // module
	IMPLEMENT					// implement
};

