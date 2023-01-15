// Copyright 2022 - 2023 GrosSlava.

#include "LeafNode.h"





bool LeafNode::GetInterpretResultAsBool() const
{
	if(LeafToken.GetType() == ETokenType::TRUE_CONST) return true;
	if(LeafToken.GetType() == ETokenType::FALSE_CONST) return false;

	if(LeafToken.GetType() == ETokenType::CHAR_CONST) return false;
	if(LeafToken.GetType() == ETokenType::STRING_CONST) return false;

	if(LeafToken.GetType() == ETokenType::FLOAT_CONST) return static_cast<bool>(std::stof(LeafToken.GetLexeme()));
	if(LeafToken.GetType() == ETokenType::DOUBLE_CONST) return static_cast<bool>(std::stod(LeafToken.GetLexeme()));
	if(LeafToken.GetType() == ETokenType::INTEGER_CONST) return static_cast<bool>(std::stoi(LeafToken.GetLexeme()));

	return false;
}

int LeafNode::GetInterpretResultAsInt() const
{
	if(LeafToken.GetType() == ETokenType::TRUE_CONST) return 1;
	if(LeafToken.GetType() == ETokenType::FALSE_CONST) return 0;

	if(LeafToken.GetType() == ETokenType::CHAR_CONST) return 0;
	if(LeafToken.GetType() == ETokenType::STRING_CONST) return 0;

	if(LeafToken.GetType() == ETokenType::FLOAT_CONST) return static_cast<int>(std::stof(LeafToken.GetLexeme()));
	if(LeafToken.GetType() == ETokenType::DOUBLE_CONST) return static_cast<int>(std::stod(LeafToken.GetLexeme()));
	if(LeafToken.GetType() == ETokenType::INTEGER_CONST) return std::stoi(LeafToken.GetLexeme());

	return 0;
}

double LeafNode::GetInterpretResultAsDouble() const
{
	if(LeafToken.GetType() == ETokenType::TRUE_CONST) return 1.0;
	if(LeafToken.GetType() == ETokenType::FALSE_CONST) return 0.0;

	if(LeafToken.GetType() == ETokenType::CHAR_CONST) return 0.0;
	if(LeafToken.GetType() == ETokenType::STRING_CONST) return 0.0;

	if(LeafToken.GetType() == ETokenType::FLOAT_CONST) return static_cast<double>(std::stof(LeafToken.GetLexeme()));
	if(LeafToken.GetType() == ETokenType::DOUBLE_CONST) return std::stod(LeafToken.GetLexeme());
	if(LeafToken.GetType() == ETokenType::INTEGER_CONST) return static_cast<double>(std::stoi(LeafToken.GetLexeme()));

	return 0.0;
}

std::string LeafNode::GetInterpretResultAsString() const
{
	return LeafToken.GetLexeme();
}