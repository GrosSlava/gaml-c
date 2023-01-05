// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../../CoreMinimal.h"

#include "../../../Parser/ASTNodes/ASTCodeGenFactory.h"
#include "../../../Parser/ASTNodes/ASTRoot.h"




class RootNodeGen : public INodeCodeGen<ASTRoot>
{
public:

	virtual std::string GenerateCode(const ASTRoot* ASTNode, const FProgramInfo& ProgramInfo) override;
};