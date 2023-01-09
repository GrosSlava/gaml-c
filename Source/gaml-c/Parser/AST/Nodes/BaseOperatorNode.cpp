// Copyright 2022 - 2023 GrosSlava.

#include "BaseOperatorNode.h"

#include "../../../Logger/CompileLogger.h"





void BaseOperatorNode::SetOperand(int Index, std::shared_ptr<IASTNode> Operand)
{
	if( Index < 0 || Index >= Operands.size() )
	{
		FCompileLogger::MessageError("Operator operand set at index out of range: " + std::to_string(Index) + " of " + std::to_string(Operands.size()));
		return;
	}

	Operands[Index] = Operand;
}