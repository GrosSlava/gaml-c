// Copyright 2022 GrosSlava.

#include "ParserStates.h"
#include "../ParserHelperLibray.h"

#include "../../Compiler/CompilerConfig.h"
#include "../../Compiler/CompilerHelperLibrary.h"

#include "../../Lexer/Lexer.h"
#include "../../Parser/Parser.h"

#include <fstream>
#include <algorithm>





IParserState* Default_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.StateContextType = EStateContextType::Global;
	InParserStates.StatesContext.ClearContexts();


	switch( InToken.GetType() )
	{
	case ETokenType::SEMICOLON:
	{
		return InParserStates.GDefault_ParserState;
	}
	case ETokenType::MODULE:
	{
		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareModule_ParserState;
	}
	case ETokenType::IMPLEMENT:
	{
		InParserStates.PushState(InParserStates.GDefault_ParserState);

		return InParserStates.GStartImplementModule_ParserState;
	}
	case ETokenType::IMPORT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		return InParserStates.GStartImportModule_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::USING:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		return InParserStates.GStartDefineAlias_ParserState;
	}
	case ETokenType::PUBLIC:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Public;
		return InParserStates.GGlobalAccessModifier_ParserState;
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Private;
		return InParserStates.GGlobalAccessModifier_ParserState;
	}
	case ETokenType::STATIC_ASSERT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.PushState(InParserStates.GDefault_ParserState);

		return InParserStates.GStartStaticAssert_ParserState;
	}
	case ETokenType::DESCRIPTION_BLOCK:
	{
		InParserStates.PushState(InParserStates.GDefault_ParserState);

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
	InParserStates.StatesContext.DescriptionContext.PrepareForNextModifier();

	switch( InToken.GetType() )
	{
	case ETokenType::EXTERN_C:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsExternC )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsExternC = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::CDECL:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::CDECL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::STDCALL:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::STDCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::FASTCALL:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::FASTCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::THISCALL:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::THISCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::CONST:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsConst )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsConst = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::MUTABLE:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsMutable )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsMutable = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::STATIC:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsStatic )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsStatic = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::INLINE:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsInline )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsInline = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::VIRTUAL:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsVirtual )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsVirtual = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::OVERRIDE:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsOverride )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsOverride = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::ABSTRACT:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsAbstract )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsAbstract = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::FINAL:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsFinal )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsFinal = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::DEPRECATED:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsDeprecated )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsDeprecated = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::UNIMPLEMENTED:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.IsUnimplemented )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		InParserStates.StatesContext.DescriptionContext.Modfiers.IsUnimplemented = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::ALIGN:
	{
		if( InParserStates.StatesContext.DescriptionContext.Modfiers.Align != -1 )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		return InParserStates.GDescriptionAlign1_ParserState;
	}
	case ETokenType::PARAM:
	{
		InParserStates.StatesContext.DescriptionContext.DescriptionContext = EDescriptionContext::Param;
		return InParserStates.GDescriptionParam1_ParserState;
	}
	case ETokenType::RETURN:
	{
		InParserStates.StatesContext.DescriptionContext.DescriptionContext = EDescriptionContext::Return;
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

	InParserStates.StatesContext.DescriptionContext.OpenBracketLayer = 1;
	return InParserStates.GDescriptionAlign2_ParserState;
}

