// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../../../CoreMinimal.h"




class IASTCodeGenFactory;

struct FProgramInfo;
struct FASTSymbols;



/*
	Interface for all AST nodes.
*/
class IASTNode
{
public:

	inline IASTNode() { }
	virtual ~IASTNode() { }



public:

	/*
		Recursive interpret AST.
	*/
	virtual void InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo) = 0;
	virtual bool GetInterpretResultAsBool() const = 0;
	virtual int GetInterpretResultAsInt() const = 0;
	virtual double GetInterpretResultAsDouble() const = 0;
	virtual std::string GetInterpretResultAsString() const = 0;


	/*
		Recursive generate code based on AST.
		Analyzer already check all names and errors.
		Code interpretation not needed.
	*/
	virtual std::string GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const = 0;
};
