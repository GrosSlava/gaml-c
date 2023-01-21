// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void CallNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool CallNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int CallNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double CallNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string CallNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





void CallNode::AssignSubTrees(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	//TODO
	OutUseLeft = true;
	OutUseRight = true;
}





std::string CallNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	return "";

	//TODO
}