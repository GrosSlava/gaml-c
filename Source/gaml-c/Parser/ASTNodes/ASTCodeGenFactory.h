// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"




struct FProgramInfo;

class IASTNode;




/*
	Interface for node code generator.
	Inherit and implement for your generator.
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
	virtual std::string GenerateCode(std::shared_ptr<T> ASTNode, const FProgramInfo& OutProgramInfo) = 0;
};



/*
	Factory for AST node code generators.
	Inherit and implement for making your concrete NodeCodeGen for your generator.
*/
class IASTCodeGenFactory
{
public:

	IASTCodeGenFactory() { }
	virtual ~IASTCodeGenFactory() { }

public:

	//TODO
	//virtual std::shared_ptr<INodeCodeGen<IASTNode>> MakeA() const = 0;
};