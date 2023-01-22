// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/ErrorLogger.h"





void AndNode::AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	if( !Lhs || !Rhs )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
	}

	Children[AND_NODE_LEFT_OPERAND] = Lhs;
	Children[AND_NODE_RIGHT_OPERAND] = Rhs;

	OutUseLeft = true;
	OutUseRight = true;
}
