// Copyright 2022 GrosSlava.

#pragma once

#include "ProgramSymbols.h"
#include "../Token/Token.h"
#include "../Compiler/CompilerFileInfo.h"
#include "../Compiler/CompilerOptions.h"
#include "../Logger/ErrorLogger.h"

#include <string>
#include <vector>




struct FParserStates;


class IParserState
{
public:

	virtual IParserState* Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo) = 0;
};

#define DECLARE_STATE_CLASS(StateName)                                                                                             \
	class StateName##_ParserState : public IParserState                                                                            \
	{                                                                                                                              \
	public:                                                                                                                        \
                                                                                                                                   \
		virtual IParserState* Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo) override; \
	};





DECLARE_STATE_CLASS(Default)

// deprecated module|func|interface|object|component|struct|enum|static
DECLARE_STATE_CLASS(DeclareAnyDeprecated) // deprecated -> module|func|interface|object|component|struct|enum|static

// static module|func|interface|object|component|struct|enum
DECLARE_STATE_CLASS(DeclareAnyStatic) // static -> module|func|interface|object|component|struct|enum

// public func|interface|object|component|struct|enum|deprecated|static
DECLARE_STATE_CLASS(DeclareAnyGlobalPublic) // public -> func|interface|object|component|struct|enum|deprecated|static

// private func|interface|object|component|struct|enum|deprecated|static
DECLARE_STATE_CLASS(DeclareAnyGlobalPrivate) // private -> func|interface|object|component|struct|enum|deprecated|static



// moudle [IDENTIFIER].[IDENTIFIER]...;
DECLARE_STATE_CLASS(StartDeclareModule)	// module -> [IDENTIFIER] -> .|;
DECLARE_STATE_CLASS(DeclareModule1)		// [IDENTIFIER] -> .|; -> [IDENTIFIER]|[Default]

// implement [IDENTIFIER].[IDENTIFIER]...;
DECLARE_STATE_CLASS(StartImplementModule)	// implement -> [IDENTIFIER] -> .|;
DECLARE_STATE_CLASS(ImplementModule1)		//[IDENTIFIER] -> .|; -> [IDENTIFIER]|[Default]

// import [IDENTIFIER].[IDENTIFIER]... as [IDENTIFIER];
DECLARE_STATE_CLASS(StartImportModule)	// import -> [IDENTIFIER] -> .|as|;
DECLARE_STATE_CLASS(ImportModule1)		// [IDENTIFIER] -> .|as|; -> [IDENTIFIER]|;
DECLARE_STATE_CLASS(ImportModule2)		// as -> [IDENTIFIER] -> ;
DECLARE_STATE_CLASS(ImportModule3)		// [IDENTIFIER] -> ; -> [Default]



// func [specifiers...] [return type]|[IDENTIFIER] [IDENTIFIER] ([params...]) [specifiers...];
DECLARE_STATE_CLASS(StartDeclareFunction)	// func -> [specifiers...]|const|[stadrad type]|[user type] -> const|[stadrad type]|[user type]
DECLARE_STATE_CLASS(DeclareFunction1)		// const -> [stadrad type]|[user type] -> [IDENTIFIER]
DECLARE_STATE_CLASS(DeclareFunction2)		// [stadrad type]|[user type] -> [IDENTIFIER] -> (|::
DECLARE_STATE_CLASS(DeclareFunction3)		// [IDENTIFIER] -> ( -> )|[stadrad type]|[user type]
DECLARE_STATE_CLASS(DeclareFunction4)		// ( -> [stadrad type]|[user type] -> )|=|,|[stadrad type]|[user type]
DECLARE_STATE_CLASS(DeclareFunction5)		// 
DECLARE_STATE_CLASS(DeclareFunction6)		// (|[stadrad type]|[user type] -> ) -> [specifiers...]|;|[|{
DECLARE_STATE_CLASS(DeclareFunction7)		// ) -> [ -> ]
DECLARE_STATE_CLASS(DeclareFunction8)		// ] -> ;|{ -> [Default]
DECLARE_STATE_CLASS(DeclareFunction9)		// )|] -> { -> }

// struct|enum|interface|object|component [IDENTIFIER];
DECLARE_STATE_CLASS(StartDeclareClass)



// using [IDENTIFIER] = [IDENTIFIER]|[expression];
DECLARE_STATE_CLASS(StartDefineAlias)

// static_assert(expression);
DECLARE_STATE_CLASS(StartStaticAssert)

// template<| [IDENTIFIER]...|... |> [IDENTIFIER] { ... }
DECLARE_STATE_CLASS(StartDefineTemplate)


//.........................................................................................................................//
//.........................................................................................................................//


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

struct FFunctionDeclarationContext
{
public:

	inline void Clear() noexcept
	{
		SignatureInfo = FFunctionSignatureInfo();
		FunctionName.clear();
		LastInputDefaultValueTokens.clear();
		DefaultValueOpenBracketLayer = 0;
		ClassDeclarationNamespace.clear();
		StaticCodeTokens.clear();
		StaticCodeOpenBracketLayer = 0;
	}


public:

