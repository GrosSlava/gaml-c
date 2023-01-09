// Copyright 2022 - 2023 GrosSlava.

#include "ScopeNode.h"

#include "../../../Token/Token.h"

#include "../ASTCodeGenFactory.h"
#include "../ASTSymbols.h"

#include "LeafNode.h"
#include "ASTOperators.h"

#include "../../../Logger/ErrorLogger.h"





void ScopeNode::BuildAST(const std::vector<Token>& InTokens, const FCompileOptions& CompileOptions)
{
	CurrentCompileOptions = CompileOptions;

	size_t LIndex = 0;
	while( LIndex < InTokens.size() )
	{
		const Token& LCurrentToken = InTokens[LIndex];
		switch( LCurrentToken.GetType() )
		{
		case ETokenType::SEMICOLON:
		{
			++LIndex;
			continue;
		}
		case ETokenType::STATIC:
		{
			if( LIndex + 1 >= InTokens.size() )
			{
				FErrorLogger::Raise(EErrorMessageType::EXPECTED_CONTROL_OPERATOR, LCurrentToken, CompileOptions);
				return;
			}

			switch( InTokens[LIndex + 1].GetType() )
			{
			case ETokenType::DO:
			{
				//TODO

				continue;
			}
			case ETokenType::WHILE:
			{
				//TODO

				continue;
			}
			case ETokenType::FOR:
			{
				//TODO

				continue;
			}
			case ETokenType::FOREACH:
			{
				//TODO

				continue;
			}
			case ETokenType::IF:
			{
				//TODO

				continue;
			}
			case ETokenType::SWITCH:
			{
				//TODO

				continue;
			}
			case ETokenType::SWITCH_ALL:
			{
				//TODO

				continue;
			}
			}

			FErrorLogger::Raise(EErrorMessageType::EXPECTED_CONTROL_OPERATOR, InTokens[LIndex + 1], CompileOptions);
			return;
		}
		case ETokenType::DO:
		{
			//TODO

			continue;
		}
		case ETokenType::WHILE:
		{
			//TODO

			continue;
		}
		case ETokenType::FOR:
		{
			//TODO

			continue;
		}
		case ETokenType::FOREACH:
		{
			//TODO

			continue;
		}
		case ETokenType::IF:
		{
			//TODO

			continue;
		}
		case ETokenType::SWITCH:
		{
			//TODO

			continue;
		}
		case ETokenType::SWITCH_ALL:
		{
			//TODO

			continue;
		}
		default:
		{
			size_t LExpressionEndIndex = LIndex + 1;
			while( LExpressionEndIndex < InTokens.size() && InTokens[LExpressionEndIndex].GetType() != ETokenType::SEMICOLON )
			{
				++LExpressionEndIndex;
			}

			ExprSequence.push_back(ParseExpr(std::vector<Token>(InTokens.begin() + LIndex, InTokens.begin() + LExpressionEndIndex - 1)));
			LIndex = LExpressionEndIndex + 1;

			continue;
		}
		}
	}
}

std::shared_ptr<IASTNode> ScopeNode::ParseExpr(const std::vector<Token>& InTokens) const
{
	const Token& LCurrentToken = InTokens[0];
	switch( LCurrentToken.GetType() )
	{
	case ETokenType::IDENTIFIER:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::EXCLAMATION:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::BINARY_INVERSE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::SIZE_OF:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::TYPE_OF:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::NAME_OF:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::ALIGN_OF:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_FUNCTION:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_STRUCT:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_ENUM:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_INTERFACE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_OBJECT:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_COMPONENT:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_SUBCLASS:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_INSTANCE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_LAMBDA:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_ITERABLE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_ENUMERABLE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_ABSTRACT:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::IS_ALIAS:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::ADDR:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::LBRA:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::LSQR:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::INTEGER_CONST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::FLOAT_CONST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::DOUBLE_CONST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::CHAR_CONST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::STRING_CONST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::TRUE_CONST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::FALSE_CONST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::CAST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::UNSAFE_CAST:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::ASSERT:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::STATIC_ASSERT:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::STATIC_ERROR:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::STATIC_WARNING:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::STATIC_MESSAGE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::BREAK:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::CONTINUE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::DEFAULT:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::LAMBDA:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::RETURN:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::VAR:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::THIS:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::SUPER:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::NONE:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::USING:
	{
		//TODO
		return nullptr;
	}
	}

	FErrorLogger::Raise(EErrorMessageType::UNEXPECTED_EXPRESSION, LCurrentToken, CurrentCompileOptions);
	return nullptr;
}





void ScopeNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool ScopeNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int ScopeNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double ScopeNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string ScopeNode::GetInterpretResultAsString() const
{
	//TODO
	return std::string();
}





std::string ScopeNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<ScopeNode>> LCodeGen = ASTCodeGenFactory->MakeScopeGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}
