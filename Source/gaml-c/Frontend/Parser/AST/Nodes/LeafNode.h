// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "ASTNode.h"

#include "Token/Token.h"




/*
	Class for leaf AST node.
	Can contains only literals (constants, variable/function/class/module names).
*/
class LeafNode final : public IASTNode
{
public:

	LeafNode() = delete;
	inline LeafNode(const Token& InToken) : LeafToken(InToken) { }



public:

	/*
		Can return correct value only for constants.
	*/
	virtual void InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo) override { }
	virtual bool GetInterpretResultAsBool() const override;
	virtual int GetInterpretResultAsInt() const override;
	virtual double GetInterpretResultAsDouble() const override;
	virtual std::string GetInterpretResultAsString() const override;

	virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const override { return ""; }




public:

	/*
		Info about leaf token.
	*/
	Token LeafToken;
};
