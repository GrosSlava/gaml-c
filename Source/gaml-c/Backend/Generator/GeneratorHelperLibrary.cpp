// Copyright 2022 - 2023 GrosSlava.

#include "GeneratorHelperLibrary.h"
#include "CompilerConfig.h"

#include <ctime>





std::string FGeneratorHelperLibrary::GetGenerationTime()
{
	const std::time_t t = std::time(0);
	std::tm CurrentTime;
#if WINDOWS_32
	localtime_s(&CurrentTime, &t);
#elif LINUX
	localtime_r(&t, &CurrentTime);
#endif

	// clang-format off
	const std::string LGenerationDateTime = std::to_string(CurrentTime.tm_year + 1900) + "." + 
											std::to_string(CurrentTime.tm_mon + 1) + "." + 
											std::to_string(CurrentTime.tm_mday) + " " +
											std::to_string(CurrentTime.tm_hour) + ":" + 
											std::to_string(CurrentTime.tm_min) + ":" + 
											std::to_string(CurrentTime.tm_sec);
	// clang-format on

	return LGenerationDateTime;
}

std::string FGeneratorHelperLibrary::GetCompilerIdentifier() noexcept
{
	// clang-format off
	static const std::string CachedCompilerIdentifier = std::string(FCompilerConfig::COMPILER_NAME) + 
														" v" + std::string(FCompilerConfig::COMPILER_VERSION);
	// clang-format on
	return CachedCompilerIdentifier;
}
