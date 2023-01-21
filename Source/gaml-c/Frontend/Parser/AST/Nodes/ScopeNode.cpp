// Copyright 2022 - 2023 GrosSlava.

#include "ScopeNode.h"

#include "Token/Token.h"

#include "Parser/AST/ASTCodeGenFactory.h"
#include "Parser/AST/ASTSymbols.h"

#include "LeafNode.h"
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
				ExprSequence.push_back(Parse_StaticDo(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::WHILE:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticWhile(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::FOR:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticFor(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::FOREACH:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticForeach(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::IF:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticIf(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::SWITCH:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticSwitch(InTokens, LIndex));

				++LIndex;
				continue;
			}
			case ETokenType::SWITCH_ALL:
			{
				HasControlStatement = true;
				ExprSequence.push_back(Parse_StaticSwitchAll(InTokens, LIndex));

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
			ExprSequence.push_back(Parse_Do(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::WHILE:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_While(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::FOR:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_For(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::FOREACH:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Foreach(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::IF:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_If(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::SWITCH:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Switch(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::SWITCH_ALL:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_SwitchAll(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::ASSERT:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Assert(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_ASSERT:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_StaticAssert(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_ERROR:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_StaticError(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_WARNING:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_StaticWarning(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::STATIC_MESSAGE:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_StaticMessage(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::USING:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Using(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::VAR:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Var(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::BREAK:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Break(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::CONTINUE:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Continue(InTokens, LIndex));

			++LIndex;
			continue;
		}
		case ETokenType::RETURN:
		{
			HasControlStatement = true;
			ExprSequence.push_back(Parse_Return(InTokens, LIndex));

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

			ExprSequence.push_back(ParseExpr(std::vector<Token>(InTokens.begin() + LIndex, InTokens.begin() + LExpressionEndIndex)));

			LIndex = LExpressionEndIndex + 1;
			continue;
		}
		}
	}
}





class UExprParseListNode
{
public:

	std::shared_ptr<IASTNode> ASTPart;

	std::shared_ptr<UExprParseListNode> Left;
	std::shared_ptr<UExprParseListNode> Right;
};

struct FExprParseList
{
public:

	void AddASTNode(std::shared_ptr<IASTNode> ASTNode)
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

std::shared_ptr<IASTNode> ScopeNode::ParseExpr(const std::vector<Token>& InTokens) const
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

			std::shared_ptr<IASTNode> LLeafNode = std::make_shared<LeafNode>(InTokens[LIndex]);
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

			std::shared_ptr<IASTNode> LLeafNode = std::make_shared<LeafNode>(InTokens[LIndex]);
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
			std::shared_ptr<IASTNode> LLeafNode = std::make_shared<LeafNode>(InTokens[LIndex]);
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
				std::shared_ptr<IASTNode> LExpr = ParseExpr(std::vector<Token>(InTokens.begin() + LIndex + 1, InTokens.begin() + LParEnd - 1));
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
				std::shared_ptr<IASTNode> LExpr = ParseExpr(std::vector<Token>(InTokens.begin() + LIndex + 1, InTokens.begin() + LSqrEnd - 1));
				LRHArrayNode->SetOperand(RHARRAY_NODE_ELEMENTS_OPERAND, LExpr);
			}

			LASTParts.AddASTNode(LRHArrayNode);

			LIndex = LSqrEnd + 1;
			continue;
		}

		//.....................................................................................//


		//...........................Unary/binary operators....................................//

#define CASE_OPERATOR(TokenName, ClassName)                                                         \
	case ETokenType::TokenName:                                                                     \
	{                                                                                               \
		std::shared_ptr<ClassName> LASTNode = std::make_shared<ClassName>(InTokens[LIndex]);        \
		LASTParts.AddASTNode(LASTNode);                                                             \
                                                                                                    \
		const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex]); \
		if( LOperatorPriority == -1 )                                                               \
		{                                                                                           \
			FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);                \
			return nullptr;                                                                         \
		}                                                                                           \
		OperatorsPrioritySort[LOperatorPriority].push_back(LASTParts.Tail);                         \
                                                                                                    \
		++LIndex;                                                                                   \
		continue;                                                                                   \
	}
			// clang-format off
		//TODO
		CASE_OPERATOR(LESS, LessNode)
		CASE_OPERATOR(GREATER, GreatherNode)
		CASE_OPERATOR(LESS_EQUAL, GreatherNode)
		CASE_OPERATOR(GREATER_EQUAL, GreatherNode)
		CASE_OPERATOR(EQUAL, GreatherNode)
		CASE_OPERATOR(NOT_EQUAL, GreatherNode)
		CASE_OPERATOR(AND, GreatherNode)
		CASE_OPERATOR(OR, GreatherNode)
		CASE_OPERATOR(EXCLAMATION, GreatherNode)
		CASE_OPERATOR(BINARY_AND, GreatherNode)
		CASE_OPERATOR(BINARY_OR, GreatherNode)
		CASE_OPERATOR(BINARY_INVERSE, GreatherNode)
		CASE_OPERATOR(BINARY_XOR, GreatherNode)
		CASE_OPERATOR(BINARY_SHL, GreatherNode)
		CASE_OPERATOR(BINARY_SHR, GreatherNode)
		CASE_OPERATOR(STAR, GreatherNode)
		CASE_OPERATOR(SLASH, GreatherNode)
		CASE_OPERATOR(INC, GreatherNode)
		CASE_OPERATOR(DEC, GreatherNode)
		CASE_OPERATOR(MOD, GreatherNode)
		CASE_OPERATOR(POW, GreatherNode)
		CASE_OPERATOR(IN, GreatherNode)
		CASE_OPERATOR(IS, GreatherNode)
		CASE_OPERATOR(PLUS, GreatherNode)
		CASE_OPERATOR(MINUS, GreatherNode)
		CASE_OPERATOR(NAMESPACE_ACCESS_OPERATOR, GreatherNode)
		CASE_OPERATOR(RIGHT_ARROW, GreatherNode)
		CASE_OPERATOR(POINT, GreatherNode)
		CASE_OPERATOR(ASSIGN, GreatherNode)
		CASE_OPERATOR(ADD_ASSIGN, GreatherNode)
		CASE_OPERATOR(SUB_ASSIGN, GreatherNode)
		CASE_OPERATOR(MUL_ASSIGN, GreatherNode)
		CASE_OPERATOR(DIV_ASSIGN, GreatherNode)
		CASE_OPERATOR(MOD_ASSIGN, GreatherNode)
		CASE_OPERATOR(POW_ASSIGN, GreatherNode)
		CASE_OPERATOR(BINARY_AND_ASSIGN, GreatherNode)
		CASE_OPERATOR(BINARY_OR_ASSIGN, GreatherNode)
		CASE_OPERATOR(BINARY_INVERSE_ASSIGN, GreatherNode)
		CASE_OPERATOR(BINARY_XOR_ASSIGN, GreatherNode)
		CASE_OPERATOR(BINARY_SHL_ASSIGN, GreatherNode)
		CASE_OPERATOR(BINARY_SHR_ASSIGN, GreatherNode)
			// clang-format on

#undef CASE_OPERATOR

			//.....................................................................................//


			//............Keyword operators with operands in pairs.................................//

#define CASE_KEYWORD_OPERATOR(TokenName, ClassName)                                                                                     \
	case ETokenType::TokenName:                                                                                                         \
	{                                                                                                                                   \
		const int LOperatorPriority = FParserHelperLibrary::GetOperationPriority(InTokens[LIndex]);                                     \
		if( LOperatorPriority == -1 )                                                                                                   \
		{                                                                                                                               \
			FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, InTokens[LIndex]);                                                    \
			return nullptr;                                                                                                             \
		}                                                                                                                               \
                                                                                                                                        \
		std::shared_ptr<ClassName> LASTNode = std::make_shared<ClassName>(InTokens[LIndex]);                                            \
		if( LIndex + 1 >= InTokens.size() )                                                                                             \
		{                                                                                                                               \
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[LIndex]);                                                    \
			return nullptr;                                                                                                             \
		}                                                                                                                               \
		++LIndex;                                                                                                                       \
		if( InTokens[LIndex].GetType() != ETokenType::LPAR )                                                                            \
		{                                                                                                                               \
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_LPAR, InTokens[LIndex]);                                                    \
			return nullptr;                                                                                                             \
		}                                                                                                                               \
                                                                                                                                        \
		const size_t LParEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LPAR, LIndex + 1, InTokens);                     \
		if( LParEnd == InTokens.size() )                                                                                                \
		{                                                                                                                               \
			FErrorLogger::Raise(EErrorMessageType::EXPECTED_RPAR, InTokens[LIndex]);                                                    \
			return nullptr;                                                                                                             \
		}                                                                                                                               \
                                                                                                                                        \
		if( LParEnd > LIndex + 1 )                                                                                                      \
		{                                                                                                                               \
			std::shared_ptr<IASTNode> LExpr = ParseExpr(std::vector<Token>(InTokens.begin() + LIndex + 1, InTokens.begin() + LParEnd)); \
			LASTNode->SetOperand(0, LExpr);                                                                                             \
		}                                                                                                                               \
                                                                                                                                        \
		LASTParts.AddASTNode(LASTNode);                                                                                                 \
		/* not add to operators priority sort because it already has an operand */                                                      \
                                                                                                                                        \
		LIndex = LParEnd + 1;                                                                                                           \
		continue;                                                                                                                       \
	}
			// clang-format off
			//TODO
		CASE_KEYWORD_OPERATOR(SIZE_OF, GreatherNode)
		CASE_KEYWORD_OPERATOR(TYPE_OF, GreatherNode)
		CASE_KEYWORD_OPERATOR(NAME_OF, GreatherNode)
		CASE_KEYWORD_OPERATOR(ALIGN_OF, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_FUNCTION, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_STRUCT, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_ENUM, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_INTERFACE, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_OBJECT, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_COMPONENT, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_SUBCLASS, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_INSTANCE, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_LAMBDA, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_ITERABLE, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_ENUMERABLE, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_ABSTRACT, GreatherNode)
		CASE_KEYWORD_OPERATOR(IS_ALIAS, GreatherNode)
		CASE_KEYWORD_OPERATOR(ADDR, GreatherNode)
		CASE_KEYWORD_OPERATOR(DEFAULT, GreatherNode)
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


			FErrorLogger::Raise(EErrorMessageType::UNEXPECTED_EXPRESSION, InTokens[LIndex]);
			return nullptr;
		}
	}

	// link nodes
	for( long long int i = OperatorsPrioritySort.size() - 1; i >= 0; --i )
	{
		for( std::shared_ptr<UExprParseListNode> LExprParseListNode : OperatorsPrioritySort[i] )
		{
			// clang-format off
			if( 
				std::shared_ptr<BaseExpressionOperatorNode> LAsExpressionOperatorNode =
				std::dynamic_pointer_cast<BaseExpressionOperatorNode>(LExprParseListNode->ASTPart) 
			  )
			// clang-format on
			{
				std::shared_ptr<IASTNode> LLeftOperand = nullptr;
				std::shared_ptr<IASTNode> LRightOperand = nullptr;

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
				LAsExpressionOperatorNode->AssignSubTrees(LLeftOperand, LRightOperand, LUsedLeft, LUsedRight);

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





std::shared_ptr<IASTNode> ScopeNode::Parse_Scope(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::LBRA )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, "", 0, 0, 0);
		return nullptr;
	}

	const size_t LBraScopeEnd = FParserHelperLibrary::GetLastClosePairIndex(ETokenType::LBRA, Index + 1, InTokens);
	if( LBraScopeEnd == InTokens.size() )
	{
		FErrorLogger::Raise(EErrorMessageType::EXPECTED_RBRA, InTokens[Index]);
		return nullptr;
	}

	std::shared_ptr<ScopeNode> LScopeNode = std::make_shared<ScopeNode>();
	if( LBraScopeEnd > Index + 1 )
	{
		LScopeNode->BuildAST(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LBraScopeEnd));
	}

	Index = LBraScopeEnd;
	return LScopeNode;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticDo(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::DO )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, "", 0, 0, 0);
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

	std::shared_ptr<IASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LStaticDoNode->SetOperand(STATIC_DO_NODE_BODY_OPERAND, LDoScope);

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
			std::shared_ptr<IASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd));
			LStaticDoNode->SetOperand(STATIC_DO_NODE_CONDITION_OPERAND, LConditionExpr);
		}

		Index = LParEnd;
	}

	return LStaticDoNode;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticWhile(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticFor(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticForeach(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticIf(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticSwitch(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticSwitchAll(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Do(const std::vector<Token>& InTokens, size_t& Index) const
{
	if( Index >= InTokens.size() || InTokens[Index].GetType() != ETokenType::DO )
	{
		FErrorLogger::Raise(EErrorMessageType::INVALID_STATE, "", 0, 0, 0);
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

	std::shared_ptr<IASTNode> LDoScope = Parse_Scope(InTokens, Index);
	LDoNode->SetOperand(DO_NODE_BODY_OPERAND, LDoScope);

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
			std::shared_ptr<IASTNode> LConditionExpr = ParseExpr(std::vector<Token>(InTokens.begin() + Index + 1, InTokens.begin() + LParEnd));
			LDoNode->SetOperand(DO_NODE_CONDITION_OPERAND, LConditionExpr);
		}

		Index = LParEnd;
	}

	return LDoNode;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_While(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_For(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Foreach(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_If(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Switch(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_SwitchAll(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Assert(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticAssert(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticError(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticWarning(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_StaticMessage(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Using(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Var(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Break(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Continue(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Return(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Call(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_IndexAccess(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Class(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Array(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Lambda(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Thernal(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_Cast(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}

std::shared_ptr<IASTNode> ScopeNode::Parse_UnsafeCast(const std::vector<Token>& InTokens, size_t& Index) const
{
	//TODO
	return nullptr;
}



//..........................................................................................................................//
//..........................................................................................................................//



void ScopeNode::InterpretAST(const FProgramInfo& ProgramInfo, FASTSymbols& LocalInfo)
{
	//TODO
}

bool ScopeNode::GetInterpretResultAsBool() const
{
	//TODO
	return false;
}

int ScopeNode::GetInterpretResultAsInt() const
{
	//TODO
	return 0;
}

double ScopeNode::GetInterpretResultAsDouble() const
{
	//TODO
	return 0.0;
}

std::string ScopeNode::GetInterpretResultAsString() const
{
	//TODO
	return std::string();
}





std::string ScopeNode::GenerateCode(std::shared_ptr<IASTCodeGenFactory> ASTCodeGenFactory, const FProgramInfo& ProgramInfo) const
{
	if( ASTCodeGenFactory == nullptr ) return "";

	std::shared_ptr<INodeCodeGen<ScopeNode>> LCodeGen = ASTCodeGenFactory->MakeScopeGen();
	if( LCodeGen == nullptr ) return "";

	return LCodeGen->GenerateCode(this, ProgramInfo);
}
