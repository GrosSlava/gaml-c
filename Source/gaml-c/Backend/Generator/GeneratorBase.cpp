// Copyright 2022 - 2023 GrosSlava.

#include "GeneratorBase.h"

#include "Platform/PlatformHelperLibrary.h"
#include "Platform/GenericPlatform.h"

#include <fstream>





// clang-format off
bool BaseGenerator::GenerateCode
(
	const FGamlFileInfo& FileInfo, const FIRInfo& IRInfo, 
	std::string& OutCompiledObjectFilePath
)
// clang-format on
{
	// set context
	CurrentFileInfo = FileInfo;
	OutCompiledObjectFilePath.clear();


	// generate code for low-level language
	std::string GeneratedCodeStr;
	GeneratedCodeStr.reserve(16384);
	ProcessGeneration(GeneratedCodeStr, IRInfo);


	// create other language file
	const std::string LOutFilePath = GetOutputFilePath(GetOutFileExtension());
	if( LOutFilePath.empty() ) return false;

	std::ofstream LFile(LOutFilePath);
	if( !LFile.is_open() )
	{
		FCompileLogger::Raise(EErrorType::ERROR, FileInfo.FileNameOnly, "Can't create file '" + LOutFilePath + "'!", 0, 0);
		return false;
	}

	LFile.write(GeneratedCodeStr.c_str(), GeneratedCodeStr.size());
	LFile.close();


	// compile generated code to binary
	const std::string LFileExtension = FPlatformHelperLibrary::GetPlatformObjectFileExtension(FCoreObjects::CompileOptions.TargetPlatform);
	if( LFileExtension.empty() )
	{
		RaiseError(EErrorMessageType::INVALID_GENERATION_EXTENSION, 0, 0, 0);
		return false;
	}
	OutCompiledObjectFilePath = GetOutputFilePath(LFileExtension);
	CompileToBinary(LOutFilePath, OutCompiledObjectFilePath);
	

	// remove generated low-level code if needed
	if( !FCoreObjects::CompileOptions.DumpGeneratedCode )
	{
		std::remove(LOutFilePath.c_str());
	}

	return true;
}
