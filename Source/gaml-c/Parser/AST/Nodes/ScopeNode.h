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

	/*
		Flag shows that this AST has any control statement. 
	*/
	bool HasControlStatement = false;
};