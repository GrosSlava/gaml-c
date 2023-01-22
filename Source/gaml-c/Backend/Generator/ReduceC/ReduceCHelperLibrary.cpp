// Copyright 2022 - 2023 GrosSlava.

#include "ReduceCHelperLibrary.h"





std::string FReduceCHelperLibrary::GetStandardTypeNameCStr(const std::string& TypeName)
{
	/*
		Table for token type hashing.
		Key - hash of standard type compile name.
		Value - C type naem.
	*/
	static std::unordered_map<size_t, std::string> TypeCache;


	const size_t LTypeHash = std::hash<std::string> {}(TypeName);
	auto LTypeCacheIter = TypeCache.find(LTypeHash);
	if( LTypeCacheIter != TypeCache.end() )
	{
		return LTypeCacheIter->second;
	}

	// clang-format off
#define CASE_TYPE(StandardTypeName, CTypeName) if( TypeName == EStandardTypesName::StandardTypeName ) { TypeCache.insert(std::pair(LTypeHash, CTypeName)); return CTypeName; }

	CASE_TYPE(UINT8_Name, "unsigned char")
	CASE_TYPE(UINT16_Name, "unsigned short int")
	CASE_TYPE(UINT32_Name, "unsigned int")
	CASE_TYPE(UINT64_Name, "unsigned long long int")
	CASE_TYPE(INT8_Name, "signed char")
	CASE_TYPE(INT16_Name, "signed short int")
	CASE_TYPE(INT32_Name, "signed int")
	CASE_TYPE(INT64_Name, "signed long long int")
	CASE_TYPE(ADDR_T_Name, "unsigned long long int")
	CASE_TYPE(FLOAT_Name, "float")
	CASE_TYPE(DOUBLE_Name, "double")
	CASE_TYPE(BOOL_Name, "signed char")
	CASE_TYPE(CHAR_Name, "unsigned short int")
	CASE_TYPE(STRING_Name, "string")
	CASE_TYPE(VECTOR4D_Name, "vector4d")
	CASE_TYPE(VECTOR3D_Name, "vector3d")
	CASE_TYPE(VECTOR2D_Name, "vector2d")

	// clang-format on

	return "";
}





