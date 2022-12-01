// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Token/Token.h"




struct FProgramInfo;




/*
	Abstract syntax tree.
*/
class AST
{
public:

	inline AST() { }
	virtual ~AST() { }



public:

	void BuildAST(const std::vector<Token>& InTokens);
	void InterpretAST(const FProgramInfo& OutProgramInfo);

	bool GetInterpretResultAsBool() const;
	int GetInterpretResultAsInt() const;
	double GetInterpretResultAsDouble() const;
	std::string GetInterpretResultAsString() const;




public:

	//TODO
};