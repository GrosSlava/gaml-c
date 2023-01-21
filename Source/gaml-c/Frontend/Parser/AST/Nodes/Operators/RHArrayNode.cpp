// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void RHArrayNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool RHArrayNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int RHArrayNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double RHArrayNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string RHArrayNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





void RHArrayNode::AssignSubTrees(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	//TODO
	OutUseLeft = true;
	OutUseRight = true;
}





std::string RHArrayNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	return "";

	//TODO
}