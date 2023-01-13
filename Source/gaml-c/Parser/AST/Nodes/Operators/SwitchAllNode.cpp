// Copyright 2022 - 2023 GrosSlava.

#include "../ASTOperators.h"
#include "../../../../Logger/CompileLogger.h"





void SwitchAllNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool SwitchAllNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int SwitchAllNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double SwitchAllNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string SwitchAllNode::GetInterpretResultAsString() const
{
	//TODO
	return "";
}





std::string SwitchAllNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<SwitchAllNode>> LCodeGen = ASTCodeGenFactory->MakeSwitchAllGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}