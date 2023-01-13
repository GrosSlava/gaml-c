// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void StaticSwitchAllNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool StaticSwitchAllNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int StaticSwitchAllNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double StaticSwitchAllNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string StaticSwitchAllNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





std::string StaticSwitchAllNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<StaticSwitchAllNode>> LCodeGen = ASTCodeGenFactory->MakeStaticSwitchAllGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}