// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void StaticForeachNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool StaticForeachNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOREACH_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOREACH: Invalid body AST");
		return false;
	}

	return LBody->GetInterpretResultAsBool();
}

int StaticForeachNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOREACH_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOREACH: Invalid body AST");
		return 0;
	}

	return LBody->GetInterpretResultAsInt();
}

double StaticForeachNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOREACH_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOREACH: Invalid body AST");
		return 0.0;
	}

	return LBody->GetInterpretResultAsDouble();
}

std::string StaticForeachNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_FOREACH_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC FOREACH: Invalid body AST");
		return "";
	}

	return LBody->GetInterpretResultAsString();
}





std::string StaticForeachNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<StaticForeachNode>> LCodeGen = ASTCodeGenFactory->MakeStaticForeachGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}