IParserState* DescriptionAlign2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		++InParserStates.StatesContext.DescriptionContext.OpenBracketLayer;
		InParserStates.StatesContext.DescriptionContext.CodeTokens.push_back(InToken);

		return InParserStates.GDescriptionAlign2_ParserState;
	}
	case ETokenType::RPAR:
	{
		--InParserStates.StatesContext.DescriptionContext.OpenBracketLayer;
		if( InParserStates.StatesContext.DescriptionContext.OpenBracketLayer == 0 )
		{
			return InParserStates.GDescriptionAlign3_ParserState;
		}

		InParserStates.StatesContext.DescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionAlign2_ParserState;
	}
	default:
	{
		InParserStates.StatesContext.DescriptionContext.CodeTokens.push_back(InToken);
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
	LAST.BuildAST(InParserStates.StatesContext.DescriptionContext.CodeTokens);
	LAST.InterpretAST(OutProgramInfo);
	InParserStates.StatesContext.DescriptionContext.Modfiers.Align = LAST.GetInterpretResultAsInt();

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

	switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		FVariableInfo LNewVariable;
		LNewVariable.VariableName = InToken.GetLexeme();
		LNewVariable.MetaInfo.DeclaredAtLine = InToken.GetLine();
		LNewVariable.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.DescriptionContext.Inputs.push_back(LNewVariable);
		break;
	}
	case EDescriptionContext::Return:
	{
		if( !InParserStates.StatesContext.DescriptionContext.Return.VariableName.empty() )
		{
			InParserStates.RaiseError(EErrorMessageType::ARGUMENT_NAME_REDEFINITION, InToken);
			return nullptr;
		}

		InParserStates.StatesContext.DescriptionContext.Return.VariableName = InToken.GetLexeme();
		InParserStates.StatesContext.DescriptionContext.Return.MetaInfo.DeclaredAtLine = InToken.GetLine();
		InParserStates.StatesContext.DescriptionContext.Return.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
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
			switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
			{
			case EDescriptionContext::Param:
			{
				if( InParserStates.StatesContext.DescriptionContext.Inputs.back().Modifiers.IsConst )
				{
					InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.StatesContext.DescriptionContext.Inputs.back().Modifiers.IsConst = true;
				break;
			}
			case EDescriptionContext::Return:
			{
				if( InParserStates.StatesContext.DescriptionContext.Return.Modifiers.IsConst )
				{
					InParserStates.RaiseError(EErrorMessageType::RETURN_TYPE_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.StatesContext.DescriptionContext.Return.Modifiers.IsConst = true;
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
			switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
			{
			case EDescriptionContext::Param:
			{
				if( InParserStates.StatesContext.DescriptionContext.Inputs.back().Modifiers.IsMutable )
				{
					InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.StatesContext.DescriptionContext.Inputs.back().Modifiers.IsMutable = true;
				break;
			}
			case EDescriptionContext::Return:
			{
				if( InParserStates.StatesContext.DescriptionContext.Return.Modifiers.IsMutable )
				{
					InParserStates.RaiseError(EErrorMessageType::RETURN_TYPE_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				InParserStates.StatesContext.DescriptionContext.Return.Modifiers.IsMutable = true;
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
		switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
		{
		case EDescriptionContext::Param:
		{
			InParserStates.StatesContext.DescriptionContext.Inputs.back().TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
			break;
		}
		case EDescriptionContext::Return:
		{
			InParserStates.StatesContext.DescriptionContext.Return.TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
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
		InParserStates.PushState(InParserStates.GDescriptionParam4_ParserState);
		InParserStates.PushState(InParserStates.GDescriptionParamBuildinTemplateType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.BuildinTemplateTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		InParserStates.PushState(InParserStates.GDescriptionParam4_ParserState);
		InParserStates.PushState(InParserStates.GDescriptionParamLambdaType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();

		return InParserStates.GStartLambdaType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.PushState(InParserStates.GDescriptionParam4_ParserState);
		InParserStates.PushState(InParserStates.GDescriptionParamUserType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.UserTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartUserType_ParserState;
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
		InParserStates.StatesContext.DescriptionContext.OpenBracketLayer = 1;
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
		++InParserStates.StatesContext.DescriptionContext.OpenBracketLayer;
		InParserStates.StatesContext.DescriptionContext.CodeTokens.push_back(InToken);

		return InParserStates.GDescriptionParam5_ParserState;
	}
	case ETokenType::RPAR:
	{
		--InParserStates.StatesContext.DescriptionContext.OpenBracketLayer;
		if( InParserStates.StatesContext.DescriptionContext.OpenBracketLayer == 0 )
		{
			return InParserStates.GDescriptionParam6_ParserState;
		}

		InParserStates.StatesContext.DescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionParam5_ParserState;
	}
	default:
	{
		InParserStates.StatesContext.DescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionParam5_ParserState;
	}
	}

	return nullptr;
}

IParserState* DescriptionParam6_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		InParserStates.StatesContext.DescriptionContext.Inputs.back().DefaultValueTree.BuildAST(InParserStates.StatesContext.DescriptionContext.CodeTokens);
		break;
	}
	case EDescriptionContext::Return:
	{
		InParserStates.StatesContext.DescriptionContext.Return.DefaultValueTree.BuildAST(InParserStates.StatesContext.DescriptionContext.CodeTokens);
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
	// state to return already pushed

	switch( InToken.GetType() )
	{
	case ETokenType::MODULE:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.StatesContext.ModuleDeclarationContext.ModuleInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ModuleDeclarationContext.ModuleInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareModule_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Inputs = InParserStates.StatesContext.DescriptionContext.Inputs;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Return = InParserStates.StatesContext.DescriptionContext.Return;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();


		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::PUBLIC:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Public;

		if( InParserStates.StatesContext.StateContextType == EStateContextType::Global )
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

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Private;

		if( InParserStates.StatesContext.StateContextType == EStateContextType::Global )
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

IParserState* DescriptionParamBuildinTemplateType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		InParserStates.StatesContext.DescriptionContext.Inputs.back().TypeID = InParserStates.StatesContext.BuildinTemplateTypeContext.TypeID;
		break;
	}
	case EDescriptionContext::Return:
	{
		InParserStates.StatesContext.DescriptionContext.Return.TypeID = InParserStates.StatesContext.BuildinTemplateTypeContext.TypeID;
		break;
	}
	default:
	{
		InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
		return nullptr;
	}
	}

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DescriptionParamLambdaType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		InParserStates.StatesContext.DescriptionContext.Inputs.back().TypeID = InParserStates.StatesContext.LambdaTypeContext.TypeID;
		break;
	}
	case EDescriptionContext::Return:
	{
		InParserStates.StatesContext.DescriptionContext.Return.TypeID = InParserStates.StatesContext.LambdaTypeContext.TypeID;
		break;
	}
	default:
	{
		InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
		return nullptr;
	}
	}

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DescriptionParamUserType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InParserStates.StatesContext.DescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		InParserStates.StatesContext.DescriptionContext.Inputs.back().TypeID = InParserStates.StatesContext.UserTypeContext.TypeID;
		break;
	}
	case EDescriptionContext::Return:
	{
		InParserStates.StatesContext.DescriptionContext.Return.TypeID = InParserStates.StatesContext.UserTypeContext.TypeID;
		break;
	}
	default:
	{
		InParserStates.RaiseError(EErrorMessageType::INVALID_STATE, InToken);
		return nullptr;
	}
	}

	return InParserStates.PopStateChecked(InToken);
}



IParserState* GlobalAccessModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	// global state already pushed

	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::Global;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Inputs = InParserStates.StatesContext.DescriptionContext.Inputs;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Return = InParserStates.StatesContext.DescriptionContext.Return;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Struct;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Interface;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Object;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Component;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType = EClassType::Enum;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* LocalAccessModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	// local state already pushed

	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Inputs = InParserStates.StatesContext.DescriptionContext.Inputs;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.Return = InParserStates.StatesContext.DescriptionContext.Return;
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::VAR:
	{
		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareField_ParserState;
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


	InParserStates.StatesContext.ModuleDeclarationContext.ModulePath.push_back(InToken.GetLexeme());

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

		return InParserStates.PopStateChecked(InToken);
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


	InParserStates.StatesContext.ModuleImplementingContext.ModulePath.push_back(InToken.GetLexeme());

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

		return InParserStates.PopStateChecked(InToken);
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


	InParserStates.StatesContext.ModuleImportingContext.ModulePath.push_back(InToken.GetLexeme());

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

		return InParserStates.PopStateChecked(InToken);
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


	InParserStates.StatesContext.ModuleImportingContext.AliasName = InToken.GetLexeme();

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

	return InParserStates.PopStateChecked(InToken);
}





IParserState* StartDeclareFunction_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_FUNCTION_NAME, InToken);
		return nullptr;
	}


	InParserStates.StatesContext.FunctionDeclarationContext.FunctionName = InToken.GetLexeme();
	return InParserStates.GDeclareFunction1_ParserState;
}

IParserState* DeclareFunction1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::NAMESPACE_ACCESS_OPERATOR:
	{
		if( InParserStates.StatesContext.FunctionDeclarationContext.ClassDeclarationNamespace.empty() )
		{
			InParserStates.StatesContext.FunctionDeclarationContext.ClassDeclarationNamespace =
				InParserStates.StatesContext.FunctionDeclarationContext.FunctionName;
			InParserStates.StatesContext.FunctionDeclarationContext.FunctionName.clear();
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

		return InParserStates.PopStateChecked(InToken);
	}
	case ETokenType::LSQR:
	{
		InParserStates.StatesContext.FunctionDeclarationContext.StaticCodeOpenBracketLayer = 1;
		return InParserStates.GDeclareFunction2_ParserState;
	}
	case ETokenType::LBRA:
	{
		if( !InParserStates.RegisterFunctionFromContext(OutProgramInfo, true, InToken) )
		{
			return nullptr;
		}

		InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeOpenBracketLayer = 1;
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
		++InParserStates.StatesContext.FunctionDeclarationContext.StaticCodeOpenBracketLayer;
		InParserStates.StatesContext.FunctionDeclarationContext.StaticCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction2_ParserState;
	}
	case ETokenType::RSQR:
	{
		--InParserStates.StatesContext.FunctionDeclarationContext.StaticCodeOpenBracketLayer;
		if( InParserStates.StatesContext.FunctionDeclarationContext.StaticCodeOpenBracketLayer == 0 )
		{
			return InParserStates.GDeclareFunction3_ParserState;
		}

		InParserStates.StatesContext.FunctionDeclarationContext.StaticCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction2_ParserState;
	}
	default:
	{
		InParserStates.StatesContext.FunctionDeclarationContext.StaticCodeTokens.push_back(InToken);
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

		return InParserStates.PopStateChecked(InToken);
	}
	case ETokenType::LBRA:
	{
		if( !InParserStates.RegisterFunctionFromContext(OutProgramInfo, true, InToken) )
		{
			return nullptr;
		}

		InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeOpenBracketLayer = 1;
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
		++InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeOpenBracketLayer;
		InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction4_ParserState;
	}
	case ETokenType::RBRA:
	{
		--InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeOpenBracketLayer;
		if( InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeOpenBracketLayer == 0 )
		{
			if( !InParserStates.RegisterFunctionImplementationFromContext(OutProgramInfo, InToken) )
			{
				return nullptr;
			}

			return InParserStates.PopStateChecked(InToken);
		}

		InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction4_ParserState;
	}
	default:
	{
		InParserStates.StatesContext.FunctionImplementationContext.FunctionCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction4_ParserState;
	}
	}

	return nullptr;
}



IParserState* StartDeclareClass_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_CLASS_NAME, InToken);
	}

	InParserStates.StatesContext.ClassDeclarationContext.ClassName = InToken.GetLexeme();
	return InParserStates.GDeclareClass1_ParserState;
}

