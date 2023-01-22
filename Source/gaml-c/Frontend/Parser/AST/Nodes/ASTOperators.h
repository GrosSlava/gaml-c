// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "ASTNode.h"




DECLARE_NODE(OperandNode, 0);




/*
	Operand 0 - Body AST.
	Operand 1 - Condition expression (optional).
*/
DECLARE_NODE(StaticDoNode, 2);
#define STATIC_DO_NODE_BODY_OPERAND 0
#define STATIC_DO_NODE_CONDITION_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(StaticWhileNode, 2);
#define STATIC_WHILE_NODE_CONDITION_OPERAND 0
#define STATIC_WHILE_NODE_BODY_OPERAND 1

/*
	Operand 0 - Init body expression.
	Operand 1 - Condition expression.
	Operand 2 - Cycle end body expression.
	Operand 3 - Cycle body AST.
*/
DECLARE_NODE(StaticForNode, 4);
#define STATIC_FOR_NODE_INIT_BODY_OPERAND 0
#define STATIC_FOR_NODE_CONDITION_OPERAND 1
#define STATIC_FOR_NODE_END_BODY_OPERAND 2
#define STATIC_FOR_NODE_BODY_OPERAND 3

/*
	Operand 0 - Iterator expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(StaticForeachNode, 2);
#define STATIC_FOREACH_NODE_ITERATOR_OPERAND 0
#define STATIC_FOREACH_NODE_BODY_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - True body AST.
	Operand 2 - False body AST (optional).
*/
DECLARE_NODE(StaticIfNode, 3);
#define STATIC_IF_NODE_CONDITION_OPERAND 0
#define STATIC_IF_NODE_TRUE_BODY_OPERAND 1
#define STATIC_IF_NODE_FALSE_BODY_OPERAND 2

/*
	Operand 0 - Switch expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(StaticSwitchNode, 2);
#define STATIC_SWITCH_NODE_SWITCH_OPERAND 0
#define STATIC_SWITCH_NODE_BODY_OPERAND 1

/*
	Operand 0 - Switch expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(StaticSwitchAllNode, 2);
#define STATIC_SWITCH_ALL_NODE_SWITCH_OPERAND 0
#define STATIC_SWITCH_ALL_NODE_BODY_OPERAND 1

/*
	Operand 0 - Body AST.
	Operand 1 - Condition expression (optional).
*/
DECLARE_NODE(DoNode, 2);
#define DO_NODE_BODY_OPERAND 0
#define DO_NODE_CONDITION_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(WhileNode, 2);
#define WHILE_NODE_CONDITION_OPERAND 0
#define WHILE_NODE_BODY_OPERAND 1

/*
	Operand 0 - Init body expression.
	Operand 1 - Condition expression.
	Operand 2 - Cycle end body expression.
	Operand 3 - Cycle body AST.
*/
DECLARE_NODE(ForNode, 4);
#define FOR_NODE_INIT_BODY_OPERAND 0
#define FOR_NODE_CONDITION_OPERAND 1
#define FOR_NODE_END_BODY_OPERAND 2
#define FOR_NODE_BODY_OPERAND 3

/*
	Operand 0 - Iterator expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(ForeachNode, 2);
#define FOREACH_NODE_ITERATOR_OPERAND 0
#define FOREACH_NODE_BODY_OPERAND 1

/*
	Operand 0 - Condition expression.
	Operand 1 - True body AST.
	Operand 2 - False body AST (optional).
*/
DECLARE_NODE(IfNode, 3);
#define IF_NODE_CONDITION_OPERAND 0
#define IF_NODE_TRUE_BODY_OPERAND 1
#define IF_NODE_FALSE_BODY_OPERAND 2

/*
	Operand 0 - Switch expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(SwitchNode, 2);
#define SWITCH_NODE_SWITCH_OPERAND 0
#define SWITCH_NODE_BODY_OPERAND 1

/*
	Operand 0 - Switch expression.
	Operand 1 - Body AST.
*/
DECLARE_NODE(SwitchAllNode, 2);
#define SWITCH_ALL_NODE_SWITCH_OPERAND 0
#define SWITCH_ALL_NODE_BODY_OPERAND 1

/*
	Operand 0 - Arguments expression.
*/
DECLARE_NODE(AssertNode, 1);
#define ASSERT_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments expression.
*/
DECLARE_NODE(StaticAssertNode, 1);
#define STATIC_ASSERT_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments expression.
*/
DECLARE_NODE(StaticErrorNode, 1);
#define STATIC_ERROR_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments expression.
*/
DECLARE_NODE(StaticWarningNode, 1);
#define STATIC_WARNING_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments expression.
*/
DECLARE_NODE(StaticMessageNode, 1);
#define STATIC_MESSAGE_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Alias name.
	Operand 1 - Original type expression.
