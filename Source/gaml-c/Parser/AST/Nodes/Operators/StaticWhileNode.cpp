// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void StaticWhileNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC WHILE: Invalid body AST");
		return;
	}
	std::shared_ptr<IASTNode> LCondition = GetOperand(STATIC_WHILE_NODE_CONDITION_OPERAND);
	if( LCondition == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC WHILE: Invalid condition AST");
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

bool StaticWhileNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC WHILE: Invalid body AST");
		return false;
	}

	return LBody->GetInterpretResultAsBool();
}

int StaticWhileNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC WHILE: Invalid body AST");
		return 0;
	}

	return LBody->GetInterpretResultAsInt();
}

double StaticWhileNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC WHILE: Invalid body AST");
		return 0.0;
	}

	return LBody->GetInterpretResultAsDouble();
}

std::string StaticWhileNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_WHILE_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC WHILE: Invalid body AST");
		return "";
	}

	return LBody->GetInterpretResultAsString();
}





std::string StaticWhileNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<StaticWhileNode>> LCodeGen = ASTCodeGenFactory->MakeStaticWhileGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}