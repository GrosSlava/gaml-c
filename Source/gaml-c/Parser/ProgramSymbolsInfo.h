// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Compiler/CompilerFileInfo.h"
#include "../Token/Token.h"




/*
	Meta information about extracted program symbol for logging, etc.
*/
struct FSymbolMetaInfo
{
public:

	inline FSymbolMetaInfo() { }
	FSymbolMetaInfo(const FGamlFileInfo& File, size_t Line) : DeclaredInFile(File), DeclaredAtLine(Line) { }



public:

	/*
		Fill meta info.
	*/
	inline void SetMetaInfo(const FGamlFileInfo& File, size_t Line)
	{
		DeclaredInFile = File;
		DeclaredAtLine = Line;
	}
	/*
		Fill meta info by token.
	*/
	inline void SetMetaInfo(const Token& InToken) { SetMetaInfo(InToken.GetFileInfo(), InToken.GetLine()); }




public:

	/*
		Info about the file in which the symbol is declared.
	*/
	FGamlFileInfo DeclaredInFile;
	/*
		Number of line in which the symbol declared(end line).
	*/
	size_t DeclaredAtLine = 0;
};




/*
	Standard access modifiers.
*/
enum class EAccessModifier : unsigned char
{
	Public,
	Protected,
	Private
};

/*
	Supported function calling conventions.
*/
enum class EFunctionCallingConvention : unsigned char
{
	DEFAULT, // default for current c-compiler
	CDECL,	 // equal to thiscall(this - first argument)
	STDCALL, // equal to pascal
	FASTCALL
};

/*
	Structure of OOP.
*/
enum class EClassType : unsigned char
{
	UNDEFINED,
	Struct,
	Interface,
	Object,
	Component,
	Enum
};

/*
	ID for standard types.
*/
enum EStandardTypesID
{
	//CLASS_ID - it is built-in template
	UINT8_ID = 0,
	UINT16_ID,
	UINT32_ID,
	UINT64_ID,
	INT8_ID,
	INT16_ID,
	INT32_ID,
	INT64_ID,
	ADDR_T_ID,
	FLOAT_ID,
	DOUBLE_ID,
	BOOL_ID,
	CHAR_ID,
	STRING_ID,
	//ARRAY_ID - it is built-in template
	VECTOR4D_ID,
	VECTOR3D_ID,
	VECTOR2D_ID,

	StandardTypesID_MAX
};

/*
	All modifiers. Each language object can have only specific range of them.
	So, analyser will check it.
*/
struct FModfiers
{
public:

	EAccessModifier AccessModifier = EAccessModifier::Public;

	bool IsExternC = false;
	EFunctionCallingConvention CallingConvention = EFunctionCallingConvention::DEFAULT;
	bool IsConst = false;
	bool IsMutable = false;
	bool IsStatic = false;
	bool IsVirtual = false;
	bool IsOverride = false;
	bool IsAbstract = false;
	bool IsFinal = false;
	bool IsDeprecated = false;
	bool IsUnimplemented = false;

	int Align = -1;



public:

	friend bool operator==(const FModfiers& A, const FModfiers& B)
	{
		// clang-format off
		return 
			A.AccessModifier == B.AccessModifier 		&& 
			A.IsExternC == B.IsExternC 					&&
			A.CallingConvention == B.CallingConvention 	&&
			A.IsConst == B.IsConst 						&&
			A.IsMutable == B.IsMutable 					&&
			A.IsStatic == B.IsStatic 					&&
			A.IsVirtual == B.IsVirtual 					&&
			A.IsOverride == B.IsOverride 				&&
			A.IsAbstract == B.IsAbstract 				&&
			A.IsFinal == B.IsFinal 						&&
			A.IsDeprecated == B.IsDeprecated 			&&
			A.IsUnimplemented == B.IsUnimplemented 		&&
			A.Align == B.Align;
		// clang-format on
	}

	friend bool operator!=(const FModfiers& A, const FModfiers& B) { return !(A == B); }
};
