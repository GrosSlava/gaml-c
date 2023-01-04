// Copyright 2022 GrosSlava.

#include "ASTRoot.h"





void ASTRoot::BuildAST(const std::vector<Token>& InTokens, size_t Index)
{
	//TODO
}

void ASTRoot::InterpretAST(const FProgramInfo& OutProgramInfo)
{
	//TODO
}

std::string ASTRoot::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& OutProgramInfo) const
{
	//TODO
	return "";
}





bool ASTRoot::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int ASTRoot::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double ASTRoot::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string ASTRoot::GetInterpretResultAsString() const
{
	//TODO
	return "";
}
