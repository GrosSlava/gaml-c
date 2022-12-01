// Copyright 2022 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"

#include "../ProgramSymbols.h"
#include "../../Token/Token.h"




enum class EStateContextType : unsigned char
{
	Global,
	InClass
};



struct FModuleDeclarationContext
{
public:

	inline void Clear() noexcept
	{
		ModuleInfo = FModuleInfo();
		ModulePath.clear();
	}


public:

	FModuleInfo ModuleInfo;
	std::vector<std::string> ModulePath;
};

struct FModuleImplementingContext
{
public:

	inline void Clear() noexcept
	{ 
		ModulePath.clear();
	}


public:

	std::vector<std::string> ModulePath;
};

struct FModuleImportingContext
{
public:

	inline void Clear() noexcept
	{
		ModulePath.clear();
		AliasName.clear();
	}


public:

	std::vector<std::string> ModulePath;
	std::string AliasName = "";
};



enum class EDescriptionContext : unsigned char
{
	UNDEFINED,
	Param,
	Return
};

struct FDescriptionContext
{
public:

	inline void Clear() noexcept
	{
		Modfiers = FModfiers();
		Inputs.clear();
		Return = FVariableInfo();
		DescriptionContext = EDescriptionContext::UNDEFINED;
		OpenBracketLayer = 0;
		CodeTokens.clear();
	}

	inline void PrepareForNextModifier() noexcept
	{
		DescriptionContext = EDescriptionContext::UNDEFINED;
		OpenBracketLayer = 0;
		CodeTokens.clear();
	}


public:

	FModfiers Modfiers;
	std::vector<FVariableInfo> Inputs;
	FVariableInfo Return;

	EDescriptionContext DescriptionContext = EDescriptionContext::UNDEFINED;
	int OpenBracketLayer = 0;
	std::vector<Token> CodeTokens;
};



struct FFunctionDeclarationContext
{
public:

	inline void Clear() noexcept
	{
		SignatureInfo = FFunctionSignatureInfo();
		FunctionName.clear();
		ClassDeclarationNamespace.clear();
		StaticCodeTokens.clear();
		StaticCodeOpenBracketLayer = 0;
	}


public:

	FFunctionSignatureInfo SignatureInfo;
	std::string ClassDeclarationNamespace = "";
	std::string FunctionName = "";

	std::vector<Token> StaticCodeTokens;
	int StaticCodeOpenBracketLayer = 0;
};

struct FVariableDeclarationContext
{
public:

	inline void Clear() noexcept
	{
		VariableInfo = FVariableInfo();
		VariableName.clear();
		DefaultValueTokens.clear();
	}


public:

	FVariableInfo VariableInfo;
	std::string VariableName = "";

	std::vector<Token> DefaultValueTokens;
};

struct FClassDeclarationContext
{
public:

	inline void Clear() noexcept
	{
		ClassInfo = FClassInfo();
		ClassName.clear();
	}


public:

	FClassInfo ClassInfo;
	std::vector<std::string> TemplateArguments;
	std::string ClassName = "";
};



struct FAliasDeclarationContext
{
public:

	inline void Clear() noexcept
	{
		OriginalTypeID = -1;
		AliasName.clear();
	}


public:

	int OriginalTypeID = -1;
	std::string AliasName = "";
};



struct FStaticAssertContext
{
public:

	inline void Clear() noexcept
	{
		Expression.clear();
		OpenBracketLayer = 0;
	}


public:

	std::vector<Token> Expression;
	int OpenBracketLayer = 0;
};



struct FFunctionImplementationContext
{
public:

	inline void Clear() noexcept
	{
		CompilingFunctionInfo = FCompilingFunctionInfo();
		FunctionCodeTokens.clear();
		FunctionCodeOpenBracketLayer = 0;
	}


public:

	FCompilingFunctionInfo CompilingFunctionInfo;
	std::vector<Token> FunctionCodeTokens;
	int FunctionCodeOpenBracketLayer = 0;
};



struct FBuildinTemplateTypeContext
{
public:

	inline void Clear() noexcept
	{
		TypeName.clear();
		TypeID = -1;
	}


public:

	std::string TypeName = "";
	int TypeID = -1;
};

struct FLambdaTypeContext
{
public:

	inline void Clear() noexcept 
	{
		TypeID = -1;
	}


public:

	int TypeID = -1;
};

struct FUserTypeContext
{
public:

	inline void Clear() noexcept
	{
		ModuleName.clear();
		TypeName.clear();
		TypeID = -1;
	}


public:

	std::string ModuleName = "";
	std::string TypeName = "";
	int TypeID = -1;
};





/*
	All states contexts.
*/
struct FStatesContext
{
public:

	/*
		Clear all context.
	*/
	inline void ClearContexts() noexcept
	{
		AccessModifierContextType = EAccessModifier::Public;

		ModuleDeclarationContext.Clear();
		ModuleImplementingContext.Clear();
		ModuleImportingContext.Clear();
		DescriptionContext.Clear();
		FunctionDeclarationContext.Clear();
		VariableDeclarationContext.Clear();
		ClassDeclarationContext.Clear();
		AliasDeclarationContext.Clear();
		StaticAssertContext.Clear();
		FunctionImplementationContext.Clear();

		ClearTypeContexts();
	}
	/*
		Clear only local context used in class declaration.
	*/
	inline void ClearContextsLocal() noexcept
	{
		AccessModifierContextType = EAccessModifier::Public;

		DescriptionContext.Clear();
		FunctionDeclarationContext.Clear();
		VariableDeclarationContext.Clear();
		AliasDeclarationContext.Clear();
		StaticAssertContext.Clear();
		FunctionImplementationContext.Clear();

		ClearTypeContexts();
	}
	/*
		Clear only types detection context.
	*/
	inline void ClearTypeContexts() noexcept 
	{ 
		BuildinTemplateTypeContext.Clear();
		LambdaTypeContext.Clear();
		UserTypeContext.Clear();
	}




public:

	bool ModuleNameDeclared = false;
	EStateContextType StateContextType = EStateContextType::Global;

	EAccessModifier AccessModifierContextType = EAccessModifier::Public;

	FModuleDeclarationContext ModuleDeclarationContext;
	FModuleImplementingContext ModuleImplementingContext;
	FModuleImportingContext ModuleImportingContext;
	FDescriptionContext DescriptionContext;
	FFunctionDeclarationContext FunctionDeclarationContext;
	FVariableDeclarationContext VariableDeclarationContext;
	FClassDeclarationContext ClassDeclarationContext;
	FAliasDeclarationContext AliasDeclarationContext;
	FStaticAssertContext StaticAssertContext;
	FFunctionImplementationContext FunctionImplementationContext;

	FBuildinTemplateTypeContext BuildinTemplateTypeContext;
	FLambdaTypeContext LambdaTypeContext;
	FUserTypeContext UserTypeContext;
};