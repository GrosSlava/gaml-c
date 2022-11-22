// Copyright 2022 GrosSlava.

#include "ReduceCGenerator.h"





void ReduceCGenerator::ProcessGeneration(const FProgramInfo& ProgramInfo)
{
	GeneratedCodeStr = "/*\n";
	GeneratedCodeStr += FGeneratorHelperLibrary::GetGenerationTime() + "\n";
	GeneratedCodeStr += FGeneratorHelperLibrary::GetCompilerIdentifier() + "\n";
	GeneratedCodeStr += "*/\n\n\n";


	GeneratedCodeStr += "/*.......................................Types declaration.......................................*/\n\n";
	for( const std::pair<std::string, FClassInfo>& LClassInfo : ProgramInfo.Classes )
	{
		GeneratedCodeStr += "struct " + LClassInfo.first + ";\n";
	}
	GeneratedCodeStr += "\n";

	for( const std::pair<std::string, FClassInfo>& LClassInfo : ProgramInfo.Classes )
	{
		GeneratedCodeStr += GetClassDeclarationCStr(LClassInfo.first, LClassInfo.second, ProgramInfo);
		GeneratedCodeStr += "\n\n";
	}
	GeneratedCodeStr += "/*...............................................................................................*/\n\n";


	GeneratedCodeStr += "/*..................................Global variables declaration.................................*/\n\n";
	for( const FCompilingVariableInfo& LStaticVariableInfo : ProgramInfo.CompilingStaticVariables )
	{
		if( !LStaticVariableInfo.IsInThisModule ) GeneratedCodeStr += "extern ";

		GeneratedCodeStr += GetVariableDeclarationCStr(LStaticVariableInfo.VariableInfo, false, true, false, ProgramInfo) + ";\n";
	}
	GeneratedCodeStr += "\n";
	GeneratedCodeStr += "/*...............................................................................................*/\n\n";


	GeneratedCodeStr += "/*.....................................Functions declaration.....................................*/\n\n";
	for( const std::pair<std::string, FFunctionSignatureInfo>& LFunctionInfo : ProgramInfo.Functions )
	{
		if( ProgramInfo.CompilingFunctionsAST.find(LFunctionInfo.first) == ProgramInfo.CompilingFunctionsAST.end() )
		{
			GeneratedCodeStr += "extern ";
		}
		GeneratedCodeStr += GetFunctionSignatureCStr(LFunctionInfo.first, LFunctionInfo.second, ProgramInfo) + ";\n";
	}
	GeneratedCodeStr += "\n";
	GeneratedCodeStr += "/*...............................................................................................*/\n\n";


	GeneratedCodeStr += "/*...................................Functions implementation....................................*/\n\n";
	for( const std::pair<std::string, FCompilingFunctionInfo>& LCompilingFunctionInfo : ProgramInfo.CompilingFunctionsAST )
	{
		GeneratedCodeStr += GetFunctionSignatureCStr(LCompilingFunctionInfo.first, ProgramInfo.Functions.at(LCompilingFunctionInfo.first), ProgramInfo);
		GeneratedCodeStr += "\n";
		GeneratedCodeStr += "{\n";
		GeneratedCodeStr += GetFunctionImplementationBodyCStr(LCompilingFunctionInfo.first, LCompilingFunctionInfo.second, ProgramInfo);
		GeneratedCodeStr += "\n}";
		GeneratedCodeStr += "\n\n";
	}
	GeneratedCodeStr += "/*................................................................................................*/\n\n";
}





std::string ReduceCGenerator::GetClassDeclarationCStr(const std::string& ClassCompileName, const FClassInfo& ClassInfo, const FProgramInfo& ProgramInfo) const
{
	std::string LResult = "";

	LResult += "struct " + ClassCompileName;
	LResult += "\n";
	LResult += "{\n";
	LResult += GetClassVariablesCStr(ClassInfo, ProgramInfo); // tabs are included
	LResult += "\n};";

	return LResult;
}

