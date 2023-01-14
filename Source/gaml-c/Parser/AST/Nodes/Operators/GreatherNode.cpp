// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void GreatherNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool GreatherNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int GreatherNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double GreatherNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string GreatherNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





void GreatherNode::AssignSubTrees(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	//TODO
	OutUseLeft = true;
	OutUseRight = true;
}





std::string GreatherNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	return "";

	//TODO
}