// Copyright 2022 - 2023 GrosSlava.

#include "ScopeNode.h"

#include "../../../Token/Token.h"

#include "../ASTCodeGenFactory.h"
#include "../ASTSymbols.h"





void ScopeNode::BuildAST(const std::vector<Token>& InTokens, const FCompileOptions& CompileOptions)
{
	//TODO
}

std::shared_ptr<IASTNode> ScopeNode::ParseExpr(const std::vector<Token>& InTokens) const
{
	//TODO
	return std::shared_ptr<IASTNode>();
}





void ScopeNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool ScopeNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int ScopeNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double ScopeNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string ScopeNode::GetInterpretResultAsString() const
{
	//TODO
	return std::string();
}





std::string ScopeNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<ScopeNode>> LCodeGen = ASTCodeGenFactory->MakeScopeGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}
