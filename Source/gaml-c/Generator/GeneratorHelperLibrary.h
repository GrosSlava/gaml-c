// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Compiler/CompilerConfig.h"

#include <ctime>




/*
	Helper library for common generator operations.
*/
struct FGeneratorHelperLibrary
{
	/*
		@return compilation date-time in formatted string.
	*/
	static std::string GetGenerationTime()
	{
		const std::time_t t = std::time(0);
		std::tm CurrentTime;
		localtime_s(&CurrentTime, &t);

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

	/*
		@return compiler identifier string.
	*/
	static inline std::string GetCompilerIdentifier() noexcept
	{
		return std::string(FCompilerConfig::COMPILER_NAME) + " v" + std::string(FCompilerConfig::COMPILER_VERSION);
	}
};
