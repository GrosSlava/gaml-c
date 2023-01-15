// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void DoNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	std::shared_ptr<IASTNode> LBody = GetOperand(DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator DO: Invalid body AST");
		return;
	}
	std::shared_ptr<IASTNode> LCondition = GetOperand(DO_NODE_CONDITION_OPERAND);

	bool LConditionSuccess = true;
	do
	{
		LBody->InterpretAST(ProgramInfo, LocalInfo);

		if( LCondition == nullptr )
		{
			LConditionSuccess = false;
		}
		else
		{
			LCondition->InterpretAST(ProgramInfo, LocalInfo);
			LConditionSuccess = LCondition->GetInterpretResultAsBool();
		}
	} while( LConditionSuccess );
}

bool DoNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator DO: Invalid body AST");
		return false;
	}

	return LBody->GetInterpretResultAsBool();
}

int DoNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator DO: Invalid body AST");
		return 0;
	}

	return LBody->GetInterpretResultAsInt();
}

double DoNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator DO: Invalid body AST");
		return 0.0;
	}

	return LBody->GetInterpretResultAsDouble();
}

std::string DoNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator DO: Invalid body AST");
		return "";
	}

	return LBody->GetInterpretResultAsString();
}





std::string DoNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<DoNode>> LCodeGen = ASTCodeGenFactory->MakeDoGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}