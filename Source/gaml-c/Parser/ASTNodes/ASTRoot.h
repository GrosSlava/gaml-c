// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"

#include "ASTNode.h"




/*
	AST root.
*/
class ASTRoot : public SequenceNode
{
public:

	inline ASTRoot() { }



public:

	virtual void BuildAST(const std::vector<Token>& InTokens, size_t Index = 0) override;
	virtual void InterpretAST(const FProgramInfo& ProgramInfo) override;
	virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const override;

	virtual bool GetInterpretResultAsBool() const override;
	virtual int GetInterpretResultAsInt() const override;
	virtual double GetInterpretResultAsDouble() const override;
	virtual std::string GetInterpretResultAsString() const override;
};