// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void StaticDoNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC DO: Invalid body AST");
		return;
	}
	std::shared_ptr<IASTNode> LCondition = GetOperand(STATIC_DO_NODE_CONDITION_OPERAND);

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

bool StaticDoNode::GetInterpretResultAsBool() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC DO: Invalid body AST");
		return false;
	}

	return LBody->GetInterpretResultAsBool();
}

int StaticDoNode::GetInterpretResultAsInt() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC DO: Invalid body AST");
		return 0;
	}

	return LBody->GetInterpretResultAsInt();
}

double StaticDoNode::GetInterpretResultAsDouble() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC DO: Invalid body AST");
		return 0.0;
	}

	return LBody->GetInterpretResultAsDouble();
}

std::string StaticDoNode::GetInterpretResultAsString() const
{
	std::shared_ptr<IASTNode> LBody = GetOperand(STATIC_DO_NODE_BODY_OPERAND);
	if( LBody == nullptr )
	{
		FCompileLogger::MessageError("Operator STATIC DO: Invalid body AST");
		return "";
	}

	return LBody->GetInterpretResultAsString();
}





std::string StaticDoNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<StaticDoNode>> LCodeGen = ASTCodeGenFactory->MakeStaticDoGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}