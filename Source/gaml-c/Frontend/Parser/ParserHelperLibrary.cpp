// Copyright 2022 - 2023 GrosSlava.

#include "ParserHelperLibrary.h"





size_t FParserHelperLibrary::GetLastClosePairIndex(ETokenType OpenPair, size_t StartIndex, const std::vector<Token>& Tokens) noexcept
{
	if( !IsOpenPairToken(OpenPair) )
	{
		return Tokens.size();
	}

	int LOpenCount = 1;
	size_t LIndex = StartIndex;
	const ETokenType LCloseType = FParserHelperLibrary::GetMatchClosePairType(OpenPair);

	while( LIndex < Tokens.size() && LOpenCount > 0 )
	{
		const ETokenType& LTokenType = Tokens[LIndex].GetType();

		if( LTokenType == OpenPair )
		{
			++LOpenCount;
		}
		else if( LTokenType == LCloseType )
		{
			--LOpenCount;
		}

		++LIndex;
	}

	if( LOpenCount > 0 )
	{
		return Tokens.size();
	}
	return LIndex - 1;
}





std::string FParserHelperLibrary::GetModuleRealName(const std::string& ModuleNameOrAlias, const FProgramInfo& ProgramInfo)
{
	if( ProgramInfo.ImportedModulesInfo.find(ModuleNameOrAlias) != ProgramInfo.ImportedModulesInfo.end() ) return ModuleNameOrAlias;

	const auto LMainModuleInfo = ProgramInfo.ImportedModulesInfo.find(ProgramInfo.MainModuleName);
	if( LMainModuleInfo == ProgramInfo.ImportedModulesInfo.end() ) return "";

	for( const auto& LAliasPair : LMainModuleInfo->second.ImportedModuleNameAliases )
	{
		if( ModuleNameOrAlias == LAliasPair.first )
		{
			return LAliasPair.second;
		}
	}

	return "";
}

std::string FParserHelperLibrary::GetModuleRealName(std::vector<std::string> ModulePathParts, const FProgramInfo& ProgramInfo)
{
	if( ModulePathParts.empty() )
	{
		return "";
	}

	const std::string LFirstPartRealName = GetModuleRealName(ModulePathParts[0], ProgramInfo);

	if( LFirstPartRealName.empty() )
	{
		return GetModuleCompileName(ModulePathParts);
	}

	ModulePathParts[0] = LFirstPartRealName;
	return GetModuleCompileName(ModulePathParts);
}

std::string FParserHelperLibrary::GetModuleRealNameWithFirstPartCheck(const std::string& ModuleNameOrAlias, const FProgramInfo& ProgramInfo)
{
	if( ModuleNameOrAlias.empty() )
	{
		return "";
	}

	std::vector<std::string> SplittedParts;
	FCompilerHelperLibrary::SplitPathToParts(ModuleNameOrAlias, SplittedParts, '.');

	return GetModuleRealName(SplittedParts, ProgramInfo);
}



std::string FParserHelperLibrary::GetCompileName(const std::string& ContextCompileName, const std::string& OriginalName) noexcept
{
	if( OriginalName.empty() )
	{
		return "";
	}

	std::string LCompileName = "";
	LCompileName.reserve(OriginalName.size() + ContextCompileName.size() + 1);

	if( !ContextCompileName.empty() )
	{
		LCompileName += ContextCompileName + FCompilerConfig::COMPILE_NAME_SEPARATOR;
	}

	LCompileName += OriginalName;

	return LCompileName;
}

// clang-format off
std::string FParserHelperLibrary::GetCompileName
(
	const std::string& ContextCompileName, const std::string& OriginalName, const std::vector<std::string>& ArgumentNames
) noexcept
// clang-format on
{
	if( OriginalName.empty() )
	{
		return "";
	}

	std::string LCompileName = "";
	LCompileName.reserve(OriginalName.size() + ContextCompileName.size() + ArgumentNames.size() * 2);

	if( !ContextCompileName.empty() )
	{
		LCompileName += ContextCompileName + FCompilerConfig::COMPILE_NAME_SEPARATOR;
	}

	LCompileName += OriginalName;
	for( const std::string& LArgumentStr : ArgumentNames )
	{
		LCompileName += FCompilerConfig::COMPILE_NAME_SEPARATOR + LArgumentStr;
	}

	return LCompileName;
}

// clang-format off
std::string FParserHelperLibrary::GetFunctionCompileName
(
	const std::string& ContextCompileName, const std::string& OriginalName, 
	bool IsConst, const std::vector<std::string>& ArgumentTypeNames
) noexcept
// clang-format on
{
	if( OriginalName.empty() )
	{
		return "";
	}

	std::string LFunctionCompileName = GetCompileName(ContextCompileName, OriginalName, ArgumentTypeNames);

	if( IsConst )
	{
		LFunctionCompileName = "const" + LFunctionCompileName;
	}

	return LFunctionCompileName;
}

