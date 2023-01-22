// Copyright 2022 - 2023 GrosSlava.

#include "ASTNode.h"

#include "Logger/ErrorLogger.h"





void ASTNode::SetChild(int Index, std::shared_ptr<ASTNode> Child)
{
	if( Index < 0 || Index >= Children.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::AST_SET_CHILD_OUT_OF_RANGE, ContextToken);
		return;
	}

	Children[Index] = Child;
}