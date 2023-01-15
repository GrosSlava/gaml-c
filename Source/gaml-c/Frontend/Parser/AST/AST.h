// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "ASTSymbols.h"




class ScopeNode;
class IASTCodeGenFactory;
struct Token;

struct FCompileOptions;
struct FProgramInfo;



/*
	Abstract syntax tree.
*/
class AST final
{
public:

	inline AST() { }



public:

	/*
		Generate AST.

		@param InTokens - Array of tokens to parse concrete expression.
		@param CompileOptions - Current compiling options.
	*/
	void BuildAST(const std::vector<Token>& InTokens, const FCompileOptions& CompileOptions);

	/*
		Recursive interpret AST.
	*/
	void InterpretAST(const FProgramInfo& ProgramInfo);
	bool GetInterpretResultAsBool() const;
	int GetInterpretResultAsInt() const;
	double GetInterpretResultAsDouble() const;
	std::string GetInterpretResultAsString() const;

	/*
		Gnerate code based on AST.
	*/
	std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const;

public:

	/*
		Check that AST contains only single expression without control operators.
	*/
	bool IsPureExpression() const noexcept;




public:

	/*
		AST main scope.
	*/
	std::shared_ptr<ScopeNode> MainScope = nullptr;
};