IParserState* DeclareClass1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		return InParserStates.GDeclareClass2_ParserState;
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

IParserState* DeclareClass2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ParentTypesID.push_back(FParserHelperLibrary::GetStandardTypeID(InToken));
		return InParserStates.GDeclareClass3_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		InParserStates.PushState(InParserStates.GDeclareClass3_ParserState);
		InParserStates.PushState(InParserStates.GDeclareClassParentBuildinTemplateType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.BuildinTemplateTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.PushState(InParserStates.GDeclareClass3_ParserState);
		InParserStates.PushState(InParserStates.GDeclareClassParentUserType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.UserTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartUserType_ParserState;
	}


	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::RPAR:
	{
		return InParserStates.GDeclareClass4_ParserState;
	}
	case ETokenType::COMMA:
	{
		return InParserStates.GDeclareClass2_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClass4_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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
	InParserStates.StatesContext.StateContextType = EStateContextType::InClass;
	InParserStates.StatesContext.ClearContextsLocal();

	switch( InToken.GetType() )
	{
	case ETokenType::DESCRIPTION_BLOCK:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::PUBLIC:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Public;

		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::PROTECTED:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Protected;

		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Private;

		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.FunctionDeclarationContext.SignatureInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::VAR:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareField_ParserState;
	}
	case ETokenType::STATIC_ASSERT:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		return InParserStates.GStartStaticAssert_ParserState;
	}
	case ETokenType::USING:
	{
		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);

		return InParserStates.GStartDefineAlias_ParserState;
	}
	case ETokenType::RBRA:
	{
		if( !InParserStates.FinishClassRegistrationFromContext(OutProgramInfo, InToken) )
		{
			return nullptr;
		}
		return InParserStates.PopStateChecked(InToken);
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareClassParentBuildinTemplateType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ParentTypesID.push_back(InParserStates.StatesContext.BuildinTemplateTypeContext.TypeID);

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DeclareClassParentUserType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ParentTypesID.push_back(InParserStates.StatesContext.UserTypeContext.TypeID);

	return InParserStates.PopStateChecked(InToken);
}



