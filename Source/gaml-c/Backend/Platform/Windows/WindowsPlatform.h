// Copyright 2022 - 2023 GrosSlava.

#pragma once

#if !WINDOWS_32 && !WINDOWS_64
#error "WINDOWS platform not defined!"
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



	static inline std::string GetMSVCRootDirectory() noexcept
	{
		std::string LResult = "";
		LResult.reserve(256);

		// clang-format off
		LResult += "C:\\Program Files\\Microsoft Visual Studio\\";
		const std::string LVisualStudioYearVersion = FCompilerHelperLibrary::GetBestFolderName("C:/Program Files/Microsoft Visual Studio", {"2022", "2019", "2017"});
		LResult += LVisualStudioYearVersion;
		LResult += "\\";
		const std::string LVisualStudioType = FCompilerHelperLibrary::GetBestFolderName("C:/Program Files/Microsoft Visual Studio/" + LVisualStudioYearVersion, {"Professional", "Community"});
		LResult += LVisualStudioType;
		LResult += "\\VC\\Tools\\MSVC\\";
		LResult += FCompilerHelperLibrary::GetFirstFolderName("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC");
		// clang-format on

		return LResult;
	}

	static inline std::string GetMSVCHostDirectory() noexcept
	{
		std::string LResult = GetMSVCRootDirectory() + "\\bin\\";
#if WINDOWS_64
		LResult += "Hostx64";
#elif WINDOWS_32
		LResult += "Hostx86";
#endif
		return LResult;
	}
};