std::string ReduceCGenerator::GetFunctionSignatureCStr(const std::string& FunctionCompileName, const FFunctionSignatureInfo& FunctionInfo, const FProgramInfo& ProgramInfo) const
{
	std::string LResult = "";


	FVariableInfo LReturnVariableInfo;
	LReturnVariableInfo.Modifiers.IsConst = FunctionInfo.Return.Modifiers.IsConst;
	LReturnVariableInfo.TypeID = FunctionInfo.Return.TypeID;

	// We can't return pointer to function from function, only lambda. So, recursion will stop.
	LResult += GetVariableDeclarationCStr(LReturnVariableInfo, true, false, false, ProgramInfo) + " ";

	if( FunctionInfo.Modifiers.CallingConvention != EFunctionCallingConvention::DEFAULT ) LResult += GetCallingConventionCStr(FunctionInfo.Modifiers.CallingConvention) + " ";

	LResult += FunctionCompileName;

	LResult += "(";
	if( FunctionInfo.Inputs.empty() )
	{
		LResult += GetStandardTypeNameCStr(EStandardTypesID::VOID_ID);
	}
	else
	{
		for( size_t i = 0; i < FunctionInfo.Inputs.size(); ++i )
		{
			LResult += GetVariableDeclarationCStr(FunctionInfo.Inputs[i], true, true, true, ProgramInfo);
			if( i + 1 < FunctionInfo.Inputs.size() ) LResult += ", ";
		}
	}

	LResult += ")";

	return LResult;
}

std::string ReduceCGenerator::GetFunctionImplementationBodyCStr(const std::string& FunctionCompileName, const FCompilingFunctionInfo& FunctionCompileInfo, const FProgramInfo& ProgramInfo) const
{
	//TODO

	return std::string();
}





