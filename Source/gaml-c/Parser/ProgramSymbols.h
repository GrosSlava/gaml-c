// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "AST.h"
#include "../Token/Token.h"
#include "../Compiler/CompilerFileInfo.h"

#include <unordered_map>
#include <map>




/*
	Structures of language objects prototypes from modules.
	Each object(methods/functions...) realization will be in AST.
*/



/*
	Meta information about extracted program symbol for logging, etc.
*/
struct FSymbolMetaInfo
{
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
	VOID_ID = 0,
	//CLASS_ID - it is build in template
	UINT8_ID,
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
	//ARRAY_ID - it is build in template
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
	EAccessModifier AccessModifier = EAccessModifier::Public;

	bool IsExternC = false;
	EFunctionCallingConvention CallingConvention = EFunctionCallingConvention::DEFAULT;
	bool IsConst = false;
	bool IsMutable = false;
	bool IsStatic = false;
	bool IsInline = false;
	bool IsVirtual = false;
	bool IsOverride = false;
	bool IsAbstract = false;
	bool IsFinal = false;
	bool IsDeprecated = false;
	bool IsUnimplemented = false;

	int Align = -1;
};




/*
	Symbol types.
*/
enum class ETypePathSwitch
{
	UNDEFINED,
	EStandard,
	EClass,
	EFunctionSignature
};
/*
	Path to information about class.
*/
struct FClassTypePath
{
	/*
		Class compile name.
	*/
	std::string ClassCompileName = "";
};
/*
	Path to information about function signature.
*/
struct FFunctionSignaturePath
{
	/*
		Build-time ID of function signature.
	*/
	int FunctionSignatureID = -1;
};
/*
	Main struct to find path to type.
*/
struct FUserTypePath
{
	ETypePathSwitch PathSwitch = ETypePathSwitch::UNDEFINED;

	FClassTypePath ClassPath;
	FFunctionSignaturePath FunctionSignaturePath;
};





/*
	Information about variable.
*/
struct FVariableInfo
{
	/*
		Build-time type id.
	*/
	int TypeID = 0;
	/*
		Variable name.
	*/
	std::string VariableName = "";

	/*
		Context modifiers.
	*/
	FModfiers Modifiers;
	/*
		Meta info.
	*/
	FSymbolMetaInfo MetaInfo;
	/*
		AST for default value.
	*/
	AST DefaultValueTree;
};

/*
	Information about variable with compile-time data.
*/
struct FCompilingVariableInfo
{
	/*
		Variable info.
	*/
	FVariableInfo VariableInfo;
	/*
		This variable declared in current translating module.
	*/
	bool IsInThisModule = false;
};


/*
	Information about function signature.
*/
struct FFunctionSignatureInfo
{
	/*
		Info about function return.
	*/
	FVariableInfo Return;
	/*
		Info about function inputs.
	*/
	std::vector<FVariableInfo> Inputs;

	/*
		Context modifiers.
	*/
	FModfiers Modifiers;
	/*
		Meta info.
	*/
	FSymbolMetaInfo MetaInfo;
	/*
		AST for function static code.
	*/
	AST StaticCodeTree;
};

/*
	Information about function for compile-time.
	Function info is 2 parts: Signature and realization.
*/
struct FCompilingFunctionInfo
{
	/*
		Function realization AST.
	*/
	AST FunctionCodeTree;
};


/*
	Information about class.
*/
struct FClassInfo
{
	/*
		Class specialization.
	*/
	EClassType ClassType = EClassType::UNDEFINED;
	/*
		Array of parent build-time type IDs.
	*/
	std::vector<int> ParentTypesID;

	/*
		Context modifiers.
	*/
	FModfiers Modifiers;
	/*
		Meta info.
	*/
	FSymbolMetaInfo MetaInfo;

	/*
		After semantic analis there will be all variables from all parent classes.
		Will be supplemented by the current alignment.

		Key - variable name(same to in FVariableInfo).
		Value - Variable info.
	*/
	std::map<std::string, FVariableInfo> Variables;
	/*
		After semantic analis there will be full map of virtual functions.
		All functions have in first argument hidden "this".

		Key - function name.
		Value - compile function name.
	*/
	std::unordered_map<std::string, std::string> VirtualFunctionsTable;
};


/*
	Information about module.
*/
struct FModuleInfo
{
	/*
		Array of required modules full name(no packages).
	*/
	std::vector<std::string> RequiredModulesNames;
	/*
		Key - alias name.
		Value - module/package name.
	*/
	std::unordered_map<std::string, std::string> ImportedModuleNameAliases;

	/*
		Context modifiers.
	*/
	FModfiers Modifiers;
	/*
		Meta info.
	*/
	FSymbolMetaInfo MetaInfo;
};




/*
	All information about compiling unit. 
*/
struct FProgramInfo
{
public:

	inline FProgramInfo()
	{
		for( int i = 0; i < EStandardTypesID::StandardTypesID_MAX; ++i )
		{
			FUserTypePath LUserTypePath;
			LUserTypePath.PathSwitch = ETypePathSwitch::EStandard;
			TypesMap.push_back(LUserTypePath);
		}
	}



public:

	/*
		The name of the module, if we compile the module, otherwise we compile the executable file(tmp name "main"). 
	*/
	std::string MainModuleName = "";
	/*
		Key - module name.
		Value - module info.
	*/
	std::unordered_map<std::string, FModuleInfo> ImportedModulesInfo;


	//........................Declaration information from all modules............................//

	/*
		All used classes in program.

		Key - class compile name.
		Value - class info.
	*/
	std::unordered_map<std::string, FClassInfo> Classes;
	/*
		All used functions in program.
		Class methods are functions too.

		Key - function compile name.
		Value - function signature info.
	*/
	std::unordered_map<std::string, FFunctionSignatureInfo> Functions;

	/*
		Unique function signatures. Each new signature is new type with unique id.

		Key - signature id.
		Value - function signature.
	*/
	std::vector<FFunctionSignatureInfo> FunctionSignaturesTypesMap;
	/*
		Key - alias compile name.
		Value - type real id.
	*/
	std::unordered_map<std::string, size_t> TypeAliases;
	/*
		All types in compiling process will be cached here.
		Function signatures id too.

		Key - type id.
		Value - path to type.
	*/
	std::vector<FUserTypePath> TypesMap;

	//............................................................................................//


	//.............................Translation information........................................//

	/*
		Key - function compile name.
		Value - compiling function info.
	*/
	std::unordered_map<std::string, FCompilingFunctionInfo> CompilingFunctionsAST;
	/*
		Cached static variables from all classes.
	*/
	std::vector<FCompilingVariableInfo> CompilingStaticVariables;

	//............................................................................................//
};