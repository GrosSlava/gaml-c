// Copyright 2022 GrosSlava.

#include "ParserStates.h"
#include "ParserHelperLibray.h"

#include "../Compiler/CompilerConfig.h"
#include "../Compiler/CompilerHelperLibrary.h"

#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"

#include <fstream>





IParserState* Default_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StateContextType = EStateContextType::Global;
	InParserStates.ClearContexts();


	switch( InToken.GetType() )
	{
	case ETokenType::SEMICOLON:
	{
		return InParserStates.GDefault_ParserState;
	}
	case ETokenType::MODULE:
	{
		return InParserStates.GStartDeclareModule_ParserState;
	}
	case ETokenType::IMPLEMENT:
	{
		return InParserStates.GStartImplementModule_ParserState;
	}
	case ETokenType::IMPORT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		return InParserStates.GStartImportModule_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::USING:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		return InParserStates.GStartDefineAlias_ParserState;
	}
	case ETokenType::PUBLIC:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.AccessModifierContextType = EAccessModifier::Public;
		return InParserStates.GDeclareAnyGlobalPublic_ParserState;
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.AccessModifierContextType = EAccessModifier::Private;
		return InParserStates.GDeclareAnyGlobalPrivate_ParserState;
	}
	case ETokenType::STATIC_ASSERT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		return InParserStates.GStartStaticAssert_ParserState;
	}
	case ETokenType::TEMPLATE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		return InParserStates.GStartDefineTemplate_ParserState;
	}
	case ETokenType::DESCRIPTION_BLOCK:
	{
		//TODO
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}





IParserState* DeclareAnyGlobalPublic_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		InParserStates.StateContextType = EStateContextType::Global;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Modifiers.AccessModifier = EAccessModifier::Public;

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Public;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Public;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Public;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Public;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Public;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}



IParserState* DeclareAnyGlobalPrivate_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		InParserStates.StateContextType = EStateContextType::Global;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Modifiers.AccessModifier = EAccessModifier::Private;

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Private;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Private;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Private;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Private;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = EAccessModifier::Private;

		return InParserStates.GStartDeclareClass_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}





IParserState* StartDeclareModule_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}


	InParserStates.ModuleDeclarationContext.ModulePath.push_back(InToken.GetLexeme());

	return InParserStates.GDeclareModule1_ParserState;
}

IParserState* DeclareModule1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::POINT:
	{
		return InParserStates.GStartDeclareModule_ParserState;
	}
	case ETokenType::SEMICOLON:
	{
		if( !InParserStates.RegisterModuleFromContext(OutProgramInfo, InToken) )
		{
			return nullptr;
		}

		return InParserStates.GDefault_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}



IParserState* StartImplementModule_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}


	InParserStates.ModuleImplementingContext.ModulePath.push_back(InToken.GetLexeme());

	return InParserStates.GImplementModule1_ParserState;
}

IParserState* ImplementModule1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::POINT:
	{
		return InParserStates.GStartImplementModule_ParserState;
	}
	case ETokenType::SEMICOLON:
	{
		if( !InParserStates.ImplementModuleFromContext(OutProgramInfo, InToken) )
		{
			return nullptr;
		}

		return InParserStates.GDefault_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}



IParserState* StartImportModule_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}


	InParserStates.ModuleImportingContext.ModulePath.push_back(InToken.GetLexeme());

	return InParserStates.GImportModule1_ParserState;
}

IParserState* ImportModule1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::POINT:
	{
		return InParserStates.GStartImportModule_ParserState;
	}
	case ETokenType::AS:
	{
		return InParserStates.GImportModule2_ParserState;
	}
	case ETokenType::SEMICOLON:
	{
		if( !InParserStates.ImportModuleFromContext(OutProgramInfo, InToken) )
		{
			return nullptr;
		}

		return InParserStates.GDefault_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* ImportModule2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}


	InParserStates.ModuleImportingContext.AliasName = InToken.GetLexeme();

	return InParserStates.GImportModule3_ParserState;
}

IParserState* ImportModule3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::SEMICOLON )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
		return nullptr;
	}


	if( !InParserStates.ImportModuleFromContext(OutProgramInfo, InToken) )
	{
		return nullptr;
	}

	return InParserStates.GDefault_ParserState;
}





IParserState* StartDeclareFunction_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_FUNCTION_NAME, InToken);
		return nullptr;
	}


	InParserStates.FunctionDeclarationContext.FunctionName = InToken.GetLexeme();
	return InParserStates.GDeclareFunction1_ParserState;
}

