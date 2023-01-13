// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void WhileNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	std::shared_ptr<IASTNode> LBody = GetOperand(WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator WHILE: Invalid body AST");
		return;
	}
	std::shared_ptr<IASTNode> LCondition = GetOperand(WHILE_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator WHILE: Invalid condition AST");
		return;
	}

	bool LConditionSuccess = true;

	LCondition->InterpretAST(ProgramInfo, LocalInfo);
	LConditionSuccess = LCondition->GetInterpretResultAsBool();
	while( LConditionSuccess )
	{
		LBody->InterpretAST(ProgramInfo, LocalInfo);

		LCondition->InterpretAST(ProgramInfo, LocalInfo);
		LConditionSuccess = LCondition->GetInterpretResultAsBool();
	}
}

bool WhileNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator WHILE: Invalid body AST");
		return false;
	}

	return LBody->GetInterpretResultAsBool();
}

int WhileNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator WHILE: Invalid body AST");
		return 0;
	}

	return LBody->GetInterpretResultAsInt();
}

double WhileNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator WHILE: Invalid body AST");
		return 0.0;
	}

	return LBody->GetInterpretResultAsDouble();
}

std::string WhileNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator WHILE: Invalid body AST");
		return "";
	}

	return LBody->GetInterpretResultAsString();
}





std::string WhileNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<WhileNode>> LCodeGen = ASTCodeGenFactory->MakeWhileGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}