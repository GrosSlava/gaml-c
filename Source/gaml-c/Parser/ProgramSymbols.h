// Copyright 2022 GrosSlava.

#pragma once

#include "AST.h"
#include "../Token/Token.h"
#include "../Compiler/CompilerFileInfo.h"

#include <string>
#include <vector>
#include <unordered_map>



/*
	Structures of language objects prototypes from modules.
	Each object(methods/functions...) realization will be in AST.
	Templates are instantiated into concrete objects after mention in code.
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
	ID for standard types.
*/
enum EStandardTypesID
{
	VOID_ID = 0,
	ANY_ID = 1,
	//CLASS_ID - it is build in template
	UINT8_ID = 2,
	UINT16_ID = 3,
	UINT32_ID = 4,
	UINT64_ID = 5,
	INT8_ID = 6,
	INT16_ID = 7,
	INT32_ID = 8,
	INT64_ID = 9,
	ADDR_T_ID = 10,
	FLOAT_ID = 11,
	DOUBLE_ID = 12,
	BOOL_ID = 13,
	CHAR_ID = 14,
	STRING_ID = 15,
	//ARRAY_ID - it is build in template
	VECTOR4D_ID = 16,
	VECTOR3D_ID = 17,
	VECTOR2D_ID = 18,

	StandardTypesID_MAX
};

enum class ETypePathSwitch
{
	UNDEFINED,
	EStandard,
	EClass,
	EFunctionSignature
};

struct FClassTypePath
{
	std::string ClassCompileName = "";
};

struct FFunctionSignaturePath
{
	int FunctionSignatureID = -1;
};

struct FUserTypePath
{
	ETypePathSwitch PathSwitch = ETypePathSwitch::UNDEFINED;

	FClassTypePath ClassPath;
	FFunctionSignaturePath FunctionSignaturePath;
};





enum class EAccessModifier
{
	Public,
	Protected,
	Private
};



struct FVariableInfo
{
	int TypeID = -1;
	std::string VariableName = "";

	EAccessModifier AccessModifier = EAccessModifier::Public;
	bool IsConst = false;
	bool IsMutable = false;
	bool IsDeprecated = false;
	bool IsStatic = false;

	AST DefaultValueTree;

	FSymbolMetaInfo MetaInfo;
};



enum class EFunctionCallingConvention
{
	DEFAULT, // default for current c-compiler
	CDECL,	 // equal to thiscall(this - first argument)
	STDCALL, // equal to pascal
	FASTCALL,
	THISCALL
};

struct FFunctionSignatureInfo
{
	EFunctionCallingConvention FunctionCallingConvention = EFunctionCallingConvention::DEFAULT;
	int ReturnTypeID = -1;
	bool ReturnTypeIsConst = false;
	std::vector<FVariableInfo> Inputs;

	EAccessModifier AccessModifier = EAccessModifier::Public;
	bool IsStatic = false;
	bool IsDeprecated = false;
	bool IsUnimplemented = false;
	bool IsInline = false;
	bool IsVirtual = false;
	bool IsConst = false;
	bool IsAbstract = false;
	bool IsOverride = false;
	bool IsFinal = false;
	bool IsExternC = false;

	AST StaticCodeTree;

	FSymbolMetaInfo MetaInfo;
};



enum class EClassType
{
	UNDEFINED,
	Struct,
	Interface,
	Object,
	Component,
	Enum
};

struct FClassInfo
{
	EClassType ClassType = EClassType::UNDEFINED;
	std::vector<int> ParentTypesID;
	int Align = -1;

	EAccessModifier AccessModifier = EAccessModifier::Public;
	bool IsAbstract = false;
	bool IsFinal = false;
	bool IsDeprecated = false;
	bool IsStatic = false;

	/*
		After semantic analis there will be all variables from all parent classes.
		Will be supplemented by the current alignment.

		Key - variable name(same to in FVariableInfo).
		Value - Variable info.
	*/
	std::unordered_map<std::string, FVariableInfo> Variables;
	/*
		After semantic analis there will be full map of virtual functions.
		All functions have in first argument hidden "this".

		Key - function name.
		Value - compile function name.
	*/
	std::unordered_map<std::string, std::string> VirtualFunctionsTable;

	FSymbolMetaInfo MetaInfo;
};



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

	bool IsDeprecated = false;
	bool IsStatic = false;

	FSymbolMetaInfo MetaInfo;
};





struct FTemplateCodeInfo
{
	std::vector<std::string> TemplateArguments;
	AST StaticCodeTree;
	std::vector<Token> TemplateCode;

	FSymbolMetaInfo MetaInfo;
};



struct FCompilingFunctionInfo
{
	AST FunctionCodeTree;
};

struct FCompilingVariableInfo
{
	FVariableInfo VariableInfo;
	bool IsInThisModule = false;
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
			FUserTypePath LUserTyePath;
			LUserTyePath.PathSwitch = ETypePathSwitch::EStandard;
			TypesMap.push_back(LUserTyePath);
		}
	}



public:

	/*
		Key - class compile name.
		Value - class info.
	*/
	std::unordered_map<std::string, FClassInfo> Classes;
	/*
		Key - function compile name.
		Value - function signature info.
	*/
	std::unordered_map<std::string, FFunctionSignatureInfo> Functions;



	/*
		The name of the module, if we compile the module, otherwise we compile the executable file(tmp name "main"). 
	*/
	std::string MainModuleName = "";
	/*
		Key - module name.
		Value - module info.
	*/
	std::unordered_map<std::string, FModuleInfo> ImportedModulesInfo;



	/*
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
		Key - type id.
		Value - path to type.

		All types in compiling process will be cached here.
		Function signatures id too.
	*/
	std::vector<FUserTypePath> TypesMap;



	/*
		Key - function compile name.
		Value - compiling function info.
	*/
	std::unordered_map<std::string, FCompilingFunctionInfo> CompilingFunctionsAST;
	/*
		Index of available ID for new lambda function in this module.
	*/
	int CompilingLambdaFunctionsNum = 0;
	/*
		All lambda functions take first argument "void*".

		Key - lambda function compile name.
		Value - lambda data context class compile name.
	*/
	std::unordered_map<std::string, std::string> CompilingLambdaFunctionsToContextData;
	/*
		Cached static variables from all classes.
	*/
	std::vector<FCompilingVariableInfo> CompilingStaticVariables;
	/*
		Key - template code compile name.
		Value - template code info.
	*/
	std::unordered_map<std::string, FTemplateCodeInfo> TemplateCode;
};