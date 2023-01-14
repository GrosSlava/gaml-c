// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void LessNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool LessNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int LessNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double LessNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string LessNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





void LessNode::AssignSubTrees(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	//TODO
	OutUseLeft = true;
	OutUseRight = true;
}





std::string LessNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	return "";

	//TODO
}