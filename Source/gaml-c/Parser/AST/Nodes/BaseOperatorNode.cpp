// Copyright 2022 - 2023 GrosSlava.

#include "BaseOperatorNode.h"

#include "../../../Logger/ErrorLogger.h"





void BaseOperatorNode::SetOperand(int Index, std::shared_ptr<IASTNode> Operand)
{
	if( Index < 0 || Index >= Operands.size() )
	{
		FCompileOptions LCompileOptions;
		LCompileOptions.IncludeContextIntoErrors = true;
		FErrorLogger::Raise(EErrorMessageType::AST_SET_OPERATOR_OPERAND_OUT_OF_RANGE, ContextToken, LCompileOptions);
		return;
	}

	Operands[Index] = Operand;
}