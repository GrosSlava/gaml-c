// Copyright 2022 GrosSlava.

#pragma once

#include "../Token/Token.h"

#include <vector>




class AST
{
public:

	inline AST() { }
	virtual ~AST() { }



public:

	void BuildAST(const std::vector<Token>& InTokens);



public:

	//TODO
};