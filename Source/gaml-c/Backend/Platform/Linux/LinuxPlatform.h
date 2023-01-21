// Copyright 2022 - 2023 GrosSlava.

#pragma once

#if !LINUX
#error "LINUX platform not defined!"
#endif

#include "CoreObjects.h"
#include "GamlFileInfo.h"
#include "CompilerHelperLibrary.h"

#include "Logger/ErrorLogger.h"




struct FGenericPlatform
{
	// clang-format off
	static int RunThirdPartyCompiler
	(
		const FGamlFileInfo& OriginalFile,
		const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
	)
	// clang-format on
	{
		switch( FCoreObjects::CompileOptions.CodeGenerationType )
		{
		case ECodeGenerationType::ReduceC:
		{
			return RunGCC(OriginalFile, FilePath, OutputDirectoryPath, CompiledObjectFilePath);
		}
		case ECodeGenerationType::LLVM:
		{
			return RunLLC(OriginalFile, FilePath, OutputDirectoryPath, CompiledObjectFilePath);
		}
		}

		FErrorLogger::Raise(EErrorMessageType::UNSUPPORTED_CODE_GENERATOR, OriginalFile.GetFileFullPath(), 0, 0, 0);
		return 0;
	}

	// clang-format off
	static int RunThirdPartyLinker
	(
		const std::string& OutputFilePath,
		const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths
	);
	// clang-format on




	// clang-format off
	static int RunGCC
	(
		const FGamlFileInfo& OriginalFile,
		const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
	);
	// clang-format on

	// clang-format off
	static int RunLLC
	(
		const FGamlFileInfo& OriginalFile,
		const std::string& FilePath, const std::string& OutputDirectoryPath, const std::string& CompiledObjectFilePath
	);
	// clang-format on
};
