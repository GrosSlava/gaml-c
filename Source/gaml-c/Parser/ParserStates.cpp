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
		InParserStates.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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

		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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
		return InParserStates.GGlobalAccessModifier_ParserState;
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.AccessModifierContextType = EAccessModifier::Private;
		return InParserStates.GGlobalAccessModifier_ParserState;
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
		return InParserStates.GStartDescription_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}





IParserState* StartDescription_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::DOG:
	{
		return InParserStates.GDescriptionModifier_ParserState;
	}
	case ETokenType::DESCRIPTION_BLOCK:
	{
		return InParserStates.GEndDescription_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DescriptionModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.DescriptionContext.PrepareForNextModifier();

	switch( InToken.GetType() )
	{
	case ETokenType::EXTERN_C:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsExternC )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsExternC = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::CDECL:
	{
		if( InParserStates.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::CDECL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::STDCALL:
	{
		if( InParserStates.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::STDCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::FASTCALL:
	{
		if( InParserStates.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::FASTCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::THISCALL:
	{
		if( InParserStates.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::THISCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::CONST:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsConst )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsConst = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::MUTABLE:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsMutable )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsMutable = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::STATIC:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsStatic )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsStatic = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::INLINE:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsInline )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsInline = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::VIRTUAL:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsVirtual )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsVirtual = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::OVERRIDE:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsOverride )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsOverride = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::ABSTRACT:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsAbstract )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsAbstract = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::FINAL:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsFinal )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsFinal = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::DEPRECATED:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsDeprecated )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsDeprecated = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::UNIMPLEMENTED:
	{
		if( InParserStates.DescriptionContext.Modfiers.IsUnimplemented )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.DescriptionContext.Modfiers.IsUnimplemented = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::ALIGN:
	{
		if( InParserStates.DescriptionContext.Modfiers.Align != -1 )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		return InParserStates.GDescriptionAlign1_ParserState;
	}
	case ETokenType::PARAM:
	{
		InParserStates.DescriptionContext.DescriptionContext = EDescriptionContext::Param;
		return InParserStates.GDescriptionParam1_ParserState;
	}
	case ETokenType::RETURN:
	{
		InParserStates.DescriptionContext.DescriptionContext = EDescriptionContext::Return;
		return InParserStates.GDescriptionParam1_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DescriptionAlign1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::LPAR )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LPAR, InToken);
		return nullptr;
	}

	InParserStates.DescriptionContext.OpenBracketLayer = 1;
	return InParserStates.GDescriptionAlign2_ParserState;
}

IParserState* DescriptionAlign2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		++InParserStates.DescriptionContext.OpenBracketLayer;
		InParserStates.DescriptionContext.CodeTokens.push_back(InToken);

		return InParserStates.GDescriptionAlign2_ParserState;
	}
	case ETokenType::RPAR:
	{
		--InParserStates.DescriptionContext.OpenBracketLayer;
		if( InParserStates.DescriptionContext.OpenBracketLayer == 0 )
		{
			return InParserStates.GDescriptionAlign3_ParserState;
		}

		InParserStates.DescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionAlign2_ParserState;
	}
	default:
	{
		InParserStates.DescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionAlign2_ParserState;
	}
	}

	return nullptr;
}

IParserState* DescriptionAlign3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::DOG:
	{
		return InParserStates.GDescriptionModifier_ParserState;
	}
	case ETokenType::DESCRIPTION_BLOCK:
	{
		return InParserStates.GEndDescription_ParserState;
	}
	}

	AST LAST;
	LAST.BuildAST(InParserStates.DescriptionContext.CodeTokens);
	//TODO interpret ast
	//InParserStates.DescriptionContext.Modfiers.Align =

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DescriptionParam1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	switch( InParserStates.DescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		FVariableInfo LNewVariable;
		LNewVariable.VariableName = InToken.GetLexeme();
		LNewVariable.MetaInfo.DeclaredAtLine = InToken.GetLine();
		LNewVariable.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.DescriptionContext.Inputs.push_back(LNewVariable);
		break;
	}
	case EDescriptionContext::Return:
	{
		if( !InParserStates.DescriptionContext.Return.VariableName.empty() )
		{
			InParserStates.RaiseError(EErrorMessageType::ARGUMENT_NAME_REDEFINITION, InToken);
			return nullptr;
		}

		InParserStates.DescriptionContext.Return.VariableName = InToken.GetLexeme();
		InParserStates.DescriptionContext.Return.MetaInfo.DeclaredAtLine = InToken.GetLine();
		InParserStates.DescriptionContext.Return.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		break;
	}
	default:
	{
		InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
		return nullptr;
	}
	}

	return InParserStates.GDescriptionParam2_ParserState;
}

