// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "ASTNode.h"




/*
	Class for AST expressions scope.
*/
class ScopeNode final : public ASTNode
{
public:

	ScopeNode() = delete;
	inline ScopeNode(const Token& InToken) : ASTNode(InToken, 0) { }



public:

	/*
		Recursive generate AST.

		@param InTokens - Array of all scope tokens to parse.
		@param CompileOptions - Current compiling options.
	*/
	void BuildAST(const std::vector<Token>& InTokens);

	/*
		@return true if scope has control statement.
	*/
	inline bool GetHasControlStatement() const noexcept { return HasControlStatement; }

public:

	virtual void AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight) override;

	virtual std::string GetNodeName() const noexcept override { return "ScopeNode"; }

private:

	/*
		Recursive parse expression.

		@param InTokens - Slice of tokens only for expression. Terminate ";" not included.
		@return AST.
	*/
	std::shared_ptr<ASTNode> ParseExpr(const std::vector<Token>& InTokens) const;


	/*
		Parse helpers.
		
		@param Index - Index of start, includes operator.
		Index after work points to the end of parsed operator construction (not end + 1).
	*/

	/*
		{ ... }
	*/
	std::shared_ptr<ASTNode> Parse_Scope(const std::vector<Token>& InTokens, size_t& Index) const;

	/*
		static do { ... } (CONDITION)
	*/
	std::shared_ptr<ASTNode> Parse_StaticDo(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static while (CONDITION) { ... }
	*/
	std::shared_ptr<ASTNode> Parse_StaticWhile(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static for (INIT; CONDITION; EXPRESSION) { ... }
	*/
	std::shared_ptr<ASTNode> Parse_StaticFor(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static foreach (EXPRESSION) { ... }
	*/
	std::shared_ptr<ASTNode> Parse_StaticForeach(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static if (CONDITION) { ... } elif (CONDITION) { ... } else { ... }
	*/
	std::shared_ptr<ASTNode> Parse_StaticIf(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static switch(EXPRESSION) { case A{ ... } ... }
	*/
	std::shared_ptr<ASTNode> Parse_StaticSwitch(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static switch_all(EXPRESSION) { case A{ ... } ... }
	*/
	std::shared_ptr<ASTNode> Parse_StaticSwitchAll(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		do { ... } (CONDITION)
	*/
	std::shared_ptr<ASTNode> Parse_Do(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		while (CONDITION) { ... }
	*/
	std::shared_ptr<ASTNode> Parse_While(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		for (INIT; CONDITION; EXPRESSION) { ... }
	*/
	std::shared_ptr<ASTNode> Parse_For(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		foreach (EXPRESSION) { ... }
	*/
	std::shared_ptr<ASTNode> Parse_Foreach(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		if (CONDITION) { ... } elif (CONDITION) { ... } else { ... }
	*/
	std::shared_ptr<ASTNode> Parse_If(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		switch(EXPRESSION) { case A{ ... } ... }
	*/
	std::shared_ptr<ASTNode> Parse_Switch(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		switch_all(EXPRESSION) { case A{ ... } ... }
	*/
	std::shared_ptr<ASTNode> Parse_SwitchAll(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		assert(condition, message);
	*/
	std::shared_ptr<ASTNode> Parse_Assert(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_assert(condition, message);
	*/
	std::shared_ptr<ASTNode> Parse_StaticAssert(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_error(message);
	*/
	std::shared_ptr<ASTNode> Parse_StaticError(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_warning(message);
	*/
	std::shared_ptr<ASTNode> Parse_StaticWarning(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_message(message);
	*/
	std::shared_ptr<ASTNode> Parse_StaticMessage(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		using LOCAL_ALIAS = TYPE;
	*/
	std::shared_ptr<ASTNode> Parse_Using(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		var TYPE NAME = EXPRESSION;
	*/
	std::shared_ptr<ASTNode> Parse_Var(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		break;
	*/
	std::shared_ptr<ASTNode> Parse_Break(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		continue;
	*/
	std::shared_ptr<ASTNode> Parse_Continue(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		return EXPRESSION;
	*/
	std::shared_ptr<ASTNode> Parse_Return(const std::vector<Token>& InTokens, size_t& Index) const;

	/*
		IDENTIFIER(EXPRESSION)
	*/
	std::shared_ptr<ASTNode> Parse_Call(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		IDENTIFIER[EXPRESSION]
	*/
	std::shared_ptr<ASTNode> Parse_IndexAccess(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		class<|EXPRESSION|>
	*/
	std::shared_ptr<ASTNode> Parse_Class(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		array<|EXPRESSION|>
	*/
	std::shared_ptr<ASTNode> Parse_Array(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		lambda (EXPRESSION) [EXPRESSION] { ... }
	*/
	std::shared_ptr<ASTNode> Parse_Lambda(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		CONDITION ? EXPRESSION : EXPRESSION 
	*/
	std::shared_ptr<ASTNode> Parse_Thernal(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		cast<|EXPRESSION|>(EXPRESSION)
	*/
	std::shared_ptr<ASTNode> Parse_Cast(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		unsafe_cast<|EXPRESSION|>(EXPRESSION)
	*/
	std::shared_ptr<ASTNode> Parse_UnsafeCast(const std::vector<Token>& InTokens, size_t& Index) const;




private:

	/*
		Flag shows that this AST has any control statement. 
	*/
	bool HasControlStatement = false;
};