IParserState* StartDeclareField_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
		return InParserStates.GDeclareField1_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		InParserStates.PushState(InParserStates.GDeclareField1_ParserState);
		InParserStates.PushState(InParserStates.GDeclareFieldBuildinTemplateType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.BuildinTemplateTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		InParserStates.PushState(InParserStates.GDeclareField1_ParserState);
		InParserStates.PushState(InParserStates.GDeclareFieldLambdaType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();

		return InParserStates.GStartLambdaType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.PushState(InParserStates.GDeclareField1_ParserState);
		InParserStates.PushState(InParserStates.GDeclareFieldUserType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.UserTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartUserType_ParserState;
	}

	switch( InToken.GetType() )
	{
	case ETokenType::STATIC:
	{
		if( InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.Modifiers.IsStatic )
		{
			InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
		}

		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.Modifiers.IsStatic = true;
		return InParserStates.GStartDeclareField_ParserState;
	}
	case ETokenType::CONST:
	{
		if( InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.Modifiers.IsConst )
		{
			InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
		}

		InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.Modifiers.IsConst = true;
		return InParserStates.GStartDeclareField_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareField1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
	}

	InParserStates.StatesContext.VariableDeclarationContext.VariableName = InToken.GetLexeme();

	return InParserStates.GDeclareField2_ParserState;
}

IParserState* DeclareField2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::ASSIGN:
	{
		return InParserStates.GDeclareField3_ParserState;
	}
	case ETokenType::SEMICOLON:
	{
		if( !InParserStates.RegisterVariableFromContext(OutProgramInfo, InToken) )
		{
			return nullptr;
		}

		return InParserStates.PopStateChecked(InToken);
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* DeclareField3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() == ETokenType::SEMICOLON )
	{
		if( InParserStates.StatesContext.VariableDeclarationContext.DefaultValueTokens.empty() )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
		}

		if( !InParserStates.RegisterVariableFromContext(OutProgramInfo, InToken) )
		{
			return nullptr;
		}

		return InParserStates.PopStateChecked(InToken);
	}
	else
	{
		InParserStates.StatesContext.VariableDeclarationContext.DefaultValueTokens.push_back(InToken);
	}

	return InParserStates.GDeclareField3_ParserState;
}

IParserState* DeclareFieldBuildinTemplateType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.TypeID = InParserStates.StatesContext.BuildinTemplateTypeContext.TypeID;

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DeclareFieldLambdaType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.TypeID = InParserStates.StatesContext.LambdaTypeContext.TypeID;

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DeclareFieldUserType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.VariableDeclarationContext.VariableInfo.TypeID = InParserStates.StatesContext.UserTypeContext.TypeID;

	return InParserStates.PopStateChecked(InToken);
}





IParserState* StartDefineAlias_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_ALIAS_NAME, InToken);
		return nullptr;
	}


	InParserStates.StatesContext.AliasDeclarationContext.AliasName = InToken.GetLexeme();
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
		InParserStates.StatesContext.AliasDeclarationContext.OriginalTypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
		return InParserStates.GDefineAlias3_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		InParserStates.PushState(InParserStates.GDefineAlias3_ParserState);
		InParserStates.PushState(InParserStates.GDefineAliasBuildinTemplateType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.BuildinTemplateTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		InParserStates.PushState(InParserStates.GDefineAlias3_ParserState);
		InParserStates.PushState(InParserStates.GDefineAliasLambdaType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();

		return InParserStates.GStartLambdaType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.PushState(InParserStates.GDefineAlias3_ParserState);
		InParserStates.PushState(InParserStates.GDefineAliasUserType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.UserTypeContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartUserType_ParserState;
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

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DefineAliasBuildinTemplateType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.AliasDeclarationContext.OriginalTypeID = InParserStates.StatesContext.BuildinTemplateTypeContext.TypeID;

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DefineAliasLambdaType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.AliasDeclarationContext.OriginalTypeID = InParserStates.StatesContext.LambdaTypeContext.TypeID;

	return InParserStates.PopStateChecked(InToken);
}

IParserState* DefineAliasUserType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	InParserStates.StatesContext.AliasDeclarationContext.OriginalTypeID = InParserStates.StatesContext.UserTypeContext.TypeID;

	return InParserStates.PopStateChecked(InToken);
}



IParserState* StartStaticAssert_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::LPAR )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LPAR, InToken);
		return nullptr;
	}


	InParserStates.StatesContext.StaticAssertContext.Clear();

	return InParserStates.GStaticAssert1_ParserState;
}

