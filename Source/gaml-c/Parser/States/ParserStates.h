// Copyright 2022 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"

#include "StatesContext.h"

#include "../ProgramSymbols.h"
#include "../../Token/Token.h"

#include "../../Compiler/CompilerFileInfo.h"
#include "../../Compiler/CompilerOptions.h"

#include "../../Logger/ErrorLogger.h"

#include <memory>




//..................................................States.................................................................//

struct FParserStates;

/*
	Parser state interface.
*/
class IParserState
{
public:

	virtual ~IParserState() { }

public:

	virtual std::shared_ptr<IParserState> Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo) = 0;
};

#define DECLARE_STATE_CLASS(StateName)                                                                                                             \
	class StateName##_ParserState : public IParserState                                                                                            \
	{                                                                                                                                              \
	public:                                                                                                                                        \
                                                                                                                                                   \
		virtual std::shared_ptr<IParserState> Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo) override; \
	};




//;|module|implement|import|func|struct|interface|object|component|enum|using|public|private|static_assert|***
DECLARE_STATE_CLASS(Default)

// *** ... ***
DECLARE_STATE_CLASS(StartDescription)	  // -> *** -> @|***
DECLARE_STATE_CLASS(DescriptionModifier)  // *** -> @ -> [MODIFIER]|param|return|align
DECLARE_STATE_CLASS(DescriptionAlign1)	  // @ -> align -> (
DECLARE_STATE_CLASS(DescriptionAlign2)	  // align -> ( -> )
DECLARE_STATE_CLASS(DescriptionAlign3)	  // ( -> ) -> @|***
DECLARE_STATE_CLASS(DescriptionParam1)	  // @ -> param|return -> [IDENTIFIER]
DECLARE_STATE_CLASS(DescriptionParam2)	  // [IDENTIFIER] -> : -> const|mut|[standard type]|[user type]
DECLARE_STATE_CLASS(DescriptionParam3)	  // : -> const|mut|[standard type]|[user type] -> (|@|***
DECLARE_STATE_CLASS(DescriptionParam4)	  // [standard type]|[user type] -> (|@|*** -> )
DECLARE_STATE_CLASS(DescriptionParam5)	  // ( -> ... -> )
DECLARE_STATE_CLASS(DescriptionParam6)	  // ... -> ) -> @|***
DECLARE_STATE_CLASS(EndDescription)		  // *** -> *** -> public|private|module|func|struct|interface|object|component|enum
DECLARE_STATE_CLASS(DescriptionParamType) // -> [user type]|[lambda]|[buildin template] ->

// public|private func|interface|object|component|struct|enum
DECLARE_STATE_CLASS(GlobalAccessModifier) // -> public|private -> func|interface|object|component|struct|enum
DECLARE_STATE_CLASS(LocalAccessModifier)  // -> public|protected|private -> func|var



// moudle [IDENTIFIER].[IDENTIFIER]...;
DECLARE_STATE_CLASS(StartDeclareModule) // -> module -> [IDENTIFIER]
DECLARE_STATE_CLASS(DeclareModule1)		// module -> [IDENTIFIER] -> .|;

// implement [IDENTIFIER].[IDENTIFIER]...;
DECLARE_STATE_CLASS(StartImplementModule) // -> implement -> [IDENTIFIER]
DECLARE_STATE_CLASS(ImplementModule1)	  // implement -> [IDENTIFIER] -> .|;

// import [IDENTIFIER].[IDENTIFIER]... as [IDENTIFIER];
DECLARE_STATE_CLASS(StartImportModule) // -> import -> [IDENTIFIER]
DECLARE_STATE_CLASS(ImportModule1)	   // import -> [IDENTIFIER] -> .|as|;
DECLARE_STATE_CLASS(ImportModule2)	   // -> as -> [IDENTIFIER]
DECLARE_STATE_CLASS(ImportModule3)	   // as -> [IDENTIFIER] -> ;



// func [IDENTIFIER];
DECLARE_STATE_CLASS(StartDeclareFunction) // -> func -> [IDENTIFIER]
DECLARE_STATE_CLASS(DeclareFunction1)	  // func -> [IDENTIFIER] -> ::|;|[|{
DECLARE_STATE_CLASS(DeclareFunction2)	  // [IDENTIFIER] -> [ -> ]
DECLARE_STATE_CLASS(DeclareFunction3)	  // [ -> ] -> ;|{
DECLARE_STATE_CLASS(DeclareFunction4)	  // [IDENTIFIER]|] -> { -> }

