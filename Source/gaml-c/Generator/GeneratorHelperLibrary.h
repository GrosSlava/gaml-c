// Copyright 2022 GrosSlava.

#pragma once

#include "../Compiler/CompilerHelperLibrary.h"

#include <ctime>
#include <string>




/*
	Helper library for common generator operations.
*/
struct FGeneratorHelperLibrary
{
public:

	static std::string GetGenerationTime()
	{
		const std::time_t t = std::time(0);
		std::tm CurrentTime;
		localtime_s(&CurrentTime, &t);

		const std::string LGenerationDateTime = std::to_string(CurrentTime.tm_year + 1900) + "." + 
												std::to_string(CurrentTime.tm_mon + 1) + "." + 
												std::to_string(CurrentTime.tm_mday) + " " +
												std::to_string(CurrentTime.tm_hour) + ":" + 
												std::to_string(CurrentTime.tm_min) + ":" + 
												std::to_string(CurrentTime.tm_sec);

		return LGenerationDateTime;
	}

	static std::string GetMSVCRootDirectory() 
	{
		std::string LResult = "";

		LResult += "C:\\Program Files\\Microsoft Visual Studio\\";
		const std::string LVisualStudioYearVersion = FCompilerHelperLibrary::GetBestFolderName("C:/Program Files/Microsoft Visual Studio", {"2022", "2019", "2017"});
		LResult += LVisualStudioYearVersion;
		LResult += "\\";
		const std::string LVisualStudioType = FCompilerHelperLibrary::GetBestFolderName("C:/Program Files/Microsoft Visual Studio/" + LVisualStudioYearVersion, {"Professional", "Community"});
		LResult += LVisualStudioType;
		LResult += "\\VC\\Tools\\MSVC\\";
		LResult += FCompilerHelperLibrary::GetFirstFolderName("C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC");

		return LResult;
	}

	static inline std::string GetMSVCHostDirectory()
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
