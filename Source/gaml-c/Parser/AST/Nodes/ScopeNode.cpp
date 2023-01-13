// Copyright 2022 - 2023 GrosSlava.

#include "ScopeNode.h"

#include "../../../Token/Token.h"

#include "../ASTCodeGenFactory.h"
#include "../ASTSymbols.h"

#include "LeafNode.h"
#include "ASTOperators.h"

#include "../../ParserHelperLibrary.h"
#include "../../../Logger/ErrorLogger.h"





void ScopeNode::BuildAST(const std::vector<Token>& InTokens, const FCompileOptions& CompileOptions)
{
	CurrentCompileOptions = CompileOptions;

	size_t LIndex = 0;
	while( LIndex < InTokens.size() )
	{
		switch( InTokens[LIndex].GetType() )
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
				FErrorLogger::Raise(EErrorMessageType::EXPECTED_CONTROL_OPERATOR, InTokens[LIndex], CompileOptions);
				return;
			}
			++LIndex;

			switch( InTokens[LIndex].GetType() )
			{
			case ETokenType::DO:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticDo(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::WHILE:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticWhile(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::FOR:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticFor(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::FOREACH:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticForeach(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::IF:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticIf(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::SWITCH:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticSwitch(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::SWITCH_ALL:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticSwitchAll(InTokens, LIndex));

				++LIndex;
				continue;
			}
			}

			FErrorLogger::Raise(EErrorMessageType::EXPECTED_CONTROL_OPERATOR, InTokens[LIndex], CompileOptions);
			return;
		}
		case ETokenType::DO:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Do(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::WHILE:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_While(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::FOR:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_For(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::FOREACH:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Foreach(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::IF:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_If(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::SWITCH:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Switch(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::SWITCH_ALL:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_SwitchAll(InTokens, LIndex));

			++LIndex;
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
	case ETokenType::PLUS:
	{
		//TODO
		return nullptr;
	}
	case ETokenType::MINUS:
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





std::shared_ptr<IASTNode> ScopeNode::Parse_Scope(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, "", 0, 0, 0, CurrentCompileOptions);
		return nullptr;
	}

	const size_t LBraScopeEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LBRA, Index + 1, InTokens);
	if( LBraScopeEnd == InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_RBRA, InTokens[Index], CurrentCompileOptions);
		return nullptr;
	}

	std::shared_ptr<ScopeNode> LScopeNode = std::make_shared<ScopeNode>();
	if( LBraScopeEnd > Index + 1 )
	{
		LScopeNode->BuildAST(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LBraScopeEnd - 1), CurrentCompileOptions);
	}

	Index = LBraScopeEnd;
	return LScopeNode;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticDo(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::DO )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, "", 0, 0, 0, CurrentCompileOptions);
		return nullptr;
	}

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index], CurrentCompileOptions);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index], CurrentCompileOptions);
		return nullptr;
	}

	std::shared_ptr<StaticDoNode> LStaticDoNode = std::make_shared<StaticDoNode>();

	std::shared_ptr<IASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LStaticDoNode->SetOperand(STATIC_DO_NODE_BODY_OPERAND, LDoScope);

	if( Index + 1 < InTokens.size() && InTokens[Index + 1].GetType() == ETokenType::LPAR )
	{
		++Index;

		const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, Index + 1, InTokens);
		if( LParEnd == InTokens.size() )
		{
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[Index], CurrentCompileOptions);
			return nullptr;
		}

		if( LParEnd > Index + 1 )
		{
			std::shared_ptr<IASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd - 1));
			LStaticDoNode->SetOperand(STATIC_DO_NODE_CONDITION_OPERAND, LConditionExpr);
		}

		Index = LParEnd;
	}

	return LStaticDoNode;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticWhile(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticFor(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticForeach(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticIf(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticSwitch(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticSwitchAll(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Do(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::DO )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, "", 0, 0, 0, CurrentCompileOptions);
		return nullptr;
	}

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index], CurrentCompileOptions);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index], CurrentCompileOptions);
		return nullptr;
	}

	std::shared_ptr<DoNode> LDoNode = std::make_shared<DoNode>();

	std::shared_ptr<IASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LDoNode->SetOperand(DO_NODE_BODY_OPERAND, LDoScope);

	if( Index + 1 < InTokens.size() && InTokens[Index + 1].GetType() == ETokenType::LPAR )
	{
		++Index;

		const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, Index + 1, InTokens);
		if( LParEnd == InTokens.size() )
		{
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[Index], CurrentCompileOptions);
			return nullptr;
		}

		if( LParEnd > Index + 1 )
		{
			std::shared_ptr<IASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd - 1));
			LDoNode->SetOperand(DO_NODE_CONDITION_OPERAND, LConditionExpr);
		}

		Index = LParEnd;
	}

	return LDoNode;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_While(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_For(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Foreach(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_If(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Switch(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_SwitchAll(const std::vector<Token>& InTokens, size_t& Index) const
{
	return nullptr;
}



//..........................................................................................................................//
//..........................................................................................................................//



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
