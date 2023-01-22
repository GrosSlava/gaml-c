// Copyright 2022 - 2023 GrosSlava.

#include "Parser/AST/Nodes/ASTOperators.h"
#include "Logger/ErrorLogger.h"





void IsEnumerableNode::AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	OutUseLeft = false;
	OutUseRight = false;

	FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
}
