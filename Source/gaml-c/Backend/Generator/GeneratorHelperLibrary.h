// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"




/**
	Helper library for common generator operations.
*/
struct FGeneratorHelperLibrary
{
	/**
		@return compilation date-time in formatted string.
	*/
	static std::string GetGenerationTime();

	/**
		@return compiler identifier string.
	*/
	static std::string GetCompilerIdentifier() noexcept;
};
