// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void ForNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool ForNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator FOR: Invalid body AST");
		return false;
	}

	return LBody->GetInterpretResultAsBool();
}

int ForNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator FOR: Invalid body AST");
		return 0;
	}

	return LBody->GetInterpretResultAsInt();
}

double ForNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator FOR: Invalid body AST");
		return 0.0;
	}

	return LBody->GetInterpretResultAsDouble();
}

std::string ForNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator FOR: Invalid body AST");
		return "";
	}

	return LBody->GetInterpretResultAsString();
}





std::string ForNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<ForNode>> LCodeGen = ASTCodeGenFactory->MakeForGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}