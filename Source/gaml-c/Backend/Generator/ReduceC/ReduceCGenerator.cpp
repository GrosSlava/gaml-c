// Copyright 2022 - 2023 GrosSlava.

#include "ReduceCGenerator.h"
#include "ReduceCHelperLibrary.h"





void ReduceCGenerator::ProcessGeneration(std::string& GeneratedCodeStr, const FIRInfo& IRInfo)
{
	GeneratedCodeStr += "/*\n";
	GeneratedCodeStr += FGeneratorHelperLibrary::GetGenerationTime() + "\n";
	GeneratedCodeStr += FGeneratorHelperLibrary::GetCompilerIdentifier() + "\n";
	GeneratedCodeStr += "*/\n\n";

#if 0 //TODO
	GeneratedCodeStr += "\n/*.......................................Types declaration.......................................*/\n\n";
	for( const std::pair<std::string, FClassInfo>& LClassInfo : ProgramInfo.Classes )
	{
		GeneratedCodeStr += "struct " + LClassInfo.first + ";\n";
	}
	GeneratedCodeStr += "\n";

	for( const std::pair<std::string, FClassInfo>& LClassInfo : ProgramInfo.Classes )
	{
		// clang-format off
		GeneratedCodeStr += FReduceCHelperLibrary::GetClassDeclarationCStr
		(
			LClassInfo.first, LClassInfo.second, FCoreObjects::CompileOptions.TargetPlatform, ProgramInfo
		);
		// clang-format on
		GeneratedCodeStr += "\n";
	}
	GeneratedCodeStr += "\n/*...............................................................................................*/\n";


	GeneratedCodeStr += "\n/*..................................Global variables declaration.................................*/\n\n";
	for( const FCompilingVariableInfo& LStaticVariableInfo : ProgramInfo.CompilingStaticVariables )
	{
		if( !LStaticVariableInfo.IsInThisModule )
		{
			GeneratedCodeStr += "extern ";
		}

		// clang-format off
		GeneratedCodeStr += FReduceCHelperLibrary::GetVariableDeclarationCStr
		(
			LStaticVariableInfo.VariableInfo, false, true, false,
			FCoreObjects::CompileOptions.TargetPlatform, ProgramInfo
		);
		// clang-format on
		GeneratedCodeStr += ";\n";
	}
	GeneratedCodeStr += "\n/*...............................................................................................*/\n";


	GeneratedCodeStr += "\n/*.....................................Functions declaration.....................................*/\n\n";
	for( const std::pair<std::string, FFunctionInfo>& LFunctionInfo : ProgramInfo.Functions )
	{
		if( ProgramInfo.CompilingFunctionsAST.find(LFunctionInfo.first) == ProgramInfo.CompilingFunctionsAST.end() )
		{
			GeneratedCodeStr += "extern ";
		}

		// clang-format off
		GeneratedCodeStr += FReduceCHelperLibrary::GetFunctionSignatureCStr
		(
			LFunctionInfo.first, LFunctionInfo.second.SignatureInfo,
			FCoreObjects::CompileOptions.TargetPlatform, ProgramInfo
		);
		// clang-format on
		GeneratedCodeStr += ";\n";
	}
	GeneratedCodeStr += "\n/*...............................................................................................*/\n";


	GeneratedCodeStr += "\n/*...................................Functions implementation....................................*/\n\n";
	for( const std::pair<std::string, FCompilingFunctionInfo>& LCompilingFunctionInfo : ProgramInfo.CompilingFunctionsAST )
	{
		// clang-format off
		GeneratedCodeStr += FReduceCHelperLibrary::GetFunctionSignatureCStr
		(
			LCompilingFunctionInfo.first, ProgramInfo.Functions.at(LCompilingFunctionInfo.first).SignatureInfo, 
			FCoreObjects::CompileOptions.TargetPlatform, ProgramInfo
		);
		// clang-format on

		GeneratedCodeStr += "\n{\n";
		GeneratedCodeStr += FReduceCHelperLibrary::GetFunctionImplementationBodyCStr(LCompilingFunctionInfo.first, LCompilingFunctionInfo.second, ProgramInfo);
		GeneratedCodeStr += "\n}\n";
	}
	GeneratedCodeStr += "\n/*................................................................................................*/\n";
#endif

	std::replace(GeneratedCodeStr.begin(), GeneratedCodeStr.end(), FCompilerConfig::COMPILE_NAME_SEPARATOR, '_');
}
