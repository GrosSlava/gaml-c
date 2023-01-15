// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/CompileLogger.h"





void SwitchNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool SwitchNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int SwitchNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double SwitchNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string SwitchNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





std::string SwitchNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<SwitchNode>> LCodeGen = ASTCodeGenFactory->MakeSwitchGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}