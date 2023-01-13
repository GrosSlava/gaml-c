// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void IfNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid condition AST");
		return;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid true AST");
		return;
	}

	LCondition->InterpretAST(ProgramInfo, LocalInfo);
	if( LCondition->GetInterpretResultAsBool() )
	{
		LTrueBody->InterpretAST(ProgramInfo, LocalInfo);
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return;
		}

		LFalseBody->InterpretAST(ProgramInfo, LocalInfo);
	}
}

bool IfNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid condition AST");
		return false;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid true AST");
		return false;
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsBool();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return false;
		}

		return LFalseBody->GetInterpretResultAsBool();
	}

	return false;
}

int IfNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid condition AST");
		return 0;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid true AST");
		return 0;
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsInt();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return 0;
		}

		return LFalseBody->GetInterpretResultAsInt();
	}

	return 0;
}

double IfNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid condition AST");
		return 0.0;
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid true AST");
		return 0.0;
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsDouble();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return 0.0;
		}

		return LFalseBody->GetInterpretResultAsDouble();
	}

	return 0.0;
}

std::string IfNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LCondition = GetOperand(IF_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid condition AST");
		return "";
	}
	std::shared_ptr<IASTNode> LTrueBody = GetOperand(IF_NODE_TRUE_BODY_OPERAND);
	if( LTrueBody == nullptr )
	{
		FCompileLogger::MessageError("Operator IF: Invalid true AST");
		return "";
	}

	if( LCondition->GetInterpretResultAsBool() )
	{
		return LTrueBody->GetInterpretResultAsString();
	}
	else
	{
		std::shared_ptr<IASTNode> LFalseBody = GetOperand(IF_NODE_FALSE_BODY_OPERAND);
		if( LTrueBody == nullptr )
		{
			return "";
		}

		return LFalseBody->GetInterpretResultAsString();
	}

	return "";
}





std::string IfNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<IfNode>> LCodeGen = ASTCodeGenFactory->MakeIfGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}