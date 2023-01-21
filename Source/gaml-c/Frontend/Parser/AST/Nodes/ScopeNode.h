// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "ASTNode.h"




struct Token;



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
	void BuildAST(const std::vector<Token>& InTokens);

public:

	virtual void InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo) override;
	virtual bool GetInterpretResultAsBool() const override;
	virtual int GetInterpretResultAsInt() const override;
	virtual double GetInterpretResultAsDouble() const override;
	virtual std::string GetInterpretResultAsString() const override;

	virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const override;

public:

	inline bool GetHasControlStatement() const noexcept { return HasControlStatement; }

private:

	/*
		Recursive parse expression.

		@param InTokens - Slice of tokens only for expression. Terminate ";" not included.
		@return AST.
	*/
	std::shared_ptr<IASTNode> ParseExpr(const std::vector<Token>& InTokens) const;


	/*
		Parse helpers.
		
		@param Index - Index of start, includes operator.
		Index after work points to the end of parsed operator construction (not end + 1).
	*/

	/*
		{ ... }
	*/
	std::shared_ptr<IASTNode> Parse_Scope(const std::vector<Token>& InTokens, size_t& Index) const;

	/*
		static do { ... } (CONDITION)
	*/
	std::shared_ptr<IASTNode> Parse_StaticDo(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static while (CONDITION) { ... }
	*/
	std::shared_ptr<IASTNode> Parse_StaticWhile(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static for (INIT; CONDITION; EXPRESSION) { ... }
	*/
	std::shared_ptr<IASTNode> Parse_StaticFor(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static foreach (EXPRESSION) { ... }
	*/
	std::shared_ptr<IASTNode> Parse_StaticForeach(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static if (CONDITION) { ... } elif (CONDITION) { ... } else { ... }
	*/
	std::shared_ptr<IASTNode> Parse_StaticIf(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		TODO
	*/
	std::shared_ptr<IASTNode> Parse_StaticSwitch(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		TODO
	*/
	std::shared_ptr<IASTNode> Parse_StaticSwitchAll(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		do { ... } (CONDITION)
	*/
	std::shared_ptr<IASTNode> Parse_Do(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		while (CONDITION) { ... }
	*/
	std::shared_ptr<IASTNode> Parse_While(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		for (INIT; CONDITION; EXPRESSION) { ... }
	*/
	std::shared_ptr<IASTNode> Parse_For(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		foreach (EXPRESSION) { ... }
	*/
	std::shared_ptr<IASTNode> Parse_Foreach(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		if (CONDITION) { ... } elif (CONDITION) { ... } else { ... }
	*/
	std::shared_ptr<IASTNode> Parse_If(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		TODO
	*/
	std::shared_ptr<IASTNode> Parse_Switch(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		TODO
	*/
	std::shared_ptr<IASTNode> Parse_SwitchAll(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		assert(condition, message);
	*/
	std::shared_ptr<IASTNode> Parse_Assert(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_assert(condition, message);
	*/
	std::shared_ptr<IASTNode> Parse_StaticAssert(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_error(message);
	*/
	std::shared_ptr<IASTNode> Parse_StaticError(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_warning(message);
	*/
	std::shared_ptr<IASTNode> Parse_StaticWarning(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		static_message(message);
	*/
	std::shared_ptr<IASTNode> Parse_StaticMessage(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		using LOCAL_ALIAS = TYPE;
	*/
	std::shared_ptr<IASTNode> Parse_Using(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		var TYPE NAME = EXPRESSION;
	*/
	std::shared_ptr<IASTNode> Parse_Var(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		break;
	*/
	std::shared_ptr<IASTNode> Parse_Break(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		continue;
	*/
	std::shared_ptr<IASTNode> Parse_Continue(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		return EXPRESSION;
	*/
	std::shared_ptr<IASTNode> Parse_Return(const std::vector<Token>& InTokens, size_t& Index) const;

	/*
		IDENTIFIER(EXPRESSION)
	*/
	std::shared_ptr<IASTNode> Parse_Call(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		IDENTIFIER[EXPRESSION]
	*/
	std::shared_ptr<IASTNode> Parse_IndexAccess(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		class<|EXPRESSION|>
	*/
	std::shared_ptr<IASTNode> Parse_Class(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		array<|EXPRESSION|>
	*/
	std::shared_ptr<IASTNode> Parse_Array(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		lambda (EXPRESSION) [EXPRESSION] { ... }
	*/
	std::shared_ptr<IASTNode> Parse_Lambda(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		CONDITION ? EXPRESSION : EXPRESSION 
	*/
	std::shared_ptr<IASTNode> Parse_Thernal(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		cast<|EXPRESSION|>(EXPRESSION)
	*/
	std::shared_ptr<IASTNode> Parse_Cast(const std::vector<Token>& InTokens, size_t& Index) const;
	/*
		unsafe_cast<|EXPRESSION|>(EXPRESSION)
	*/
	std::shared_ptr<IASTNode> Parse_UnsafeCast(const std::vector<Token>& InTokens, size_t& Index) const;



public:

	/*
		Array of AST expressions in order to be compiled or interpreted.
	*/
	std::vector<std::shared_ptr<IASTNode>> ExprSequence;

private:

	/*
		Flag shows that this AST has any control statement. 
	*/
	bool HasControlStatement = false;
};