IParserState* DeclareFunction1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::NAMESPACE_ACCESS_OPERATOR:
	{
		if( InParserStates.FunctionDeclarationContext.ClassDeclarationNamespace.empty() )
		{
			InParserStates.FunctionDeclarationContext.ClassDeclarationNamespace = InParserStates.FunctionDeclarationContext.FunctionName;
			InParserStates.FunctionDeclarationContext.FunctionName.clear();
		}
		else
		{
			InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
			return nullptr;
		}

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::SEMICOLON:
	{
		if( !InParserStates.RegisterFunctionFromContext(OutProgramInfo, false, InToken) )
		{
			return nullptr;
		}

		if( InParserStates.StateContextType == EStateContextType::Global )
		{
			return InParserStates.GDefault_ParserState;
		}
		else if( InParserStates.StateContextType == EStateContextType::InClass )
		{
			//TODO to class context
		}
	}
	case ETokenType::LSQR:
	{
		InParserStates.FunctionDeclarationContext.StaticCodeOpenBracketLayer = 1;
		return InParserStates.GDeclareFunction2_ParserState;
	}
	case ETokenType::LBRA:
	{
		if( !InParserStates.RegisterFunctionFromContext(OutProgramInfo, true, InToken) )
		{
			return nullptr;
		}

		InParserStates.FunctionImplementationContext.FunctionCodeOpenBracketLayer = 1;
		return InParserStates.GDeclareFunction4_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
	return nullptr;
}

IParserState* DeclareFunction2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InParserStates.FunctionDeclarationContext.StaticCodeOpenBracketLayer == 0 )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LSQR, InToken);
		return nullptr;
	}


	switch( InToken.GetType() )
	{
	case ETokenType::LSQR:
	{
		++InParserStates.FunctionDeclarationContext.StaticCodeOpenBracketLayer;
		InParserStates.FunctionDeclarationContext.StaticCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction2_ParserState;
	}
	case ETokenType::RSQR:
	{
		--InParserStates.FunctionDeclarationContext.StaticCodeOpenBracketLayer;
		if( InParserStates.FunctionDeclarationContext.StaticCodeOpenBracketLayer == 0 )
		{
			return InParserStates.GDeclareFunction3_ParserState;
		}

		InParserStates.FunctionDeclarationContext.StaticCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction2_ParserState;
	}
	default:
	{
		InParserStates.FunctionDeclarationContext.StaticCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction2_ParserState;
	}
	}

	return nullptr;
}

IParserState* DeclareFunction3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::SEMICOLON:
	{
		if( !InParserStates.RegisterFunctionFromContext(OutProgramInfo, false, InToken) )
		{
			return nullptr;
		}

		if( InParserStates.StateContextType == EStateContextType::Global )
		{
			return InParserStates.GDefault_ParserState;
		}
		else if( InParserStates.StateContextType == EStateContextType::InClass )
		{
			//TODO to class context
		}
	}
	case ETokenType::LBRA:
	{
		if( !InParserStates.RegisterFunctionFromContext(OutProgramInfo, true, InToken) )
		{
			return nullptr;
		}

		InParserStates.FunctionImplementationContext.FunctionCodeOpenBracketLayer = 1;
		return InParserStates.GDeclareFunction4_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareFunction4_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InParserStates.FunctionImplementationContext.FunctionCodeOpenBracketLayer == 0 )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LBRA, InToken);
		return nullptr;
	}

	switch( InToken.GetType() )
	{
	case ETokenType::LBRA:
	{
		++InParserStates.FunctionImplementationContext.FunctionCodeOpenBracketLayer;
		InParserStates.FunctionImplementationContext.FunctionCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction4_ParserState;
	}
	case ETokenType::RBRA:
	{
		--InParserStates.FunctionImplementationContext.FunctionCodeOpenBracketLayer;
		if( InParserStates.FunctionImplementationContext.FunctionCodeOpenBracketLayer == 0 )
		{
			if( !InParserStates.RegisterFunctionImplementationFromContext(OutProgramInfo, InToken) )
			{
				return nullptr;
			}

			if( InParserStates.StateContextType == EStateContextType::Global )
			{
				return InParserStates.GDefault_ParserState;
			}
			else if( InParserStates.StateContextType == EStateContextType::InClass )
			{
				//TODO to class context
			}
		}

		InParserStates.FunctionImplementationContext.FunctionCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction4_ParserState;
	}
	default:
	{
		InParserStates.FunctionImplementationContext.FunctionCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction4_ParserState;
	}
	}

	return nullptr;
}



IParserState* StartDeclareClass_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	//TODO
	return nullptr;
}