IParserState* StaticAssert1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() == ETokenType::RPAR )
	{
		if( InParserStates.StatesContext.StaticAssertContext.OpenBracketLayer == 0 )
		{
			AST LAST;
			LAST.BuildAST(InParserStates.StatesContext.StaticAssertContext.Expression);
			LAST.InterpretAST(OutProgramInfo);

			return InParserStates.GStaticAssert2_ParserState;
		}
	}


	if( FParserHelperLibrary::IsOpenPairToken(InToken) )
	{
		++InParserStates.StatesContext.StaticAssertContext.OpenBracketLayer;
	}
	else if( FParserHelperLibrary::IsClosePairToken(InToken) )
	{
		--InParserStates.StatesContext.StaticAssertContext.OpenBracketLayer;
	}

	InParserStates.StatesContext.StaticAssertContext.Expression.push_back(InToken);

	return InParserStates.GStaticAssert1_ParserState;
}

IParserState* StaticAssert2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::SEMICOLON )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
		return nullptr;
	}


	return InParserStates.PopStateChecked(InToken);
}





IParserState* StartBuildinTemplateType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	//TODO
	return nullptr;
}



IParserState* StartLambdaType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	//TODO
	return nullptr;
}



IParserState* StartUserType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::POINT:
	{
		InParserStates.StatesContext.UserTypeContext.ModuleName = InParserStates.StatesContext.UserTypeContext.TypeName + InToken.GetLexeme();
		InParserStates.StatesContext.UserTypeContext.TypeName = "";
		return InParserStates.GUserType1_ParserState;
	}
	case ETokenType::NAMESPACE_ACCESS_OPERATOR:
	{
		InParserStates.StatesContext.UserTypeContext.ModuleName = InParserStates.StatesContext.UserTypeContext.TypeName;
		InParserStates.StatesContext.UserTypeContext.TypeName = "";
		return InParserStates.GUserType3_ParserState;
	}
	default:
	{
		// clang-format off
		const std::string LCompileName = FParserHelperLibrary::GetCompileName
		(
			OutProgramInfo.MainModuleName, InParserStates.StatesContext.UserTypeContext.TypeName
		);
		// clang-format on

		int LUserTypeId = FParserHelperLibrary::GetUserTypeID(LCompileName, OutProgramInfo);
		if( LUserTypeId == -1 )
		{
			FUserTypePath LTypePath;
			LTypePath.PathSwitch = ETypePathSwitch::EClass;
			LTypePath.ClassPath.ClassCompileName = LCompileName;
			OutProgramInfo.TypesMap.push_back(LTypePath);
			LUserTypeId = OutProgramInfo.TypesMap.size() - 1;
		}

		InParserStates.StatesContext.UserTypeContext.TypeID = LUserTypeId;

		IParserState* LResultOperatingState = InParserStates.PopStateChecked(InToken);
		IParserState* LPrevState = LResultOperatingState->Process(InParserStates, InToken, OutProgramInfo);
		return LPrevState->Process(InParserStates, InToken, OutProgramInfo);
	}
	}

	return nullptr;
}

IParserState* UserType1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	InParserStates.StatesContext.UserTypeContext.ModuleName += InToken.GetLexeme();
	return InParserStates.GUserType2_ParserState;
}

IParserState* UserType2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	switch( InToken.GetType() )
	{
	case ETokenType::POINT:
	{
		InParserStates.StatesContext.UserTypeContext.ModuleName += InToken.GetLexeme();
		return InParserStates.GUserType1_ParserState;
	}
	case ETokenType::NAMESPACE_ACCESS_OPERATOR:
	{
		return InParserStates.GUserType3_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

IParserState* UserType3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	InParserStates.StatesContext.UserTypeContext.TypeName = InToken.GetLexeme();

	const std::string LModuleName = FParserHelperLibrary::GetModuleCompileName(InParserStates.StatesContext.UserTypeContext.ModuleName);
	const std::string LCompileName = FParserHelperLibrary::GetCompileName(LModuleName, InParserStates.StatesContext.UserTypeContext.TypeName);

	int LUserTypeId = FParserHelperLibrary::GetUserTypeID(LCompileName, OutProgramInfo);
	if( LUserTypeId == -1 )
	{
		FUserTypePath LTypePath;
		LTypePath.PathSwitch = ETypePathSwitch::EClass;
		LTypePath.ClassPath.ClassCompileName = LCompileName;
		OutProgramInfo.TypesMap.push_back(LTypePath);
		LUserTypeId = OutProgramInfo.TypesMap.size() - 1;
	}

	InParserStates.StatesContext.UserTypeContext.TypeID = LUserTypeId;

	IParserState* LResultOperatingState = InParserStates.PopStateChecked(InToken);
	return LResultOperatingState->Process(InParserStates, InToken, OutProgramInfo);
}


//.............................................................................................................................//
//.............................................................................................................................//


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
	DELETE_STATE(DescriptionParamBuildinTemplateType)
	DELETE_STATE(DescriptionParamLambdaType)
	DELETE_STATE(DescriptionParamUserType)

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
	DELETE_STATE(DeclareClassInternal)
	DELETE_STATE(DeclareClassParentBuildinTemplateType)
	DELETE_STATE(DeclareClassParentUserType)

	DELETE_STATE(StartDeclareField)
	DELETE_STATE(DeclareField1)
	DELETE_STATE(DeclareField2)
	DELETE_STATE(DeclareField3)
	DELETE_STATE(DeclareFieldBuildinTemplateType)
	DELETE_STATE(DeclareFieldLambdaType)
	DELETE_STATE(DeclareFieldUserType)


	DELETE_STATE(StartDefineAlias)
	DELETE_STATE(DefineAlias1)
	DELETE_STATE(DefineAlias2)
	DELETE_STATE(DefineAlias3)
	DELETE_STATE(DefineAliasBuildinTemplateType)
	DELETE_STATE(DefineAliasLambdaType)
	DELETE_STATE(DefineAliasUserType)

	DELETE_STATE(StartStaticAssert)
	DELETE_STATE(StaticAssert1)
	DELETE_STATE(StaticAssert2)


	DELETE_STATE(StartBuildinTemplateType)

	DELETE_STATE(StartLambdaType)

	DELETE_STATE(StartUserType)
	DELETE_STATE(UserType1)
	DELETE_STATE(UserType2)
	DELETE_STATE(UserType3)
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
	StatesContext.ModuleNameDeclared = true;
}

