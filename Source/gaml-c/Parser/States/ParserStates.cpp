// Copyright 2022 - 2023 GrosSlava.

#include "ParserStates.h"
#include "../ParserHelperLibrary.h"

#include "../../Compiler/CompilerConfig.h"
#include "../../Compiler/CompilerHelperLibrary.h"

#include "../../Lexer/Lexer.h"
#include "../../Parser/Parser.h"

#include <fstream>





std::shared_ptr<IParserState> Default_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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
		FModuleDeclarationContext& LModuleContext = InParserStates.StatesContext.ModuleDeclarationContext;
		LModuleContext.ModuleInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LModuleContext.ModuleInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDefault_ParserState);
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

		FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDefault_ParserState);
		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Struct;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDefault_ParserState);
		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Interface;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDefault_ParserState);
		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Object;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDefault_ParserState);
		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Component;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDefault_ParserState);
		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Enum;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDefault_ParserState);
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

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Public;

		InParserStates.PushState(InParserStates.GDefault_ParserState);
		return InParserStates.GGlobalAccessModifier_ParserState;
	}
	case ETokenType::PROTECTED:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Protected;

		InParserStates.PushState(InParserStates.GDefault_ParserState);
		return InParserStates.GGlobalAccessModifier_ParserState;
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Private;

		InParserStates.PushState(InParserStates.GDefault_ParserState);
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





std::shared_ptr<IParserState> StartDescription_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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

