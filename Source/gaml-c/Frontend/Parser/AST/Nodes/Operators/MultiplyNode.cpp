// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/ErrorLogger.h"





void MultiplyNode::AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	if( !Lhs || !Rhs )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
	}

	Children[MULTIPLY_NODE_LEFT_OPERAND] = Lhs;
	Children[MULTIPLY_NODE_RIGHT_OPERAND] = Rhs;

	OutUseLeft = true;
	OutUseRight = true;
}
