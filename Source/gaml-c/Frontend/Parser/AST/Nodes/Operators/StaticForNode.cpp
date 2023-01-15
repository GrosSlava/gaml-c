// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void StaticForNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool StaticForNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOR: Invalid body AST");
		return false;
	}

	return LBody->GetInterpretResultAsBool();
}

int StaticForNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOR: Invalid body AST");
		return 0;
	}

	return LBody->GetInterpretResultAsInt();
}

double StaticForNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOR: Invalid body AST");
		return 0.0;
	}

	return LBody->GetInterpretResultAsDouble();
}

std::string StaticForNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOR_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOR: Invalid body AST");
		return "";
	}

	return LBody->GetInterpretResultAsString();
}





std::string StaticForNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<StaticForNode>> LCodeGen = ASTCodeGenFactory->MakeStaticForGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}