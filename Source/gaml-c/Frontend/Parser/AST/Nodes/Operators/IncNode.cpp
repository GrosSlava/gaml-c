// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/ErrorLogger.h"





void IncNode::AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	if(!Lhs)
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
	}
	
	Children[INC_NODE_LEFT_OPERAND] = Lhs;
	
	OutUseLeft = true;
	OutUseRight = false;
}