	FFunctionSignatureInfo SignatureInfo;
	std::string ClassDeclarationNamespace = "";
	std::string FunctionName = "";
	std::vector<Token> LastInputDefaultValueTokens;
	int DefaultValueOpenBracketLayer = 0;

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

	EAccessModifier CurrentAccessModifier = EAccessModifier::Public;
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



enum class EStateContextType
{
	Global,
	InClass
};





/*
	Main parser state maschine.
	@see IParserState.
*/
struct FParserStates
{
public:

	FParserStates(const FGamlFileInfo& InFileInfo, const FCompileOptions& InCompileOptions, bool InIsMainModule);
	~FParserStates();



public:

#define DECLARE_STATE(StateName) StateName##_ParserState* G##StateName##_ParserState = nullptr;


	DECLARE_STATE(Default)

	DECLARE_STATE(DeclareAnyDeprecated)

	DECLARE_STATE(DeclareAnyStatic)

	DECLARE_STATE(DeclareAnyGlobalPublic)

	DECLARE_STATE(DeclareAnyGlobalPrivate)


	DECLARE_STATE(StartDeclareModule)
	DECLARE_STATE(DeclareModule1)

	DECLARE_STATE(StartImplementModule)
	DECLARE_STATE(ImplementModule1)

	DECLARE_STATE(StartImportModule)
	DECLARE_STATE(ImportModule1)
	DECLARE_STATE(ImportModule2)
	DECLARE_STATE(ImportModule3)


	DECLARE_STATE(StartDeclareFunction)
	DECLARE_STATE(DeclareFunction1)
	DECLARE_STATE(DeclareFunction2)
	DECLARE_STATE(DeclareFunction3)
	DECLARE_STATE(DeclareFunction4)
	DECLARE_STATE(DeclareFunction5)
	DECLARE_STATE(DeclareFunction6)
	DECLARE_STATE(DeclareFunction7)
	DECLARE_STATE(DeclareFunction8)
	DECLARE_STATE(DeclareFunction9)

	DECLARE_STATE(StartDeclareClass)


	DECLARE_STATE(StartDefineAlias)

	DECLARE_STATE(StartStaticAssert)

	DECLARE_STATE(StartDefineTemplate)

public:

	inline const FGamlFileInfo& GetFileInfo() const noexcept { return FileInfo; }
	inline const FCompileOptions& GetCompileOptions() const noexcept { return CompileOptions; }
	inline bool GetIsMainModule() const noexcept { return IsMainModule; }


	inline void RaiseError(EErrorMessageType ErrorMessageType, const Token& Token) const 
	{ 
		FErrorLogger::Raise(ErrorMessageType, FileInfo.GetFileFullPath(), Token.GetLine(), Token.GetPos(), CompileOptions); 
	}

	inline void ClearContexts() noexcept
	{
		IsDeprecatedContext = false;
		IsStaticContext = false;
		AccessModifierContextType = EAccessModifier::Public;

		ModuleDeclarationContext.Clear();
		ModuleImplementingContext.Clear();
		ModuleImportingContext.Clear();
		FunctionDeclarationContext.Clear();
		VariableDeclarationContext.Clear();
		ClassDeclarationContext.Clear();
		AliasDeclarationContext.Clear();
		FunctionImplementationContext.Clear();
	}


	void RegisterMainModule(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool ImplementModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool ImportModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterFunctionFromContext(FProgramInfo& OutProgramInfo, bool SkipIfExist, const Token& TokenCTX);
	bool RegisterVariableFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX); 
	bool RegisterClassFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterAliasFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterFunctionImplementationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);

private:

	bool ImportModule(FProgramInfo& OutProgramInfo, const std::string& ImportModuleRelativePath, const std::string& ImortModuleName, const Token& TokenCTX);
	bool ImportPackage(FProgramInfo& OutProgramInfo, const std::string& ImportPackageRelativePath, const Token& TokenCTX);

	std::string GetCTXFunctionCompileName(const FProgramInfo& OutProgramInfo) const;
	std::string GetCTXClassCompileName(const FProgramInfo& OutProgramInfo) const;
	std::string GetCTXTypeAliasCompileName(const FProgramInfo& OutProgramInfo) const;



private:

	FGamlFileInfo FileInfo;
	FCompileOptions CompileOptions;
	bool IsMainModule = true;

public:

	bool ModuleNameDeclared = false;
	EStateContextType StateContextType = EStateContextType::Global;

	bool IsDeprecatedContext = false;
	bool IsStaticContext = false;
	EAccessModifier AccessModifierContextType = EAccessModifier::Public;

	FModuleDeclarationContext ModuleDeclarationContext;
	FModuleImplementingContext ModuleImplementingContext;
	FModuleImportingContext ModuleImportingContext;
	FFunctionDeclarationContext FunctionDeclarationContext;
	FVariableDeclarationContext VariableDeclarationContext;
	FClassDeclarationContext ClassDeclarationContext;
	FAliasDeclarationContext AliasDeclarationContext;
	FFunctionImplementationContext FunctionImplementationContext;
};