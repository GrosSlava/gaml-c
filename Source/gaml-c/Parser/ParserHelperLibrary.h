// Copyright 2022 GrosSlava.

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
		Check that given token is open pair.
	*/
	static inline bool IsOpenPairToken(const Token& InToken) noexcept
	{
		const ETokenType LTokenType = InToken.GetType();

		// clang-format off
		return	LTokenType == ETokenType::LBRA || LTokenType == ETokenType::LPAR || 
				LTokenType == ETokenType::LSQR || LTokenType == ETokenType::LTRI;
		// clang-format on
	}
	/*
		Check that given token is close pair.
	*/
	static inline bool IsClosePairToken(const Token& InToken) noexcept
	{
		const ETokenType LTokenType = InToken.GetType();

		// clang-format off
		return	LTokenType == ETokenType::RBRA || LTokenType == ETokenType::RPAR ||
				LTokenType == ETokenType::RSQR || LTokenType == ETokenType::RTRI;
		// clang-format on
	}
	/*
		@return close pair based on given open pair.
	*/
	static inline ETokenType GetMatchClosePairType(const Token& InToken) noexcept
	{
		const ETokenType LTokenType = InToken.GetType();

		switch( LTokenType )
		{
		case ETokenType::LBRA: return ETokenType::RBRA;
		case ETokenType::LPAR: return ETokenType::RPAR;
		case ETokenType::LSQR: return ETokenType::RSQR;
		case ETokenType::LTRI: return ETokenType::RTRI;
		}

		return ETokenType::IDENTIFIER; // undefined
	}
	/*
		@return open pair based on given close pair.
	*/
	static inline ETokenType GetMatchOpenPairType(const Token& InToken) noexcept
	{
		const ETokenType LTokenType = InToken.GetType();

		switch( LTokenType )
		{
		case ETokenType::RBRA: return ETokenType::LBRA;
		case ETokenType::RPAR: return ETokenType::LPAR;
		case ETokenType::RSQR: return ETokenType::LSQR;
		case ETokenType::RTRI: return ETokenType::LTRI;
		}

		return ETokenType::IDENTIFIER; // undefined
	}
	/*
		Check that pair TokenA matchs pair TokenB.
	*/
	static inline bool DoesPairTokensMatch(const Token& TokenA, const Token& TokenB) noexcept
	{
		const ETokenType LAType = TokenA.GetType();
		const ETokenType LBType = TokenB.GetType();

		// clang-format off
		return	(LAType == ETokenType::LBRA && LBType == ETokenType::RBRA) || (LAType == ETokenType::RBRA && LBType == ETokenType::LBRA) || 
				(LAType == ETokenType::LPAR && LBType == ETokenType::RPAR) || (LAType == ETokenType::RPAR && LBType == ETokenType::LPAR) ||
				(LAType == ETokenType::LSQR && LBType == ETokenType::RSQR) || (LAType == ETokenType::RSQR && LBType == ETokenType::LSQR) ||
				(LAType == ETokenType::LTRI && LBType == ETokenType::RTRI) || (LAType == ETokenType::RTRI && LBType == ETokenType::LTRI);
		// clang-format on
	}




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
		const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo
	) noexcept;
	// clang-format on

	/*
		Construct standard type compile name.

		@param StandardTypeID - ID of standard type.
		@return constructed type name.
	*/
	static inline std::string GetStandardTypeCompileName(EStandardTypesID StandardTypeID)
	{
		// clang-format off
		switch( StandardTypeID )
		{
		case EStandardTypesID::VOID_ID:		return "vv";
		case EStandardTypesID::UINT8_ID:	return "u8";
		case EStandardTypesID::UINT16_ID:	return "u16";
		case EStandardTypesID::UINT32_ID:	return "u32";
		case EStandardTypesID::UINT64_ID:	return "u64";
		case EStandardTypesID::INT8_ID:		return "i8";
		case EStandardTypesID::INT16_ID:	return "i16";
		case EStandardTypesID::INT32_ID:	return "i32";
		case EStandardTypesID::INT64_ID:	return "i64";
		case EStandardTypesID::ADDR_T_ID:	return "addr";
		case EStandardTypesID::FLOAT_ID:	return "f";
		case EStandardTypesID::DOUBLE_ID:	return "d";
		case EStandardTypesID::BOOL_ID:		return "b";
		case EStandardTypesID::CHAR_ID:		return "c";
		case EStandardTypesID::STRING_ID:	return "s";
		case EStandardTypesID::VECTOR4D_ID: return "v4";
		case EStandardTypesID::VECTOR3D_ID: return "v3";
		case EStandardTypesID::VECTOR2D_ID: return "v2";
		}
		// clang-format on

		return "";
	}
	/*
		Try to get type as string.

		@param TypeID - ID of type.
		@param ProgramInfo - current program info.
		@return constructed type name.
	*/
	static inline std::string GetTypeName(int TypeID, const FProgramInfo& ProgramInfo) noexcept
	{
		if( TypeID < 0 || TypeID >= ProgramInfo.TypesMap.size() ) return "";

		const FUserTypePath& LTypePath = ProgramInfo.TypesMap[TypeID];
		switch( LTypePath.PathSwitch )
		{
		case ETypePathSwitch::Standard:
		{
			return GetStandardTypeCompileName(static_cast<EStandardTypesID>(TypeID));
		}
		case ETypePathSwitch::Class:
		{
			return LTypePath.ClassPath.ClassCompileName;
		}
		case ETypePathSwitch::FunctionSignature:
		{
			const FFunctionSignatureInfo& LFunctionSignature = ProgramInfo.FunctionSignaturesTypesMap[LTypePath.FunctionSignaturePath.FunctionSignatureID];
			return GetFunctionCompileName("", "fsign", LFunctionSignature, ProgramInfo);
		}
		}

		return "";
	}




	/*
		Check that given token is standard type.
	*/
	static inline bool IsStandardType(ETokenType TokenType) noexcept
	{
		// clang-format off
		return	TokenType == ETokenType::VOID		|| 
				TokenType == ETokenType::UINT8		|| TokenType == ETokenType::UINT16		|| TokenType == ETokenType::UINT32	|| TokenType == ETokenType::UINT64	||
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
		Check that given type ID is standard type.
	*/
	static inline bool IsStandardType(int TypeID) noexcept { return TypeID >= 0 && TypeID < EStandardTypesID::StandardTypesID_MAX; }
	/*
		Check that given token is standard type and can be used as variable type.
	*/
	static inline bool IsVariableStandardType(ETokenType TokenType) noexcept { return IsStandardType(TokenType) && TokenType != ETokenType::VOID; }
	/*
		Check that given token is standard type and can be used as variable type.
	*/
	static inline bool IsVariableStandardType(const Token& InToken) noexcept { return IsVariableStandardType(InToken.GetType()); }
	/*
		Check that given type ID is standard type and can be used as variable type.
	*/
	static inline bool IsVariableStandardType(int TypeID) noexcept { return IsStandardType(TypeID) && TypeID != EStandardTypesID::VOID_ID; }
	/*
		Check that given token is standard type and can be used as function return type.
	*/
	static inline bool IsFunctionReturnStandardType(ETokenType TokenType) noexcept { return IsStandardType(TokenType); }
	/*
		Check that given token is standard type and can be used as function return type.
	*/
	static inline bool IsFunctionReturnStandardType(const Token& InToken) noexcept { return IsFunctionReturnStandardType(InToken.GetType()); }
	/*
		Check that given type ID is standard type and can be used as function return type.
	*/
	static inline bool IsFunctionReturnStandardType(int TypeID) noexcept { return IsStandardType(TypeID); }
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
				TokenType == ETokenType::INLINE 	|| TokenType == ETokenType::VIRTUAL 		|| TokenType == ETokenType::OVERRIDE 	|| 
				TokenType == ETokenType::ABSTRACT 	|| TokenType == ETokenType::FINAL			|| 
				TokenType == ETokenType::DEPRECATED || TokenType == ETokenType::UNIMPLEMENTED;
		// clang-format on
	}
	/*
		Check that given token is modifier.
	*/
	static inline bool IsModifierToken(const Token& InToken) noexcept { return IsModifierToken(InToken.GetType()); }




	/*
		Try to convert token into standard type ID.
	*/
	static inline int GetStandardTypeID(const Token& InToken) noexcept
	{
		// clang-format off
		switch( InToken.GetType() )
		{
		case ETokenType::VOID:		return EStandardTypesID::VOID_ID;
		case ETokenType::UINT8:		return EStandardTypesID::UINT8_ID;
		case ETokenType::UINT16:	return EStandardTypesID::UINT16_ID;
		case ETokenType::UINT32:	return EStandardTypesID::UINT32_ID;
		case ETokenType::UINT64:	return EStandardTypesID::UINT64_ID;
		case ETokenType::INT8:		return EStandardTypesID::INT8_ID;
		case ETokenType::INT16:		return EStandardTypesID::INT16_ID;
		case ETokenType::INT32:		return EStandardTypesID::INT32_ID;
		case ETokenType::INT64:		return EStandardTypesID::INT64_ID;
		case ETokenType::ADDR_T:	return EStandardTypesID::ADDR_T_ID;
		case ETokenType::FLOAT:		return EStandardTypesID::FLOAT_ID;
		case ETokenType::DOUBLE:	return EStandardTypesID::DOUBLE_ID;
		case ETokenType::BOOL:		return EStandardTypesID::BOOL_ID;
		case ETokenType::CHAR:		return EStandardTypesID::CHAR_ID;
		case ETokenType::STRING:	return EStandardTypesID::STRING_ID;
		case ETokenType::VECTOR4D:	return EStandardTypesID::VECTOR4D_ID;
		case ETokenType::VECTOR3D:	return EStandardTypesID::VECTOR3D_ID;
		case ETokenType::VECTOR2D:	return EStandardTypesID::VECTOR2D_ID;
		}
		// clang-format on

		return -1;
	}
	/*
		Try to get function signature ID.
	*/
	static int GetFunctionSignatureID(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo) noexcept;
	/*
		Try to get function signature ID.
	*/
	static int GetFunctionSignatureID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo) noexcept;
	/*
		Try to get function signature as type ID.
	*/
	static int GetFunctionSignatureTypeID(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo) noexcept;
	/*
		Try to get function signature as type ID.
	*/
	static int GetFunctionSignatureTypeID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo) noexcept;
	/*
		Try to get class as type ID.
	*/
	static int GetClassTypeID(const std::string& ClassCompileName, const FProgramInfo& ProgramInfo) noexcept;
	/*
		Try to get user type ID by compile name.
	*/
	static int GetUserTypeID(const std::string& CompileName, const FProgramInfo& ProgramInfo) noexcept;




	/*
		Check that given function signatures are same.
	*/
	static bool AreFunctionSignaturesSame(const FFunctionSignatureInfo& FS1, const FFunctionSignatureInfo& FS2) noexcept;

	/*
		Find first module name declaration in tokens array.
	*/
	static std::string GetFirstModuleName(const std::vector<Token>& Tokens) noexcept;
};