IParserState* StartDefineAlias_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_ALIAS_NAME, InToken);
		return nullptr;
	}


	InParserStates.AliasDeclarationContext.AliasName = InToken.GetLexeme();
	return InParserStates.GDefineAlias1_ParserState;
}

IParserState* DefineAlias1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::ASSIGN )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_ASSIGN, InToken);
		return nullptr;
	}


	return InParserStates.GDefineAlias2_ParserState;
}

IParserState* DefineAlias2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		InParserStates.AliasDeclarationContext.OriginalTypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
		return InParserStates.GDefineAlias3_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		//TODO
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		//TODO user type
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		//TODO lambda
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DefineAlias3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::SEMICOLON )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
		return nullptr;
	}


	if( !InParserStates.RegisterAliasFromContext(OutProgramInfo, InToken) )
	{
		return nullptr;
	}

	if( InParserStates.StateContextType == EStateContextType::Global )
	{
		return InParserStates.GDefault_ParserState;
	}
	else if( InParserStates.StateContextType == EStateContextType::InClass )
	{
		//TODO to class context
	}

	return nullptr;
}



IParserState* StartStaticAssert_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::LPAR )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LPAR, InToken);
		return nullptr;
	}


	InParserStates.StaticAssertContext.Clear();

	return InParserStates.GStaticAssert1_ParserState;
}

IParserState* StaticAssert1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() == ETokenType::RPAR )
	{
		if( InParserStates.StaticAssertContext.OpenBracketLayer == 0 )
		{
			AST LAST;
			LAST.BuildAST(InParserStates.StaticAssertContext.Expression);
			//TODO interpret ast

			return InParserStates.GStaticAssert2_ParserState;
		}
	}


	if( FParserHelperLibrary::IsOpenPairToken(InToken) )
	{
		++InParserStates.StaticAssertContext.OpenBracketLayer;
	}
	else if( FParserHelperLibrary::IsClosePairToken(InToken) )
	{
		--InParserStates.StaticAssertContext.OpenBracketLayer;
	}

	InParserStates.StaticAssertContext.Expression.push_back(InToken);

	return InParserStates.GStaticAssert1_ParserState;
}

IParserState* StaticAssert2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::SEMICOLON )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
		return nullptr;
	}


	if( InParserStates.StateContextType == EStateContextType::Global )
	{
		return InParserStates.GDefault_ParserState;
	}
	else if( InParserStates.StateContextType == EStateContextType::InClass )
	{
		//TODO to class context
	}

	return nullptr;

}



IParserState* StartDefineTemplate_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	//TODO
	return nullptr;
}



//.............................................................................................................................//
//.............................................................................................................................//





FParserStates::FParserStates(const FGamlFileInfo& InFileInfo, const FCompileOptions& InCompileOptions, bool InIsMainModule) : 
	FileInfo(InFileInfo), CompileOptions(InCompileOptions), IsMainModule(InIsMainModule)
{
#define CREATE_STATE(StateName) G##StateName##_ParserState = new StateName##_ParserState();


	CREATE_STATE(Default)

	CREATE_STATE(DeclareAnyGlobalPublic)

	CREATE_STATE(DeclareAnyGlobalPrivate)


	CREATE_STATE(StartDeclareModule)
	CREATE_STATE(DeclareModule1)

	CREATE_STATE(StartImplementModule)
	CREATE_STATE(ImplementModule1)

	CREATE_STATE(StartImportModule)
	CREATE_STATE(ImportModule1)
	CREATE_STATE(ImportModule2)
	CREATE_STATE(ImportModule3)


	CREATE_STATE(StartDeclareFunction)
	CREATE_STATE(DeclareFunction1)
	CREATE_STATE(DeclareFunction2)
	CREATE_STATE(DeclareFunction3)
	CREATE_STATE(DeclareFunction4)

	CREATE_STATE(StartDeclareClass)


	CREATE_STATE(StartDefineAlias)
	CREATE_STATE(DefineAlias1)
	CREATE_STATE(DefineAlias2)
	CREATE_STATE(DefineAlias3)

	CREATE_STATE(StartStaticAssert)
	CREATE_STATE(StaticAssert1)
	CREATE_STATE(StaticAssert2)

	CREATE_STATE(StartDefineTemplate)
}

