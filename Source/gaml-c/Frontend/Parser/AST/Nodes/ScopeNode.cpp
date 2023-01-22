// Copyright 2022 - 2023 GrosSlava.

#include "ScopeNode.h"

#include "ASTOperators.h"

#include "Parser/ParserHelperLibrary.h"
#include "Logger/ErrorLogger.h"





void ScopeNode::BuildAST(const std::vector<Token>& InTokens)
{
	size_t LIndex = 0;
	while( LIndex < InTokens.size() )
	{
		switch( InTokens[LIndex].GetType() )
		{
		case ETokenType::SEMICOLON:
		{
			++LIndex;
			continue;
		}
		case ETokenType::STATIC:
		{
			if( LIndex + 1 >= InTokens.size() )
			{
				FErrorLogger::Raise(EErrorMessageType::EXPECTED_CONTROL_OPERATOR, InTokens[LIndex]);
				return;
			}
			++LIndex;

			switch( InTokens[LIndex].GetType() )
			{
			case ETokenType::DO:
			{
				HasControlStatement = true;
				Children.push_back(Parse_StaticDo(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::WHILE:
			{
				HasControlStatement = true;
				Children.push_back(Parse_StaticWhile(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::FOR:
			{
				HasControlStatement = true;
				Children.push_back(Parse_StaticFor(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::FOREACH:
			{
				HasControlStatement = true;
				Children.push_back(Parse_StaticForeach(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::IF:
			{
				HasControlStatement = true;
				Children.push_back(Parse_StaticIf(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::SWITCH:
			{
				HasControlStatement = true;
				Children.push_back(Parse_StaticSwitch(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::SWITCH_ALL:
			{
				HasControlStatement = true;
				Children.push_back(Parse_StaticSwitchAll(InTokens, LIndex));

				++LIndex;
				continue;
			}
			}

			FErrorLogger::Raise(EErrorMessageType::EXPECTED_CONTROL_OPERATOR, InTokens[LIndex]);
			return;
		}
		case ETokenType::DO:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Do(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::WHILE:
		{
			HasControlStatement = true;
			Children.push_back(Parse_While(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::FOR:
		{
			HasControlStatement = true;
			Children.push_back(Parse_For(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::FOREACH:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Foreach(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::IF:
		{
			HasControlStatement = true;
			Children.push_back(Parse_If(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::SWITCH:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Switch(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::SWITCH_ALL:
		{
			HasControlStatement = true;
			Children.push_back(Parse_SwitchAll(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::ASSERT:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Assert(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_ASSERT:
		{
			HasControlStatement = true;
			Children.push_back(Parse_StaticAssert(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_ERROR:
		{
			HasControlStatement = true;
			Children.push_back(Parse_StaticError(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_WARNING:
		{
			HasControlStatement = true;
			Children.push_back(Parse_StaticWarning(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_MESSAGE:
		{
			HasControlStatement = true;
			Children.push_back(Parse_StaticMessage(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::USING:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Using(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::VAR:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Var(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::BREAK:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Break(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::CONTINUE:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Continue(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::RETURN:
		{
			HasControlStatement = true;
			Children.push_back(Parse_Return(InTokens, LIndex));

			++LIndex;
			continue;
		}
		default:
		{
			size_t LExpressionEndIndex = LIndex + 1;
			while( LExpressionEndIndex < InTokens.size() && InTokens[LExpressionEndIndex].GetType() != ETokenType::SEMICOLON )
			{
				++LExpressionEndIndex;
			}

			Children.push_back(ParseExpr(std::vector<Token>(InTokens.begin() + LIndex, InTokens.begin() + LExpressionEndIndex)));

			LIndex = LExpressionEndIndex + 1;
			continue;
		}
		}
	}
}

void ScopeNode::AssignSubTrees(std::shared_ptr<ASTNode> Lhs, std::shared_ptr<ASTNode> Rhs, bool& OutUseLeft, bool& OutUseRight)
{
	OutUseLeft = false;
	OutUseRight = false;

	FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
}





class UExprParseListNode
{
public:

	std::shared_ptr<ASTNode> ASTPart;

	std::shared_ptr<UExprParseListNode> Left;
	std::shared_ptr<UExprParseListNode> Right;
};

struct FExprParseList
{
public:

	void AddASTNode(std::shared_ptr<ASTNode> ASTNode)
	{
		if( Head == nullptr )
		{
			Head = std::make_shared<UExprParseListNode>();
			Head->ASTPart = ASTNode;
			Tail = Head;
		}
		else
		{
			std::shared_ptr<UExprParseListNode> LNewNode = std::make_shared<UExprParseListNode>();
			LNewNode->ASTPart = ASTNode;
			LNewNode->Left = Tail;

			Tail->Right = LNewNode;
			Tail = LNewNode;
		}
	}

	void RemoveLeftFor(std::shared_ptr<UExprParseListNode> ExprParseListNode)
	{
		std::shared_ptr<UExprParseListNode> LLeftListNode = ExprParseListNode->Left;
		if( !LLeftListNode )
		{
			return;
		}

		if( std::shared_ptr<UExprParseListNode> LLeftLeftOperandListNode = LLeftListNode->Left )
		{
			LLeftLeftOperandListNode->Right = ExprParseListNode;
		}
		else
		{
			Head = ExprParseListNode;
		}

		ExprParseListNode->Left = LLeftListNode->Left;
	}

	void RemoveRightFor(std::shared_ptr<UExprParseListNode> ExprParseListNode)
	{
		std::shared_ptr<UExprParseListNode> LRightListNode = ExprParseListNode->Right;
		if( !LRightListNode )
		{
			return;
		}

		if( std::shared_ptr<UExprParseListNode> LRightRightOperandListNode = LRightListNode->Right )
		{
			LRightRightOperandListNode->Left = ExprParseListNode;
		}
		else
		{
			Tail = ExprParseListNode;
		}

		ExprParseListNode->Right = LRightListNode->Right;
	}

public:

	std::shared_ptr<UExprParseListNode> Head;
	std::shared_ptr<UExprParseListNode> Tail;
};

std::shared_ptr<ASTNode> ScopeNode::ParseExpr(const std::vector<Token>& InTokens) const
{
	if( InTokens.empty() )
	{
		return nullptr;
	}

	// List for converting given tokens into unrelated AST nodes
	FExprParseList LASTParts;

	// Array of array of operators AST nodes indexes.
	// First index - index of priority (reserve 32 that is more than we have)
	// Second index - pointer to AST operator node in LASTParts in order from left to right
	std::vector<std::vector<std::shared_ptr<UExprParseListNode>>> OperatorsPrioritySort(32);

	// convert tokens to ASTParts and fill OperatorsPrioritySort
	size_t LIndex = 0;
	while( LIndex < InTokens.size() )
	{
		switch( InTokens[LIndex].GetType() )
		{
			//.....................................Operands........................................//

		case ETokenType::IDENTIFIER:
		{
			if( LIndex + 1 < InTokens.size() )
			{
				switch( InTokens[LIndex + 1].GetType() )
				{
				case ETokenType::LPAR:
				{
					LASTParts.AddASTNode(Parse_Call(InTokens, LIndex));

					++LIndex;
					continue;
				}
				case ETokenType::LSQR:
				{
					LASTParts.AddASTNode(Parse_IndexAccess(InTokens, LIndex));

					++LIndex;
					continue;
				}
				}
			}

			std::shared_ptr<ASTNode> LLeafNode = std::make_shared<OperandNode>(InTokens[LIndex]);
			LASTParts.AddASTNode(LLeafNode);

			++LIndex;
			continue;
		}
		case ETokenType::UINT8:
		case ETokenType::UINT16:
		case ETokenType::UINT32:
		case ETokenType::UINT64:
		case ETokenType::INT8:
		case ETokenType::INT16:
		case ETokenType::INT32:
		case ETokenType::INT64:
		case ETokenType::ADDR_T:
		case ETokenType::FLOAT:
		case ETokenType::DOUBLE:
		case ETokenType::BOOL:
		case ETokenType::CHAR:
		case ETokenType::STRING:
		case ETokenType::VECTOR4D:
		case ETokenType::VECTOR3D:
		case ETokenType::VECTOR2D:
		{
			if( LIndex + 1 < InTokens.size() )
			{
				switch( InTokens[LIndex + 1].GetType() )
				{
				case ETokenType::LPAR:
				{
					LASTParts.AddASTNode(Parse_Call(InTokens, LIndex));

					++LIndex;
					continue;
				}
				}
			}

			std::shared_ptr<ASTNode> LLeafNode = std::make_shared<OperandNode>(InTokens[LIndex]);
			LASTParts.AddASTNode(LLeafNode);

			++LIndex;
			continue;
		}
		case ETokenType::CLASS:
		{
			LASTParts.AddASTNode(Parse_Class(InTokens, LIndex));
			++LIndex;
			continue;
		}
		case ETokenType::ARRAY:
		{
			LASTParts.AddASTNode(Parse_Array(InTokens, LIndex));
			++LIndex;
			continue;
		}
		case ETokenType::LAMBDA:
		{
			LASTParts.AddASTNode(Parse_Lambda(InTokens, LIndex));
			++LIndex;
			continue;
		}
		case ETokenType::INTEGER_CONST:
		case ETokenType::FLOAT_CONST:
		case ETokenType::DOUBLE_CONST:
		case ETokenType::CHAR_CONST:
		case ETokenType::STRING_CONST:
		case ETokenType::TRUE_CONST:
		case ETokenType::FALSE_CONST:
		case ETokenType::THIS:
		case ETokenType::SUPER:
		case ETokenType::NONE:
		{
			std::shared_ptr<ASTNode> LLeafNode = std::make_shared<OperandNode>(InTokens[LIndex]);
			LASTParts.AddASTNode(LLeafNode);

			++LIndex;
			continue;
		}
		case ETokenType::LPAR:
		{
			const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, LIndex + 1, InTokens);
			if( LParEnd == InTokens.size() )
			{
				FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[LIndex]);
				return nullptr;
			}

			if( LParEnd > LIndex + 1 )
			{
				std::shared_ptr<ASTNode> LExpr = ParseExpr(std::vector<Token>(InTokens.begin() + LIndex + 1, InTokens.begin() + LParEnd - 1));
				LASTParts.AddASTNode(LExpr);
			}

			LIndex = LParEnd + 1;
			continue;
		}
		case ETokenType::LSQR:
		{
			const size_t LSqrEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LSQR, LIndex + 1, InTokens);
			if( LSqrEnd == InTokens.size() )
			{
				FErrorLogger::Raise(EErrorMessageType::EXPECTED_RSQR, InTokens[LIndex]);
				return nullptr;
			}

			std::shared_ptr<RHArrayNode> LRHArrayNode = std::make_shared<RHArrayNode>(InTokens[LIndex]);

			if( LSqrEnd > LIndex + 1 )
			{
				std::shared_ptr<ASTNode> LExpr = ParseExpr(std::vector<Token>(InTokens.begin() + LIndex + 1, InTokens.begin() + LSqrEnd - 1));
				LRHArrayNode->SetChild(RHARRAY_NODE_ELEMENTS_OPERAND, LExpr);
			}

			LASTParts.AddASTNode(LRHArrayNode);

			LIndex = LSqrEnd + 1;
			continue;
		}

		//.....................................................................................//


		//...........................Unary/binary operators....................................//

#define CASE_OPERATOR(TokenName, ClassName)                                                                \
	case ETokenType::TokenName:                                                                            \
	{                                                                                                      \
		std::shared_ptr<ClassName> LASTNode = std::make_shared<ClassName>(InTokens[LIndex]);               \
		LASTParts.AddASTNode(LASTNode);                                                                    \
                                                                                                           \
		const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex], false); \
		if( LOperatorPriority == -1 )                                                                      \
		{                                                                                                  \
			FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);                       \
			return nullptr;                                                                                \
		}                                                                                                  \
		OperatorsPrioritySort[LOperatorPriority].push_back(LASTParts.Tail);                                \
                                                                                                           \
		++LIndex;                                                                                          \
		continue;                                                                                          \
	}
			// clang-format off
		CASE_OPERATOR(LESS, LessNode)
		CASE_OPERATOR(GREATER, GreatherNode)
		CASE_OPERATOR(LESS_EQUAL, LessEqualNode)
		CASE_OPERATOR(GREATER_EQUAL, GreatherEqualNode)
		CASE_OPERATOR(EQUAL, EqualNode)
		CASE_OPERATOR(NOT_EQUAL, NotEqualNode)
		CASE_OPERATOR(AND, AndNode)
		CASE_OPERATOR(OR, OrNode)
		CASE_OPERATOR(EXCLAMATION, ExclimationNode)
		CASE_OPERATOR(BINARY_AND, BinaryAndNode)
		CASE_OPERATOR(BINARY_OR, BinaryOrNode)
		CASE_OPERATOR(BINARY_INVERSE, BinaryInverseNode)
		CASE_OPERATOR(BINARY_XOR, BinaryXorNode)
		CASE_OPERATOR(BINARY_SHL, BinaryShlNode)
		CASE_OPERATOR(BINARY_SHR, BinaryShrNode)
		CASE_OPERATOR(STAR, MultiplyNode)
		CASE_OPERATOR(SLASH, DivideNode)
		CASE_OPERATOR(INC, IncNode)
		CASE_OPERATOR(DEC, DecNode)
		CASE_OPERATOR(MOD, ModNode)
		CASE_OPERATOR(POW, PowNode)
		CASE_OPERATOR(IN, InNode)
		CASE_OPERATOR(IS, IsNode)
			// clang-format on
		case ETokenType::PLUS:
		{
			if( LIndex == 0 || FParserHelperLibrary::IsOperatorToken(InTokens[LIndex - 1]) )
			{
				std::shared_ptr<PositiveNode> LASTNode = std::make_shared<PositiveNode>(InTokens[LIndex]);
				LASTParts.AddASTNode(LASTNode);

				const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex], true);
				if( LOperatorPriority == -1 )
				{
					FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);
					return nullptr;
				}
				OperatorsPrioritySort[LOperatorPriority].push_back(LASTParts.Tail);

				++LIndex;
				continue;
			}
			else
			{
				std::shared_ptr<PlusNode> LASTNode = std::make_shared<PlusNode>(InTokens[LIndex]);
				LASTParts.AddASTNode(LASTNode);

				const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex], false);
				if( LOperatorPriority == -1 )
				{
					FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);
					return nullptr;
				}
				OperatorsPrioritySort[LOperatorPriority].push_back(LASTParts.Tail);

				++LIndex;
				continue;
			}
		}
		case ETokenType::MINUS:
		{
			if( LIndex == 0 || FParserHelperLibrary::IsOperatorToken(InTokens[LIndex - 1]) )
			{
				std::shared_ptr<NegativeNode> LASTNode = std::make_shared<NegativeNode>(InTokens[LIndex]);
				LASTParts.AddASTNode(LASTNode);

				const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex], true);
				if( LOperatorPriority == -1 )
				{
					FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);
					return nullptr;
				}
				OperatorsPrioritySort[LOperatorPriority].push_back(LASTParts.Tail);

				++LIndex;
				continue;
			}
			else
			{
				std::shared_ptr<MinusNode> LASTNode = std::make_shared<MinusNode>(InTokens[LIndex]);
				LASTParts.AddASTNode(LASTNode);

				const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex], false);
				if( LOperatorPriority == -1 )
				{
					FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);
					return nullptr;
				}
				OperatorsPrioritySort[LOperatorPriority].push_back(LASTParts.Tail);

				++LIndex;
				continue;
			}
		}
			// clang-format off
		CASE_OPERATOR(NAMESPACE_ACCESS_OPERATOR, NamespaceAccessNode)
		CASE_OPERATOR(RIGHT_ARROW, RightArrowNode)
		CASE_OPERATOR(POINT, PointNode)
		CASE_OPERATOR(ASSIGN, AssignNode)
		CASE_OPERATOR(ADD_ASSIGN, AddAssignNode)
		CASE_OPERATOR(SUB_ASSIGN, SubAssignNode)
		CASE_OPERATOR(MUL_ASSIGN, MulAssignNode)
		CASE_OPERATOR(DIV_ASSIGN, DivAssignNode)
		CASE_OPERATOR(MOD_ASSIGN, ModAssignNode)
		CASE_OPERATOR(POW_ASSIGN, PowAssignNode)
		CASE_OPERATOR(BINARY_AND_ASSIGN, BinaryAndAssignNode)
		CASE_OPERATOR(BINARY_OR_ASSIGN, BinaryOrAssignNode)
		CASE_OPERATOR(BINARY_INVERSE_ASSIGN, BinaryInverseAssignNode)
		CASE_OPERATOR(BINARY_XOR_ASSIGN, BinaryXorAssignNode)
		CASE_OPERATOR(BINARY_SHL_ASSIGN, BinaryShlAssignNode)
		CASE_OPERATOR(BINARY_SHR_ASSIGN, BinaryShrAssignNode)
			// clang-format on

#undef CASE_OPERATOR

			//.....................................................................................//


			//............Keyword operators with operands in pairs.................................//

#define CASE_KEYWORD_OPERATOR(TokenName, ClassName)                                                                                    \
	case ETokenType::TokenName:                                                                                                        \
	{                                                                                                                                  \
		const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex], false);                             \
		if( LOperatorPriority == -1 )                                                                                                  \
		{                                                                                                                              \
			FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);                                                   \
			return nullptr;                                                                                                            \
		}                                                                                                                              \
                                                                                                                                       \
		std::shared_ptr<ClassName> LASTNode = std::make_shared<ClassName>(InTokens[LIndex]);                                           \
		if( LIndex + 1 >= InTokens.size() )                                                                                            \
		{                                                                                                                              \
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[LIndex]);                                                   \
			return nullptr;                                                                                                            \
		}                                                                                                                              \
		++LIndex;                                                                                                                      \
		if( InTokens[LIndex].GetType() != ETokenType::LPAR )                                                                           \
		{                                                                                                                              \
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[LIndex]);                                                   \
			return nullptr;                                                                                                            \
		}                                                                                                                              \
                                                                                                                                       \
		const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, LIndex + 1, InTokens);                    \
		if( LParEnd == InTokens.size() )                                                                                               \
		{                                                                                                                              \
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[LIndex]);                                                   \
			return nullptr;                                                                                                            \
		}                                                                                                                              \
                                                                                                                                       \
		if( LParEnd > LIndex + 1 )                                                                                                     \
		{                                                                                                                              \
			std::shared_ptr<ASTNode> LExpr = ParseExpr(std::vector<Token>(InTokens.begin() + LIndex + 1, InTokens.begin() + LParEnd)); \
			LASTNode->SetChild(0, LExpr);                                                                                              \
		}                                                                                                                              \
                                                                                                                                       \
		LASTParts.AddASTNode(LASTNode);                                                                                                \
		/* not add to operators priority sort because it already has an operand */                                                     \
                                                                                                                                       \
		LIndex = LParEnd + 1;                                                                                                          \
		continue;                                                                                                                      \
	}
			// clang-format off
		CASE_KEYWORD_OPERATOR(SIZE_OF, SizeOfNode)
		CASE_KEYWORD_OPERATOR(TYPE_OF, TypeOfNode)
		CASE_KEYWORD_OPERATOR(NAME_OF, NameOfNode)
		CASE_KEYWORD_OPERATOR(IS_FUNCTION, IsFunctionNode)
		CASE_KEYWORD_OPERATOR(IS_STRUCT, IsStructNode)
		CASE_KEYWORD_OPERATOR(IS_ENUM, IsEnumNode)
		CASE_KEYWORD_OPERATOR(IS_INTERFACE, IsInterfaceNode)
		CASE_KEYWORD_OPERATOR(IS_OBJECT, IsObjectNode)
		CASE_KEYWORD_OPERATOR(IS_COMPONENT, IsComponentNode)
		CASE_KEYWORD_OPERATOR(IS_SUBCLASS, IsSubclassNode)
		CASE_KEYWORD_OPERATOR(IS_INSTANCE, IsInstanceNode)
		CASE_KEYWORD_OPERATOR(IS_LAMBDA, IsLambdaNode)
		CASE_KEYWORD_OPERATOR(IS_ITERABLE, IsIterableNode)
		CASE_KEYWORD_OPERATOR(IS_ENUMERABLE, IsEnumerableNode)
		CASE_KEYWORD_OPERATOR(IS_ABSTRACT, IsAbstractNode)
		CASE_KEYWORD_OPERATOR(IS_ALIAS, IsAliasNode)
		CASE_KEYWORD_OPERATOR(ADDR, AddrNode)
		CASE_KEYWORD_OPERATOR(DEFAULT, DefaultNode)
			// clang-format on

#undef CASE_KEYWORD_OPERATOR

			//.....................................................................................//


			//.......................Special format keyword operators..............................//

		case ETokenType::QUESTION:
		{
			LASTParts.AddASTNode(Parse_Thernal(InTokens, LIndex));
			++LIndex;
			continue;
		}
		case ETokenType::CAST:
		{
			LASTParts.AddASTNode(Parse_Cast(InTokens, LIndex));
			++LIndex;
			continue;
		}
		case ETokenType::UNSAFE_CAST:
		{
			LASTParts.AddASTNode(Parse_UnsafeCast(InTokens, LIndex));
			++LIndex;
			continue;
		}

			//.....................................................................................//
		}

		FErrorLogger::Raise(EErrorMessageType::UNEXPECTED_EXPRESSION, InTokens[LIndex]);
		return nullptr;
	}

	// link nodes
	for( long long int i = OperatorsPrioritySort.size() - 1; i >= 0; --i )
	{
		for( std::shared_ptr<UExprParseListNode> LExprParseListNode : OperatorsPrioritySort[i] )
		{
			if( LExprParseListNode->ASTPart )
			{
				std::shared_ptr<ASTNode> LLeftOperand = nullptr;
				std::shared_ptr<ASTNode> LRightOperand = nullptr;

				if( std::shared_ptr<UExprParseListNode> LLeftOperandListNode = LExprParseListNode->Left )
				{
					LLeftOperand = LLeftOperandListNode->ASTPart;
				}
				if( std::shared_ptr<UExprParseListNode> LRightOperandListNode = LExprParseListNode->Right )
				{
					LRightOperand = LRightOperandListNode->ASTPart;
				}

				bool LUsedLeft = false;
				bool LUsedRight = false;
				LExprParseListNode->ASTPart->AssignSubTrees(LLeftOperand, LRightOperand, LUsedLeft, LUsedRight);

				if( LUsedLeft )
				{
					LASTParts.RemoveLeftFor(LExprParseListNode);
				}
				if( LUsedRight )
				{
					LASTParts.RemoveRightFor(LExprParseListNode);
				}
			}
			else
			{
				FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[0]);
				return nullptr;
			}
		}
	}

	if( LASTParts.Head == nullptr || LASTParts.Head->Left != nullptr || LASTParts.Head->Right != nullptr )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_SEMICOLON, InTokens[0]);
		return nullptr;
	}
	return LASTParts.Head->ASTPart;
}





std::shared_ptr<ASTNode> ScopeNode::Parse_Scope(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
		return nullptr;
	}

	const size_t LBraScopeEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LBRA, Index + 1, InTokens);
	if( LBraScopeEnd == InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_RBRA, InTokens[Index]);
		return nullptr;
	}

	std::shared_ptr<ScopeNode> LScopeNode = std::make_shared<ScopeNode>(InTokens[Index]);
	if( LBraScopeEnd > Index + 1 )
	{
		LScopeNode->BuildAST(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LBraScopeEnd));
	}

	Index = LBraScopeEnd;
	return LScopeNode;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticDo(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::DO )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
		return nullptr;
	}
	std::shared_ptr<StaticDoNode> LStaticDoNode = std::make_shared<StaticDoNode>(InTokens[Index]);

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}

	std::shared_ptr<ASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LStaticDoNode->SetChild(STATIC_DO_NODE_BODY_OPERAND, LDoScope);

	if( Index + 1 < InTokens.size() && InTokens[Index + 1].GetType() == ETokenType::LPAR )
	{
		++Index;

		const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, Index + 1, InTokens);
		if( LParEnd == InTokens.size() )
		{
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[Index]);
			return nullptr;
		}

		if( LParEnd > Index + 1 )
		{
			std::shared_ptr<ASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd));
			LStaticDoNode->SetChild(STATIC_DO_NODE_CONDITION_OPERAND, LConditionExpr);
		}

		Index = LParEnd;
	}

	return LStaticDoNode;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticWhile(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::WHILE )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
		return nullptr;
	}
	std::shared_ptr<StaticWhileNode> LStaticWhileNode = std::make_shared<StaticWhileNode>(InTokens[Index]);

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[Index]);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LPAR )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[Index]);
		return nullptr;
	}

	const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, Index + 1, InTokens);
	if( LParEnd == InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[Index]);
		return nullptr;
	}

	if( LParEnd > Index + 1 )
	{
		std::shared_ptr<ASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd));
		LStaticWhileNode->SetChild(STATIC_WHILE_NODE_CONDITION_OPERAND, LConditionExpr);
	}
	Index = LParEnd;

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}

	std::shared_ptr<ASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LStaticWhileNode->SetChild(STATIC_WHILE_NODE_BODY_OPERAND, LDoScope);

	return LStaticWhileNode;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticFor(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticForeach(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticIf(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticSwitch(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticSwitchAll(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Do(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::DO )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
		return nullptr;
	}
	std::shared_ptr<DoNode> LDoNode = std::make_shared<DoNode>(InTokens[Index]);

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}

	std::shared_ptr<ASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LDoNode->SetChild(DO_NODE_BODY_OPERAND, LDoScope);

	if( Index + 1 < InTokens.size() && InTokens[Index + 1].GetType() == ETokenType::LPAR )
	{
		++Index;

		const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, Index + 1, InTokens);
		if( LParEnd == InTokens.size() )
		{
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[Index]);
			return nullptr;
		}

		if( LParEnd > Index + 1 )
		{
			std::shared_ptr<ASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd));
			LDoNode->SetChild(DO_NODE_CONDITION_OPERAND, LConditionExpr);
		}

		Index = LParEnd;
	}

	return LDoNode;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_While(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::WHILE )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, ContextToken);
		return nullptr;
	}
	std::shared_ptr<WhileNode> LWhileNode = std::make_shared<WhileNode>(InTokens[Index]);

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[Index]);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LPAR )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[Index]);
		return nullptr;
	}

	const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, Index + 1, InTokens);
	if( LParEnd == InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[Index]);
		return nullptr;
	}

	if( LParEnd > Index + 1 )
	{
		std::shared_ptr<ASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd));
		LWhileNode->SetChild(WHILE_NODE_CONDITION_OPERAND, LConditionExpr);
	}
	Index = LParEnd;

	if( Index + 1 >= InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}
	++Index;

	if( InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_LBRA, InTokens[Index]);
		return nullptr;
	}

	std::shared_ptr<ASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LWhileNode->SetChild(WHILE_NODE_BODY_OPERAND, LDoScope);

	return LWhileNode;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_For(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Foreach(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_If(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Switch(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_SwitchAll(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Assert(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticAssert(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticError(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticWarning(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_StaticMessage(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Using(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Var(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Break(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Continue(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Return(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Call(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_IndexAccess(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Class(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Array(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Lambda(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Thernal(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_Cast(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<ASTNode> ScopeNode::Parse_UnsafeCast(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}