// clang-format off
std::string FParserHelperLibrary::GetFunctionCompileName
(	
	const std::string& ContextCompileName, const std::string& OriginalName,
	const FFunctionSignatureInfo& FunctionSignatureInfo
) noexcept
// clang-format on
{
	std::vector<std::string> LArgumentsNames;
	LArgumentsNames.reserve(FunctionSignatureInfo.Inputs.size());

	for( const FVariableInfo& LVariableInfo : FunctionSignatureInfo.Inputs )
	{
		if( LVariableInfo.TypeInfo.TypeCompileName.empty() )
		{
			return "";
		}

		LArgumentsNames.push_back(LVariableInfo.TypeInfo.TypeCompileName);
	}

	return GetFunctionCompileName(ContextCompileName, OriginalName, FunctionSignatureInfo.Modifiers.IsConst, LArgumentsNames);
}

ETypeKind FParserHelperLibrary::GetUserTypeKind(const std::string& CompileName, const FProgramInfo& ProgramInfo) noexcept
{
	if( CompileName.empty() )
	{
		return ETypeKind::UNDEFINED;
	}

	auto LClassIter = ProgramInfo.Classes.find(CompileName);
	if( LClassIter != ProgramInfo.Classes.end() )
	{
		return ETypeKind::Class;
	}

	auto LAliasIter = ProgramInfo.TypeAliases.find(CompileName);
	if( LAliasIter != ProgramInfo.TypeAliases.end() )
	{
		return LAliasIter->second.TypeKind;
	}

	auto LFunctionIter = ProgramInfo.Functions.find(CompileName);
	if( LFunctionIter != ProgramInfo.Functions.end() )
	{
		return ETypeKind::FunctionPointer;
	}

	return ETypeKind::UNDEFINED;
}





bool FParserHelperLibrary::AreFunctionSignaturesSame(const FFunctionSignatureInfo& FS1, const FFunctionSignatureInfo& FS2) noexcept
{
	if( FS1.Inputs.size() != FS2.Inputs.size() )
	{
		return false;
	}

	auto LFS1Iter = FS1.Inputs.begin();
	auto LFS2Iter = FS2.Inputs.begin();

	while( LFS1Iter != FS1.Inputs.end() )
	{
		if( LFS1Iter->TypeInfo != LFS2Iter->TypeInfo )
		{
			return false;
		}

		++LFS1Iter;
		++LFS2Iter;
	}

	if( FS1.Modifiers.IsConst != FS2.Modifiers.IsConst )
	{
		return false;
	}

	return true;
}

bool FParserHelperLibrary::AreFunctionsDeepEqual(const FFunctionSignatureInfo& FS1, const FFunctionSignatureInfo& FS2) noexcept
{
	if( FS1.Modifiers != FS2.Modifiers )
	{
		return false;
	}
	if( FS1.Inputs.size() != FS2.Inputs.size() || FS1.Returns.size() != FS2.Returns.size() )
	{
		return false;
	}

	auto LFS1InputsIter = FS1.Inputs.begin();
	auto LFS2InputsIter = FS2.Inputs.begin();
	while( LFS1InputsIter != FS1.Inputs.end() )
	{
		// clang-format off
		if( 
			LFS1InputsIter->TypeInfo != LFS2InputsIter->TypeInfo || 
			LFS1InputsIter->VariableName != LFS2InputsIter->VariableName || 
			LFS1InputsIter->Modifiers != LFS2InputsIter->Modifiers
		  )
		// clang-format on
		{
			return false;
		}

		++LFS1InputsIter;
		++LFS2InputsIter;
	}

	auto LFS1ReturnsIter = FS1.Returns.begin();
	auto LFS2ReturnsIter = FS2.Returns.begin();
	while( LFS1ReturnsIter != FS1.Returns.end() )
	{
		// clang-format off
		if( 
			LFS1ReturnsIter->TypeInfo != LFS2ReturnsIter->TypeInfo || 
			LFS1ReturnsIter->VariableName != LFS2ReturnsIter->VariableName || 
			LFS1ReturnsIter->Modifiers != LFS2ReturnsIter->Modifiers
		  )
		// clang-format on
		{
			return false;
		}

		++LFS1ReturnsIter;
		++LFS2ReturnsIter;
	}

	return true;
}



