// Copyright 2022 - 2023 GrosSlava.

#include "AST.h"

#include "Nodes/ScopeNode.h"





void AST::BuildAST(const std::vector<Token>& InTokens)
{
	if( InTokens.empty() )
	{
		return;
	}

	Token LToken(FGamlFileInfo(), "Root", 0, 0);
	MainScope = std::make_shared<ScopeNode>(LToken);
	MainScope->BuildAST(InTokens);
}


bool AST::IsPureExpression() const noexcept
{
	return MainScope != nullptr && MainScope->GetChildrenCount() == 1 && !MainScope->GetHasControlStatement();
}





std::string GetTreeAsStrHelper(std::shared_ptr<ASTNode> Node, const std::string& Indent)
{
	if( Node == nullptr )
	{
		return "";
	}

	std::string LResult = Indent + Node->GetNodeName() + "<" + Node->GetCTXToken().GetLexeme() + ">\n";

	for( int i = 0; i < Node->GetChildrenCount(); ++i )
	{
		LResult += GetTreeAsStrHelper(Node->GetChild(i), Indent + "\t");
	}

	return LResult;
}

std::string AST::GetTreeAsStr() const noexcept
{
	std::string LIndexnt = "";
	return GetTreeAsStrHelper(MainScope, LIndexnt);
}
