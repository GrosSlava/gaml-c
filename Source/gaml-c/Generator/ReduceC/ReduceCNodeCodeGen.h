// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"

#include "../../Parser/AST/ASTCodeGenFactory.h"




DECLARE_NODE_CODE_GEN(ScopeNodeGen, ScopeNode);



/*
	Concrete factory for nodes code generators.
*/
class ReduceC_ASTCodeGenFactory : public IASTCodeGenFactory
{
public:

	virtual std::shared_ptr<INodeCodeGen<ScopeNode>> MakeScopeGen() const override;
};