// clang-format off
std::string FReduceCHelperLibrary::GetFunctionSignatureCStr
(
	const std::string& FunctionCompileName, const FFunctionSignatureInfo& FunctionInfo, 
	ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
)
// clang-format on
{
	std::string LResult = "";
	LResult.reserve(128);

	if( FunctionInfo.Returns.empty() )
	{
		LResult += "void ";
	}
	else
	{
		// We can't return pointer to function from function, only lambda. So, recursion will stop.
		LResult += GetVariableDeclarationCStr(FunctionInfo.Returns[0], true, false, false, TargetPlatform, ProgramInfo) + " ";
	}

	if( FunctionInfo.Modifiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
	{
		LResult += GetCallingConventionCStr(FunctionInfo.Modifiers.CallingConvention, TargetPlatform) + " ";
	}

	LResult += FunctionCompileName;

	LResult += "(";
	if( FunctionInfo.Inputs.empty() )
	{
		LResult += "void";
	}
	else
	{
		int i = 0;
		for( const FVariableInfo& LInputInfo : FunctionInfo.Inputs )
		{
			LResult += GetVariableDeclarationCStr(LInputInfo, true, true, true, TargetPlatform, ProgramInfo);
			if( i + 1 < FunctionInfo.Inputs.size() ) LResult += ", ";
			++i;
		}
	}
	LResult += ")";

	return LResult;
}

// clang-format off
std::string FReduceCHelperLibrary::GetFunctionPointerCStr
(
	const std::string& Name, const FFunctionSignatureInfo& FunctionInfo, bool IncludeConst, 
	ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
)
// clang-format on
{
	std::string LResult = "";
	LResult.reserve(128);

	if( FunctionInfo.Returns.empty() )
	{
		LResult += "void ";
	}
	else
	{
		// We can't return pointer to function from function, only lambda. So, recursion will stop.
		LResult += GetVariableDeclarationCStr(FunctionInfo.Returns[0], true, false, false, TargetPlatform, ProgramInfo);
	}

	LResult += "(";
	if( FunctionInfo.Modifiers.CallingConvention != EFunctionCallingConvention::DEFAULT )
	{
		LResult += GetCallingConventionCStr(FunctionInfo.Modifiers.CallingConvention, TargetPlatform) + " ";
	}
	LResult += "*";
	if( FunctionInfo.Modifiers.IsConst && IncludeConst )
	{
		LResult += "const";
		if( !Name.empty() ) LResult += " ";
	}
	if( !Name.empty() )
	{
		LResult += Name;
	}
	LResult += ") (";
	if( FunctionInfo.Inputs.empty() )
	{
		LResult += "void";
	}
	else
	{
		int i = 0;
		for( const FVariableInfo& LInputInfo : FunctionInfo.Inputs )
		{
			LResult += GetVariableDeclarationCStr(LInputInfo, true, false, true, TargetPlatform, ProgramInfo);
			if( i + 1 < FunctionInfo.Inputs.size() ) LResult += ", ";
			++i;
		}
	}
	LResult += ")";

	return LResult;
}

// clang-format off
std::string FReduceCHelperLibrary::GetFunctionImplementationBodyCStr
(
	const std::string& FunctionCompileName, const FCompilingFunctionInfo& FunctionCompileInfo, 
	const FProgramInfo& ProgramInfo
)
// clang-format on
{
	//return FunctionCompileInfo.FunctionCodeTree.GenerateCode(std::make_shared<ReduceC_ASTCodeGenFactory>(), ProgramInfo);
	return "";
}





// clang-format off
std::string FReduceCHelperLibrary::GetClassDeclarationCStr
(
	const std::string& ClassCompileName, const FClassInfo& ClassInfo, 
	ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
)
// clang-format on
{
	std::string LResult = "";

	LResult += "struct " + ClassCompileName;
	LResult += "\n{\n";
	LResult += GetClassVariablesCStr(ClassInfo, TargetPlatform, ProgramInfo); // tabs and \n are included
	LResult += "};";

	return LResult;
}

std::string FReduceCHelperLibrary::GetClassVariablesCStr(const FClassInfo& ClassInfo, ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo)
{
	std::string LResult = "";
	LResult.reserve(ClassInfo.Variables.size() * 64);

	for( const std::pair<std::string, FVariableInfo>& LVariableInfo : ClassInfo.Variables )
	{
		LResult += "\t" + GetVariableDeclarationCStr(LVariableInfo.second, false, true, false, TargetPlatform, ProgramInfo) + ";\n";
	}

	return LResult;
}





// clang-format off
std::string FReduceCHelperLibrary::GetVariableDeclarationCStr
(
	const FVariableInfo& VariableInfo, bool IncludeConst, bool IncludeName, bool IsFunctionArgument, 
	ETargetPlatform TargetPlatform, const FProgramInfo& ProgramInfo
)
// clang-format on
{
	std::string LResult = "";
	LResult.reserve(64);


	switch( VariableInfo.TypeInfo.TypeKind )
	{
	case ETypeKind::Standard:
	{
		if( VariableInfo.Modifiers.IsConst && IncludeConst ) LResult += "const ";

		LResult += GetStandardTypeNameCStr(VariableInfo.TypeInfo.TypeCompileName);
		// clang-format off
		if( 
			IsFunctionArgument && 
			((VariableInfo.Modifiers.IsConst && VariableInfo.TypeInfo.TypeCompileName == EStandardTypesName::STRING_Name) || VariableInfo.Modifiers.IsMutable)
		)
		// clang-format on
		{
			LResult += "*";
		}

		if( !VariableInfo.VariableName.empty() && IncludeName )
		{
			LResult += " ";
			LResult += VariableInfo.VariableName;
		}

		break;
	}
	case ETypeKind::Class:
	{
		const std::string& LClassCompileName = VariableInfo.TypeInfo.TypeCompileName;
		const FClassInfo& LClassInfo = ProgramInfo.Classes.at(LClassCompileName);

		if( VariableInfo.Modifiers.IsConst && IncludeConst ) LResult += "const ";

		if( LClassInfo.ClassType == EClassType::Enum )
		{
			LResult += GetStandardTypeNameCStr(LClassInfo.ParentTypesInfo[0].TypeCompileName);
		}
		else
		{
			LResult += "struct " + LClassCompileName;
		}

		if( IsFunctionArgument && VariableInfo.Modifiers.IsMutable )
		{
			LResult += "*";
		}
		else if( LClassInfo.ClassType == EClassType::Interface || LClassInfo.ClassType == EClassType::Object || LClassInfo.ClassType == EClassType::Component )
		{
			LResult += "*";
		}
		else if( IsFunctionArgument && VariableInfo.Modifiers.IsConst && LClassInfo.ClassType == EClassType::Struct )
		{
			LResult += "*";
		}

		if( !VariableInfo.VariableName.empty() && IncludeName )
		{
			LResult += " ";
			LResult += VariableInfo.VariableName;
		}

		break;
	}
	case ETypeKind::FunctionPointer:
	{
		const FFunctionSignatureInfo& LFunctionSignature = ProgramInfo.Functions.at(VariableInfo.TypeInfo.TypeCompileName).SignatureInfo;

		LResult += GetFunctionPointerCStr(IncludeName ? VariableInfo.VariableName : "", LFunctionSignature, IncludeConst, TargetPlatform, ProgramInfo);
		break;
	}
	case ETypeKind::AnyPointer:
	{
		if( VariableInfo.Modifiers.IsConst && IncludeConst ) LResult += "const ";

		LResult += "void*";

		if( !VariableInfo.VariableName.empty() && IncludeName )
		{
			LResult += " ";
			LResult += VariableInfo.VariableName;
		}
	}
	}

	return LResult;
}