bool FParserStates::RegisterModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( StatesContext.ModuleDeclarationContext.ModulePath.empty() )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StatesContext.StateContextType != EStateContextType::Global )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	if( StatesContext.ModuleNameDeclared )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_REDEFINITION, TokenCTX);
		return false;
	}

	const std::string LModuleName = FParserHelperLibrary::GetModuleCompileName(StatesContext.ModuleDeclarationContext.ModulePath);
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



	OutProgramInfo.ImportedModulesInfo.insert(std::pair(LModuleName, StatesContext.ModuleDeclarationContext.ModuleInfo));
	OutProgramInfo.MainModuleName = LModuleName;
	StatesContext.ModuleNameDeclared = true;

	return true;
}

bool FParserStates::ImplementModuleFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( StatesContext.ModuleImplementingContext.ModulePath.empty() )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StatesContext.StateContextType != EStateContextType::Global )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	if( StatesContext.ModuleNameDeclared )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_REDEFINITION, TokenCTX);
		return false;
	}

	if( !GetIsMainModule() )
	{
		RaiseError(EErrorMessageType::IMPORTING_IMPLEMENT_MODULE, TokenCTX);
		return false;
	}



	const std::string LModuleName = FParserHelperLibrary::GetModuleCompileName(StatesContext.ModuleImplementingContext.ModulePath);

	if( OutProgramInfo.ImportedModulesInfo.find(LModuleName) != OutProgramInfo.ImportedModulesInfo.end() )
	{
		RaiseError(EErrorMessageType::MODULE_DOUBLE_IMPORT, TokenCTX);
		return false;
	}

	OutProgramInfo.MainModuleName = LModuleName;
	StatesContext.ModuleNameDeclared = true;

	const std::string LImportingModuleRelativePath = FCompilerHelperLibrary::MakePathFromParts(StatesContext.ModuleImplementingContext.ModulePath);
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
	if( StatesContext.ModuleImportingContext.ModulePath.empty() )
	{
		RaiseError(EErrorMessageType::MODULE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StatesContext.StateContextType != EStateContextType::Global )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}



	const std::string LImportingModuleRelativePath = FCompilerHelperLibrary::MakePathFromParts(StatesContext.ModuleImportingContext.ModulePath);
	const std::string LModuleName = FParserHelperLibrary::GetModuleCompileName(StatesContext.ModuleImportingContext.ModulePath);

	if( !StatesContext.ModuleImportingContext.AliasName.empty() )
	{
		if( StatesContext.ModuleImportingContext.AliasName.find('.') != std::string::npos )
		{
			RaiseError(EErrorMessageType::MODULE_ALIAS_CONTAINS_INVALID_CHAR, TokenCTX);
			return false;
		}

		// clang-format off
		if( 
			OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.find(StatesContext.ModuleImportingContext.AliasName) != 
			OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.end() 
		  )
		// clang-format on
		{
			RaiseError(EErrorMessageType::MODULE_ALIAS_NAME_REDEFINITION, TokenCTX);
			return false;
		}

		// clang-format off
		OutProgramInfo.ImportedModulesInfo[OutProgramInfo.MainModuleName].ImportedModuleNameAliases.insert
		(
			std::pair(StatesContext.ModuleImportingContext.AliasName, LModuleName)
		);
		// clang-format on
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

// clang-format off
bool FParserStates::ImportModule
(
	FProgramInfo& OutProgramInfo, 
	const std::string& ImportModuleRelativePath, const std::string& ImportModuleName, const Token& TokenCTX
)
// clang-format on
{
	if( ImportModuleName == FCompilerConfig::RESERVED_MAIN_MODULE_NAME )
	{
		RaiseError(EErrorMessageType::IMPORTING_MAIN_MODULE, TokenCTX);
		return false;
	}


	const std::string LCompilerPathOnly = FCompilerHelperLibrary::SplitFilePath(CompileOptions.PathToCompiler).PathToFileOnly;

	std::vector<std::string> LCurrentModulePathParts;
	FParserHelperLibrary::SplitModuleNameToParts(OutProgramInfo.MainModuleName, LCurrentModulePathParts);
	const std::string LUpDirectory = FCompilerHelperLibrary::MakeUpDirectoryStr(LCurrentModulePathParts.size() - 1);


	std::ifstream LFile;
	FGamlFileInfo LModuleFileInfo;

	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath
		(
			FileInfo.PathToFileOnly + LUpDirectory + ImportModuleRelativePath + "." + FCompilerConfig::HEADER_FILE_EXTENSION
		);
		// clang-format on
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath
		(
			FileInfo.PathToFileOnly + LUpDirectory + ImportModuleRelativePath + "." + FCompilerConfig::COMPILE_FILE_EXTENSION
		);
		// clang-format on
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath
		(
			LCompilerPathOnly + ImportModuleRelativePath + "." + FCompilerConfig::HEADER_FILE_EXTENSION
		);
		// clang-format on
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo = FCompilerHelperLibrary::SplitFilePath
		(
			LCompilerPathOnly + ImportModuleRelativePath + "." + FCompilerConfig::COMPILE_FILE_EXTENSION
		);
		// clang-format on
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
	FParserHelperLibrary::SplitModuleNameToParts(OutProgramInfo.MainModuleName, LCurrentModulePathParts);
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

		// return empty name for implementing modules, so do not include them
		const std::string LPackageModuleRealName = FParserHelperLibrary::GetFirstModuleName(LTokens);
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
	if( StatesContext.FunctionDeclarationContext.FunctionName.empty() )
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
			for( int i = 0; i < StatesContext.FunctionDeclarationContext.SignatureInfo.Inputs.size(); ++i )
			{
				// clang-format off
				if( 
					StatesContext.FunctionDeclarationContext.SignatureInfo.Inputs[i].VariableName != 
					(*LProgramFunctionIterator).second.Inputs[i].VariableName 
				  )
				// clang-format on
				{
					RaiseError(EErrorMessageType::FUNCTION_ARGUMENT_NAME_MISMATCH, TokenCTX);
					return false;
				}
			}

			if( !StatesContext.FunctionDeclarationContext.StaticCodeTokens.empty() )
			{
				RaiseError(EErrorMessageType::FUNCTION_STATIC_CODE_OVERRIDE, TokenCTX);
				return false;
			}

			return true;
		}

		RaiseError(EErrorMessageType::FUNCTION_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	StatesContext.FunctionDeclarationContext.SignatureInfo.StaticCodeTree.BuildAST(StatesContext.FunctionDeclarationContext.StaticCodeTokens);

	const bool ThisSignatureExists = FParserHelperLibrary::GetFunctionSignatureID(StatesContext.FunctionDeclarationContext.SignatureInfo, OutProgramInfo) != -1;
	if( !ThisSignatureExists )
	{
		OutProgramInfo.FunctionSignaturesTypesMap.push_back(StatesContext.FunctionDeclarationContext.SignatureInfo);

		FUserTypePath LTypePath;
		LTypePath.PathSwitch = ETypePathSwitch::EFunctionSignature;
		LTypePath.FunctionSignaturePath.FunctionSignatureID = OutProgramInfo.FunctionSignaturesTypesMap.size() - 1; // size > 0
		OutProgramInfo.TypesMap.push_back(LTypePath);
	}

	OutProgramInfo.Functions.insert(std::pair(LFunctionCompileName, StatesContext.FunctionDeclarationContext.SignatureInfo));

	// clang-format off
	if(
		StatesContext.StateContextType == EStateContextType::InClass &&
		(
			StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers.IsVirtual || 
			StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers.IsOverride || 
			StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers.IsAbstract
		) 
	  )
	// clang-format on
	{
		// clang-format off
		StatesContext.ClassDeclarationContext.ClassInfo.VirtualFunctionsTable.insert
		(
			std::pair(StatesContext.FunctionDeclarationContext.FunctionName, LFunctionCompileName)
		);
		// clang-format on
	}

	return true;
}

bool FParserStates::RegisterVariableFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( StatesContext.VariableDeclarationContext.VariableName.empty() )
	{
		RaiseError(EErrorMessageType::VARIABLE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StatesContext.StateContextType != EStateContextType::InClass )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	// clang-format off
	if( 
		StatesContext.ClassDeclarationContext.ClassInfo.Variables.find(StatesContext.VariableDeclarationContext.VariableName) !=
		StatesContext.ClassDeclarationContext.ClassInfo.Variables.end() 
	)
	// clang-format on
	{
		RaiseError(EErrorMessageType::VARIABLE_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	StatesContext.VariableDeclarationContext.VariableInfo.VariableName = StatesContext.VariableDeclarationContext.VariableName;
	StatesContext.VariableDeclarationContext.VariableInfo.DefaultValueTree.BuildAST(StatesContext.VariableDeclarationContext.DefaultValueTokens);

	// clang-format off
	StatesContext.ClassDeclarationContext.ClassInfo.Variables.insert
	(
		std::pair(StatesContext.VariableDeclarationContext.VariableName, StatesContext.VariableDeclarationContext.VariableInfo)
	);
	// clang-format on

	return true;
}

bool FParserStates::RegisterClassFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( StatesContext.ClassDeclarationContext.ClassName.empty() )
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



	OutProgramInfo.Classes.insert(std::pair(LClassCompileName, StatesContext.ClassDeclarationContext.ClassInfo));

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

bool FParserStates::FinishClassRegistrationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( StatesContext.ClassDeclarationContext.ClassName.empty() )
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

	auto LClassInfoIter = OutProgramInfo.Classes.find(LClassCompileName);
	if( LClassInfoIter == OutProgramInfo.Classes.end() )
	{
		RaiseError(EErrorMessageType::CLASS_NAME_NOT_FOUND, TokenCTX);
		return false;
	}

	LClassInfoIter->second.Variables = StatesContext.ClassDeclarationContext.ClassInfo.Variables;
	LClassInfoIter->second.VirtualFunctionsTable = StatesContext.ClassDeclarationContext.ClassInfo.VirtualFunctionsTable;

	return true;
}


bool FParserStates::RegisterAliasFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	if( StatesContext.AliasDeclarationContext.AliasName.empty() )
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



	OutProgramInfo.TypeAliases.insert(std::pair(LAliasCompileName, StatesContext.AliasDeclarationContext.OriginalTypeID));

	return true;
}

bool FParserStates::RegisterFunctionImplementationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	// our function implementation based on declaration context as a part of function declaration/implementation usage
	if( StatesContext.FunctionDeclarationContext.FunctionName.empty() )
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



	StatesContext.FunctionImplementationContext.CompilingFunctionInfo.FunctionCodeTree.BuildAST(StatesContext.FunctionImplementationContext.FunctionCodeTokens);


	OutProgramInfo.CompilingFunctionsAST.insert(std::pair(LFunctionCompileName, StatesContext.FunctionImplementationContext.CompilingFunctionInfo));

	return true;
}





