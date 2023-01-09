// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../../CoreMinimal.h"

#include "ASTNode.h"
#include "../../../Compiler/CompilerOptions.h"




class Token;


/*
	Class for AST expressions scope.
*/
class ScopeNode final : public IASTNode
{
public:

	inline ScopeNode() { }



public:

	/*
		Recursive generate AST.

		@param InTokens - Array of all scope tokens to parse.
		@param CompileOptions - Current compiling options.
	*/
	void BuildAST(const std::vector<Token>& InTokens, const FCompileOptions& CompileOptions);

public:

	virtual void InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo) override;
	virtual bool GetInterpretResultAsBool() const override;
	virtual int GetInterpretResultAsInt() const override;
	virtual double GetInterpretResultAsDouble() const override;
	virtual std::string GetInterpretResultAsString() const override;

	virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const override;


private:

	std::shared_ptr<IASTNode> ParseExpr(const std::vector<Token>& InTokens) const;




public:

	/*
		Array of AST expressions in order to be compiled or interpreted.
	*/
	std::vector<std::shared_ptr<IASTNode>> ExprSequence;

private:

	/*
		Cached compile options.
	*/
	FCompileOptions CurrentCompileOptions;
};