std::shared_ptr<IParserState> DescriptionModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;
	LDescriptionContext.PrepareForNextModifier();

	switch( InToken.GetType() )
	{
	case ETokenType::EXTERN_C:
	{
		if( LDescriptionContext.Modfiers.IsExternC )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsExternC = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::CDECL:
	{
		if( LDescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::CDECL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::STDCALL:
	{
		if( LDescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::STDCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::FASTCALL:
	{
		if( LDescriptionContext.Modfiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.CallingConvention = EFunctionCallingConvention::FASTCALL;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::CONST:
	{
		if( LDescriptionContext.Modfiers.IsConst )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsConst = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::MUTABLE:
	{
		if( LDescriptionContext.Modfiers.IsMutable )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsMutable = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::STATIC:
	{
		if( LDescriptionContext.Modfiers.IsStatic )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsStatic = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::INLINE:
	{
		if( LDescriptionContext.Modfiers.IsInline )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsInline = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::VIRTUAL:
	{
		if( LDescriptionContext.Modfiers.IsVirtual )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsVirtual = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::OVERRIDE:
	{
		if( LDescriptionContext.Modfiers.IsOverride )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsOverride = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::ABSTRACT:
	{
		if( LDescriptionContext.Modfiers.IsAbstract )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsAbstract = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::FINAL:
	{
		if( LDescriptionContext.Modfiers.IsFinal )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsFinal = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::DEPRECATED:
	{
		if( LDescriptionContext.Modfiers.IsDeprecated )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsDeprecated = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::UNIMPLEMENTED:
	{
		if( LDescriptionContext.Modfiers.IsUnimplemented )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		LDescriptionContext.Modfiers.IsUnimplemented = true;
		return InParserStates.GStartDescription_ParserState;
	}
	case ETokenType::ALIGN:
	{
		if( LDescriptionContext.Modfiers.Align != -1 )
		{
			InParserStates.RaiseError(EErrorMessageType::DOUBLE_MODIFIER, InToken);
			return nullptr;
		}
		return InParserStates.GDescriptionAlign1_ParserState;
	}
	case ETokenType::PARAM:
	{
		LDescriptionContext.DescriptionContext = EDescriptionContext::Param;
		return InParserStates.GDescriptionParam1_ParserState;
	}
	case ETokenType::RETURN:
	{
		LDescriptionContext.DescriptionContext = EDescriptionContext::Return;
		return InParserStates.GDescriptionParam1_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DescriptionAlign1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	if( InToken.GetType() != ETokenType::LPAR )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LPAR, InToken);
		return nullptr;
	}

	LDescriptionContext.OpenBracketLayer = 1;
	return InParserStates.GDescriptionAlign2_ParserState;
}

std::shared_ptr<IParserState> DescriptionAlign2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		++LDescriptionContext.OpenBracketLayer;
		LDescriptionContext.CodeTokens.push_back(InToken);

		return InParserStates.GDescriptionAlign2_ParserState;
	}
	case ETokenType::RPAR:
	{
		--LDescriptionContext.OpenBracketLayer;
		if( LDescriptionContext.OpenBracketLayer == 0 )
		{
			return InParserStates.GDescriptionAlign3_ParserState;
		}

		LDescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionAlign2_ParserState;
	}
	default:
	{
		LDescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionAlign2_ParserState;
	}
	}

	return nullptr;
}

std::shared_ptr<IParserState> DescriptionAlign3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

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
	LAST.BuildAST(LDescriptionContext.CodeTokens);
	LAST.InterpretAST(OutProgramInfo);
	LDescriptionContext.Modfiers.Align = LAST.GetInterpretResultAsInt();

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DescriptionParam1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	switch( LDescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		FVariableInfo LNewVariable;
		LNewVariable.VariableName = InToken.GetLexeme();
		LNewVariable.MetaInfo.DeclaredAtLine = InToken.GetLine();
		LNewVariable.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LDescriptionContext.Inputs.push_back(LNewVariable);
		break;
	}
	case EDescriptionContext::Return:
	{
		if( !LDescriptionContext.Return.VariableName.empty() )
		{
			InParserStates.RaiseError(EErrorMessageType::ARGUMENT_NAME_REDEFINITION, InToken);
			return nullptr;
		}

		LDescriptionContext.Return.VariableName = InToken.GetLexeme();
		LDescriptionContext.Return.MetaInfo.DeclaredAtLine = InToken.GetLine();
		LDescriptionContext.Return.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
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

std::shared_ptr<IParserState> DescriptionParam2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::COLON )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_COLON, InToken);
		return nullptr;
	}

	return InParserStates.GDescriptionParam3_ParserState;
}

std::shared_ptr<IParserState> DescriptionParam3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	if( FParserHelperLibrary::IsModifierToken(InToken) )
	{
		switch( InToken.GetType() )
		{
		case ETokenType::CONST:
		{
			switch( LDescriptionContext.DescriptionContext )
			{
			case EDescriptionContext::Param:
			{
				if( LDescriptionContext.Inputs.back().Modifiers.IsConst )
				{
					InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				LDescriptionContext.Inputs.back().Modifiers.IsConst = true;
				break;
			}
			case EDescriptionContext::Return:
			{
				if( LDescriptionContext.Return.Modifiers.IsConst )
				{
					InParserStates.RaiseError(EErrorMessageType::RETURN_TYPE_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				LDescriptionContext.Return.Modifiers.IsConst = true;
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
			switch( LDescriptionContext.DescriptionContext )
			{
			case EDescriptionContext::Param:
			{
				if( LDescriptionContext.Inputs.back().Modifiers.IsMutable )
				{
					InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				LDescriptionContext.Inputs.back().Modifiers.IsMutable = true;
				break;
			}
			case EDescriptionContext::Return:
			{
				if( LDescriptionContext.Return.Modifiers.IsMutable )
				{
					InParserStates.RaiseError(EErrorMessageType::RETURN_TYPE_DOUBLE_MODIFIER, InToken);
					return nullptr;
				}

				LDescriptionContext.Return.Modifiers.IsMutable = true;
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
		switch( LDescriptionContext.DescriptionContext )
		{
		case EDescriptionContext::Param:
		{
			LDescriptionContext.Inputs.back().TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
			break;
		}
		case EDescriptionContext::Return:
		{
			LDescriptionContext.Return.TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
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
		InParserStates.PushState(InParserStates.GDescriptionParamType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		InParserStates.PushState(InParserStates.GDescriptionParam4_ParserState);
		InParserStates.PushState(InParserStates.GDescriptionParamType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();

		return InParserStates.GStartLambdaType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.PushState(InParserStates.GDescriptionParam4_ParserState);
		InParserStates.PushState(InParserStates.GDescriptionParamType_ParserState);

		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		return InParserStates.GStartUserType_ParserState;
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DescriptionParam4_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		LDescriptionContext.OpenBracketLayer = 1;
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

std::shared_ptr<IParserState> DescriptionParam5_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	switch( InToken.GetType() )
	{
	case ETokenType::LPAR:
	{
		++LDescriptionContext.OpenBracketLayer;
		LDescriptionContext.CodeTokens.push_back(InToken);

		return InParserStates.GDescriptionParam5_ParserState;
	}
	case ETokenType::RPAR:
	{
		--LDescriptionContext.OpenBracketLayer;
		if( LDescriptionContext.OpenBracketLayer == 0 )
		{
			return InParserStates.GDescriptionParam6_ParserState;
		}

		LDescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionParam5_ParserState;
	}
	default:
	{
		LDescriptionContext.CodeTokens.push_back(InToken);
		return InParserStates.GDescriptionParam5_ParserState;
	}
	}

	return nullptr;
}

std::shared_ptr<IParserState> DescriptionParam6_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	switch( LDescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		LDescriptionContext.Inputs.back().DefaultValueTree.BuildAST(LDescriptionContext.CodeTokens);
		break;
	}
	case EDescriptionContext::Return:
	{
		LDescriptionContext.Return.DefaultValueTree.BuildAST(LDescriptionContext.CodeTokens);
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

std::shared_ptr<IParserState> EndDescription_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	// state to return already pushed
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;

	switch( InToken.GetType() )
	{
	case ETokenType::MODULE:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
			return nullptr;
		}

		FModuleDeclarationContext& LModuleContext = InParserStates.StatesContext.ModuleDeclarationContext;
		LModuleContext.ModuleInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LModuleContext.ModuleInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LModuleContext.ModuleInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareModule_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
		if( InParserStates.StatesContext.StateContextType == EStateContextType::InClass )
		{
			LFunctionContext.FunctionInfo.ClassDeclarationNamespace = InParserStates.StatesContext.ClassDeclarationContext.ClassName;
		}
		LFunctionContext.FunctionInfo.SignatureInfo.Modifiers = LDescriptionContext.Modfiers;
		LFunctionContext.FunctionInfo.SignatureInfo.Inputs = LDescriptionContext.Inputs;
		LFunctionContext.FunctionInfo.SignatureInfo.Return = LDescriptionContext.Return;
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Struct;
		LClassContext.ClassInfo.Modifiers = LDescriptionContext.Modfiers;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Interface;
		LClassContext.ClassInfo.Modifiers = LDescriptionContext.Modfiers;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Object;
		LClassContext.ClassInfo.Modifiers = LDescriptionContext.Modfiers;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Component;
		LClassContext.ClassInfo.Modifiers = LDescriptionContext.Modfiers;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Enum;
		LClassContext.ClassInfo.Modifiers = LDescriptionContext.Modfiers;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

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
	case ETokenType::PROTECTED:
	{
		InParserStates.RegisterMainModule(OutProgramInfo, InToken);

		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Protected;

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

std::shared_ptr<IParserState> DescriptionParamType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FDescriptionContext& LDescriptionContext = InParserStates.StatesContext.DescriptionContext;
	FTypeDetectionContext& LTypeDetectionCntext = InParserStates.StatesContext.TypeDetectionContext;

	switch( LDescriptionContext.DescriptionContext )
	{
	case EDescriptionContext::Param:
	{
		LDescriptionContext.Inputs.back().TypeID = LTypeDetectionCntext.TypeID;
		break;
	}
	case EDescriptionContext::Return:
	{
		LDescriptionContext.Return.TypeID = LTypeDetectionCntext.TypeID;
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



std::shared_ptr<IParserState> GlobalAccessModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	// global state already pushed

	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::Global;

		FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
		LFunctionContext.FunctionInfo.SignatureInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LFunctionContext.FunctionInfo.SignatureInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LFunctionContext.FunctionInfo.SignatureInfo.Inputs = InParserStates.StatesContext.DescriptionContext.Inputs;
		LFunctionContext.FunctionInfo.SignatureInfo.Return = InParserStates.StatesContext.DescriptionContext.Return;
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::STRUCT:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Struct;
		LClassContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LClassContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::INTERFACE:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Interface;
		LClassContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LClassContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::OBJECT:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Object;
		LClassContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LClassContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::COMPONENT:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Component;
		LClassContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LClassContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	case ETokenType::ENUM:
	{
		InParserStates.StatesContext.StateContextType = EStateContextType::InClass;

		FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;
		LClassContext.ClassInfo.ClassType = EClassType::Enum;
		LClassContext.ClassInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LClassContext.ClassInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LClassContext.ClassInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LClassContext.ClassInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareClass_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> LocalAccessModifier_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	// local state already pushed

	switch( InToken.GetType() )
	{
	case ETokenType::FUNCTION:
	{
		FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
		if( InParserStates.StatesContext.StateContextType == EStateContextType::InClass )
		{
			LFunctionContext.FunctionInfo.ClassDeclarationNamespace = InParserStates.StatesContext.ClassDeclarationContext.ClassName;
		}
		LFunctionContext.FunctionInfo.SignatureInfo.Modifiers = InParserStates.StatesContext.DescriptionContext.Modfiers;
		LFunctionContext.FunctionInfo.SignatureInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LFunctionContext.FunctionInfo.SignatureInfo.Inputs = InParserStates.StatesContext.DescriptionContext.Inputs;
		LFunctionContext.FunctionInfo.SignatureInfo.Return = InParserStates.StatesContext.DescriptionContext.Return;
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::VAR:
	{
		FVariableDeclarationContext& LVariableContext = InParserStates.StatesContext.VariableDeclarationContext;
		LVariableContext.VariableInfo.Modifiers.AccessModifier = InParserStates.StatesContext.AccessModifierContextType;
		LVariableContext.VariableInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LVariableContext.VariableInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		return InParserStates.GStartDeclareField_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}





std::shared_ptr<IParserState> StartDeclareModule_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	InParserStates.StatesContext.ModuleDeclarationContext.ModulePath.push_back(InToken.GetLexeme());
	return InParserStates.GDeclareModule1_ParserState;
}

std::shared_ptr<IParserState> DeclareModule1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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



std::shared_ptr<IParserState> StartImplementModule_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	InParserStates.StatesContext.ModuleImplementingContext.ModulePath.push_back(InToken.GetLexeme());
	return InParserStates.GImplementModule1_ParserState;
}

std::shared_ptr<IParserState> ImplementModule1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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



std::shared_ptr<IParserState> StartImportModule_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	InParserStates.StatesContext.ModuleImportingContext.ModulePath.push_back(InToken.GetLexeme());
	return InParserStates.GImportModule1_ParserState;
}

std::shared_ptr<IParserState> ImportModule1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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

std::shared_ptr<IParserState> ImportModule2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	InParserStates.StatesContext.ModuleImportingContext.AliasName = InToken.GetLexeme();
	return InParserStates.GImportModule3_ParserState;
}

std::shared_ptr<IParserState> ImportModule3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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





std::shared_ptr<IParserState> StartDeclareFunction_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
	FFunctionImplementationContext& LFunctionImplContext = InParserStates.StatesContext.FunctionImplementationContext;

	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_FUNCTION_NAME, InToken);
		return nullptr;
	}

	LFunctionContext.FunctionName = InToken.GetLexeme();
	return InParserStates.GDeclareFunction1_ParserState;
}

std::shared_ptr<IParserState> DeclareFunction1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
	FFunctionImplementationContext& LFunctionImplContext = InParserStates.StatesContext.FunctionImplementationContext;

	switch( InToken.GetType() )
	{
	case ETokenType::NAMESPACE_ACCESS_OPERATOR:
	{
		if( InParserStates.StatesContext.StateContextType != EStateContextType::Global )
		{
			InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
			return nullptr;
		}

		if( LFunctionContext.FunctionInfo.ClassDeclarationNamespace.empty() )
		{
			LFunctionContext.FunctionInfo.ClassDeclarationNamespace = LFunctionContext.FunctionName;
			LFunctionContext.FunctionName.clear();
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
		LFunctionContext.StaticCodeOpenBracketLayer = 1;
		return InParserStates.GDeclareFunction2_ParserState;
	}
	case ETokenType::LBRA:
	{
		if( !InParserStates.RegisterFunctionFromContext(OutProgramInfo, true, InToken) )
		{
			return nullptr;
		}

		LFunctionImplContext.FunctionCodeOpenBracketLayer = 1;
		return InParserStates.GDeclareFunction4_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DeclareFunction2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
	FFunctionImplementationContext& LFunctionImplContext = InParserStates.StatesContext.FunctionImplementationContext;

	switch( InToken.GetType() )
	{
	case ETokenType::LSQR:
	{
		++LFunctionContext.StaticCodeOpenBracketLayer;
		LFunctionContext.StaticCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction2_ParserState;
	}
	case ETokenType::RSQR:
	{
		--LFunctionContext.StaticCodeOpenBracketLayer;
		if( LFunctionContext.StaticCodeOpenBracketLayer == 0 )
		{
			return InParserStates.GDeclareFunction3_ParserState;
		}

		LFunctionContext.StaticCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction2_ParserState;
	}
	default:
	{
		LFunctionContext.StaticCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction2_ParserState;
	}
	}

	return nullptr;
}

std::shared_ptr<IParserState> DeclareFunction3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
	FFunctionImplementationContext& LFunctionImplContext = InParserStates.StatesContext.FunctionImplementationContext;

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

		LFunctionImplContext.FunctionCodeOpenBracketLayer = 1;
		return InParserStates.GDeclareFunction4_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DeclareFunction4_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
	FFunctionImplementationContext& LFunctionImplContext = InParserStates.StatesContext.FunctionImplementationContext;

	switch( InToken.GetType() )
	{
	case ETokenType::LBRA:
	{
		++LFunctionImplContext.FunctionCodeOpenBracketLayer;
		LFunctionImplContext.FunctionCodeTokens.push_back(InToken);

		return InParserStates.GDeclareFunction4_ParserState;
	}
	case ETokenType::RBRA:
	{
		--LFunctionImplContext.FunctionCodeOpenBracketLayer;
		if( LFunctionImplContext.FunctionCodeOpenBracketLayer == 0 )
		{
			if( !InParserStates.RegisterFunctionImplementationFromContext(OutProgramInfo, InToken) )
			{
				return nullptr;
			}
			return InParserStates.PopStateChecked(InToken);
		}

		LFunctionImplContext.FunctionCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction4_ParserState;
	}
	default:
	{
		LFunctionImplContext.FunctionCodeTokens.push_back(InToken);
		return InParserStates.GDeclareFunction4_ParserState;
	}
	}

	return nullptr;
}



std::shared_ptr<IParserState> StartDeclareClass_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;

	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_CLASS_NAME, InToken);
	}

	LClassContext.ClassName = InToken.GetLexeme();
	return InParserStates.GDeclareClass1_ParserState;
}

std::shared_ptr<IParserState> DeclareClass1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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

std::shared_ptr<IParserState> DeclareClass2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;

	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		LClassContext.ClassInfo.ParentTypesID.push_back(FParserHelperLibrary::GetStandardTypeID(InToken));
		return InParserStates.GDeclareClass3_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		InParserStates.PushState(InParserStates.GDeclareClass3_ParserState);
		InParserStates.PushState(InParserStates.GDeclareClassParentType_ParserState);
		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		InParserStates.PushState(InParserStates.GDeclareClass3_ParserState);
		InParserStates.PushState(InParserStates.GDeclareClassParentType_ParserState);
		return InParserStates.GStartUserType_ParserState;
	}


	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DeclareClass3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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

std::shared_ptr<IParserState> DeclareClass4_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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

std::shared_ptr<IParserState> DeclareClassInternal_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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
		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Public;

		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);
		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::PROTECTED:
	{
		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Protected;

		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);
		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::PRIVATE:
	{
		InParserStates.StatesContext.AccessModifierContextType = EAccessModifier::Private;

		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);
		return InParserStates.GLocalAccessModifier_ParserState;
	}
	case ETokenType::FUNCTION:
	{
		FFunctionDeclarationContext& LFunctionContext = InParserStates.StatesContext.FunctionDeclarationContext;
		LFunctionContext.FunctionInfo.ClassDeclarationNamespace = InParserStates.StatesContext.ClassDeclarationContext.ClassName;
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LFunctionContext.FunctionInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);
		return InParserStates.GStartDeclareFunction_ParserState;
	}
	case ETokenType::VAR:
	{
		FVariableDeclarationContext& LVariableContext = InParserStates.StatesContext.VariableDeclarationContext;
		LVariableContext.VariableInfo.MetaInfo.DeclaredInFile = InToken.GetFileInfo();
		LVariableContext.VariableInfo.MetaInfo.DeclaredAtLine = InToken.GetLine();

		InParserStates.PushState(InParserStates.GDeclareClassInternal_ParserState);
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

std::shared_ptr<IParserState> DeclareClassParentType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FClassDeclarationContext& LClassContext = InParserStates.StatesContext.ClassDeclarationContext;

	LClassContext.ClassInfo.ParentTypesID.push_back(InParserStates.StatesContext.TypeDetectionContext.TypeID);
	return InParserStates.PopStateChecked(InToken);
}



std::shared_ptr<IParserState> StartDeclareField_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FVariableDeclarationContext& LVariableContext = InParserStates.StatesContext.VariableDeclarationContext;

	if( InParserStates.StatesContext.StateContextType == EStateContextType::InClass )
	{
		if( InParserStates.StatesContext.ClassDeclarationContext.ClassInfo.ClassType == EClassType::Enum )
		{
			LVariableContext.VariableInfo.TypeID = -1; // analyzer will set type by enum parent
			LVariableContext.VariableName = InToken.GetLexeme();
			return InParserStates.GDeclareField2_ParserState;
		}
	}

	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		LVariableContext.VariableInfo.TypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
		return InParserStates.GDeclareField1_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		InParserStates.PushState(InParserStates.GDeclareField1_ParserState);
		InParserStates.PushState(InParserStates.GDeclareFieldType_ParserState);
		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		InParserStates.StatesContext.ClearTypeContexts();

		InParserStates.PushState(InParserStates.GDeclareField1_ParserState);
		InParserStates.PushState(InParserStates.GDeclareFieldType_ParserState);
		return InParserStates.GStartLambdaType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		InParserStates.PushState(InParserStates.GDeclareField1_ParserState);
		InParserStates.PushState(InParserStates.GDeclareFieldType_ParserState);
		return InParserStates.GStartUserType_ParserState;
	}

	switch( InToken.GetType() )
	{
	case ETokenType::STATIC:
	{
		if( LVariableContext.VariableInfo.Modifiers.IsStatic )
		{
			InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
		}

		LVariableContext.VariableInfo.Modifiers.IsStatic = true;
		return InParserStates.GStartDeclareField_ParserState;
	}
	case ETokenType::CONST:
	{
		if( LVariableContext.VariableInfo.Modifiers.IsConst )
		{
			InParserStates.RaiseError(EErrorMessageType::MEMBER_DOUBLE_MODIFIER, InToken);
		}

		LVariableContext.VariableInfo.Modifiers.IsConst = true;
		return InParserStates.GStartDeclareField_ParserState;
	}
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DeclareField1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FVariableDeclarationContext& LVariableContext = InParserStates.StatesContext.VariableDeclarationContext;

	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
	}

	LVariableContext.VariableName = InToken.GetLexeme();
	return InParserStates.GDeclareField2_ParserState;
}

std::shared_ptr<IParserState> DeclareField2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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

std::shared_ptr<IParserState> DeclareField3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FVariableDeclarationContext& LVariableContext = InParserStates.StatesContext.VariableDeclarationContext;

	if( InToken.GetType() == ETokenType::SEMICOLON )
	{
		if( LVariableContext.DefaultValueTokens.empty() )
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
		LVariableContext.DefaultValueTokens.push_back(InToken);
	}

	return InParserStates.GDeclareField3_ParserState;
}

std::shared_ptr<IParserState> DeclareFieldType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FVariableDeclarationContext& LVariableContext = InParserStates.StatesContext.VariableDeclarationContext;

	LVariableContext.VariableInfo.TypeID = InParserStates.StatesContext.TypeDetectionContext.TypeID;
	return InParserStates.PopStateChecked(InToken);
}





std::shared_ptr<IParserState> StartDefineAlias_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FAliasDeclarationContext& LAliasContext = InParserStates.StatesContext.AliasDeclarationContext;

	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_ALIAS_NAME, InToken);
		return nullptr;
	}

	LAliasContext.AliasName = InToken.GetLexeme();
	return InParserStates.GDefineAlias1_ParserState;
}

std::shared_ptr<IParserState> DefineAlias1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::ASSIGN )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_ASSIGN, InToken);
		return nullptr;
	}

	return InParserStates.GDefineAlias2_ParserState;
}

std::shared_ptr<IParserState> DefineAlias2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FAliasDeclarationContext& LAliasContext = InParserStates.StatesContext.AliasDeclarationContext;

	if( FParserHelperLibrary::IsStandardType(InToken) )
	{
		LAliasContext.OriginalTypeID = FParserHelperLibrary::GetStandardTypeID(InToken);
		return InParserStates.GDefineAlias3_ParserState;
	}
	else if( FParserHelperLibrary::IsBuiltinTemplateType(InToken) )
	{
		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		InParserStates.PushState(InParserStates.GDefineAlias3_ParserState);
		InParserStates.PushState(InParserStates.GDefineAliasType_ParserState);
		return InParserStates.GStartBuildinTemplateType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::LAMBDA )
	{
		InParserStates.StatesContext.ClearTypeContexts();

		InParserStates.PushState(InParserStates.GDefineAlias3_ParserState);
		InParserStates.PushState(InParserStates.GDefineAliasType_ParserState);
		return InParserStates.GStartLambdaType_ParserState;
	}
	else if( InToken.GetType() == ETokenType::IDENTIFIER )
	{
		InParserStates.StatesContext.ClearTypeContexts();
		InParserStates.StatesContext.TypeDetectionContext.TypeName = InToken.GetLexeme();

		InParserStates.PushState(InParserStates.GDefineAlias3_ParserState);
		InParserStates.PushState(InParserStates.GDefineAliasType_ParserState);
		return InParserStates.GStartUserType_ParserState;
	}

	InParserStates.RaiseError(EErrorMessageType::UNEXPECTED_EXPRESSION, InToken);
	return nullptr;
}

std::shared_ptr<IParserState> DefineAlias3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
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

std::shared_ptr<IParserState> DefineAliasType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FAliasDeclarationContext& LAliasContext = InParserStates.StatesContext.AliasDeclarationContext;

	LAliasContext.OriginalTypeID = InParserStates.StatesContext.TypeDetectionContext.TypeID;
	return InParserStates.PopStateChecked(InToken);
}



std::shared_ptr<IParserState> StartStaticAssert_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FStaticAssertContext& LStaticAssertContext = InParserStates.StatesContext.StaticAssertContext;

	if( InToken.GetType() != ETokenType::LPAR )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_LPAR, InToken);
		return nullptr;
	}

	LStaticAssertContext.Clear();
	return InParserStates.GStaticAssert1_ParserState;
}

std::shared_ptr<IParserState> StaticAssert1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FStaticAssertContext& LStaticAssertContext = InParserStates.StatesContext.StaticAssertContext;

	if( InToken.GetType() == ETokenType::RPAR )
	{
		if( LStaticAssertContext.OpenBracketLayer == 0 )
		{
			if( !InParserStates.RegisterStaticAssertFromContext(OutProgramInfo, InToken) )
			{
				return nullptr;
			}
			return InParserStates.GStaticAssert2_ParserState;
		}
	}


	if( FParserHelperLibrary::IsOpenPairToken(InToken) )
	{
		++LStaticAssertContext.OpenBracketLayer;
	}
	else if( FParserHelperLibrary::IsClosePairToken(InToken) )
	{
		--LStaticAssertContext.OpenBracketLayer;
	}

	LStaticAssertContext.Expression.push_back(InToken);
	return InParserStates.GStaticAssert1_ParserState;
}

