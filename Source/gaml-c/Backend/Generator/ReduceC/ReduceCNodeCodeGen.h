// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "Parser/AST/ASTCodeGenFactory.h"




DECLARE_NODE_CODE_GEN(ScopeNodeGen, ScopeNode);

DECLARE_NODE_CODE_GEN(StaticDoNodeGen, StaticDoNode);
DECLARE_NODE_CODE_GEN(StaticWhileNodeGen, StaticWhileNode);
DECLARE_NODE_CODE_GEN(StaticForNodeGen, StaticForNode);
DECLARE_NODE_CODE_GEN(StaticForeachNodeGen, StaticForeachNode);
DECLARE_NODE_CODE_GEN(StaticIfNodeGen, StaticIfNode);
DECLARE_NODE_CODE_GEN(StaticSwitchNodeGen, StaticSwitchNode);
DECLARE_NODE_CODE_GEN(StaticSwitchAllNodeGen, StaticSwitchAllNode);
DECLARE_NODE_CODE_GEN(DoNodeGen, DoNode);
DECLARE_NODE_CODE_GEN(WhileNodeGen, WhileNode);
DECLARE_NODE_CODE_GEN(ForNodeGen, ForNode);
DECLARE_NODE_CODE_GEN(ForeachNodeGen, ForeachNode);
DECLARE_NODE_CODE_GEN(IfNodeGen, IfNode);
DECLARE_NODE_CODE_GEN(SwitchNodeGen, SwitchNode);
DECLARE_NODE_CODE_GEN(SwitchAllNodeGen, SwitchAllNode);



/*
	Concrete factory for nodes code generators.
*/
class ReduceC_ASTCodeGenFactory : public IASTCodeGenFactory
{
public:

	virtual std::shared_ptr<INodeCodeGen<ScopeNode>> MakeScopeGen() const override;

	virtual std::shared_ptr<INodeCodeGen<class StaticDoNode>> MakeStaticDoGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class StaticWhileNode>> MakeStaticWhileGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class StaticForNode>> MakeStaticForGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class StaticForeachNode>> MakeStaticForeachGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class StaticIfNode>> MakeStaticIfGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class StaticSwitchNode>> MakeStaticSwitchGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class StaticSwitchAllNode>> MakeStaticSwitchAllGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class DoNode>> MakeDoGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class WhileNode>> MakeWhileGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class ForNode>> MakeForGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class ForeachNode>> MakeForeachGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class IfNode>> MakeIfGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class SwitchNode>> MakeSwitchGen() const override;
	virtual std::shared_ptr<INodeCodeGen<class SwitchAllNode>> MakeSwitchAllGen() const override;
};