*/
DECLARE_NODE(UsingNode, 2);
#define USING_NODE_ALIAS_OPERAND 0
#define USING_NODE_ORIGINAL_TYPE_OPERAND 1

/*
	Operand 0 - Variable type expression.
	Operand 2 - Variable name.
	Operand 3 - Default value expression.
*/
DECLARE_NODE(VarNode, 3);
#define VAR_NODE_TYPE_OPERAND 0
#define VAR_NODE_NAME_TYPE_OPERAND 1
#define VAR_NODE_NAME_DEFAULR_VALUE_OPERAND 1

/*
*/
DECLARE_NODE(BreakNode, 0);

/*
*/
DECLARE_NODE(ContinueNode, 0);

/*
	Operand 0 - Return expression.
*/
DECLARE_NODE(ReturnNode, 1);
#define RETURN_NODE_RETURN_OPERAND 0




/*
	Operand 0 - Name to call.
	Operand 1 - Arguments expression.
*/
DECLARE_NODE(CallNode, 2);
#define CALL_NODE_NAME_OPERAND 0
#define CALL_NODE_ARGUMENTS_OPERAND 1

/*
	Operand 0 - Name to access.
	Operand 1 - Index expression.
*/
DECLARE_NODE(IndexAccessNode, 2);
#define INDEX_ACCESS_NODE_NAME_OPERAND 0
#define INDEX_ACCESS_NODE_INDEX_OPERAND 1

/*
	Operand 0 - Elements expression.
*/
DECLARE_NODE(RHArrayNode, 1);
#define RHARRAY_NODE_ELEMENTS_OPERAND 0

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(LessNode, 2);
#define LESS_NODE_LEFT_OPERAND 0
#define LESS_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(GreatherNode, 2);
#define GREATHER_NODE_LEFT_OPERAND 0
#define GREATHER_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(LessEqualNode, 2);
#define LESS_EQUAL_NODE_LEFT_OPERAND 0
#define LESS_EQUAL_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(GreatherEqualNode, 2);
#define GREATHER_EQUAL_NODE_LEFT_OPERAND 0
#define GREATHER_EQUAL_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(EqualNode, 2);
#define EQUAL_NODE_LEFT_OPERAND 0
#define EQUAL_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(NotEqualNode, 2);
#define NOT_EQUAL_NODE_LEFT_OPERAND 0
#define NOT_EQUAL_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(AndNode, 2);
#define AND_NODE_LEFT_OPERAND 0
#define AND_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(OrNode, 2);
#define OR_NODE_LEFT_OPERAND 0
#define OR_NODE_RIGHT_OPERAND 1

/*
	Operand 1 - Right expression.
*/
DECLARE_NODE(ExclimationNode, 1);
#define EXCLIMATION_NODE_RIGHT_OPERAND 0

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryAndNode, 2);
#define BINARY_AND_NODE_LEFT_OPERAND 0
#define BINARY_AND_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryOrNode, 2);
#define BINARY_OR_NODE_LEFT_OPERAND 0
#define BINARY_OR_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryInverseNode, 2);
#define BINARY_INVERSE_NODE_LEFT_OPERAND 0
#define BINARY_INVERSE_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryXorNode, 2);
#define BINARY_XOR_NODE_LEFT_OPERAND 0
#define BINARY_XOR_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryShlNode, 2);
#define BINARY_SHL_NODE_LEFT_OPERAND 0
#define BINARY_SHL_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryShrNode, 2);
#define BINARY_SHR_NODE_LEFT_OPERAND 0
#define BINARY_SHR_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(MultiplyNode, 2);
#define MULTIPLY_NODE_LEFT_OPERAND 0
#define MULTIPLY_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(DivideNode, 2);
#define DIVIDE_NODE_LEFT_OPERAND 0
#define DIVIDE_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
*/
DECLARE_NODE(IncNode, 1);
#define INC_NODE_LEFT_OPERAND 0

/*
	Operand 0 - Left expression.
*/
DECLARE_NODE(DecNode, 1);
#define DEC_NODE_LEFT_OPERAND 0

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(ModNode, 2);
#define MOD_NODE_LEFT_OPERAND 0
#define MOD_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(PowNode, 2);
#define POW_NODE_LEFT_OPERAND 0
#define POW_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(InNode, 2);
#define IN_NODE_LEFT_OPERAND 0
#define IN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(IsNode, 2);
#define IS_NODE_LEFT_OPERAND 0
#define IS_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(PlusNode, 2);
#define PLUS_NODE_LEFT_OPERAND 0
#define PLUS_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(MinusNode, 2);
#define MINUS_NODE_LEFT_OPERAND 0
#define MINUS_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Right expression.
*/
DECLARE_NODE(PositiveNode, 1);
#define POSITIVE_NODE_RIGHT_OPERAND 0

