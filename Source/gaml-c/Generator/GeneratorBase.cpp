// Copyright 2022 GrosSlava.

#include "GeneratorBase.h"

#include "../Platform/PlatformHelperLibrary.h"
#include "../Platform/GenericPlatform.h"

#include <fstream>





// clang-format off
bool BaseGenerator::GenerateCode
(
    const FGamlFileInfo& FileInfo, const FCompileOptions& CompileOptions, const FProgramInfo& ProgramInfo, 
    std::string& OutCompiledObjectFilePath
)
// clang-format on
{
	// set context
	CurrentFileInfo = FileInfo;
	CurrentCompileOptions = CompileOptions;

	OutCompiledObjectFilePath.clear();


	// generate code for low-level language
	std::string GeneratedCodeStr;
	GeneratedCodeStr.reserve(16384);
	ProcessGeneration(GeneratedCodeStr, ProgramInfo);


	// create other language file
	const std::string LOutFilePath = GetOutputFilePath(GetOutFileExtension());
	if( LOutFilePath.empty() ) return false;

	std::ofstream LFile(LOutFilePath);
	if( !LFile.is_open() )
	{
		FCompileLogger::Raise(EErrorStage::INITIALIZATION, EErrorType::ERROR, FileInfo.FileNameOnly, "Can't create file '" + LOutFilePath + "'!", 0, 0);
		return false;
	}

	LFile.write(GeneratedCodeStr.c_str(), GeneratedCodeStr.size());
	LFile.close();


	// compile generated code by native compiler
	if( !CurrentCompileOptions.NoTranslation )
	{
		const std::string LFileExtension = FPlatformHelperLibrary::GetPlatformObjectFileExtension(CurrentCompileOptions.TargetPlatform);
		if( LFileExtension.empty() )
		{
			RaiseError(EErrorMessageType::INVALID_GENERATION_EXTENSION, 0, 0, 0);
			return false;
		}

		OutCompiledObjectFilePath = GetOutputFilePath(LFileExtension);
		FGenericPlatform::RunThirdPartyCompiler(CurrentFileInfo, CurrentCompileOptions, LOutFilePath, GetOutputDirectoryPath(), OutCompiledObjectFilePath);
	}

	// remove generated low-level code if needed
	if( !CurrentCompileOptions.DumpGeneratedCode )
	{
		std::remove(LOutFilePath.c_str());
	}

	return true;
}
