// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"




struct FProgramInfo;




/*
	Interface for node code generator.
*/
template<class T>
class INodeCodeGen
{
public:

	INodeCodeGen() { }
	virtual ~INodeCodeGen() { }



public:

	/*
		Produce third-party compiler specific code based on ASTNode.
	*/
	virtual std::string GenerateCode(const T* ASTNode, const FProgramInfo& ProgramInfo) = 0;
};



/*
	Factory for AST node code generators.
	Inherit it and implement for making your concrete NodeCodeGen for your generator.
*/
class IASTCodeGenFactory
{
public:

	IASTCodeGenFactory() { }
	virtual ~IASTCodeGenFactory() { }

public:

	virtual std::shared_ptr<INodeCodeGen<class ASTRoot>> MakeRootGen() const = 0;
};