std::string FParserStates::GetCTXFunctionCompileName(const FProgramInfo& OutProgramInfo) const
{
	if( StatesContext.FunctionDeclarationContext.SignatureInfo.Modifiers.IsExternC )
	{
		// clang-format off
		return FParserHelperLibrary::GetFunctionCompileName
		(
			"", 
			StatesContext.FunctionDeclarationContext.FunctionName,
			StatesContext.FunctionDeclarationContext.SignatureInfo, 
			OutProgramInfo
		);
		// clang-format on
	}


	std::string LFunctionCompileName = "";
	switch( StatesContext.StateContextType )
	{
	case EStateContextType::Global:
	{
		std::string LContextCompileName = OutProgramInfo.MainModuleName;
		if( !StatesContext.FunctionDeclarationContext.ClassDeclarationNamespace.empty() )
		{
			// clang-format off
			LContextCompileName = FParserHelperLibrary::GetCompileName
			(
				OutProgramInfo.MainModuleName, StatesContext.FunctionDeclarationContext.ClassDeclarationNamespace
			);
			// clang-format on
		}

		// clang-format off
		LFunctionCompileName = FParserHelperLibrary::GetFunctionCompileName
		(
			LContextCompileName, StatesContext.FunctionDeclarationContext.FunctionName, StatesContext.FunctionDeclarationContext.SignatureInfo, OutProgramInfo
		);
		// clang-format on

		break;
	}
	case EStateContextType::InClass:
	{
		// clang-format off
		const std::string LClassCompileName = FParserHelperLibrary::GetCompileName
		(
			OutProgramInfo.MainModuleName, StatesContext.ClassDeclarationContext.ClassName
		);
		// clang-format on

		if( LClassCompileName.empty() )
		{
			return "";
		}

		// clang-format off
		LFunctionCompileName = FParserHelperLibrary::GetFunctionCompileName
		(
			LClassCompileName, StatesContext.FunctionDeclarationContext.FunctionName, StatesContext.FunctionDeclarationContext.SignatureInfo, OutProgramInfo
		);
		// clang-format on

		break;
	}
	}

	return LFunctionCompileName;
}