std::shared_ptr<IParserState> StaticAssert2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	if( InToken.GetType() != ETokenType::SEMICOLON )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_SEMICOLON, InToken);
		return nullptr;
	}

	return InParserStates.PopStateChecked(InToken);
}





std::shared_ptr<IParserState> StartBuildinTemplateType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	//TODO
	return nullptr;
}



std::shared_ptr<IParserState> StartLambdaType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	//TODO
	return nullptr;
}



std::shared_ptr<IParserState> StartUserType_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FTypeDetectionContext& LTypeDetectionContext = InParserStates.StatesContext.TypeDetectionContext;

	switch( InToken.GetType() )
	{
	case ETokenType::POINT:
	{
		LTypeDetectionContext.ModuleName = LTypeDetectionContext.TypeName + InToken.GetLexeme();
		LTypeDetectionContext.TypeName.clear();
		return InParserStates.GUserType1_ParserState;
	}
	case ETokenType::NAMESPACE_ACCESS_OPERATOR:
	{
		LTypeDetectionContext.ModuleName = LTypeDetectionContext.TypeName;
		LTypeDetectionContext.TypeName.clear();
		return InParserStates.GUserType3_ParserState;
	}
	default:
	{
		std::string LContextCompileName = InParserStates.GetCTXClassCompileName(OutProgramInfo);
		if( LContextCompileName.empty() )
		{
			LContextCompileName = OutProgramInfo.MainModuleName;
		}


		const std::string LInContextCompileName = FParserHelperLibrary::GetCompileName(LContextCompileName, LTypeDetectionContext.TypeName);
		const std::string LGlobalCompileName = FParserHelperLibrary::GetCompileName(OutProgramInfo.MainModuleName, LTypeDetectionContext.TypeName);

		int LUserTypeId = FParserHelperLibrary::GetUserTypeID(LInContextCompileName, OutProgramInfo);
		if( LUserTypeId == -1 )
		{
			int LUserTypeId = FParserHelperLibrary::GetUserTypeID(LGlobalCompileName, OutProgramInfo);
		}
		if( LUserTypeId == -1 )
		{
			FUserTypePath LTypePath;
			LTypePath.PathSwitch = ETypePathSwitch::Class;
			LTypePath.ClassPath.ClassCompileName = LGlobalCompileName;
			OutProgramInfo.TypesMap.push_back(LTypePath);
			LUserTypeId = OutProgramInfo.TypesMap.size() - 1;
		}

		LTypeDetectionContext.TypeID = LUserTypeId;

		std::shared_ptr<IParserState> LResultOperatingState = InParserStates.PopStateChecked(InToken);
		std::shared_ptr<IParserState> LPrevState = LResultOperatingState->Process(InParserStates, InToken, OutProgramInfo);
		return LPrevState->Process(InParserStates, InToken, OutProgramInfo);
	}
	}

	return nullptr;
}