// struct|enum|interface|object|component [IDENTIFIER];
DECLARE_STATE_CLASS(StartDeclareClass)		// -> struct|enum|interface|object|component -> [IDENTIFIER]
DECLARE_STATE_CLASS(DeclareClass1)			// struct|enum|interface|object|component| -> [IDENTIFIER] -> (|{
DECLARE_STATE_CLASS(DeclareClass2)			// [IDENTIFIER] -> ( -> [standard type]|[user type]
DECLARE_STATE_CLASS(DeclareClass3)			// ( -> [standard type]|[user type] -> ,|)
DECLARE_STATE_CLASS(DeclareClass4)			// [standard type]|[user type] -> ) -> {
DECLARE_STATE_CLASS(DeclareClassInternal)	// [IDENTIFIER]|) -> { -> ***|public|protected|private|func|var|static_assert|using|}
DECLARE_STATE_CLASS(DeclareClassParentType) // -> [user type]|[buildin template] ->

// var static|const|[standard type]|[user type] [IDENTIFIER];
DECLARE_STATE_CLASS(StartDeclareField) // -> var -> static|const|[standard type]|[user type]
DECLARE_STATE_CLASS(DeclareField1)	   // var|static|const -> [standard type]|[user type] -> [IDENTIFIER]
DECLARE_STATE_CLASS(DeclareField2)	   // [standard type]|[user type] -> [IDENTIFIER] -> =|;
DECLARE_STATE_CLASS(DeclareField3)	   // [IDENTIFIER] -> = -> ...;
DECLARE_STATE_CLASS(DeclareFieldType)  // -> [user type]|[buildin template]| ->



// using [IDENTIFIER] = [standard type]|[user type];
DECLARE_STATE_CLASS(StartDefineAlias) // -> using -> [IDENTIFIER]
DECLARE_STATE_CLASS(DefineAlias1)	  // using -> [IDENTIFIER] -> =
DECLARE_STATE_CLASS(DefineAlias2)	  // [IDENTIFIER] -> = -> [standard type]|[user type]
DECLARE_STATE_CLASS(DefineAlias3)	  // = -> [standard type]|[user type] -> ;
DECLARE_STATE_CLASS(DefineAliasType)  // -> [user type]|[buildin template]|[lambda] ->

// static_assert(expression);
DECLARE_STATE_CLASS(StartStaticAssert) // -> static_assert -> (
DECLARE_STATE_CLASS(StaticAssert1)	   // static_assert -> ( -> )
DECLARE_STATE_CLASS(StaticAssert2)	   // ( -> ) -> ;



// class|array <|[stadrad type]|[user type]|>
DECLARE_STATE_CLASS(StartBuildinTemplateType) // -> class|array -> <|
//DECLARE_STATE_CLASS(BuildinTemplateType1)	  // class|array -> <| -> [standard type]|[user type]
//DECLARE_STATE_CLASS(BuildinTemplateType2)	  // <| -> [standard type]|[user type] -> |>

// lambda ([stadrad type]|[user type]) => [stadrad type]|[user type]
DECLARE_STATE_CLASS(StartLambdaType) // -> lambda -> (
//DECLARE_STATE_CLASS(LambdaType1)	 // lambda -> ( -> [stadrad type]|[user type]
//DECLARE_STATE_CLASS(LambdaType2)	 // ( -> [stadrad type]|[user type] -> ,|)
//DECLARE_STATE_CLASS(LambdaType3)	 // [stadrad type]|[user type] -> ) -> =>
//DECLARE_STATE_CLASS(LambdaType4)	 // ) -> => -> [stadrad type]|[user type]

// [IDENTIFIER].[IDENTIFIER]::[IDENTIFIER]
DECLARE_STATE_CLASS(StartUserType) // -> [IDENTIFIER] -> .|::|[return to prev state]
DECLARE_STATE_CLASS(UserType1)	   // [IDENTIFIER] -> . -> [IDENTIFIER]
DECLARE_STATE_CLASS(UserType2)	   // . -> [IDENTIFIER] -> .|::
DECLARE_STATE_CLASS(UserType3)	   // [IDENTIFIER] -> :: -> [IDENTIFIER]

//.........................................................................................................................//




/*
	Main parser state maschine.
	@see IParserState, FStatesContext, AST.
*/
struct FParserStates
{
public:

	FParserStates() = delete;
	FParserStates(const FGamlFileInfo& InFileInfo, const FCompileOptions& InCompileOptions, bool InIsMainModule) :
		FileInfo(InFileInfo), CompileOptions(InCompileOptions), IsMainModule(InIsMainModule)
	{
	}
	~FParserStates() { }



public:

#define DECLARE_STATE(StateName) std::shared_ptr<StateName##_ParserState> G##StateName##_ParserState = std::make_shared<StateName##_ParserState>();


	DECLARE_STATE(Default)

	DECLARE_STATE(StartDescription)
	DECLARE_STATE(DescriptionModifier)
	DECLARE_STATE(DescriptionAlign1)
	DECLARE_STATE(DescriptionAlign2)
	DECLARE_STATE(DescriptionAlign3)
	DECLARE_STATE(DescriptionParam1)
	DECLARE_STATE(DescriptionParam2)
	DECLARE_STATE(DescriptionParam3)
	DECLARE_STATE(DescriptionParam4)
	DECLARE_STATE(DescriptionParam5)
	DECLARE_STATE(DescriptionParam6)
	DECLARE_STATE(EndDescription)
	DECLARE_STATE(DescriptionParamType)

