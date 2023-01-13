// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Token/Token.h"
#include "ProgramSymbols.h"

#include "../Compiler/CompilerHelperLibrary.h"
#include "../Compiler/CompilerConfig.h"




/*
	Helper library for common parser operations.
*/
struct FParserHelperLibrary
{
	/*
		Check that given token type is open pair.
	*/
	static inline bool IsOpenPairToken(ETokenType TokenType) noexcept
	{
		// clang-format off
		return	TokenType == ETokenType::LBRA || TokenType == ETokenType::LPAR || 
				TokenType == ETokenType::LSQR || TokenType == ETokenType::LTRI;
		// clang-format on
	}
	/*
		Check that given token is open pair.
	*/
	static inline bool IsOpenPairToken(const Token& InToken) noexcept { return IsOpenPairToken(InToken.GetType()); }

	/*
		Check that given token type is close pair.
	*/
	static inline bool IsClosePairToken(ETokenType TokenType) noexcept
	{
		// clang-format off
		return	TokenType == ETokenType::RBRA || TokenType == ETokenType::RPAR ||
				TokenType == ETokenType::RSQR || TokenType == ETokenType::RTRI;
		// clang-format on
	}
	/*
		Check that given token is close pair.
	*/
	static inline bool IsClosePairToken(const Token& InToken) noexcept { return IsClosePairToken(InToken.GetType()); }

	/*
		@return close pair based on given open pair.
	*/
	static inline ETokenType GetMatchClosePairType(ETokenType TokenType) noexcept
	{
		switch( TokenType )
		{
		case ETokenType::LBRA: return ETokenType::RBRA;
		case ETokenType::LPAR: return ETokenType::RPAR;
		case ETokenType::LSQR: return ETokenType::RSQR;
		case ETokenType::LTRI: return ETokenType::RTRI;
		}

		return ETokenType::IDENTIFIER; // undefined
	}
	/*
		@return close pair based on given open pair.
	*/
	static inline ETokenType GetMatchClosePairType(const Token& InToken) noexcept { return GetMatchClosePairType(InToken.GetType()); }

	/*
		@return open pair based on given close pair.
	*/
	static inline ETokenType GetMatchOpenPairType(ETokenType TokenType) noexcept
	{
		switch( TokenType )
		{
		case ETokenType::RBRA: return ETokenType::LBRA;
		case ETokenType::RPAR: return ETokenType::LPAR;
		case ETokenType::RSQR: return ETokenType::LSQR;
		case ETokenType::RTRI: return ETokenType::LTRI;
		}

		return ETokenType::IDENTIFIER; // undefined
	}
	/*
		@return open pair based on given close pair.
	*/
	static inline ETokenType GetMatchOpenPairType(const Token& InToken) noexcept { return GetMatchOpenPairType(InToken.GetType()); }

	/*
		Check that pair TokenA matchs pair TokenB.
	*/
	static inline bool DoesPairTokensMatch(ETokenType TokenTypeA, ETokenType TokenTypeB) noexcept
	{
		// clang-format off
		return	(TokenTypeA == ETokenType::LBRA && TokenTypeB == ETokenType::RBRA) || (TokenTypeA == ETokenType::RBRA && TokenTypeB == ETokenType::LBRA) || 
				(TokenTypeA == ETokenType::LPAR && TokenTypeB == ETokenType::RPAR) || (TokenTypeA == ETokenType::RPAR && TokenTypeB == ETokenType::LPAR) ||
				(TokenTypeA == ETokenType::LSQR && TokenTypeB == ETokenType::RSQR) || (TokenTypeA == ETokenType::RSQR && TokenTypeB == ETokenType::LSQR) ||
				(TokenTypeA == ETokenType::LTRI && TokenTypeB == ETokenType::RTRI) || (TokenTypeA == ETokenType::RTRI && TokenTypeB == ETokenType::LTRI);
		// clang-format on
	}
	/*
		Check that pair TokenA matchs pair TokenB.
	*/
	static inline bool DoesPairTokensMatch(const Token& TokenA, const Token& TokenB) noexcept
	{
		return DoesPairTokensMatch(TokenA.GetType(), TokenB.GetType());
	}

	/*
		Find close pair for given open with nested pairs.

		S - function expected start
		F - function return index
		"{.{.....}.}"
		".^........^"
		".S........F"

		@param OpenPair - Open pair for search.
		@param StartIndex - Index in Tokens after open pair to start.
		@return index of close pair, if can't find return index = Tokens.size().
	*/
	static size_t GetLastClosePairIndex(ETokenType OpenPair, size_t StartIndex, const std::vector<Token>& Tokens) noexcept;