std::shared_ptr<IParserState> UserType1_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FTypeDetectionContext& LTypeDetectionContext = InParserStates.StatesContext.TypeDetectionContext;

	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	LTypeDetectionContext.ModuleName += InToken.GetLexeme();
	return InParserStates.GUserType2_ParserState;
}

std::shared_ptr<IParserState> UserType2_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FTypeDetectionContext& LTypeDetectionContext = InParserStates.StatesContext.TypeDetectionContext;

	switch( InToken.GetType() )
	{
	case ETokenType::POINT:
	{
		LTypeDetectionContext.ModuleName += InToken.GetLexeme();
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

std::shared_ptr<IParserState> UserType3_ParserState::Process(FParserStates& InParserStates, const Token& InToken, FProgramInfo& OutProgramInfo)
{
	FTypeDetectionContext& LTypeDetectionContext = InParserStates.StatesContext.TypeDetectionContext;

	if( InToken.GetType() != ETokenType::IDENTIFIER )
	{
		InParserStates.RaiseError(EErrorMessageType::EXPECTED_IDENTIFIER, InToken);
		return nullptr;
	}

	LTypeDetectionContext.TypeName = InToken.GetLexeme();

	const std::string LModuleName = FParserHelperLibrary::GetModuleRealNameWithFirstPartCheck(LTypeDetectionContext.ModuleName, OutProgramInfo);
	const std::string LCompileName = FParserHelperLibrary::GetCompileName(LModuleName, LTypeDetectionContext.TypeName);

	int LUserTypeId = FParserHelperLibrary::GetUserTypeID(LCompileName, OutProgramInfo);
	if( LUserTypeId == -1 )
	{
		FUserTypePath LTypePath;
		LTypePath.PathSwitch = ETypePathSwitch::Class;
		LTypePath.ClassPath.ClassCompileName = LCompileName;
		OutProgramInfo.TypesMap.push_back(LTypePath);
		LUserTypeId = OutProgramInfo.TypesMap.size() - 1;
	}

	LTypeDetectionContext.TypeID = LUserTypeId;

	std::shared_ptr<IParserState> LResultOperatingState = InParserStates.PopStateChecked(InToken);
	return LResultOperatingState->Process(InParserStates, InToken, OutProgramInfo);
}


//.............................................................................................................................//
//.............................................................................................................................//


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


	const std::string LCompilerPathOnly = FGamlFileInfo(CompileOptions.PathToCompiler).PathToFileOnly;

	std::vector<std::string> LCurrentModulePathParts;
	FParserHelperLibrary::SplitModuleCompileNameToParts(OutProgramInfo.MainModuleName, LCurrentModulePathParts);
	const std::string LUpDirectory = FCompilerHelperLibrary::MakeUpDirectoryStr(LCurrentModulePathParts.size() - 1);


	std::ifstream LFile;
	FGamlFileInfo LModuleFileInfo;

	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo.SetFromPath
		(
			FileInfo.PathToFileOnly + LUpDirectory + ImportModuleRelativePath + "." + FCompilerConfig::HEADER_FILE_EXTENSION
		);
		// clang-format on
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo.SetFromPath
		(
			FileInfo.PathToFileOnly + LUpDirectory + ImportModuleRelativePath + "." + FCompilerConfig::COMPILE_FILE_EXTENSION
		);
		// clang-format on
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo.SetFromPath
		(
			LCompilerPathOnly + ImportModuleRelativePath + "." + FCompilerConfig::HEADER_FILE_EXTENSION
		);
		// clang-format on
		LFile.open(LModuleFileInfo.GetFileFullPath(), std::ios::binary);
	}
	if( !LFile.is_open() )
	{
		// clang-format off
		LModuleFileInfo.SetFromPath
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
	const std::string LCompilerPathOnly = FGamlFileInfo(CompileOptions.PathToCompiler).PathToFileOnly;

	std::vector<std::string> LCurrentModulePathParts;
	FParserHelperLibrary::SplitModuleCompileNameToParts(OutProgramInfo.MainModuleName, LCurrentModulePathParts);
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
	FFunctionDeclarationContext& LFunctionContext = StatesContext.FunctionDeclarationContext;

	if( LFunctionContext.FunctionName.empty() )
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
			for( int i = 0; i < LFunctionContext.FunctionInfo.SignatureInfo.Inputs.size(); ++i )
			{
				// clang-format off
				if( 
					LFunctionContext.FunctionInfo.SignatureInfo.Inputs[i].VariableName != 
					(*LProgramFunctionIterator).second.SignatureInfo.Inputs[i].VariableName 
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


	LFunctionContext.FunctionInfo.ClassDeclarationNamespace = GetCTXClassCompileName(OutProgramInfo);
	LFunctionContext.FunctionInfo.SignatureInfo.StaticCodeTree.BuildAST(LFunctionContext.StaticCodeTokens);

	const bool ThisSignatureExists = FParserHelperLibrary::GetFunctionSignatureID(LFunctionContext.FunctionInfo.SignatureInfo, OutProgramInfo) != -1;
	if( !ThisSignatureExists )
	{
		OutProgramInfo.FunctionSignaturesTypesMap.push_back(LFunctionContext.FunctionInfo.SignatureInfo);

		FUserTypePath LTypePath;
		LTypePath.PathSwitch = ETypePathSwitch::FunctionSignature;
		LTypePath.FunctionSignaturePath.FunctionSignatureID = OutProgramInfo.FunctionSignaturesTypesMap.size() - 1; // size > 0
		OutProgramInfo.TypesMap.push_back(LTypePath);
	}

	OutProgramInfo.Functions.insert(std::pair(LFunctionCompileName, LFunctionContext.FunctionInfo));
	return true;
}

bool FParserStates::RegisterFunctionImplementationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	FFunctionImplementationContext& LFunctionImplContext = StatesContext.FunctionImplementationContext;

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



	LFunctionImplContext.CompilingFunctionInfo.FunctionCodeTree.BuildAST(LFunctionImplContext.FunctionCodeTokens);

	OutProgramInfo.CompilingFunctionsAST.insert(std::pair(LFunctionCompileName, LFunctionImplContext.CompilingFunctionInfo));
	return true;
}

bool FParserStates::RegisterVariableFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	FVariableDeclarationContext& LVariableContext = StatesContext.VariableDeclarationContext;
	FClassDeclarationContext& LClassContext = StatesContext.ClassDeclarationContext;

	if( LVariableContext.VariableName.empty() )
	{
		RaiseError(EErrorMessageType::VARIABLE_NAME_GENERATION_PROBLEM, TokenCTX);
		return false;
	}

	if( StatesContext.StateContextType != EStateContextType::InClass )
	{
		RaiseError(EErrorMessageType::INVALID_STATE, TokenCTX);
		return false;
	}

	if( LClassContext.ClassInfo.Variables.find(LVariableContext.VariableName) != LClassContext.ClassInfo.Variables.end() )
	{
		RaiseError(EErrorMessageType::VARIABLE_NAME_REDEFINITION, TokenCTX);
		return false;
	}



	LVariableContext.VariableInfo.VariableName = LVariableContext.VariableName;
	LVariableContext.VariableInfo.DefaultValueTree.BuildAST(LVariableContext.DefaultValueTokens);

	LClassContext.ClassInfo.Variables.insert(std::pair(LVariableContext.VariableName, LVariableContext.VariableInfo));
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



	const bool ThisClassTypeExists = FParserHelperLibrary::GetClassTypeID(LClassCompileName, OutProgramInfo) != -1;
	if( !ThisClassTypeExists )
	{
		FUserTypePath LTypePath;
		LTypePath.PathSwitch = ETypePathSwitch::Class;
		LTypePath.ClassPath.ClassCompileName = LClassCompileName;
		OutProgramInfo.TypesMap.push_back(LTypePath);
	}

	OutProgramInfo.Classes.insert(std::pair(LClassCompileName, StatesContext.ClassDeclarationContext.ClassInfo));
	return true;
}

bool FParserStates::FinishClassRegistrationFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	FClassDeclarationContext& LClassContext = StatesContext.ClassDeclarationContext;

	if( LClassContext.ClassName.empty() )
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



	LClassInfoIter->second.Variables = LClassContext.ClassInfo.Variables;
	LClassInfoIter->second.VirtualFunctionsTable = LClassContext.ClassInfo.VirtualFunctionsTable;

	return true;
}

