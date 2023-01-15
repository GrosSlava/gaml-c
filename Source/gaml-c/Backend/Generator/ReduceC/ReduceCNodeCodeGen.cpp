// Copyright 2022 - 2023 GrosSlava.

#include "ReduceCNodeCodeGen.h"





std::shared_ptr<INodeCodeGen<ScopeNode>> ReduceC_ASTCodeGenFactory::MakeScopeGen() const
{
	return std::make_shared<ScopeNodeGen>();
}

std::shared_ptr<INodeCodeGen<class StaticDoNode>> ReduceC_ASTCodeGenFactory::MakeStaticDoGen() const
{
	return std::make_shared<StaticDoNodeGen>();
}

std::shared_ptr<INodeCodeGen<class StaticWhileNode>> ReduceC_ASTCodeGenFactory::MakeStaticWhileGen() const
{
	return std::make_shared<StaticWhileNodeGen>();
}

std::shared_ptr<INodeCodeGen<class StaticForNode>> ReduceC_ASTCodeGenFactory::MakeStaticForGen() const
{
	return std::make_shared<StaticForNodeGen>();
}

std::shared_ptr<INodeCodeGen<class StaticForeachNode>> ReduceC_ASTCodeGenFactory::MakeStaticForeachGen() const
{
	return std::make_shared<StaticForeachNodeGen>();
}

std::shared_ptr<INodeCodeGen<class StaticIfNode>> ReduceC_ASTCodeGenFactory::MakeStaticIfGen() const
{
	return std::make_shared<StaticIfNodeGen>();
}

std::shared_ptr<INodeCodeGen<class StaticSwitchNode>> ReduceC_ASTCodeGenFactory::MakeStaticSwitchGen() const
{
	return std::make_shared<StaticSwitchNodeGen>();
}

std::shared_ptr<INodeCodeGen<class StaticSwitchAllNode>> ReduceC_ASTCodeGenFactory::MakeStaticSwitchAllGen() const
{
	return std::make_shared<StaticSwitchAllNodeGen>();
}

std::shared_ptr<INodeCodeGen<class DoNode>> ReduceC_ASTCodeGenFactory::MakeDoGen() const
{
	return std::make_shared<DoNodeGen>();
}

std::shared_ptr<INodeCodeGen<class WhileNode>> ReduceC_ASTCodeGenFactory::MakeWhileGen() const
{
	return std::make_shared<WhileNodeGen>();
}

std::shared_ptr<INodeCodeGen<class ForNode>> ReduceC_ASTCodeGenFactory::MakeForGen() const
{
	return std::make_shared<ForNodeGen>();
}

std::shared_ptr<INodeCodeGen<class ForeachNode>> ReduceC_ASTCodeGenFactory::MakeForeachGen() const
{
	return std::make_shared<ForeachNodeGen>();
}

std::shared_ptr<INodeCodeGen<class IfNode>> ReduceC_ASTCodeGenFactory::MakeIfGen() const
{
	return std::make_shared<IfNodeGen>();
}

std::shared_ptr<INodeCodeGen<class SwitchNode>> ReduceC_ASTCodeGenFactory::MakeSwitchGen() const
{
	return std::make_shared<SwitchNodeGen>();
}

std::shared_ptr<INodeCodeGen<class SwitchAllNode>> ReduceC_ASTCodeGenFactory::MakeSwitchAllGen() const
{
	return std::make_shared<SwitchAllNodeGen>();
}