/*
	Operand 0 - Right expression.
*/
DECLARE_NODE(NegativeNode, 1);
#define NEGATIVE_NODE_RIGHT_OPERAND 0

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(NamespaceAccessNode, 2);
#define NAMESPACE_NODE_LEFT_OPERAND 0
#define NAMESPACE_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(RightArrowNode, 2);
#define RIGHT_ARROW_NODE_LEFT_OPERAND 0
#define RIGHT_ARROW_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(PointNode, 2);
#define POINT_NODE_LEFT_OPERAND 0
#define POINT_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(AssignNode, 2);
#define ASSIGN_NODE_LEFT_OPERAND 0
#define ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(AddAssignNode, 2);
#define ADD_ASSIGN_NODE_LEFT_OPERAND 0
#define ADD_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(SubAssignNode, 2);
#define SUB_ASSIGN_NODE_LEFT_OPERAND 0
#define SUB_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(MulAssignNode, 2);
#define MUL_ASSIGN_NODE_LEFT_OPERAND 0
#define MUL_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(DivAssignNode, 2);
#define DIV_ASSIGN_NODE_LEFT_OPERAND 0
#define DIV_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(ModAssignNode, 2);
#define MOD_ASSIGN_NODE_LEFT_OPERAND 0
#define MOD_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(PowAssignNode, 2);
#define POW_ASSIGN_NODE_LEFT_OPERAND 0
#define POW_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryAndAssignNode, 2);
#define BINARY_AND_ASSIGN_NODE_LEFT_OPERAND 0
#define BINARY_AND_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryOrAssignNode, 2);
#define BINARY_OR_ASSIGN_NODE_LEFT_OPERAND 0
#define BINARY_OR_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryInverseAssignNode, 2);
#define BINARY_INVERSE_ASSIGN_NODE_LEFT_OPERAND 0
#define BINARY_INVERSE_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryXorAssignNode, 2);
#define BINARY_XOR_ASSIGN_NODE_LEFT_OPERAND 0
#define BINARY_XOR_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryShlAssignNode, 2);
#define BINARY_SHL_ASSIGN_NODE_LEFT_OPERAND 0
#define BINARY_SHL_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Left expression.
	Operand 1 - Right expression.
*/
DECLARE_NODE(BinaryShrAssignNode, 2);
#define BINARY_SHR_ASSIGN_NODE_LEFT_OPERAND 0
#define BINARY_SHR_ASSIGN_NODE_RIGHT_OPERAND 1

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(SizeOfNode, 1);
#define SIZE_OF_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(TypeOfNode, 1);
#define TYPE_OF_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(NameOfNode, 1);
#define NAME_OF_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsFunctionNode, 1);
#define IS_FUNCTION_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsStructNode, 1);
#define IS_STRUCT_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsEnumNode, 1);
#define IS_ENUM_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsInterfaceNode, 1);
#define IS_INTERFACE_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsObjectNode, 1);
#define IS_OBJECT_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsComponentNode, 1);
#define IS_COMPONENT_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsSubclassNode, 1);
#define IS_SUBCLASS_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsInstanceNode, 1);
#define IS_INSTANCE_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsLambdaNode, 1);
#define IS_LAMBDA_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsIterableNode, 1);
#define IS_ITERABLE_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsEnumerableNode, 1);
#define IS_ENUMERABLE_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsAbstractNode, 1);
#define IS_ABSTRACT_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(IsAliasNode, 1);
#define IS_ALIAS_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(AddrNode, 1);
#define ADDR_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Arguments.
*/
DECLARE_NODE(DefaultNode, 1);
#define DEFAULT_NODE_ARGUMENTS_OPERAND 0

/*
	Operand 0 - Condition expression.
	Operand 1 - True expression.
	Operand 2 - False expression.
*/
DECLARE_NODE(TernaryIfNode, 3);
#define TERNARY_IF_NODE_CONDITION_OPERAND 0
#define TERNARY_IF_NODE_TRUE_OPERAND 1
#define TERNARY_IF_NODE_FALSE_OPERAND 2

/*
	Operand 0 - Cast to type expression.
	Operand 1 - Casted from expression.
*/
DECLARE_NODE(CastNode, 2);
#define CAST_NODE_TO_OPERAND 0
#define CAST_NODE_FROM_OPERAND 0

/*
	Operand 0 - Cast to type expression.
	Operand 1 - Casted from expression.
*/
DECLARE_NODE(UnsafeCastNode, 2);
#define UNSAFE_CAST_NODE_TO_OPERAND 0
#define UNSAFE_CAST_NODE_FROM_OPERAND 0