bool FParserStates::RegisterAliasFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	FAliasDeclarationContext& LAliasContext = StatesContext.AliasDeclarationContext;

	if( LAliasContext.AliasName.empty() )
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



	OutProgramInfo.TypeAliases.insert(std::pair(LAliasCompileName, LAliasContext.OriginalTypeID));
	return true;
}

bool FParserStates::RegisterStaticAssertFromContext(FProgramInfo& OutProgramInfo, const Token& TokenCTX)
{
	FStaticAssertContext& LStaticAssertContext = StatesContext.StaticAssertContext;

	LStaticAssertContext.StaticAssertInfo.CodeTree.BuildAST(LStaticAssertContext.Expression);
	LStaticAssertContext.StaticAssertInfo.ModuleContextName = OutProgramInfo.MainModuleName;
	LStaticAssertContext.StaticAssertInfo.ClassContextName = GetCTXClassCompileName(OutProgramInfo);

	OutProgramInfo.StaticAsserts.push_back(LStaticAssertContext.StaticAssertInfo);
	return true;
}





std::string FParserStates::GetCTXFunctionCompileName(const FProgramInfo& OutProgramInfo) const
{
	const FFunctionDeclarationContext& LFunctionContext = StatesContext.FunctionDeclarationContext;

	if( LFunctionContext.FunctionInfo.SignatureInfo.Modifiers.IsExternC )
	{
		// clang-format off
		return FParserHelperLibrary::GetFunctionCompileName
		(
			"", 
			LFunctionContext.FunctionName,
			LFunctionContext.FunctionInfo.SignatureInfo, 
			OutProgramInfo
		);
		// clang-format on
	}

	std::string LContextCompileName = GetCTXClassCompileName(OutProgramInfo);
	if( LContextCompileName.empty() )
	{
		LContextCompileName = OutProgramInfo.MainModuleName;
	}

	// clang-format off
	return FParserHelperLibrary::GetFunctionCompileName
	(
		LContextCompileName, LFunctionContext.FunctionName, LFunctionContext.FunctionInfo.SignatureInfo, OutProgramInfo
	);
	// clang-format on
}

