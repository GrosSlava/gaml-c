// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "AST/AST.h"
#include "ProgramSymbolsInfo.h"




/*
	Symbol types.
*/
enum class ETypePathSwitch
{
	UNDEFINED,
	Standard,
	Class,
	FunctionSignature
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
		Info about function inputs.

		Key - variable name(same to in FVariableInfo).
		Value - Variable info.
	*/
	std::vector<FVariableInfo> Inputs;
	/*
		Info about function returns.

		Key - variable name(same to in FVariableInfo).
		Value - Variable info.
	*/
	std::vector<FVariableInfo> Returns;

	/*
		Context modifiers.
	*/
	FModfiers Modifiers;

	/*
		AST for function static code.
	*/
	AST StaticCodeTree;
};

/*
	Information about function.
*/
struct FFunctionInfo
{
	/*
		Compile name of context class.
		Empty if declared in global space.
	*/
	std::string ClassDeclarationNamespace = "";
	/*
		Function signature info.
	*/
	FFunctionSignatureInfo SignatureInfo;

	/*
		Meta info.
	*/
	FSymbolMetaInfo MetaInfo;
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
	Information about static assert.
*/
struct FStaticAssertInfo
{
	/*
		Assert AST.
	*/
	AST CodeTree;

	/*
		Context module compile name.
	*/
	std::string ModuleContextName = "";
	/*
		Context class compile name.
	*/
	std::string ClassContextName = "";
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
			LUserTypePath.PathSwitch = ETypePathSwitch::Standard;
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
		Value - function info.
	*/
	std::unordered_map<std::string, FFunctionInfo> Functions;

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


	//.................................Compile time actions.......................................//

	/*
		Array of all static asserts from all imported modules.
	*/
	std::vector<FStaticAssertInfo> StaticAsserts;

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
