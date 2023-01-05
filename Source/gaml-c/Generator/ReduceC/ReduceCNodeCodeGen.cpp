// Copyright 2022 - 2023 GrosSlava.

#include "ReduceCNodeCodeGen.h"

#include "ASTCodeGen/RootNodeGen.h"





std::shared_ptr<INodeCodeGen<ASTRoot>> ReduceC_ASTCodeGenFactory::MakeRootGen() const
{
	return std::make_shared<RootNodeGen>();
}