std::string FParserStates::GetCTXClassCompileName(const FProgramInfo& OutProgramInfo) const
{
	const FClassDeclarationContext& LClassContext = StatesContext.ClassDeclarationContext;
	const FFunctionDeclarationContext& LFunctionContext = StatesContext.FunctionDeclarationContext;

	switch( StatesContext.StateContextType )
	{
	case EStateContextType::Global:
	{
		return FParserHelperLibrary::GetCompileName(OutProgramInfo.MainModuleName, LFunctionContext.FunctionInfo.ClassDeclarationNamespace);
	}
	case EStateContextType::InClass:
	{
		return FParserHelperLibrary::GetCompileName(OutProgramInfo.MainModuleName, LClassContext.ClassName);
	}
	}

	return "";
}

std::string FParserStates::GetCTXTypeAliasCompileName(const FProgramInfo& OutProgramInfo) const
{
	const FAliasDeclarationContext& LAliasContext = StatesContext.AliasDeclarationContext;

	std::string LContextCompileName = GetCTXClassCompileName(OutProgramInfo);
	if( LContextCompileName.empty() )
	{
		LContextCompileName = OutProgramInfo.MainModuleName;
	}

	return FParserHelperLibrary::GetCompileName(LContextCompileName, LAliasContext.AliasName);
}
