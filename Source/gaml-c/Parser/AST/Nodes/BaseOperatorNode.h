// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../../CoreMinimal.h"

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
	inline BaseOperatorNode(int OperandsCount) : Operands(OperandsCount, nullptr) { }



public:

	/*
		@return operand at index, invalid index returns nullptr.
	*/
	inline std::shared_ptr<IASTNode> GetOperand(int Index) noexcept
	{
		if( Index < 0 || Index >= Operands.size() ) return nullptr;

		return Operands[Index];
	}
	/*
		Set operand at index.
		Invalid index cause compilation error, but continue work.
	*/
	void SetOperand(int Index, std::shared_ptr<IASTNode> Operand);




protected:

	/*
		AST for operator expression.
	*/
	std::vector<std::shared_ptr<IASTNode>> Operands;
};



#define DECLARE_OPERATOR_NODE(Name)                                                                                                              \
	class Name final : public BaseOperatorNode                                                                                                   \
	{                                                                                                                                            \
	public:                                                                                                                                      \
                                                                                                                                                 \
		using BaseOperatorNode::BaseOperatorNode;                                                                                                \
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