FParserStates::~FParserStates()
{
#define DELETE_STATE(StateName) if( G##StateName##_ParserState != nullptr ) delete G##StateName##_ParserState;


	DELETE_STATE(Default)

	DELETE_STATE(DeclareAnyGlobalPublic)

	DELETE_STATE(DeclareAnyGlobalPrivate)


	DELETE_STATE(StartDeclareModule)
	DELETE_STATE(DeclareModule1)

	DELETE_STATE(StartImplementModule)
	DELETE_STATE(ImplementModule1)

	DELETE_STATE(StartImportModule)
	DELETE_STATE(ImportModule1)
	DELETE_STATE(ImportModule2)
	DELETE_STATE(ImportModule3)


	DELETE_STATE(StartDeclareFunction)
	DELETE_STATE(DeclareFunction1)
	DELETE_STATE(DeclareFunction2)
	DELETE_STATE(DeclareFunction3)
	DELETE_STATE(DeclareFunction4)

	DELETE_STATE(StartDeclareClass)


	DELETE_STATE(StartDefineAlias)
	DELETE_STATE(DefineAlias1)
	DELETE_STATE(DefineAlias2)
	DELETE_STATE(DefineAlias3)

	DELETE_STATE(StartStaticAssert)
	DELETE_STATE(StaticAssert1)
	DELETE_STATE(StaticAssert2)

	DELETE_STATE(StartDefineTemplate)
}





void FParserStates::RegisterMainModule(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( !OutProgramInfo.MainModuleName.empty() ) return;

	if( !GetIsMainModule() )
	{
		// imported module should already have name in MainModuleName
		RaiseError(EErrorMessageType::NO_NAME_NOT_MAIN_MODULE, TokenCTX);
	}


	FModuleInfo LModuleInfo;
	LModuleInfo.MetaInfo.DeclaredInFile = TokenCTX.GetFileInfo();
	LModuleInfo.MetaInfo.DeclaredAtLine = TokenCTX.GetLine();


	OutProgramInfo.ImportedModulesInfo.insert(std::pair(FCompilerConfig::RESERVED_MAIN_MODULE_NAME, LModuleInfo));
	OutProgramInfo.MainModuleName = FCompilerConfig::RESERVED_MAIN_MODULE_NAME;
	ModuleNameDeclared = true;
}

bool FParserStates::RegisterModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( ModuleDeclarationContext.ModulePath.empty() )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StateContextType != EStateContextType::Global )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	if( ModuleNameDeclared )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredInFile = TokenCTX.GetFileInfo();
	ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredAtLine = TokenCTX.GetLine();


	const std::string LModuleName = FCompilerHelperLibrary::MakePathFromParts(ModuleDeclarationContext.ModulePath, false, '.');
	if( !GetIsMainModule() && OutProgramInfo.MainModuleName != LModuleName ) // module name was set at the import stage
	{
		RaiseError(EErrorMessageType::INVALID_IMPORTING_MODULE_NAME, TokenCTX);
		return false;
	}

	if( OutProgramInfo.ImportedModulesInfo.find(LModuleName) != OutProgramInfo.ImportedModulesInfo.end() )
	{
		RaiseError(EErrorMessageType::MODULE_DOUBLE_IMPORT, TokenCTX);
		return false;
	}

	OutProgramInfo.ImportedModulesInfo.insert(std::pair(LModuleName, ModuleDeclarationContext.ModuleInfo));
	OutProgramInfo.MainModuleName = LModuleName;
	ModuleNameDeclared = true;

	return true;
}

bool FParserStates::ImplementModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( ModuleImplementingContext.ModulePath.empty() )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StateContextType != EStateContextType::Global )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	if( ModuleNameDeclared )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_REDEFINITION, TokenCTX);
		return false;
	}

	if( !GetIsMainModule() )
	{
		RaiseError(EErrorMessageType::IMPORTING_IMPLEMENT_MODULE, TokenCTX);
		return false;
	}



	const std::string LModuleName = FCompilerHelperLibrary::MakePathFromParts(ModuleImplementingContext.ModulePath, false, '.');

	if( OutProgramInfo.ImportedModulesInfo.find(LModuleName) != OutProgramInfo.ImportedModulesInfo.end() )
	{
		RaiseError(EErrorMessageType::MODULE_DOUBLE_IMPORT, TokenCTX);
		return false;
	}

	OutProgramInfo.MainModuleName = LModuleName;
	ModuleNameDeclared = true;

	const std::string LImportingModuleRelativePath = FCompilerHelperLibrary::MakePathFromParts(ModuleImplementingContext.ModulePath);
	const bool LImportSuccess = ImportModule(OutProgramInfo, LImportingModuleRelativePath, LModuleName, TokenCTX);
	if( !LImportSuccess )
	{
		RaiseError(EErrorMessageType::MODULE_NOT_FOUND, TokenCTX);
		return false;
	}

	return true;
}

