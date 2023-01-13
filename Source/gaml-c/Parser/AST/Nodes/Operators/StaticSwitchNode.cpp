// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void StaticSwitchNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool StaticSwitchNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int StaticSwitchNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double StaticSwitchNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string StaticSwitchNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





std::string StaticSwitchNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<StaticSwitchNode>> LCodeGen = ASTCodeGenFactory->MakeStaticSwitchGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}