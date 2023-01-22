// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/ErrorLogger.h"





void EqualNode::AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	if(!Lhs || !Rhs)
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
	}
	
	Children[EQUAL_NODE_LEFT_OPERAND] = Lhs;
	Children[EQUAL_NODE_RIGHT_OPERAND] = Rhs;
	
	OutUseLeft = true;
	OutUseRight = true;
}