	/*
		Construct module compile name.

		@param ModulePathParts - module package path.
		@return constructed module name.
	*/
	static inline std::string GetModuleCompileName(const std::vector<std::string>& ModulePathParts)
	{
		return FCompilerHelperLibrary::MakePathFromParts(ModulePathParts, false, FCompilerConfig::COMPILE_NAME_SEPARATOR);
	}
	/*
		Construct module compile name.

		@param ModuleName - original module name from file.
		@return constructed module name.
	*/
	static inline std::string GetModuleCompileName(const std::string& ModuleName)
	{
		std::vector<std::string> SplittedParts;
		FCompilerHelperLibrary::SplitPathToParts(ModuleName, SplittedParts, '.');

		return GetModuleCompileName(SplittedParts);
	}
	/*
		Convert module name to parts.

		@param ModuleCompileName - nome of module to convert.
		@param OutParts - result of splitting will be here.
	*/
	static inline void SplitModuleCompileNameToParts(const std::string& ModuleCompileName, std::vector<std::string>& OutParts)
	{
		FCompilerHelperLibrary::SplitPathToParts(ModuleCompileName, OutParts, FCompilerConfig::COMPILE_NAME_SEPARATOR);
	}
	/*
		Return module real compile name.

		@param ModuleNameOrAlias - module compile name or alias.
		@ProgramInfo ProgramInfo - current program info.
		@return module real compile name.
	*/
	static std::string GetModuleRealName(const std::string& ModuleNameOrAlias, const FProgramInfo& ProgramInfo);
	/*
		Return module real compile name.
		First part can be module/package alias. 

		@param ModulePathParts - module package path.
		@ProgramInfo ProgramInfo - current program info.
		@return module real compile name.
	*/
	static std::string GetModuleRealName(std::vector<std::string> ModulePathParts, const FProgramInfo& ProgramInfo);
	/*
		Return module real compile name.
		First part can be module/package alias. 

		@param ModuleNameOrAlias - module compile name or alias.
		@ProgramInfo ProgramInfo - current program info.
		@return module real compile name.
	*/
	static std::string GetModuleRealNameWithFirstPartCheck(const std::string& ModuleNameOrAlias, const FProgramInfo& ProgramInfo);

	/*
		Construct any compile name.

		@param ContextCompileName - compile name of context(module, class, function) where declared name.
		@param OriginalName - object original name.
		@return constructed name.
	*/
	static std::string GetCompileName(const std::string& ContextCompileName, const std::string& OriginalName) noexcept;
	// clang-format off
	/*
		Construct any compile name.

		@param ContextCompileName - compile name of context(module, class, function) where declared name.
		@param OriginalName - object original name.
		@param ArgumentNames - array of any argument names.
		@return constructed name.
	*/
	static std::string GetCompileName
	(
		const std::string& ContextCompileName, const std::string& OriginalName, const std::vector<std::string>& ArgumentNames
	) noexcept;
	// clang-format on
	// clang-format off
	/*
		Construct function compile name.

		@param ContextCompileName - compile name of context(module, class) where declared function.
		@param OriginalName - function original name.
		@param IsConst - function const overload.
		@param ArgumentTypeNames - array of function argument types names.
		@return constructed function name.
	*/
	static std::string GetFunctionCompileName
	(
		const std::string& ContextCompileName, const std::string& OriginalName, 
		bool IsConst, const std::vector<std::string>& ArgumentTypeNames
	) noexcept;
	// clang-format on
	// clang-format off
	/*
		Construct function compile name.

		@param ContextCompileName - compile name of context(module, class) where declared function.
		@param OriginalName - function original name.
		@param FunctionSignatureInfo - function signature info.
		@param ProgramInfo - current program info.
		@return constructed function name.
	*/
	static std::string GetFunctionCompileName
	(	
		const std::string& ContextCompileName, const std::string& OriginalName,
		const FFunctionSignatureInfo& FunctionSignatureInfo
	) noexcept;
	// clang-format on
	/*
		Construct any compile name.

		@param ContextCompileName - compile name of context(module, class, function) where declared name.
		@param OriginalName - object original name.
		@param ArgumentNames - array of any argument names.
		@return constructed name.
	*/
	static inline std::string GetFunctionPointerCompileName(const FFunctionSignatureInfo& FunctionSignatureInfo) noexcept
	{
		return GetFunctionCompileName("", "fsign", FunctionSignatureInfo);
	}
	/*
		Construct standard type compile name.

		@param StandardTypeID - ID of standard type.
		@return constructed type name.
	*/
	static inline std::string GetStandardTypeCompileName(const Token& InToken) noexcept
	{
		// clang-format off
		switch( InToken.GetType() )
		{
		case ETokenType::UINT8:		return EStandardTypesName::UINT8_Name;
		case ETokenType::UINT16:	return EStandardTypesName::UINT16_Name;
		case ETokenType::UINT32:	return EStandardTypesName::UINT32_Name;
		case ETokenType::UINT64:	return EStandardTypesName::UINT64_Name;
		case ETokenType::INT8:		return EStandardTypesName::INT8_Name;
		case ETokenType::INT16:		return EStandardTypesName::INT16_Name;
		case ETokenType::INT32:		return EStandardTypesName::INT32_Name;
		case ETokenType::INT64:		return EStandardTypesName::INT64_Name;
		case ETokenType::ADDR_T:	return EStandardTypesName::ADDR_T_Name;
		case ETokenType::FLOAT:		return EStandardTypesName::FLOAT_Name;
		case ETokenType::DOUBLE:	return EStandardTypesName::DOUBLE_Name;
		case ETokenType::BOOL:		return EStandardTypesName::BOOL_Name;
		case ETokenType::CHAR:		return EStandardTypesName::CHAR_Name;
		case ETokenType::STRING:	return EStandardTypesName::STRING_Name;
		case ETokenType::VECTOR4D:	return EStandardTypesName::VECTOR4D_Name;
		case ETokenType::VECTOR3D:	return EStandardTypesName::VECTOR3D_Name;
		case ETokenType::VECTOR2D:	return EStandardTypesName::VECTOR2D_Name;
		}
		// clang-format on

		return "";
	}

