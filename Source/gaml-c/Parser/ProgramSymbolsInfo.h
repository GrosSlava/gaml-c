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
	Compile names of standard types.
*/
struct EStandardTypesName
{
	const static std::string UINT8_Name;
	const static std::string UINT16_Name;
	const static std::string UINT32_Name;
	const static std::string UINT64_Name;
	const static std::string INT8_Name;
	const static std::string INT16_Name;
	const static std::string INT32_Name;
	const static std::string INT64_Name;
	const static std::string ADDR_T_Name;
	const static std::string FLOAT_Name;
	const static std::string DOUBLE_Name;
	const static std::string BOOL_Name;
	const static std::string CHAR_Name;
	const static std::string STRING_Name;
	const static std::string VECTOR4D_Name;
	const static std::string VECTOR3D_Name;
	const static std::string VECTOR2D_Name;
};

/*
	Kind of type for switch.
*/
enum class ETypeKind
{
	UNDEFINED = 0,
	Standard,
	Class,
	FunctionPointer,
	AnyPointer
};
struct FTypeInfo
{
public:

	inline FTypeInfo() { }
	inline FTypeInfo(ETypeKind InTypeKind, const std::string& InTypeCompileName) : TypeKind(InTypeKind), TypeCompileName(InTypeCompileName) { }

public:

	/*
		Kind of type for switch.
	*/
	ETypeKind TypeKind = ETypeKind::UNDEFINED;

	/*
		Compile name of type.
		Empty for AnyPointer or Class with undefined name.
	*/
	std::string TypeCompileName = "";
	/*
		Potential names if name can't be exactly detected.
	*/
	std::vector<std::string> PotentialNames;



public:

	friend bool operator==(const FTypeInfo& A, const FTypeInfo& B)
	{
		if( A.PotentialNames.size() != A.PotentialNames.size() ) return false;

		auto AIter = A.PotentialNames.begin();
		auto BIter = B.PotentialNames.begin();

		while( AIter != A.PotentialNames.end() )
		{
			if( *AIter != *BIter )
			{
				return false;
			}

			++AIter;
			++BIter;
		}

		return A.TypeKind == B.TypeKind && A.TypeCompileName == B.TypeCompileName;
	}

	friend bool operator!=(const FTypeInfo& A, const FTypeInfo& B) { return !(A == B); }
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
