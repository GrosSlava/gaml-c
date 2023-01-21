// Copyright 2022 - 2023 GrosSlava.

#include "AST.h"

#include "Nodes/ScopeNode.h"
#include "ASTSymbols.h"





void AST::BuildAST(const std::vector<Token>& InTokens)
{
	MainScope = std::make_shared<ScopeNode>();
	MainScope->BuildAST(InTokens);
}





void AST::InterpretAST(const FProgramInfo& ProgramInfo)
{
	if( MainScope == nullptr )
	{
		return;
	}

	FASTSymbols LSymbols;
	MainScope->InterpretAST(ProgramInfo, LSymbols);
}

bool AST::GetInterpretResultAsBool() const
{
	if( MainScope == nullptr )
	{
		return false;
	}

	return MainScope->GetInterpretResultAsBool();
}

int AST::GetInterpretResultAsInt() const
{
	if( MainScope == nullptr )
	{
		return 0;
	}

	return MainScope->GetInterpretResultAsInt();
}

double AST::GetInterpretResultAsDouble() const
{
	if( MainScope == nullptr )
	{
		return 0.0;
	}

	return MainScope->GetInterpretResultAsDouble();
}

std::string AST::GetInterpretResultAsString() const
{
	if( MainScope == nullptr )
	{
		return "";
	}

	return MainScope->GetInterpretResultAsString();
}





std::string AST::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( MainScope == nullptr )
	{
		return "";
	}

	return MainScope->GenerateCode(ASTCodeGenFactory, ProgramInfo);
}





bool AST::IsPureExpression() const noexcept
{
	return MainScope != nullptr && MainScope->ExprSequence.size() == 1 && !MainScope->GetHasControlStatement();
}
