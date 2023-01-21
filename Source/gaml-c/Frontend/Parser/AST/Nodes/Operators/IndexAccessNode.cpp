// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void IndexAccessNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool IndexAccessNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int IndexAccessNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double IndexAccessNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string IndexAccessNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





void IndexAccessNode::AssignSubTrees(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	//TODO
	OutUseLeft = true;
	OutUseRight = true;
}





std::string IndexAccessNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	return "";

	//TODO
}