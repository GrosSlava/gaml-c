// Copyright 2022 - 2023 GrosSlava.

#include "ReduceCNodeCodeGen.h"





std::shared_ptr<INodeCodeGen<ScopeNode>> ReduceC_ASTCodeGenFactory::MakeScopeGen() const
{
	return std::make_shared<ScopeNodeGen>();
}