IParserState* DescriptionParam2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::COLON )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_COLON, InToken);
		return nullptr;
	}

	return InParserStates.GDescriptionParam3_ParserState;
}

IParserState* DescriptionParam3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsModifierToken(InToken) )
	{
		switch( InToken.GetType() )
		{
		case ETokenType::CONST:
		{
			switch( InParserStates.DescriptionContext.DescriptionContext )
			{
			case EDescriptionContext::Param:
			{
				if( InParserStates.DescriptionContext.Inputs.back().Modifiers.IsConst )
				{
					InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.DescriptionContext.Inputs.back().Modifiers.IsConst = true;
				break;
			}
			case EDescriptionContext::Return:
			{
				if( InParserStates.DescriptionContext.Return.Modifiers.IsConst )
				{
					InParserStates.RaiseError(EErrorMessageType::RETURN_TYPE_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.DescriptionContext.Return.Modifiers.IsConst = true;
				break;
			}
			default:
			{
				InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
				return nullptr;
			}
			}

			return InParserStates.GDescriptionParam3_ParserState;
		}
		case ETokenType::MUTABLE:
		{
			switch( InParserStates.DescriptionContext.DescriptionContext )
			{
			case EDescriptionContext::Param:
			{
				if( InParserStates.DescriptionContext.Inputs.back().Modifiers.IsMutable )
				{
					InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.DescriptionContext.Inputs.back().Modifiers.IsMutable = true;
				break;
			}
			case EDescriptionContext::Return:
			{
				if( InParserStates.DescriptionContext.Return.Modifiers.IsMutable )
				{
					InParserStates.RaiseError(EErrorMessageType::RETURN_TYPE_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.DescriptionContext.Return.Modifiers.IsMutable = true;
				break;
			}
			default:
			{
				InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
				return nullptr;
			}
			}

			return InParserStates.GDescriptionParam3_ParserState;
		}
		}
	}
	else if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		switch( InParserStates.DescriptionContext.DescriptionContext )
		{
		case EDescriptionContext::Param:
		{
			InParserStates.DescriptionContext.Inputs.back().TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
			break;
		}
		case EDescriptionContext::Return:
		{
			InParserStates.DescriptionContext.Return.TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
			break;
		}
		default:
		{
			InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
			return nullptr;
		}
		}

		return InParserStates.GDescriptionParam4_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		switch( InParserStates.DescriptionContext.DescriptionContext )
		{
		case EDescriptionContext::Param:
		{
			//TODO
			break;
		}
		case EDescriptionContext::Return:
		{
			//TODO
			break;
		}
		default:
		{
			InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
			return nullptr;
		}
		}

		return InParserStates.GDescriptionParam4_ParserState;
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		switch( InParserStates.DescriptionContext.DescriptionContext )
		{
		case EDescriptionContext::Param:
		{
			//TODO lambda
			break;
		}
		case EDescriptionContext::Return:
		{
			//TODO lambda
			break;
		}
		default:
		{
			InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
			return nullptr;
		}
		}

		return InParserStates.GDescriptionParam4_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		switch( InParserStates.DescriptionContext.DescriptionContext )
		{
		case EDescriptionContext::Param:
		{
			//TODO user type
			break;
		}
		case EDescriptionContext::Return:
		{
			//TODO user type
			break;
		}
		default:
		{
			InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
			return nullptr;
		}
		}

		return InParserStates.GDescriptionParam4_ParserState;
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DescriptionParam4_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		InParserStates.DescriptionContext.OpenBracketLayer = 1;
		return InParserStates.GDescriptionParam5_ParserState;
	}
	case ETokenType::DOG:
	{
		return InParserStates.GDescriptionModifier_ParserState;
	}
	case ETokenType::DESCRIPTION_BLOCK:
	{
		return InParserStates.GEndDescription_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DescriptionParam5_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		++InParserStates.DescriptionContext.OpenBracketLayer;
		InParserStates.DescriptionContext.CodeTokens.push_back(InToken);

		return InParserStates.GDescriptionParam5_ParserState;
	}
	case ETokenType::RPAR:
	{
		--InParserStates.DescriptionContext.OpenBracketLayer;
		if( InParserStates.DescriptionContext.OpenBracketLayer == 0 )
		{
			return InParserStates.GDescriptionParam6_ParserState;
		}

		InParserStates.DescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionParam5_ParserState;
	}
	default:
	{
		InParserStates.DescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionParam5_ParserState;
	}
	}

	return nullptr;
}

IParserState* DescriptionParam6_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InParserStates.DescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		InParserStates.DescriptionContext.Inputs.back().DefaultValueTree.BuildAST(InParserStates.DescriptionContext.CodeTokens);
		break;
	}
	case EDescriptionContext::Return:
	{
		InParserStates.DescriptionContext.Return.DefaultValueTree.BuildAST(InParserStates.DescriptionContext.CodeTokens);
		break;
	}
	default:
	{
		InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
		return nullptr;
	}
	}


	switch( InToken.GetType() )
	{
	case ETokenType::DOG:
	{
		return InParserStates.GDescriptionModifier_ParserState;
	}
	case ETokenType::DESCRIPTION_BLOCK:
	{
		return InParserStates.GEndDescription_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* EndDescription_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::MODULE:
	{
		if( InParserStates.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.ModuleDeclarationContext.ModuleInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareModule_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.FunctionDeclarationContext.SignatureInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Inputs = InParserStates.DescriptionContext.Inputs;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Return = InParserStates.DescriptionContext.Return;
		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();


		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		if( InParserStates.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		if( InParserStates.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		if( InParserStates.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		if( InParserStates.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		if( InParserStates.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::PUBLIC:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.AccessModifierContextType = EAccessModifier::Public;

		if( InParserStates.StateContextType == EStateContextType::Global )
		{
			return InParserStates.GGlobalAccessModifier_ParserState;
		}
		else
		{
			return InParserStates.GLocalAccessModifier_ParserState;
		}
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.AccessModifierContextType = EAccessModifier::Private;

		if( InParserStates.StateContextType == EStateContextType::Global )
		{
			return InParserStates.GGlobalAccessModifier_ParserState;
		}
		else
		{
			return InParserStates.GLocalAccessModifier_ParserState;
		}
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}



IParserState* GlobalAccessModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		InParserStates.StateContextType = EStateContextType::Global;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Modifiers.AccessModifier = InParserStates.AccessModifierContextType;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Inputs = InParserStates.DescriptionContext.Inputs;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Return = InParserStates.DescriptionContext.Return;
		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.AccessModifierContextType;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.AccessModifierContextType;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.AccessModifierContextType;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.AccessModifierContextType;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.StateContextType = EStateContextType::InClass;
		InParserStates.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.AccessModifierContextType;
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* LocalAccessModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		//TODO Class variable
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		//TODO
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		//TODO lambda
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		//TODO user type
	}

	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		InParserStates.FunctionDeclarationContext.SignatureInfo.Modifiers = InParserStates.DescriptionContext.Modfiers;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Modifiers.AccessModifier = InParserStates.AccessModifierContextType;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Inputs = InParserStates.DescriptionContext.Inputs;
		InParserStates.FunctionDeclarationContext.SignatureInfo.Return = InParserStates.DescriptionContext.Return;
		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STATIC:
	{
		//TODO
	}
	case ETokenType::CONST:
	{
		//TODO
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
		else
		{
			return InParserStates.GDeclareClassInternal_ParserState;
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
		else
		{
			return InParserStates.GDeclareClassInternal_ParserState;
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
				return InParserStates.GDeclareClassInternal_ParserState;
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
	switch( InToken.GetType() )
	{
	case ETokenType::LTRI:
	{
		return InParserStates.GDeclareClass1_ParserState;
	}
	case ETokenType::IDENTIFIER:
	{
		InParserStates.ClassDeclarationContext.ClassName = InToken.GetLexeme();
		return InParserStates.GDeclareClass4_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		InParserStates.ClassDeclarationContext.TemplateArguments.push_back(FParserHelperLibrary::GetTypeName(FParserHelperLibrary::GetStandardTypeID(InToken), OutProgramInfo));
		return InParserStates.GDeclareClass2_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		//TODO
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		//TODO lambda
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		//TODO user type
		return InParserStates.GDeclareClass2_ParserState;
	}


	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::RTRI:
	{
		return InParserStates.GDeclareClass3_ParserState;
	}
	case ETokenType::COMMA:
	{
		return InParserStates.GDeclareClass1_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}


	InParserStates.ClassDeclarationContext.ClassName = InToken.GetLexeme();
	return InParserStates.GDeclareClass4_ParserState;
}

IParserState* DeclareClass4_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		return InParserStates.GDeclareClass5_ParserState;
	}
	case ETokenType::LBRA:
	{
		if( !InParserStates.RegisterClassFromContext(OutProgramInfo, InToken) )
		{
			return nullptr;
		}
		return InParserStates.GDeclareClassInternal_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass5_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		InParserStates.ClassDeclarationContext.ClassInfo.ParentTypesID.push_back(FParserHelperLibrary::GetStandardTypeID(InToken));
		return InParserStates.GDeclareClass6_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		//TODO
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		//TODO user type
		return InParserStates.GDeclareClass6_ParserState;
	}


	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass6_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::RPAR:
	{
		return InParserStates.GDeclareClass7_ParserState;
	}
	case ETokenType::COMMA:
	{
		return InParserStates.GDeclareClass5_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass7_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::LBRA )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LBRA, InToken);
		return nullptr;
	}


	if( !InParserStates.RegisterClassFromContext(OutProgramInfo, InToken) )
	{
		return nullptr;
	}
	return InParserStates.GDeclareClassInternal_ParserState;
}

IParserState* DeclareClassInternal_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		// TODO variable
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		//TODO
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		//TODO lambda
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		//TODO user type
	}

	switch( InToken.GetType() )
	{
	case ETokenType::DESCRIPTION_BLOCK:
	{
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::PUBLIC:
	{
		InParserStates.AccessModifierContextType = EAccessModifier::Public;

		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::PROTECTED:
	{
		InParserStates.AccessModifierContextType = EAccessModifier::Protected;

		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.AccessModifierContextType = EAccessModifier::Private;

		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STATIC_ASSERT:
	{
		return InParserStates.GStartStaticAssert_ParserState;
	}
	case ETokenType::STATIC:
	{
		//TODO
	}
	case ETokenType::CONST:
	{
		//TODO
	}
	case ETokenType::RBRA:
	{
		return InParserStates.GDefault_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
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
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		//TODO lambda
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		//TODO user type
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
		return InParserStates.GDeclareClassInternal_ParserState;
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
		return InParserStates.GDeclareClassInternal_ParserState;
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





FParserStates::FParserStates(const FGamlFileInfo& InFileInfo, const FCompileOptions& InCompileOptions, bool InIsMainModule) : FileInfo(InFileInfo), CompileOptions(InCompileOptions), IsMainModule(InIsMainModule)
{
#define CREATE_STATE(StateName) G##StateName##_ParserState = new StateName##_ParserState();


	CREATE_STATE(Default)

	CREATE_STATE(StartDescription)
	CREATE_STATE(DescriptionModifier)
	CREATE_STATE(DescriptionAlign1)
	CREATE_STATE(DescriptionAlign2)
	CREATE_STATE(DescriptionAlign3)
	CREATE_STATE(DescriptionParam1)
	CREATE_STATE(DescriptionParam2)
	CREATE_STATE(DescriptionParam3)
	CREATE_STATE(DescriptionParam4)
	CREATE_STATE(DescriptionParam5)
	CREATE_STATE(DescriptionParam6)
	CREATE_STATE(EndDescription)

	CREATE_STATE(GlobalAccessModifier)
	CREATE_STATE(LocalAccessModifier)


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
	CREATE_STATE(DeclareClass1)
	CREATE_STATE(DeclareClass2)
	CREATE_STATE(DeclareClass3)
	CREATE_STATE(DeclareClass4)
	CREATE_STATE(DeclareClass5)
	CREATE_STATE(DeclareClass6)
	CREATE_STATE(DeclareClass7)
	CREATE_STATE(DeclareClassInternal)


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
#define DELETE_STATE(StateName) \
	if( G##StateName##_ParserState != nullptr ) delete G##StateName##_ParserState;


	DELETE_STATE(Default)

	DELETE_STATE(StartDescription)
	DELETE_STATE(DescriptionModifier)
	DELETE_STATE(DescriptionAlign1)
	DELETE_STATE(DescriptionAlign2)
	DELETE_STATE(DescriptionAlign3)
	DELETE_STATE(DescriptionParam1)
	DELETE_STATE(DescriptionParam2)
	DELETE_STATE(DescriptionParam3)
	DELETE_STATE(DescriptionParam4)
	DELETE_STATE(DescriptionParam5)
	DELETE_STATE(DescriptionParam6)
	DELETE_STATE(EndDescription)

	DELETE_STATE(GlobalAccessModifier)
	DELETE_STATE(LocalAccessModifier)


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
	DELETE_STATE(DeclareClass1)
	DELETE_STATE(DeclareClass2)
	DELETE_STATE(DeclareClass3)
	DELETE_STATE(DeclareClass4)
	DELETE_STATE(DeclareClass5)
	DELETE_STATE(DeclareClass6)
	DELETE_STATE(DeclareClass7)
	DELETE_STATE(DeclareClassInternal)


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
		// clang-format off
		if( 
			OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.find(ModuleImportingContext.AliasName) != 
			OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.end() 
		  )
		// clang-format on
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

	// clang-format off
	if(
		StateContextType == EStateContextType::InClass &&
		(FunctionDeclarationContext.SignatureInfo.Modifiers.IsVirtual || FunctionDeclarationContext.SignatureInfo.Modifiers.IsOverride || FunctionDeclarationContext.SignatureInfo.Modifiers.IsAbstract) 
	  )
	// clang-format on
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
		// clang-format off
		LFunctionCompileName = FParserHelperLibrary::GetFunctionCompileName
		(
			OutProgramInfo.MainModuleName, FunctionDeclarationContext.ClassDeclarationNamespace, FunctionDeclarationContext.FunctionName, FunctionDeclarationContext.SignatureInfo, OutProgramInfo
		);
		// clang-format on
		break;
	}
	case EStateContextType::InClass:
	{
		// clang-format off
		const std::string LClassCompileName = FParserHelperLibrary::GetClassCompileName(OutProgramInfo.MainModuleName, ClassDeclarationContext.ClassName, ClassDeclarationContext.TemplateArguments);
		if( LClassCompileName.empty() )
		{
			return "";
		}
		// clang-format on

		// clang-format off
		LFunctionCompileName = FParserHelperLibrary::GetFunctionCompileName
		(
			OutProgramInfo.MainModuleName, LClassCompileName, FunctionDeclarationContext.FunctionName, FunctionDeclarationContext.SignatureInfo, OutProgramInfo
		);
		// clang-format on
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
