// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Token/Token.h"
#include "ProgramSymbols.h"




/*
	Separetor for compile names.
*/
const static std::string NameSeparator = "_0";

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
		ETokenType LLeftTokenType = ETokenType::IDENTIFIER;
		ETokenType LRightTokenType = ETokenType::IDENTIFIER;

		if( IsOpenPairToken(TokenA) )
		{
			LLeftTokenType = TokenA.GetType();
		}
		else if( IsClosePairToken(TokenA) )
		{
			LRightTokenType = TokenA.GetType();
		}

		if( IsOpenPairToken(TokenB) )
		{
			LLeftTokenType = TokenB.GetType();
		}
		else if( IsClosePairToken(TokenB) )
		{
			LRightTokenType = TokenB.GetType();
		}

		// check that both of tokens set.
		if( LLeftTokenType == ETokenType::IDENTIFIER || LRightTokenType == ETokenType::IDENTIFIER ) return false;

		// clang-format off
		return	(LLeftTokenType == ETokenType::LBRA && LRightTokenType == ETokenType::RBRA) || 
				(LLeftTokenType == ETokenType::LPAR && LRightTokenType == ETokenType::RPAR) ||
				(LLeftTokenType == ETokenType::LSQR && LRightTokenType == ETokenType::RSQR) || 
				(LLeftTokenType == ETokenType::LTRI && LRightTokenType == ETokenType::RTRI);
		// clang-format on
	}




	/*
		Construct class compile name.

		@param ModuleName - name of class module.
		@param ClassName - class original name.
		@param TemplateArgumentNames - array of template arguments if class instantiated from template.
		@return constructed class name.
	*/
	static inline std::string GetClassCompileName(const std::string& ModuleName, const std::string& ClassName, const std::vector<std::string>& TemplateArgumentNames) noexcept
	{
		if( ClassName.empty() ) return "";


		std::string LClassCompileName = "";

		if( !ModuleName.empty() )
		{
			LClassCompileName += ModuleName + NameSeparator;
		}

		LClassCompileName += ClassName;
		for( const std::string& LArgumentStr : TemplateArgumentNames )
		{
			LClassCompileName += NameSeparator + LArgumentStr;
		}

		return LClassCompileName;
	}
	/*
		Construct function compile name.

		@param ModuleName - name of function module.
		@param ClassName - class original name.
		@param OriginalName - function original name.
		@param IsConst - function const overload.
		@param ArgumentTypeNames - array of function argument types names.
		@return constructed function name.
	*/
	// clang-format off
	static inline std::string GetFunctionCompileName(
														const std::string& ModuleName, const std::string& ClassName, const std::string& OriginalName, 
														bool IsConst, const std::vector<std::string>& ArgumentTypeNames
													) noexcept
	// clang-format on
	{
		if( OriginalName.empty() ) return "";


		std::string LFunctionCompileName = "";

		if( IsConst )
		{
			LFunctionCompileName += "const" + NameSeparator;
		}

		if( !ModuleName.empty() )
		{
			LFunctionCompileName += ModuleName + NameSeparator;
		}

		if( !ClassName.empty() )
		{
			LFunctionCompileName += ClassName + NameSeparator;
		}

		LFunctionCompileName += OriginalName;
		for( const std::string& LArgumentTypeStr : ArgumentTypeNames )
		{
			LFunctionCompileName += NameSeparator + LArgumentTypeStr;
		}

		return LFunctionCompileName;
	}
	/*
		Construct function compile name.

		@param ModuleName - name of function module.
		@param ClassName - class original name.
		@param OriginalName - function original name.
		@param FunctionSignatureInfo - function signature info.
		@param ProgramInfo - current program info.
		@return constructed function name.
	*/
	// clang-format off
	static inline std::string GetFunctionCompileName(	
														const std::string& ModuleName, const std::string& ClassName, const std::string& OriginalName,
														const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo
													) noexcept
	// clang-format on
	{
		std::vector<std::string> LArgumentsNames;

		for( const FVariableInfo& LVariableInfo : FunctionSignatureInfo.Inputs )
		{
			// it is finite recursion with function signature as argument
			std::string LTypeName = GetTypeName(LVariableInfo.TypeID, ProgramInfo);
			if( LTypeName.empty() ) return "";

			LArgumentsNames.push_back(LTypeName);
		}

		return GetFunctionCompileName(ModuleName, ClassName, OriginalName, FunctionSignatureInfo.Modifiers.IsConst, LArgumentsNames);
	}
	/*
		Construct static variable compile name.

		@param ModuleName - name of static variable module.
		@param ClassName - class original name.
		@param OriginalName - static variable original name.
		@return constructed static variable name.
	*/
	static inline std::string GetStaticVariableCompileName(const std::string& ModuleName, const std::string& ClassName, const std::string& OriginalName) noexcept
	{
		if( OriginalName.empty() ) return "";


		std::string VariableCompileName = "";

		if( !ModuleName.empty() )
		{
			VariableCompileName += ModuleName + NameSeparator;
		}
		if( !ClassName.empty() )
		{
			VariableCompileName += ClassName + NameSeparator;
		}

		VariableCompileName += OriginalName;

		return VariableCompileName;
	}
	/*
		Construct static variable compile name.

		@param FunctionCompileName - compile name of function where declared variable.
		@param OriginalName - static variable original name.
		@return constructed static variable name.
	*/
	static inline std::string GetStaticVariableCompileName(const std::string& FunctionCompileName, const std::string& OriginalName) noexcept
	{
		if( OriginalName.empty() ) return "";


		std::string VariableCompileName = "";

		if( !FunctionCompileName.empty() )
		{
			VariableCompileName += FunctionCompileName + NameSeparator;
		}

		VariableCompileName += OriginalName;

		return VariableCompileName;
	}
	/*
		Construct type alias compile name.

		@param ModuleName - name of alias module.
		@param ClassName - class original name.
		@param FunctionName - function original name.
		@param AliasName - alias original name.
		@return constructed alias name.
	*/
	static inline std::string GetTypeAliasCompileName(const std::string& ModuleName, const std::string& ClassName, const std::string& FunctionName, const std::string& AliasName) noexcept
	{
		if( AliasName.empty() ) return "";


		std::string LAliasCompileName = "";

		if( !ModuleName.empty() )
		{
			LAliasCompileName += ModuleName + NameSeparator;
		}
		if( !ClassName.empty() )
		{
			LAliasCompileName += ClassName + NameSeparator;
		}
		if( !FunctionName.empty() )
		{
			LAliasCompileName += FunctionName + NameSeparator;
		}

		LAliasCompileName += AliasName;

		return LAliasCompileName;
	}
	/*
		Construct template compile name.

		@param ModuleName - name of template module.
		@param ClassName - class original name.
		@param FunctionName - function original name.
		@param TemplateCodeName - template original name.
		@param TemplateArgumentNames - array of template arguments names.
		@return constructed template name.
	*/
	// clang-format off
	static inline std::string GetTemplateCodeCompileName(
															const std::string& ModuleName, const std::string& ClassName, const std::string& FunctionName, 
															const std::string& TemplateCodeName, const std::vector<std::string>& TemplateArgumentNames
														) noexcept
	// clang-format on
	{
		if( TemplateCodeName.empty() ) return "";


		std::string LTemplateCodeName = "";

		if( !ModuleName.empty() )
		{
			LTemplateCodeName += ModuleName + NameSeparator;
		}
		if( !ClassName.empty() )
		{
			LTemplateCodeName += ClassName + NameSeparator;
		}
		if( !FunctionName.empty() )
		{
			LTemplateCodeName += FunctionName + NameSeparator;
		}

		LTemplateCodeName += TemplateCodeName;
		for( const std::string& LArgumentStr : TemplateArgumentNames )
		{
			LTemplateCodeName += NameSeparator + LArgumentStr;
		}

		return LTemplateCodeName;
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
	static inline int GetFunctionSignatureID(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo) noexcept
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
	/*
		Try to get function signature ID.
	*/
	static inline int GetFunctionSignatureID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo) noexcept
	{
		auto LFunctionInfoIterator = ProgramInfo.Functions.find(FunctionCompileName);
		if( LFunctionInfoIterator == ProgramInfo.Functions.end() ) return -1;

		return GetFunctionSignatureID(LFunctionInfoIterator->second, ProgramInfo);
	}
	/*
		Try to get function signature as type ID.
	*/
	static inline int GetFunctionSignatureTypeID(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo) noexcept
	{
		const int LFunctionSignatureID = GetFunctionSignatureID(FunctionSignatureInfo, ProgramInfo);
		if( LFunctionSignatureID < 0 ) return -1;

		for( int i = 0; i < ProgramInfo.TypesMap.size(); ++i )
		{
			if( ProgramInfo.TypesMap[i].PathSwitch == ETypePathSwitch::EFunctionSignature && ProgramInfo.TypesMap[i].FunctionSignaturePath.FunctionSignatureID == LFunctionSignatureID )
			{
				return i;
			}
		}

		return -1;
	}
	/*
		Try to get function signature as type ID.
	*/
	static inline int GetFunctionSignatureTypeID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo) noexcept
	{
		auto LFunctionInfoIterator = ProgramInfo.Functions.find(FunctionCompileName);
		if( LFunctionInfoIterator == ProgramInfo.Functions.end() ) return -1;

		return GetFunctionSignatureTypeID(LFunctionInfoIterator->second, ProgramInfo);
	}
	/*
		Try to get class as type ID.
	*/
	static inline int GetClassTypeID(const std::string& ClassCompileName, const FProgramInfo& ProgramInfo) noexcept
	{
		for( int i = 0; i < ProgramInfo.TypesMap.size(); ++i )
		{
			if( ProgramInfo.TypesMap[i].PathSwitch == ETypePathSwitch::EClass && ProgramInfo.TypesMap[i].ClassPath.ClassCompileName == ClassCompileName )
			{
				return i;
			}
		}

		return -1;
	}
	/*
		Try to get type as string.
	*/
	static inline std::string GetTypeName(int TypeID, const FProgramInfo& ProgramInfo) noexcept
	{
		if( TypeID < 0 || TypeID >= ProgramInfo.TypesMap.size() ) return "";


		const FUserTypePath& LTypePath = ProgramInfo.TypesMap[TypeID];

		switch( LTypePath.PathSwitch )
		{
		case ETypePathSwitch::EStandard:
		{
			// clang-format off
			switch( static_cast<EStandardTypesID>(TypeID) )
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
		}
		case ETypePathSwitch::EClass:
		{
			return LTypePath.ClassPath.ClassCompileName;
		}
		case ETypePathSwitch::EFunctionSignature:
		{
			const FFunctionSignatureInfo& LFunctionSignature = ProgramInfo.FunctionSignaturesTypesMap[LTypePath.FunctionSignaturePath.FunctionSignatureID];
			return GetFunctionCompileName("", "", "fsign", LFunctionSignature, ProgramInfo);
		}
		}

		return "";
	}




	/*
		Check that given token is modifier.
	*/
	static inline bool IsModifierToken(ETokenType TokenType) noexcept
	{
		// clang-format off
		return	TokenType == ETokenType::EXTERN_C || 
				TokenType == ETokenType::CDECL || TokenType == ETokenType::STDCALL || TokenType == ETokenType::FASTCALL || TokenType == ETokenType::THISCALL || 
				TokenType == ETokenType::CONST || TokenType == ETokenType::MUTABLE || TokenType == ETokenType::STATIC ||  
				TokenType == ETokenType::INLINE || TokenType == ETokenType::VIRTUAL || TokenType == ETokenType::OVERRIDE || 
				TokenType == ETokenType::ABSTRACT || TokenType == ETokenType::FINAL	|| 
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
	static inline bool AreFunctionSignaturesSame(const FFunctionSignatureInfo& FS1, const FFunctionSignatureInfo& FS2) noexcept
	{
		if( FS1.Inputs.size() != FS2.Inputs.size() ) return false;

		for( int i = 0; i < FS1.Inputs.size(); ++i )
		{
			if( FS1.Inputs[i].TypeID != FS2.Inputs[i].TypeID ) return false;
		}

		if( FS1.Modifiers.IsConst != FS2.Modifiers.IsConst ) return false;

		return true;
	}

	/*
		Find first module name declaration in tokens array.
	*/
	static inline std::string GetFirstModuleName(const std::vector<Token>& Tokens) noexcept
	{
		if( Tokens.empty() ) return "";

		int ModuleNameSearchIndex = 0;
		bool LIsModule = false;

		if( Tokens[ModuleNameSearchIndex].GetType() == ETokenType::DEPRECATED )
		{
			++ModuleNameSearchIndex;
		}
		if( Tokens.size() <= ModuleNameSearchIndex ) return "";
		if( Tokens[ModuleNameSearchIndex].GetType() == ETokenType::STATIC )
		{
			++ModuleNameSearchIndex;
		}
		if( Tokens.size() <= ModuleNameSearchIndex ) return "";

		if( Tokens[ModuleNameSearchIndex].GetType() == ETokenType::MODULE )
		{
			++ModuleNameSearchIndex;
			LIsModule = true;
		}
		if( Tokens.size() <= ModuleNameSearchIndex ) return "";

		if( !LIsModule ) return "";

		std::string LModuleName = "";
		while( Tokens[ModuleNameSearchIndex].GetType() != ETokenType::SEMICOLON )
		{
			LModuleName += Tokens[ModuleNameSearchIndex].GetLexeme();
			++ModuleNameSearchIndex;
			if( Tokens.size() <= ModuleNameSearchIndex ) return "";
		}

		return LModuleName;
	}
};