std::string ReduceCGenerator::GetVariableDeclarationCStr(const FVariableInfo& VariableInfo, bool IncludeConst, bool IncludeName, bool IsFunctionArgument, const FProgramInfo& ProgramInfo) const
{
	std::string LResult = "";


	const FUserTypePath& LTypePath = ProgramInfo.TypesMap[VariableInfo.TypeID];
	switch( LTypePath.PathSwitch )
	{
	case ETypePathSwitch::EStandard:
	{
		if( VariableInfo.Modifiers.IsConst && IncludeConst ) LResult += "const ";

		LResult += GetStandardTypeNameCStr(VariableInfo.TypeID);
		if( 
			IsFunctionArgument && 
			((VariableInfo.Modifiers.IsConst && VariableInfo.TypeID == EStandardTypesID::STRING_ID) || VariableInfo.Modifiers.IsMutable)
		  )
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
	case ETypePathSwitch::EClass:
	{
		const std::string& LClassCompileName = LTypePath.ClassPath.ClassCompileName;
		const FClassInfo& LClassInfo = ProgramInfo.Classes.at(LClassCompileName);

		if( VariableInfo.Modifiers.IsConst && IncludeConst ) LResult += "const ";

		if( LClassInfo.ClassType == EClassType::Enum )
		{
			LResult += GetStandardTypeNameCStr(EStandardTypesID::UINT32_ID);
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
	case ETypePathSwitch::EFunctionSignature:
	{
		const FFunctionSignatureInfo& LFunctionSignature = ProgramInfo.FunctionSignaturesTypesMap[LTypePath.FunctionSignaturePath.FunctionSignatureID];

		LResult += GetFunctionPointerCStr(IncludeName ? VariableInfo.VariableName : "", LFunctionSignature, IncludeConst, ProgramInfo);
		break;
	}
	}


	return LResult;
}

std::string ReduceCGenerator::GetStandardTypeNameCStr(int TypeID) const
{
	switch( (EStandardTypesID)TypeID )
	{
	case EStandardTypesID::VOID_ID: return "void";
	case EStandardTypesID::UINT8_ID: return "unsigned char";
	case EStandardTypesID::UINT16_ID: return "unsigned short int";
	case EStandardTypesID::UINT32_ID: return "unsigned int";
	case EStandardTypesID::UINT64_ID: return "unsigned long long int";
	case EStandardTypesID::INT8_ID: return "signed char";
	case EStandardTypesID::INT16_ID: return "signed short int";
	case EStandardTypesID::INT32_ID: return "signed int";
	case EStandardTypesID::INT64_ID: return "signed long long int";
	case EStandardTypesID::ADDR_T_ID: return "signed long long int";
	case EStandardTypesID::FLOAT_ID: return "float";
	case EStandardTypesID::DOUBLE_ID: return "double";
	case EStandardTypesID::BOOL_ID: return "signed char";
	case EStandardTypesID::CHAR_ID: return "unsigned short int";
	case EStandardTypesID::STRING_ID: return "string";
	case EStandardTypesID::VECTOR4D_ID: return "vector4d";
	case EStandardTypesID::VECTOR3D_ID: return "vector3d";
	case EStandardTypesID::VECTOR2D_ID: return "vector2d";
	}

	return "";
}

std::string ReduceCGenerator::GetFunctionPointerCStr(const std::string& Name, const FFunctionSignatureInfo& FunctionInfo, bool IncludeConst, const FProgramInfo& ProgramInfo) const
{
	std::string LResult = "";

	FVariableInfo LReturnVariableInfo;
	LReturnVariableInfo.Modifiers.IsConst = FunctionInfo.Return.Modifiers.IsConst;
	LReturnVariableInfo.TypeID = FunctionInfo.Return.TypeID;

	// We can't return pointer to function from function, only lambda. So, recursion will stop.
	LResult += GetVariableDeclarationCStr(LReturnVariableInfo, true, false, false, ProgramInfo);
	LResult += "(";
	if( FunctionInfo.Modifiers.CallingConvention != EFunctionCallingConvention::DEFAULT ) LResult += GetCallingConventionCStr(FunctionInfo.Modifiers.CallingConvention) + " ";
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
		for( size_t i = 0; i < FunctionInfo.Inputs.size(); ++i )
		{
			LResult += GetVariableDeclarationCStr(FunctionInfo.Inputs[i], true, false, true, ProgramInfo);
			if( i + 1 < FunctionInfo.Inputs.size() ) LResult += ", ";
		}
	}
	LResult += ")";

	return LResult;
}

std::string ReduceCGenerator::GetClassVariablesCStr(const FClassInfo& ClassInfo, const FProgramInfo& ProgramInfo) const
{
	std::string LResult = "";

	for( const std::pair<std::string, FVariableInfo>& LVariableInfo : ClassInfo.Variables )
	{
		if( LVariableInfo.second.Modifiers.IsStatic ) continue; // static variables compile on another stage

		LResult += "\t" + GetVariableDeclarationCStr(LVariableInfo.second, false, true, false, ProgramInfo) + ";\n";
	}

	for( const std::pair<std::string, std::string>& LVirtualFunctionRow : ClassInfo.VirtualFunctionsTable )
	{
		LResult += "\t" + GetFunctionPointerCStr(LVirtualFunctionRow.first, ProgramInfo.Functions.at(LVirtualFunctionRow.second), false, ProgramInfo) + ";\n";
	}

	return LResult;
}





std::string ReduceCGenerator::GetCallingConventionCStr(EFunctionCallingConvention CallingConvention) const
{
	switch( CallingConvention )
	{
	case EFunctionCallingConvention::CDECL:
	{
		if( CurrentCompileOptions.TargetPlatform == ETargetPlatform::Windows )
		{
			return "__cdecl";
		}
		else
		{
			return "__attribute__((cdecl))";
		}
	}
	case EFunctionCallingConvention::STDCALL:
	{
		if( CurrentCompileOptions.TargetPlatform == ETargetPlatform::Windows )
		{
			return "__stdcall";
		}
		else
		{
			return "__attribute__((stdcall))";
		}
	}
	case EFunctionCallingConvention::FASTCALL:
	{
		if( CurrentCompileOptions.TargetPlatform == ETargetPlatform::Windows )
		{
			return "__fastcall";
		}
		else
		{
			return "__attribute__((__fastcall))";
		}
	}
	case EFunctionCallingConvention::THISCALL:
	{
		if( CurrentCompileOptions.TargetPlatform == ETargetPlatform::Windows )
		{
			return "__thiscall";
		}
		else
		{
			return "__attribute__((__thiscall))";
		}
	}
	}

	return "";
}
