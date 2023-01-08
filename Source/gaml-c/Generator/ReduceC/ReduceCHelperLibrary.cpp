// Copyright 2022 - 2023 GrosSlava.

#include "ReduceCHelperLibrary.h"
#include "ReduceCNodeCodeGen.h"





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
	return FunctionCompileInfo.FunctionCodeTree.GenerateCode(std::make_shared<ReduceC_ASTCodeGenFactory>(), ProgramInfo);
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
	LResult.reserve((ClassInfo.Variables.size() + ClassInfo.VirtualFunctionsTable.size()) * 64);

	for( const std::pair<std::string, FVariableInfo>& LVariableInfo : ClassInfo.Variables )
	{
		LResult += "\t" + GetVariableDeclarationCStr(LVariableInfo.second, false, true, false, TargetPlatform, ProgramInfo) + ";\n";
	}

	for( const std::pair<std::string, std::string>& LVirtualFunctionRow : ClassInfo.VirtualFunctionsTable )
	{
		// clang-format off
		LResult += "\t" +
					GetFunctionPointerCStr
					(
						LVirtualFunctionRow.first, ProgramInfo.Functions.at(LVirtualFunctionRow.second).SignatureInfo, false, 
						TargetPlatform, ProgramInfo
					) +
					";\n";
		// clang-format on
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


	const FUserTypePath& LTypePath = ProgramInfo.TypesMap[VariableInfo.TypeID];
	switch( LTypePath.PathSwitch )
	{
	case ETypePathSwitch::Standard:
	{
		if( VariableInfo.Modifiers.IsConst && IncludeConst ) LResult += "const ";

		LResult += GetStandardTypeNameCStr(VariableInfo.TypeID);
		// clang-format off
		if( 
			IsFunctionArgument && 
			((VariableInfo.Modifiers.IsConst && VariableInfo.TypeID == EStandardTypesID::STRING_ID) || VariableInfo.Modifiers.IsMutable)
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
	case ETypePathSwitch::Class:
	{
		const std::string& LClassCompileName = LTypePath.ClassPath.ClassCompileName;
		const FClassInfo& LClassInfo = ProgramInfo.Classes.at(LClassCompileName);

		if( VariableInfo.Modifiers.IsConst && IncludeConst ) LResult += "const ";

		if( LClassInfo.ClassType == EClassType::Enum )
		{
			LResult += GetStandardTypeNameCStr(LClassInfo.ParentTypesID[0]);
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
	case ETypePathSwitch::FunctionSignature:
	{
		const FFunctionSignatureInfo& LFunctionSignature = ProgramInfo.FunctionSignaturesTypesMap[LTypePath.FunctionSignaturePath.FunctionSignatureID];

		LResult += GetFunctionPointerCStr(IncludeName ? VariableInfo.VariableName : "", LFunctionSignature, IncludeConst, TargetPlatform, ProgramInfo);
		break;
	}
	}

	return LResult;
}