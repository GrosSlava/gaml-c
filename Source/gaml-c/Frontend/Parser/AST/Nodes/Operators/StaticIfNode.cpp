// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void StaticIfNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(STATIC_IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid condition AST");
		return;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(STATIC_IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid true AST");
		return;
	}

	LCondition->InterpretAST(ProgramInfo, LocalInfo);
	if( LCondition->GetInterpretResultAsBool() )
	{
		LTrueBody->InterpretAST(ProgramInfo, LocalInfo);
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(STATIC_IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return;
		}

		LFalseBody->InterpretAST(ProgramInfo, LocalInfo);
	}
}

bool StaticIfNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(STATIC_IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid condition AST");
		return false;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(STATIC_IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid true AST");
		return false;
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsBool();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(STATIC_IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return false;
		}

		return LFalseBody->GetInterpretResultAsBool();
	}

	return false;
}

int StaticIfNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(STATIC_IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid condition AST");
		return 0;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(STATIC_IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid true AST");
		return 0;
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsInt();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(STATIC_IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return 0;
		}

		return LFalseBody->GetInterpretResultAsInt();
	}

	return 0;
}

double StaticIfNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(STATIC_IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid condition AST");
		return 0.0;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(STATIC_IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid true AST");
		return 0.0;
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsDouble();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(STATIC_IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return 0.0;
		}

		return LFalseBody->GetInterpretResultAsDouble();
	}

	return 0.0;
}

std::string StaticIfNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(STATIC_IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid condition AST");
		return "";
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(STATIC_IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC IF: Invalid true AST");
		return "";
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsString();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(STATIC_IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return "";
		}

		return LFalseBody->GetInterpretResultAsString();
	}

	return "";
}





std::string StaticIfNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<StaticIfNode>> LCodeGen = ASTCodeGenFactory->MakeStaticIfGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}