	DECLARE_STATE(GlobalAccessModifier)
	DECLARE_STATE(LocalAccessModifier)


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

	DECLARE_STATE(StartDeclareClass)
	DECLARE_STATE(DeclareClass1)
	DECLARE_STATE(DeclareClass2)
	DECLARE_STATE(DeclareClass3)
	DECLARE_STATE(DeclareClass4)
	DECLARE_STATE(DeclareClassInternal)
	DECLARE_STATE(DeclareClassParentType)

	DECLARE_STATE(StartDeclareField)
	DECLARE_STATE(DeclareField1)
	DECLARE_STATE(DeclareField2)
	DECLARE_STATE(DeclareField3)
	DECLARE_STATE(DeclareFieldType)


	DECLARE_STATE(StartDefineAlias)
	DECLARE_STATE(DefineAlias1)
	DECLARE_STATE(DefineAlias2)
	DECLARE_STATE(DefineAlias3)
	DECLARE_STATE(DefineAliasType)

	DECLARE_STATE(StartStaticAssert)
	DECLARE_STATE(StaticAssert1)
	DECLARE_STATE(StaticAssert2)


	DECLARE_STATE(StartBuildinTemplateType)

	DECLARE_STATE(StartLambdaType)

	DECLARE_STATE(StartUserType)
	DECLARE_STATE(UserType1)
	DECLARE_STATE(UserType2)
	DECLARE_STATE(UserType3)

public:

	/*
		@return information about parsing file.
	*/
	inline const FGamlFileInfo& GetFileInfo() const noexcept { return FileInfo; }
	/*
		@return current compile options.
	*/
	inline const FCompileOptions& GetCompileOptions() const noexcept { return CompileOptions; }
	/*
		@return true if parsing main module(false if parsing imported into main module).
	*/
	inline bool GetIsMainModule() const noexcept { return IsMainModule; }


	/*
		Raise error based on state context.
	*/
	inline void RaiseError(EErrorMessageType ErrorMessageType, const Token& Token) const
	{
		FErrorLogger::Raise(ErrorMessageType, FileInfo.GetFileFullPath(), Token.GetLine(), Token.GetPos(), Token.GetLexeme().size() - 1, CompileOptions);
	}


	/*
		Check that state stack is empty.
		Should be used before using PopState.
	*/
	inline bool IsStateStackEmpty() noexcept { return StatesStack.empty(); }
	/*
		Push state into state-stack.
	*/
	inline void PushState(std::weak_ptr<IParserState> State) noexcept { StatesStack.push_back(State); }
	/*
		Pop state from stack.
		NOTE! Method not check that stack is empty.
	*/
	inline std::shared_ptr<IParserState> PopState() noexcept
	{
		std::weak_ptr<IParserState> LState = StatesStack.back();
		StatesStack.pop_back();
		return LState.lock();
	}
	/*
		Pop state from stack.
		If stack is empty cause error.
	*/
	inline std::shared_ptr<IParserState> PopStateChecked(const Token& ContextToken) noexcept
	{
		if( IsStateStackEmpty() )
		{
			RaiseError(EErrorMessageType::STATE_STACK_EMPTY, ContextToken);
		}

		return PopState();
	}


public:

	void RegisterMainModule(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool ImplementModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool ImportModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterFunctionFromContext(FProgramInfo& OutProgramInfo, bool SkipIfExist, const Token& TokenCTX);
	bool RegisterFunctionImplementationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterVariableFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterClassFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool FinishClassRegistrationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterAliasFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);
	bool RegisterStaticAssertFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX);

	bool ImportModule(FProgramInfo& OutProgramInfo, const std::string& ImportModuleRelativePath, const std::string& ImportModuleName, const Token& TokenCTX);
	bool ImportPackage(FProgramInfo& OutProgramInfo, const std::string& ImportPackageRelativePath, const Token& TokenCTX);

	std::string GetCTXFunctionCompileName(const FProgramInfo& OutProgramInfo) const;
	std::string GetCTXClassCompileName(const FProgramInfo& OutProgramInfo) const;
	std::string GetCTXTypeAliasCompileName(const FProgramInfo& OutProgramInfo) const;




public:

	/*
		Contexts for states.
	*/
	FStatesContext StatesContext;

private:

	/*
		Info of parsing file.
	*/
	FGamlFileInfo FileInfo;
	/*
		Cached compiler options.
	*/
	FCompileOptions CompileOptions;
	/*
		Indicates that the main module is being parsed (imported modules are marked as non-main).
	*/
	bool IsMainModule = true;

	/*
		States stack.
	*/
	std::vector<std::weak_ptr<IParserState>> StatesStack;
};