bool FParserStates::ImportModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( ModuleImportingContext.ModulePath.empty() )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StateContextType != EStateContextType::Global )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}



	const std::string LImportingModuleRelativePath = FCompilerHelperLibrary::MakePathFromParts(ModuleImportingContext.ModulePath);
	const std::string LModuleName = FCompilerHelperLibrary::MakePathFromParts(ModuleImportingContext.ModulePath, false, '.');

	if( !ModuleImportingContext.AliasName.empty() )
	{
		if( 
			OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.find(ModuleImportingContext.AliasName) != 
			OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.end() 
		  )
		{
			RaiseError(EErrorMessageType::MODULE_ALIAS_NAME_REDEFINITION, TokenCTX);
			return false;
		}

		OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.insert(std::pair(ModuleImportingContext.AliasName, LModuleName));
	}

	bool LImportSuccess = ImportModule(OutProgramInfo, LImportingModuleRelativePath, LModuleName, TokenCTX);
	if( !LImportSuccess )
	{
		LImportSuccess = ImportPackage(OutProgramInfo, LImportingModuleRelativePath, TokenCTX);
	}
	if( !LImportSuccess )
	{
		RaiseError(EErrorMessageType::MODULE_NOT_FOUND, TokenCTX);
		return false;
	}

	return true;
}

bool FParserStates::ImportModule(FProgramInfo& OutProgramInfo, const std::string& ImportModuleRelativePath, const std::string& ImportModuleName, const Token& TokenCTX)
{
	if( ImportModuleName == FCompilerConfig::RESERVED_MAIN_MODULE_NAME )
	{
		RaiseError(EErrorMessageType::IMPORTING_MAIN_MODULE, TokenCTX);
		return false;
	}


	const std::string LCompilerPathOnly = FCompilerHelperLibrary::SplitFilePath(CompileOptions.PathToCompiler).PathToFileOnly;

	std::vector<std::string> LCurrentModulePathParts;
	FCompilerHelperLibrary::SplitPathToParts(OutProgramInfo.MainModuleName, LCurrentModulePathParts, '.');
	const std::string LUpDirectory = FCompilerHelperLibrary::MakeUpDirectoryStr(LCurrentModulePathParts.size() - 1);


	std::ifstream LFile;
	FGamlFileInfo LModuleFileInfo;

	if( !LFile.is_open() ) 
	{
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath(FileInfo.PathToFileOnly + LUpDirectory + ImportModuleRelativePath + "." + FCompilerConfig::HEADER_FILE_EXTENSION);
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath(FileInfo.PathToFileOnly + LUpDirectory + ImportModuleRelativePath + "." + FCompilerConfig::COMPILE_FILE_EXTENSION);
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath(LCompilerPathOnly + ImportModuleRelativePath + "." + FCompilerConfig::HEADER_FILE_EXTENSION);
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath(LCompilerPathOnly + ImportModuleRelativePath + "." + FCompilerConfig::COMPILE_FILE_EXTENSION);
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		return false;
	}


	std::vector<std::string>& LRequiredModules = OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].RequiredModulesNames;

	// stop import recursion
	// clang-format off
	if( 
		ImportModuleName == OutProgramInfo.MainModuleName || 
		OutProgramInfo.ImportedModulesInfo.find(ImportModuleName) != OutProgramInfo.ImportedModulesInfo.end() ||
		std::find(LRequiredModules.begin(), LRequiredModules.end(), ImportModuleName) != LRequiredModules.end() 
	  )
	// clang-format on
	{
		LFile.close();
		return true;
	}

	LRequiredModules.push_back(ImportModuleName);


	std::string LSourceCode;
	FCompilerHelperLibrary::ReadAllFileToStr(LFile, LSourceCode);

	std::vector<Token> LTokens;
	Lexer LLexer;
	LLexer.Process(LSourceCode, LModuleFileInfo, CompileOptions, LTokens);

	const std::string LModuleRealName = FParserHelperLibrary::GetFirstModuleName(LTokens);
	if( LModuleRealName == FCompilerConfig::RESERVED_MAIN_MODULE_NAME )
	{
		RaiseError(EErrorMessageType::IMPORTING_MAIN_MODULE, TokenCTX);
		return false;
	}
	if( ImportModuleName != LModuleRealName )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_NOT_MATCH_FILE_NAME, TokenCTX);
		return false;
	}

	const std::string LSavedMainModuleName = OutProgramInfo.MainModuleName;
	OutProgramInfo.MainModuleName = ImportModuleName; // not main module should check this name by it's name
	Parser LParser;
	LParser.Process(LTokens, LModuleFileInfo, CompileOptions, false, OutProgramInfo);
	OutProgramInfo.MainModuleName = LSavedMainModuleName;

	return true;
}

