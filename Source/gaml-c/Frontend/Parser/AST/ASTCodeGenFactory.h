// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"




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

	virtual std::shared_ptr<INodeCodeGen<class StaticDoNode>> MakeStaticDoGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class StaticWhileNode>> MakeStaticWhileGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class StaticForNode>> MakeStaticForGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class StaticForeachNode>> MakeStaticForeachGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class StaticIfNode>> MakeStaticIfGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class StaticSwitchNode>> MakeStaticSwitchGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class StaticSwitchAllNode>> MakeStaticSwitchAllGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class DoNode>> MakeDoGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class WhileNode>> MakeWhileGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class ForNode>> MakeForGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class ForeachNode>> MakeForeachGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class IfNode>> MakeIfGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class SwitchNode>> MakeSwitchGen() const = 0;
	virtual std::shared_ptr<INodeCodeGen<class SwitchAllNode>> MakeSwitchAllGen() const = 0;
};