std::string FParserStates::GetCTXClassCompileName(const FProgramInfo& OutProgramInfo) const
{
	return FParserHelperLibrary::GetCompileName(OutProgramInfo.MainModuleName, StatesContext.ClassDeclarationContext.ClassName);
}

std::string FParserStates::GetCTXTypeAliasCompileName(const FProgramInfo& OutProgramInfo) const
{
	std::string LAliasCompileName = "";

	switch( StatesContext.StateContextType )
	{
	case EStateContextType::Global:
	{
		// clang-format off
		LAliasCompileName = FParserHelperLibrary::GetCompileName
		(
			OutProgramInfo.MainModuleName, StatesContext.AliasDeclarationContext.AliasName
		);
		// clang-format on
		break;
	}
	case EStateContextType::InClass:
	{
		// clang-format off
		const std::string LClassCompileName = FParserHelperLibrary::GetCompileName
		(
			OutProgramInfo.MainModuleName, StatesContext.ClassDeclarationContext.ClassName
		);
		// clang-format on

		if( LClassCompileName.empty() )
		{
			return "";
		}

		// clang-format off
		LAliasCompileName = FParserHelperLibrary::GetCompileName
		(
			LClassCompileName, StatesContext.AliasDeclarationContext.AliasName
		);
		// clang-format on

		break;
	}
	}

	return LAliasCompileName;
}
