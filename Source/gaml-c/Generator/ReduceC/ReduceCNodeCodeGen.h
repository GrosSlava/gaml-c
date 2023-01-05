// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"

#include "../../Parser/ASTNodes/ASTCodeGenFactory.h"




/*
	Concrete factory for nodes code generators.
*/
class ReduceC_ASTCodeGenFactory : public IASTCodeGenFactory
{
public:

	virtual std::shared_ptr<INodeCodeGen<class ASTRoot>> MakeRootGen() const override;
};