std::string FParserHelperLibrary::GetFirstModuleName(const std::vector<Token>& Tokens) noexcept
{
	if( Tokens.empty() )
	{
		return "";
	}

	int ModuleNameSearchIndex = 0;

	if( Tokens[ModuleNameSearchIndex].GetType() == ETokenType::DESCRIPTION_BLOCK )
	{
		do
		{
			++ModuleNameSearchIndex;
			if( Tokens.size() <= ModuleNameSearchIndex )
			{
				return "";
			}
		} while( Tokens[ModuleNameSearchIndex].GetType() != ETokenType::DESCRIPTION_BLOCK );

		++ModuleNameSearchIndex;
		if( Tokens.size() <= ModuleNameSearchIndex )
		{
			return "";
		}
	}

	if( Tokens[ModuleNameSearchIndex].GetType() == ETokenType::PUBLIC || Tokens[ModuleNameSearchIndex].GetType() == ETokenType::PRIVATE )
	{
		++ModuleNameSearchIndex;
		if( Tokens.size() <= ModuleNameSearchIndex )
		{
			return "";
		}
	}

	if( Tokens[ModuleNameSearchIndex].GetType() == ETokenType::MODULE )
	{
		++ModuleNameSearchIndex;
		if( Tokens.size() <= ModuleNameSearchIndex )
		{
			return "";
		}
	}
	else
	{
		return "";
	}

	std::string LModuleName = "";
	while( Tokens[ModuleNameSearchIndex].GetType() != ETokenType::SEMICOLON )
	{
		LModuleName += Tokens[ModuleNameSearchIndex].GetLexeme();
		++ModuleNameSearchIndex;
		if( Tokens.size() <= ModuleNameSearchIndex )
		{
			return "";
		}
	}

	return GetModuleCompileName(LModuleName);
}





int FParserHelperLibrary::GetOperationPriority(ETokenType TokenType, bool UseAlternative) noexcept
{
	switch( TokenType )
	{
	case ETokenType::ASSIGN: return 0;

	case ETokenType::COMMA: return 1;

	case ETokenType::QUESTION: return 2; // ternar if
	case ETokenType::ADD_ASSIGN: return 2;
	case ETokenType::SUB_ASSIGN: return 2;
	case ETokenType::MUL_ASSIGN: return 2;
	case ETokenType::DIV_ASSIGN: return 2;
	case ETokenType::MOD_ASSIGN: return 2;
	case ETokenType::POW_ASSIGN: return 2;
	case ETokenType::BINARY_AND_ASSIGN: return 2;
	case ETokenType::BINARY_OR_ASSIGN: return 2;
	case ETokenType::BINARY_INVERSE_ASSIGN: return 2;
	case ETokenType::BINARY_XOR_ASSIGN: return 2;
	case ETokenType::BINARY_SHL_ASSIGN: return 2;
	case ETokenType::BINARY_SHR_ASSIGN: return 2;

	case ETokenType::OR: return 3;

	case ETokenType::AND: return 4;

	case ETokenType::BINARY_OR: return 5;

	case ETokenType::BINARY_XOR: return 6;

	case ETokenType::BINARY_AND: return 7;

	case ETokenType::EQUAL: return 8;
	case ETokenType::NOT_EQUAL: return 8;
	case ETokenType::IS: return 8;

	case ETokenType::LESS: return 9;
	case ETokenType::GREATER: return 9;
	case ETokenType::LESS_EQUAL: return 9;
	case ETokenType::GREATER_EQUAL: return 9;

	case ETokenType::BINARY_SHL: return 10;
	case ETokenType::BINARY_SHR: return 10;
	case ETokenType::IN: return 10;

	case ETokenType::PLUS: return UseAlternative ? 13 : 11;
	case ETokenType::MINUS: return UseAlternative ? 13 : 11;

	case ETokenType::STAR: return 12;
	case ETokenType::SLASH: return 12;
	case ETokenType::MOD: return 12;
	case ETokenType::POW: return 12;

	case ETokenType::EXCLAMATION: return 13;
	case ETokenType::BINARY_INVERSE: return 13;

	case ETokenType::INC: return 14;
	case ETokenType::DEC: return 14;
	case ETokenType::POINT: return 14;
	case ETokenType::RIGHT_ARROW: return 14;

	case ETokenType::NAMESPACE_ACCESS_OPERATOR: return 15;

	case ETokenType::CAST: return 16;
	case ETokenType::UNSAFE_CAST: return 16;
	case ETokenType::DEFAULT: return 16;
	case ETokenType::SIZE_OF: return 16;
	case ETokenType::TYPE_OF: return 16;
	case ETokenType::NAME_OF: return 16;
	case ETokenType::IS_FUNCTION: return 16;
	case ETokenType::IS_STRUCT: return 16;
	case ETokenType::IS_ENUM: return 16;
	case ETokenType::IS_INTERFACE: return 16;
	case ETokenType::IS_OBJECT: return 16;
	case ETokenType::IS_COMPONENT: return 16;
	case ETokenType::IS_SUBCLASS: return 16;
	case ETokenType::IS_INSTANCE: return 16;
	case ETokenType::IS_LAMBDA: return 16;
	case ETokenType::IS_ITERABLE: return 16;
	case ETokenType::IS_ENUMERABLE: return 16;
	case ETokenType::IS_ABSTRACT: return 16;
	case ETokenType::IS_ALIAS: return 16;
	case ETokenType::ADDR: return 16;
	}

	return -1;
}
