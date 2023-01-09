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
		Code already optimized and have all types/errors check.
	*/
	virtual std::string GenerateCode(const T* ASTNode, const FProgramInfo& ProgramInfo) = 0;
};

/*
	Helper macros to declare class for AST node code generation.
*/
#define DECLARE_NODE_CODE_GEN(Name, ASTNodeType)                                                                \
	class Name : public INodeCodeGen<ASTNodeType>                                                               \
	{                                                                                                           \
	public:                                                                                                     \
                                                                                                                \
		virtual std::string GenerateCode(const ASTNodeType* ASTNode, const FProgramInfo& ProgramInfo) override; \
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

	virtual std::shared_ptr<INodeCodeGen<class ScopeNode>> MakeScopeGen() const = 0;
};