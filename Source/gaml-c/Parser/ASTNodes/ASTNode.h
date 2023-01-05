// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../CoreMinimal.h"

#include "ASTCodeGenFactory.h"

#include "../../Token/Token.h"




struct FProgramInfo;


/*
	Interface for all AST nodes.
*/
class IASTNode
{
public:

	IASTNode() { }
	virtual ~IASTNode() { }



public:

	virtual void BuildAST(const std::vector<Token>& InTokens, size_t Index) = 0;
	virtual void InterpretAST(const FProgramInfo& ProgramInfo) = 0;
	virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const = 0;

	virtual bool GetInterpretResultAsBool() const = 0;
	virtual int GetInterpretResultAsInt() const = 0;
	virtual double GetInterpretResultAsDouble() const = 0;
	virtual std::string GetInterpretResultAsString() const = 0;
};




/*
	Base class for unary expression.
*/
class UnaryNode : public IASTNode
{
public:

	UnaryNode() = delete;
	UnaryNode(std::shared_ptr<IASTNode> InExpr) : Expr(InExpr) { }



public:

	/*
		AST for operator expression.
	*/
	std::shared_ptr<IASTNode> Expr;
};

/*
	Base class for binary expression.
*/
class BinaryNode : public IASTNode
{
public:

	BinaryNode() = delete;
	BinaryNode(std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs) : Left(Lhs), Right(Rhs) { }



public:

	/*
		AST left from operator.
	*/
	std::shared_ptr<IASTNode> Left;
	/*
		AST right from operator.
	*/
	std::shared_ptr<IASTNode> Right;
};

/*
	Base class for ternary expression.
*/
class TernaryNode : public IASTNode
{
public:

	TernaryNode() = delete;
	TernaryNode(std::shared_ptr<IASTNode> InExpr, std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs) : Expr(InExpr), Left(Lhs), Right(Rhs) { }



public:

	/*
		AST for operator expression.
	*/
	std::shared_ptr<IASTNode> Expr;
	/*
		AST left from operator.
	*/
	std::shared_ptr<IASTNode> Left;
	/*
		AST right from operator.
	*/
	std::shared_ptr<IASTNode> Right;
};

/*
	Base class for quaternary expression.
*/
class QuaternaryNode : public IASTNode
{
public:

	QuaternaryNode() = delete;
	QuaternaryNode(std::shared_ptr<IASTNode> InInit, std::shared_ptr<IASTNode> InExpr, std::shared_ptr<IASTNode> Lhs, std::shared_ptr<IASTNode> Rhs) :
		Init(InInit), Expr(InExpr), Left(Lhs), Right(Rhs)
	{
	}



public:

	/*
		AST for operator init expression.
	*/
	std::shared_ptr<IASTNode> Init;
	/*
		AST for operator expression.
	*/
	std::shared_ptr<IASTNode> Expr;
	/*
		AST left from operator.
	*/
	std::shared_ptr<IASTNode> Left;
	/*
		AST right from operator.
	*/
	std::shared_ptr<IASTNode> Right;
};

/*
	Base class for AST expressions sequence.
*/
class SequenceNode : public IASTNode
{
public:

	SequenceNode() { }



public:

	/*
		Array of AST expressions in order to be compiled or interpreted.
	*/
	std::vector<std::shared_ptr<IASTNode>> ExprSequence;
};

/*
	Base class for leaf AST node.
*/
class LeafNode : public IASTNode
{
public:

	LeafNode() = delete;
	LeafNode(const Token& InToken) : LeafToken(InToken) { }



public:

	virtual void BuildAST(const std::vector<Token>& InTokens, size_t Index) final override {};




public:

	/*
		Info about leaf token.
	*/
	Token LeafToken;
};
