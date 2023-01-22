// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "Token/Token.h"




/*
	Base class for all AST nodes.
*/
class ASTNode
{
public:

	ASTNode() = delete;
	inline ASTNode(const Token& InToken, int MaxChildrenCoint) : Children(MaxChildrenCoint, nullptr), ContextToken(InToken) { }
	virtual ~ASTNode() { }



public:

	/*
		@return cached context token.
	*/
	inline const Token& GetCTXToken() const noexcept { return ContextToken; }
	/*
		@return count of node children.
	*/
	inline size_t GetChildrenCount() const noexcept { return Children.size(); }

	/*
		@return operand at index, invalid index returns nullptr.
	*/
	inline std::shared_ptr<ASTNode> GetChild(int Index) const noexcept
	{
		if( Index < 0 || Index >= Children.size() ) return nullptr;

		return Children[Index];
	}
	/*
		Set operand at index.
		Invalid index cause compilation error.
	*/
	void SetChild(int Index, std::shared_ptr<ASTNode> Child);

public:

	/*
		Assign left or/and right subtrees.
	*/
	virtual void AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight) = 0;

	/*
		Get node name as single string.
	*/
	virtual std::string GetNodeName() const noexcept = 0;




protected:

	/*
		AST node children.
	*/
	std::vector<std::shared_ptr<ASTNode>> Children;

	/*
		Context operator token.
	*/
	Token ContextToken;
};



#define DECLARE_NODE(Name, ChildrenCount)                                                                                                      \
	class Name final : public ASTNode                                                                                                          \
	{                                                                                                                                          \
	public:                                                                                                                                    \
                                                                                                                                               \
		inline Name(const Token& InToken) : ASTNode(InToken, ChildrenCount)                                                                    \
		{                                                                                                                                      \
		}                                                                                                                                      \
                                                                                                                                               \
	public:                                                                                                                                    \
                                                                                                                                               \
		virtual void AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight) override; \
		virtual std::string GetNodeName() const noexcept override                                                                              \
		{                                                                                                                                      \
			return #Name;                                                                                                                       \
		}                                                                                                                                      \
	};
