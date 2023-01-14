// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../../CoreMinimal.h"

#include "../../../Token/Token.h"

#include "ASTNode.h"
#include "../ASTCodeGenFactory.h"
#include "../ASTSymbols.h"




/*
	Base class for all operators.
*/
class BaseOperatorNode : public IASTNode
{
public:

	BaseOperatorNode() = delete;
	inline BaseOperatorNode(int OperandsCount, const Token& InToken) : Operands(OperandsCount, nullptr), ContextToken(InToken) { }



public:

	/*
		@return operand at index, invalid index returns nullptr.
	*/
	inline std::shared_ptr<IASTNode> GetOperand(int Index) const noexcept
	{
		if( Index < 0 || Index >= Operands.size() ) return nullptr;

		return Operands[Index];
	}
	/*
		Set operand at index.
		Invalid index cause compilation error.
	*/
	void SetOperand(int Index, std::shared_ptr<IASTNode> Operand);

	/*
		@return cached context token.
	*/
	inline const Token& GetCTXToken() const noexcept { return ContextToken; }




protected:

	/*
		AST for operator expression.
	*/
	std::vector<std::shared_ptr<IASTNode>> Operands;

	/*
		Context operator token.
	*/
	Token ContextToken;

	/*
		Cached operator work result.
	*/
	bool CachedInterperetResultBool = false;
	int CachedInterperetResultInt = 0;
	double CachedInterperetResultDouble = 0.0;
	std::string CachedInterperetResultString = "";
};

/*
	Base class for all expression operators.
*/
class BaseExpressionOperatorNode : public BaseOperatorNode
{
public:

	BaseExpressionOperatorNode() = delete;
	inline BaseExpressionOperatorNode(int OperandsCount, const Token& InToken) : BaseOperatorNode(OperandsCount, InToken) { }



public:

	/*
		Assign left or/and right subtrees.
	*/
	virtual void AssignSubTrees(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight) = 0;
};


#define DECLARE_OPERATOR_NODE(Name, OpCount)                                                                                                     \
	class Name final : public BaseOperatorNode                                                                                                   \
	{                                                                                                                                            \
	public:                                                                                                                                      \
                                                                                                                                                 \
		inline Name(const Token& InToken) : BaseOperatorNode(OpCount, InToken)                                                                   \
		{                                                                                                                                        \
		}                                                                                                                                        \
                                                                                                                                                 \
	public:                                                                                                                                      \
                                                                                                                                                 \
		virtual void InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo) override;                                             \
		virtual bool GetInterpretResultAsBool() const override;                                                                                  \
		virtual int GetInterpretResultAsInt() const override;                                                                                    \
		virtual double GetInterpretResultAsDouble() const override;                                                                              \
		virtual std::string GetInterpretResultAsString() const override;                                                                         \
                                                                                                                                                 \
		virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const override; \
	};

#define DECLARE_EXPESSION_OPERATOR_NODE(Name, OpCount)                                                                                           \
	class Name final : public BaseExpressionOperatorNode                                                                                         \
	{                                                                                                                                            \
	public:                                                                                                                                      \
                                                                                                                                                 \
		inline Name(const Token& InToken) : BaseExpressionOperatorNode(OpCount, InToken)                                                         \
		{                                                                                                                                        \
		}                                                                                                                                        \
                                                                                                                                                 \
	public:                                                                                                                                      \
                                                                                                                                                 \
		virtual void InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo) override;                                             \
		virtual bool GetInterpretResultAsBool() const override;                                                                                  \
		virtual int GetInterpretResultAsInt() const override;                                                                                    \
		virtual double GetInterpretResultAsDouble() const override;                                                                              \
		virtual std::string GetInterpretResultAsString() const override;                                                                         \
                                                                                                                                                 \
		virtual void AssignSubTrees(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight) override; \
                                                                                                                                                 \
		virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const override; \
	};
