// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"




class ScopeNode;
struct Token;



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
	void BuildAST(const std::vector<Token>& InTokens);

	/*
		Check that AST contains only single expression without control operators.
	*/
	bool IsPureExpression() const noexcept;


	/*
		Convert tree to str.
	*/
	std::string GetTreeAsStr() const noexcept;




public:

	/*
		AST main scope.
	*/
	std::shared_ptr<ScopeNode> MainScope = nullptr;
};