	/*
		Try to find type by compile name and return its kind.

		@return kind of type.
	*/
	static ETypeKind GetUserTypeKind(const std::string& CompileName, const FProgramInfo& ProgramInfo) noexcept;




	/*
		Check that given token is standard type.
	*/
	static inline bool IsStandardType(ETokenType TokenType) noexcept
	{
		// clang-format off
		return	TokenType == ETokenType::UINT8		|| TokenType == ETokenType::UINT16		|| TokenType == ETokenType::UINT32	|| TokenType == ETokenType::UINT64	||
				TokenType == ETokenType::INT8		|| TokenType == ETokenType::INT16		|| TokenType == ETokenType::INT32	|| TokenType == ETokenType::INT64	|| 
				TokenType == ETokenType::ADDR_T		|| TokenType == ETokenType::FLOAT		|| TokenType == ETokenType::DOUBLE	|| TokenType == ETokenType::BOOL	|| 
				TokenType == ETokenType::CHAR		|| TokenType == ETokenType::STRING		||
				TokenType == ETokenType::VECTOR4D	|| TokenType == ETokenType::VECTOR3D	|| TokenType == ETokenType::VECTOR2D;
		// clang-format on
	}
	/*
		Check that given token is standard type.
	*/
	static inline bool IsStandardType(const Token& InToken) noexcept { return IsStandardType(InToken.GetType()); }

	/*
		Check that given token is builtin template type.
	*/
	static inline bool IsBuiltinTemplateType(ETokenType TokenType) noexcept { return TokenType == ETokenType::ARRAY || TokenType == ETokenType::CLASS; }
	/*
		Check that given token is builtin template type.
	*/
	static inline bool IsBuiltinTemplateType(const Token& InToken) noexcept { return IsBuiltinTemplateType(InToken.GetType()); }

	/*
		Check that given token is modifier.
	*/
	static inline bool IsModifierToken(ETokenType TokenType) noexcept
	{
		// clang-format off
		return	TokenType == ETokenType::EXTERN_C 	|| 
				TokenType == ETokenType::CDECL 		|| TokenType == ETokenType::STDCALL 		|| TokenType == ETokenType::FASTCALL 	|| 
				TokenType == ETokenType::CONST 		|| TokenType == ETokenType::MUTABLE 		|| TokenType == ETokenType::STATIC 		||  
				TokenType == ETokenType::VIRTUAL 	|| TokenType == ETokenType::OVERRIDE 		|| 
				TokenType == ETokenType::ABSTRACT 	|| TokenType == ETokenType::FINAL			|| 
				TokenType == ETokenType::DEPRECATED || TokenType == ETokenType::UNIMPLEMENTED;
		// clang-format on
	}
	/*
		Check that given token is modifier.
	*/
	static inline bool IsModifierToken(const Token& InToken) noexcept { return IsModifierToken(InToken.GetType()); }




	/*
		Check that given function signatures are same.
	*/
	static bool AreFunctionSignaturesSame(const FFunctionSignatureInfo& FS1, const FFunctionSignatureInfo& FS2) noexcept;
	/*
		Check that given function signatures are completely equal.
	*/
	static bool AreFunctionsDeepEqual(const FFunctionSignatureInfo& FS1, const FFunctionSignatureInfo& FS2) noexcept;

	/*
		Find first module name declaration in tokens array.
	*/
	static std::string GetFirstModuleName(const std::vector<Token>& Tokens) noexcept;
};
