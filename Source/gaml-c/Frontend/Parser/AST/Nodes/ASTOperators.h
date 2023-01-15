// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "BaseOperatorNode.h"




/*
	Operand 0 - Body AST.
	Operand 1 - Condition expression (optional).
*/
DECLARE_OPERATOR_NODE(StaticDoNode, 2);
#define STATIC_DO_NODE_BODY_OPERAND 0
#define STATIC_DO_NODE_CONDITION_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - Body AST.
*/
DECLARE_OPERATOR_NODE(StaticWhileNode, 2);
#define STATIC_WHILE_NODE_CONDITION_OPERAND 0
#define STATIC_WHILE_NODE_BODY_OPERAND 1

/*
	Operand 0 - Init body expression.
	Operand 1 - Condition expression.
	Operand 2 - Cycle end body expression.
	Operand 3 - Cycle body AST.
*/
DECLARE_OPERATOR_NODE(StaticForNode, 4);
#define STATIC_FOR_NODE_INIT_BODY_OPERAND 0
#define STATIC_FOR_NODE_CONDITION_OPERAND 1
#define STATIC_FOR_NODE_END_BODY_OPERAND 2
#define STATIC_FOR_NODE_BODY_OPERAND 3

/*
	Operand 0 - Iterator expression.
	Operand 1 - Body AST.
*/
DECLARE_OPERATOR_NODE(StaticForeachNode, 2);
#define STATIC_FOREACH_NODE_ITERATOR_OPERAND 0
#define STATIC_FOREACH_NODE_BODY_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - True body AST.
	Operand 2 - False body AST (optional).
*/
DECLARE_OPERATOR_NODE(StaticIfNode, 3);
#define STATIC_IF_NODE_CONDITION_OPERAND 0
#define STATIC_IF_NODE_TRUE_BODY_OPERAND 1
#define STATIC_IF_NODE_FALSE_BODY_OPERAND 2

/*
	TODO
*/
DECLARE_OPERATOR_NODE(StaticSwitchNode, 2);
//TODO

/*
	TODO
*/
DECLARE_OPERATOR_NODE(StaticSwitchAllNode, 2);
//TODO

/*
	Operand 0 - Body AST.
	Operand 1 - Condition expression (optional).
*/
DECLARE_OPERATOR_NODE(DoNode, 2);
#define DO_NODE_BODY_OPERAND 0
#define DO_NODE_CONDITION_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - Body AST.
*/
DECLARE_OPERATOR_NODE(WhileNode, 2);
#define WHILE_NODE_CONDITION_OPERAND 0
#define WHILE_NODE_BODY_OPERAND 1

/*
	Operand 0 - Init body expression.
	Operand 1 - Condition expression.
	Operand 2 - Cycle end body expression.
	Operand 3 - Cycle body AST.
*/
DECLARE_OPERATOR_NODE(ForNode, 4);
#define FOR_NODE_INIT_BODY_OPERAND 0
#define FOR_NODE_CONDITION_OPERAND 1
#define FOR_NODE_END_BODY_OPERAND 2
#define FOR_NODE_BODY_OPERAND 3

/*
	Operand 0 - Iterator expression.
	Operand 1 - Body AST.
*/
DECLARE_OPERATOR_NODE(ForeachNode, 2);
#define FOREACH_NODE_ITERATOR_OPERAND 0
#define FOREACH_NODE_BODY_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - True body AST.
	Operand 2 - False body AST (optional).
*/
DECLARE_OPERATOR_NODE(IfNode, 3);
#define IF_NODE_CONDITION_OPERAND 0
#define IF_NODE_TRUE_BODY_OPERAND 1
#define IF_NODE_FALSE_BODY_OPERAND 2

/*
	TODO
*/
DECLARE_OPERATOR_NODE(SwitchNode, 2);
//TODO

/*
	TODO
*/
DECLARE_OPERATOR_NODE(SwitchAllNode, 2);
//TODO




/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_EXPESSION_OPERATOR_NODE(LessNode, 2);
#define LESS_NODE_LEFT_OPERAND 0
#define LESS_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_EXPESSION_OPERATOR_NODE(GreatherNode, 2);
#define GREATHER_NODE_LEFT_OPERAND 0
#define GREATHER_NODE_RIGHT_OPERAND 1