bool FParserStates::ImportPackage(FProgramInfo& OutProgramInfo, const std::string& ImportPackageRelativePath, const Token& TokenCTX)
{
	const std::string LCompilerPathOnly = FCompilerHelperLibrary::SplitFilePath(CompileOptions.PathToCompiler).PathToFileOnly;

	std::vector<std::string> LCurrentModulePathParts;
	FCompilerHelperLibrary::SplitPathToParts(OutProgramInfo.MainModuleName, LCurrentModulePathParts, '.');
	const std::string LUpDirectory = FCompilerHelperLibrary::MakeUpDirectoryStr(LCurrentModulePathParts.size() - 1);


	std::vector<FGamlFileInfo> FilesInfo;

	if( FilesInfo.empty() )
	{
		FCompilerHelperLibrary::GetAllGamlFilesInFolder(FileInfo.PathToFileOnly + LUpDirectory + ImportPackageRelativePath, FilesInfo);
	}
	if( FilesInfo.empty() )
	{
		FCompilerHelperLibrary::GetAllGamlFilesInFolder(LCompilerPathOnly + ImportPackageRelativePath, FilesInfo);
	}
	if( FilesInfo.empty() )
	{
		return false;
	}


	for( const FGamlFileInfo& LFileInfo : FilesInfo )
	{
		if( LFileInfo.FileNameOnly == FCompilerConfig::RESERVED_MAIN_MODULE_NAME )
		{
			continue;
		}


		std::vector<std::string>& LRequiredModules = OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].RequiredModulesNames;

		std::ifstream LFile(LFileInfo.GetFileFullPath(), std::ios::binary);
		if( !LFile.is_open() )
		{
			RaiseError(EErrorMessageType::IMPORTING_PACKAGE_PROBLEM, TokenCTX);
			return false;
		}

		std::string LSourceCode;
		FCompilerHelperLibrary::ReadAllFileToStr(LFile, LSourceCode);

		std::vector<Token> LTokens;
		Lexer LLexer;
		LLexer.Process(LSourceCode, LFileInfo, CompileOptions, LTokens);

		const std::string LPackageModuleRealName = FParserHelperLibrary::GetFirstModuleName(LTokens); // return empty name for implementing modules, so do not include them
		if( LPackageModuleRealName.empty() || LPackageModuleRealName == FCompilerConfig::RESERVED_MAIN_MODULE_NAME )
		{
			continue;
		}

		// stop import recursion
		// clang-format off
		if(
			LPackageModuleRealName == OutProgramInfo.MainModuleName || 
			OutProgramInfo.ImportedModulesInfo.find(LPackageModuleRealName) != OutProgramInfo.ImportedModulesInfo.end() ||
			std::find(LRequiredModules.begin(), LRequiredModules.end(), LPackageModuleRealName) != LRequiredModules.end() 
		  )
		// clang-format on
		{
			continue;
		}

		LRequiredModules.push_back(LPackageModuleRealName);

		const std::string LSavedMainModuleName = OutProgramInfo.MainModuleName;
		OutProgramInfo.MainModuleName = LPackageModuleRealName; // not main module should check this name by it's name
		Parser LParser;
		LParser.Process(LTokens, LFileInfo, CompileOptions, false, OutProgramInfo);
		OutProgramInfo.MainModuleName = LSavedMainModuleName;
	}

	return true;
}

