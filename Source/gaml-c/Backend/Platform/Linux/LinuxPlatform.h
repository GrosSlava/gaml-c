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
	static int RunThirdPartyLinker
	(
		const std::string& OutputFilePath,
		const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths
	);
	// clang-format on
};
