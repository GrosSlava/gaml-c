// Copyright 2022 GrosSlava.

#pragma once

#include "../Token/Token.h"
#include "ProgramSymbols.h"

#include <string>




/*
	Helper library for common parser operations.
*/
struct FParserHelperLibrary
{
public:

	static inline bool IsOpenPairToken(const Token& InToken) noexcept
	{
		const ETokenType LTokenType = InToken.GetType();

		return LTokenType == ETokenType::LBRA || LTokenType == ETokenType::LPAR || LTokenType == ETokenType::LSQR || LTokenType == ETokenType::LTRI;
	}

	static inline bool IsClosePairToken(const Token& InToken) noexcept
	{
		const ETokenType LTokenType = InToken.GetType();

		return LTokenType == ETokenType::RBRA || LTokenType == ETokenType::RPAR || LTokenType == ETokenType::RSQR || LTokenType == ETokenType::RTRI;
	}

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

		if( LLeftTokenType == ETokenType::IDENTIFIER || LRightTokenType == ETokenType::IDENTIFIER ) return false;
		

		return	(LLeftTokenType == ETokenType::LBRA && LRightTokenType == ETokenType::RBRA) || 
				(LLeftTokenType == ETokenType::LPAR && LRightTokenType == ETokenType::RPAR) ||
				(LLeftTokenType == ETokenType::LSQR && LRightTokenType == ETokenType::RSQR) || 
				(LLeftTokenType == ETokenType::LTRI && LRightTokenType == ETokenType::RTRI);
	}



	static inline std::string GetClassCompileName(const std::string& ModuleName, const std::string& ClassName, const std::vector<std::string>& TemplateArgumentNames)
	{
		if( ClassName.empty() ) return "";


		std::string LClassCompileName = "";

		if( !ModuleName.empty() )
		{
			LClassCompileName += ModuleName + "_";
		}

		LClassCompileName += ClassName;
		for( const std::string& LArgumentStr : TemplateArgumentNames )
		{
			LClassCompileName += "_" + LArgumentStr;
		}

		return LClassCompileName;
	}

	static inline std::string GetFunctionCompileName(
														const std::string& ModuleName, const std::string& ClassName, const std::string& OriginalName, 
														bool IsConst, const std::vector<std::string>& ArgumentTypeNames
													)
	{
		if( OriginalName.empty() ) return "";


		std::string LFunctionCompileName = "";

		if( IsConst )
		{
			LFunctionCompileName += "const_";
		}

		if( !ModuleName.empty() )
		{
			LFunctionCompileName += ModuleName + "_";
		}

		if( !ClassName.empty() )
		{
			LFunctionCompileName += ClassName + "_";
		}

		LFunctionCompileName += OriginalName;
		for( const std::string& LArgumentTypeStr : ArgumentTypeNames )
		{
			LFunctionCompileName += "_" + LArgumentTypeStr;
		}

		return LFunctionCompileName;
	}

	static inline std::string GetFunctionCompileName(	
														const std::string& ModuleName, const std::string& ClassName, const std::string& OriginalName,
														const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo
													)
	{
		std::vector<std::string> LArgumentsNames;

		for( const FVariableInfo& LVariableInfo : FunctionSignatureInfo.Inputs )
		{
			// it is finite recursion with function signature as argument
			std::string LTypeName = GetTypeName(LVariableInfo.TypeID, ProgramInfo);
			if( LTypeName.empty() ) return "";

			LArgumentsNames.push_back(LTypeName);
		}

		return GetFunctionCompileName(ModuleName, ClassName, OriginalName, FunctionSignatureInfo.IsConst, LArgumentsNames);
	}

	static inline std::string GetLambdaCompileName(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo)
	{
		return GetFunctionCompileName("", "", "lam", FunctionSignatureInfo, ProgramInfo);
	}

	static inline std::string GetLambdaFunctionCompileName(const std::string& ModuleName, const FFunctionSignatureInfo& FunctionSignatureInfo, int LambdaID, const FProgramInfo& ProgramInfo)
	{
		const std::string LLambdaFunctionPureName = "lam_f" + std::to_string(LambdaID);
		return GetFunctionCompileName(ModuleName, "", LLambdaFunctionPureName, FunctionSignatureInfo, ProgramInfo);
	}

	static inline std::string GetLambdaContextInfoCompileName(const std::string& ModuleName, const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo)
	{
		return GetFunctionCompileName(ModuleName, "", "lam_c", FunctionSignatureInfo, ProgramInfo);
	}

	static inline std::string GetVariableCompileName(const std::string& ModuleName, const std::string& ClassName, const std::string& OriginalName)
	{
		if( OriginalName.empty() ) return "";


		std::string VariableCompileName = "";

		if( !ModuleName.empty() )
		{
			VariableCompileName += ModuleName + "_";
		}

		if( !ClassName.empty() )
		{
			VariableCompileName += ClassName + "_";
		}

		VariableCompileName += OriginalName;

		return VariableCompileName;
	}

	static std::string GetTypeAliasCompileName(const std::string& ModuleName, const std::string& ClassName, const std::string& AliasName)
	{
		if( AliasName.empty() ) return "";


		std::string LAliasCompileName = "";

		if( !ModuleName.empty() )
		{
			LAliasCompileName += ModuleName + "_";
		}
		if( !ClassName.empty() )
		{
			LAliasCompileName += ClassName + "_";
		}

		LAliasCompileName += AliasName;

		return LAliasCompileName;
	}



	static inline bool IsStandardType(ETokenType TokenType) noexcept
	{
		return	TokenType == ETokenType::VOID		|| 
				TokenType == ETokenType::UINT8		|| TokenType == ETokenType::UINT16		|| TokenType == ETokenType::UINT32	|| TokenType == ETokenType::UINT64	||
				TokenType == ETokenType::INT8		|| TokenType == ETokenType::INT16		|| TokenType == ETokenType::INT32	|| TokenType == ETokenType::INT64	|| 
				TokenType == ETokenType::ADDR_T		|| TokenType == ETokenType::FLOAT		|| TokenType == ETokenType::DOUBLE	|| TokenType == ETokenType::BOOL	|| 
				TokenType == ETokenType::CHAR		|| TokenType == ETokenType::STRING		||
				TokenType == ETokenType::VECTOR4D	|| TokenType == ETokenType::VECTOR3D	|| TokenType == ETokenType::VECTOR2D;
	}

	static inline bool IsStandardType(const Token& InToken) noexcept
	{
		return IsStandardType(InToken.GetType());
	}

	static inline bool IsStandardType(int TypeID) noexcept 
	{ 
		return TypeID >= 0 && TypeID < EStandardTypesID::StandardTypesID_MAX;
	}

	static inline bool IsVariableStandardType(ETokenType TokenType) noexcept 
	{ 
		return IsStandardType(TokenType) && TokenType != ETokenType::VOID;
	}

	static inline bool IsVariableStandardType(const Token& InToken) noexcept 
	{ 
		return IsVariableStandardType(InToken.GetType());
	}

	static inline bool IsVariableStandardType(int TypeID) noexcept 
	{ 
		return IsStandardType(TypeID) && TypeID != EStandardTypesID::VOID_ID; 
	}

	static inline bool IsFunctionReturnStandardType(ETokenType TokenType) noexcept
	{ 
		return IsStandardType(TokenType);
	}

	static inline bool IsFunctionReturnStandardType(const Token& InToken) noexcept
	{ 
		return IsStandardType(InToken);
	}

	static inline bool IsFunctionReturnStandardType(int TypeID) noexcept
	{ 
		return IsStandardType(TypeID); 
	}



	static inline int GetStandardTypeID(const Token& InToken) noexcept
	{
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

		return -1;
	}

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

	static inline int GetFunctionSignatureID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo)
	{
		auto LFunctionInfoIterator = ProgramInfo.Functions.find(FunctionCompileName);
		if( LFunctionInfoIterator == ProgramInfo.Functions.end() ) return -1;

		return GetFunctionSignatureID(LFunctionInfoIterator->second, ProgramInfo);
	}

	static inline int GetFunctionSignatureTypeID(const FFunctionSignatureInfo& FunctionSignatureInfo, const FProgramInfo& ProgramInfo)
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

	static inline int GetFunctionSignatureTypeID(const std::string& FunctionCompileName, const FProgramInfo& ProgramInfo)
	{
		auto LFunctionInfoIterator = ProgramInfo.Functions.find(FunctionCompileName);
		if( LFunctionInfoIterator == ProgramInfo.Functions.end() ) return -1;

		return GetFunctionSignatureTypeID(LFunctionInfoIterator->second, ProgramInfo);
	}

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

	static inline std::string GetTypeName(int TypeID, const FProgramInfo& ProgramInfo)
	{
		if( TypeID < 0 || TypeID >= ProgramInfo.TypesMap.size() ) return "";


		const FUserTypePath& LTypePath = ProgramInfo.TypesMap[TypeID];

		switch( LTypePath.PathSwitch )
		{
		case ETypePathSwitch::EStandard:
		{
			switch( (EStandardTypesID)TypeID )
			{
			case EStandardTypesID::VOID_ID:		return "void";
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

	
	
	static inline bool IsFunctionLeftCpecifier(ETokenType TokenType) noexcept
	{
		return	TokenType == ETokenType::EXTERN_C || TokenType == ETokenType::INLINE || TokenType == ETokenType::VIRTUAL ||
				TokenType == ETokenType::CDECL || TokenType == ETokenType::STDCALL || TokenType == ETokenType::FASTCALL || TokenType == ETokenType::THISCALL;
				
	}

	static inline bool IsFunctionLeftCpecifier(const Token& InToken) noexcept
	{
		return IsFunctionLeftCpecifier(InToken.GetType());
	}

	static inline bool IsFunctionRightCpecifier(ETokenType TokenType) noexcept
	{
		return TokenType == ETokenType::CONST || TokenType == ETokenType::OVERRIDE || TokenType == ETokenType::ABSTRACT || TokenType == ETokenType::FINAL || TokenType == ETokenType::UNIMPLEMENTED;
	}

	static inline bool IsFunctionRightCpecifier(const Token& InToken) noexcept
	{
		return IsFunctionRightCpecifier(InToken.GetType());
	}

	static inline bool IsFunctionArgumentCpecifier(ETokenType TokenType) noexcept
	{
		return TokenType == ETokenType::CONST || TokenType == ETokenType::MUTABLE || IsVariableStandardType(TokenType);
	}

	static inline bool IsFunctionArgumentCpecifier(const Token& InToken) noexcept
	{
		return IsFunctionArgumentCpecifier(InToken.GetType());
	}

	static inline bool AreFunctionSignaturesSame(const FFunctionSignatureInfo& FS1, const FFunctionSignatureInfo& FS2) noexcept
	{
		if( FS1.Inputs.size() != FS2.Inputs.size() ) return false;

		for( int i = 0; i < FS1.Inputs.size(); ++i)
		{
			if( FS1.Inputs[i].TypeID != FS2.Inputs[i].TypeID ) return false;
		}

		if( FS1.IsConst != FS2.IsConst ) return false;

		return true;
	}



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
