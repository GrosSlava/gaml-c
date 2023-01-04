// Copyright 2022 - 2023 GrosSlava.

#include "ParserHelperLibrary.h"





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
	const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo
) noexcept
// clang-format on
{
	std::vector<std::string> LArgumentsNames;
	LArgumentsNames.reserve(FunctionSignatureInfo.Inputs.size());

	for( const FVariableInfo& LVariableInfo : FunctionSignatureInfo.Inputs )
	{
		// it is finite recursion with function signature as argument
		const std::string LTypeName = GetTypeName(LVariableInfo.TypeID, ProgramInfo);
		if( LTypeName.empty() )
		{
			return "";
		}

		LArgumentsNames.push_back(LTypeName);
	}

	return GetFunctionCompileName(ContextCompileName, OriginalName, FunctionSignatureInfo.Modifiers.IsConst, LArgumentsNames);
}





int FParserHelperLibrary::GetFunctionSignatureID(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo) noexcept
{
	for( int i = 0; i < ProgramInfo.FunctionSignaturesTypesMap.size(); ++i )
	{
		if( AreFunctionSignaturesSame(FunctionSignatureInfo, ProgramInfo.FunctionSignaturesTypesMap[i]) )
		{
			return i;
		}
	}

	return -1;
}

int FParserHelperLibrary::GetFunctionSignatureID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo) noexcept
{
	auto LFunctionInfoIterator = ProgramInfo.Functions.find(FunctionCompileName);
	if( LFunctionInfoIterator == ProgramInfo.Functions.end() )
	{
		return -1;
	}

	return GetFunctionSignatureID(LFunctionInfoIterator->second.SignatureInfo, ProgramInfo);
}

int FParserHelperLibrary::GetFunctionSignatureTypeID(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo) noexcept
{
	const int LFunctionSignatureID = GetFunctionSignatureID(FunctionSignatureInfo, ProgramInfo);
	if( LFunctionSignatureID < 0 )
	{
		return -1;
	}

	for( int i = 0; i < ProgramInfo.TypesMap.size(); ++i )
	{
		// clang-format off
		if( 
			ProgramInfo.TypesMap[i].PathSwitch == ETypePathSwitch::FunctionSignature &&
			ProgramInfo.TypesMap[i].FunctionSignaturePath.FunctionSignatureID == LFunctionSignatureID 
			)
		// clang-format on
		{
			return i;
		}
	}

	return -1;
}

int FParserHelperLibrary::GetFunctionSignatureTypeID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo) noexcept
{
	auto LFunctionInfoIterator = ProgramInfo.Functions.find(FunctionCompileName);
	if( LFunctionInfoIterator == ProgramInfo.Functions.end() )
	{
		return -1;
	}

	return GetFunctionSignatureTypeID(LFunctionInfoIterator->second.SignatureInfo, ProgramInfo);
}

int FParserHelperLibrary::GetClassTypeID(const std::string& ClassCompileName, const FProgramInfo& ProgramInfo) noexcept
{
	for( int i = 0; i < ProgramInfo.TypesMap.size(); ++i )
	{
		if( ProgramInfo.TypesMap[i].PathSwitch == ETypePathSwitch::Class && ProgramInfo.TypesMap[i].ClassPath.ClassCompileName == ClassCompileName )
		{
			return i;
		}
	}

	return -1;
}

int FParserHelperLibrary::GetUserTypeID(const std::string& CompileName, const FProgramInfo& ProgramInfo) noexcept
{
	int LTypeID = GetClassTypeID(CompileName, ProgramInfo);
	if( LTypeID == -1 )
	{
		auto LAliasIter = ProgramInfo.TypeAliases.find(CompileName);
		if( LAliasIter != ProgramInfo.TypeAliases.end() )
		{
			LTypeID = LAliasIter->second;
		}
	}

	return LTypeID;
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
		if( LFS1Iter->TypeID != LFS2Iter->TypeID )
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