bool FParserStates::RegisterFunctionFromContext(FProgramInfo& OutProgramInfo, bool SkipIfExist, const Token& TokenCTX)
{
	if( FunctionDeclarationContext.FunctionName.empty() )
	{
		RaiseError(EErrorMessageType::FUNCTION_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	const std::string LFunctionCompileName = GetCTXFunctionCompileName(OutProgramInfo);

	if( LFunctionCompileName.empty() )
	{
		RaiseError(EErrorMessageType::FUNCTION_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	auto LProgramFunctionIterator = OutProgramInfo.Functions.find(LFunctionCompileName);
	if( LProgramFunctionIterator != OutProgramInfo.Functions.end() )
	{
		if( SkipIfExist )
		{
			for( int i = 0; i < FunctionDeclarationContext.SignatureInfo.Inputs.size(); ++i )
			{
				if( FunctionDeclarationContext.SignatureInfo.Inputs[i].VariableName != (*LProgramFunctionIterator).second.Inputs[i].VariableName )
				{
					RaiseError(EErrorMessageType::FUNCTION_ARGUMENT_NAME_MISMATCH, TokenCTX);
					return false;
				}
			}

			if( !FunctionDeclarationContext.StaticCodeTokens.empty() )
			{
				RaiseError(EErrorMessageType::FUNCTION_STATIC_CODE_OVERRIDE, TokenCTX);
				return false;
			}

			return true;
		}

		RaiseError(EErrorMessageType::FUNCTION_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = TokenCTX.GetFileInfo();
	FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = TokenCTX.GetLine();
	FunctionDeclarationContext.SignatureInfo.StaticCodeTree.BuildAST(FunctionDeclarationContext.StaticCodeTokens);

	const bool ThisSignatureExists = FParserHelperLibrary::GetFunctionSignatureID(FunctionDeclarationContext.SignatureInfo, OutProgramInfo) != -1;
	if( !ThisSignatureExists )
	{
		OutProgramInfo.FunctionSignaturesTypesMap.push_back(FunctionDeclarationContext.SignatureInfo);

		FUserTypePath LTypePath;
		LTypePath.PathSwitch = ETypePathSwitch::EFunctionSignature;
		LTypePath.FunctionSignaturePath.FunctionSignatureID = OutProgramInfo.FunctionSignaturesTypesMap.size() - 1; // size > 0
		OutProgramInfo.TypesMap.push_back(LTypePath);
	}

	OutProgramInfo.Functions.insert(std::pair(LFunctionCompileName, FunctionDeclarationContext.SignatureInfo));

	if( StateContextType == EStateContextType::InClass && FunctionDeclarationContext.SignatureInfo.Modifiers.IsVirtual || FunctionDeclarationContext.SignatureInfo.Modifiers.IsOverride )
	{
		ClassDeclarationContext.ClassInfo.VirtualFunctionsTable.insert(std::pair(FunctionDeclarationContext.FunctionName, LFunctionCompileName));
	}

	return true;
}

bool FParserStates::RegisterVariableFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( VariableDeclarationContext.VariableName.empty() )
	{
		RaiseError(EErrorMessageType::VARIABLE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StateContextType != EStateContextType::InClass )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	if( ClassDeclarationContext.ClassInfo.Variables.find(VariableDeclarationContext.VariableName) != ClassDeclarationContext.ClassInfo.Variables.end() )
	{
		RaiseError(EErrorMessageType::VARIABLE_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	VariableDeclarationContext.VariableInfo.MetaInfo.DeclaredInFile = TokenCTX.GetFileInfo();
	VariableDeclarationContext.VariableInfo.MetaInfo.DeclaredAtLine = TokenCTX.GetLine();
	VariableDeclarationContext.VariableInfo.DefaultValueTree.BuildAST(VariableDeclarationContext.DefaultValueTokens);


	ClassDeclarationContext.ClassInfo.Variables.insert(std::pair(VariableDeclarationContext.VariableName, VariableDeclarationContext.VariableInfo));

	return true;
}

bool FParserStates::RegisterClassFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( ClassDeclarationContext.ClassName.empty() )
	{
		RaiseError(EErrorMessageType::CLASS_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StateContextType != EStateContextType::Global )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	const std::string LClassCompileName = GetCTXClassCompileName(OutProgramInfo);
	if( LClassCompileName.empty() )
	{
		RaiseError(EErrorMessageType::CLASS_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( OutProgramInfo.Classes.find(LClassCompileName) != OutProgramInfo.Classes.end() )
	{
		RaiseError(EErrorMessageType::CLASS_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = TokenCTX.GetFileInfo();
	ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = TokenCTX.GetLine();


	OutProgramInfo.Classes.insert(std::pair(LClassCompileName, ClassDeclarationContext.ClassInfo));

	const bool ThisClassTypeExists = FParserHelperLibrary::GetClassTypeID(LClassCompileName, OutProgramInfo) != -1;
	if( !ThisClassTypeExists )
	{
		FUserTypePath LTypePath;
		LTypePath.PathSwitch = ETypePathSwitch::EClass;
		LTypePath.ClassPath.ClassCompileName = LClassCompileName;
		OutProgramInfo.TypesMap.push_back(LTypePath);
	}

	return true;
}

bool FParserStates::RegisterAliasFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( AliasDeclarationContext.AliasName.empty() )
	{
		RaiseError(EErrorMessageType::ALIAS_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	const std::string LAliasCompileName = GetCTXTypeAliasCompileName(OutProgramInfo);

	if( LAliasCompileName.empty() )
	{
		RaiseError(EErrorMessageType::ALIAS_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( OutProgramInfo.TypeAliases.find(LAliasCompileName) != OutProgramInfo.TypeAliases.end() )
	{
		RaiseError(EErrorMessageType::ALIAS_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	OutProgramInfo.TypeAliases.insert(std::pair(LAliasCompileName, AliasDeclarationContext.OriginalTypeID));

	return true;
}

bool FParserStates::RegisterFunctionImplementationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	// our function implementation based on declaration context as a part of function declaration/implementation usage
	if( FunctionDeclarationContext.FunctionName.empty() )
	{
		RaiseError(EErrorMessageType::FUNCTION_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	const std::string LFunctionCompileName = GetCTXFunctionCompileName(OutProgramInfo);

	if( LFunctionCompileName.empty() )
	{
		RaiseError(EErrorMessageType::FUNCTION_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( OutProgramInfo.Functions.find(LFunctionCompileName) == OutProgramInfo.Functions.end() )
	{
		RaiseError(EErrorMessageType::FUNCTION_DECLARATION_NOT_FOUND, TokenCTX);
		return false;
	}

	if( OutProgramInfo.CompilingFunctionsAST.find(LFunctionCompileName) != OutProgramInfo.CompilingFunctionsAST.end() )
	{
		RaiseError(EErrorMessageType::FUNCTION_IMPLEMENTATION_NAME_REDEFINITION, TokenCTX);
		return false;
	}

	if( !GetIsMainModule() ) return true;



	FunctionImplementationContext.CompilingFunctionInfo.FunctionCodeTree.BuildAST(FunctionImplementationContext.FunctionCodeTokens);


	OutProgramInfo.CompilingFunctionsAST.insert(std::pair(LFunctionCompileName, FunctionImplementationContext.CompilingFunctionInfo));

	return true;
}





std::string FParserStates::GetCTXFunctionCompileName(const FProgramInfo& OutProgramInfo) const
{
	if( FunctionDeclarationContext.SignatureInfo.Modifiers.IsExternC )
	{
		return FParserHelperLibrary::GetFunctionCompileName("", "", FunctionDeclarationContext.FunctionName, FunctionDeclarationContext.SignatureInfo, OutProgramInfo);
	}
	

	std::string LFunctionCompileName = "";
	switch( StateContextType )
	{
	case EStateContextType::Global:
	{
		LFunctionCompileName = FParserHelperLibrary::GetFunctionCompileName
		(
			OutProgramInfo.MainModuleName, FunctionDeclarationContext.ClassDeclarationNamespace, FunctionDeclarationContext.FunctionName, FunctionDeclarationContext.SignatureInfo, OutProgramInfo
		);
		break;
	}
	case EStateContextType::InClass:
	{
		const std::string LClassCompileName = FParserHelperLibrary::GetClassCompileName(OutProgramInfo.MainModuleName, ClassDeclarationContext.ClassName, ClassDeclarationContext.TemplateArguments);
		if( LClassCompileName.empty() )
		{
			return "";
		}

		LFunctionCompileName = FParserHelperLibrary::GetFunctionCompileName
		(
			OutProgramInfo.MainModuleName, LClassCompileName, FunctionDeclarationContext.FunctionName, FunctionDeclarationContext.SignatureInfo, OutProgramInfo
		);
		break;
	}
	}

	return LFunctionCompileName;
}

std::string FParserStates::GetCTXClassCompileName(const FProgramInfo& OutProgramInfo) const
{
	return FParserHelperLibrary::GetClassCompileName(OutProgramInfo.MainModuleName, ClassDeclarationContext.ClassName, ClassDeclarationContext.TemplateArguments);
}

std::string FParserStates::GetCTXTypeAliasCompileName(const FProgramInfo& OutProgramInfo) const
{
	std::string LAliasCompileName = "";

	switch( StateContextType )
	{
	case EStateContextType::Global:
	{
		LAliasCompileName = FParserHelperLibrary::GetTypeAliasCompileName(OutProgramInfo.MainModuleName, "", "", AliasDeclarationContext.AliasName);
		break;
	}
	case EStateContextType::InClass:
	{
		const std::string LClassCompileName = FParserHelperLibrary::GetClassCompileName(OutProgramInfo.MainModuleName, ClassDeclarationContext.ClassName, ClassDeclarationContext.TemplateArguments);
		if( LClassCompileName.empty() )
		{
			return "";
		}

		LAliasCompileName = FParserHelperLibrary::GetTypeAliasCompileName(OutProgramInfo.MainModuleName, LClassCompileName, "", AliasDeclarationContext.AliasName);
		break;
	}
	}

	return LAliasCompileName;
}
