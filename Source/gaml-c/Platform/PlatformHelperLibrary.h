// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Compiler/CompilerConfig.h"




/*
	Helper library for platform specific features like extensions.
*/
struct FPlatformHelperLibrary
{
	/*
		Check that extension is any type of object file extension.
	*/
	static inline bool IsObjectFileExtension(const std::string& Extension) noexcept { return Extension == "o" || Extension == "obj"; }
	/*
		@return object file extension for TargetPlatform, if supported.
	*/
	static inline std::string GetPlatformObjectFileExtension(ETargetPlatform TargetPlatform) noexcept
	{
		switch( TargetPlatform )
		{
		case ETargetPlatform::Windows:
		{
			return "obj";
		}
		case ETargetPlatform::Linux:
		{
			return "o";
		}
		default:
		{
			return "";
		}
		}
	}


	/*
		Check that extension is any type of executable file extension.
	*/
	static inline bool IsExecutableFileExtension(const std::string& Extension) noexcept { return Extension == "exe" || Extension == "out"; }
	/*
		@return executable file extension for TargetPlatform, if supported.
	*/
	static inline std::string GetPlatformExecutableFileExtension(ETargetPlatform TargetPlatform) noexcept
	{
		switch( TargetPlatform )
		{
		case ETargetPlatform::Windows:
		{
			return "exe";
		}
		case ETargetPlatform::Linux:
		{
			return "out";
		}
		default:
		{
			return "";
		}
		}
	}


	/*
		Check that extension is any type of library file extension.
	*/
	static inline bool IsLibraryFileExtension(const std::string& Extension) noexcept { return Extension == "dll" || Extension == "so"; }
	/*
		@return library file extension for TargetPlatform, if supported.
	*/
	static inline std::string GetPlatformLibraryFileExtension(ETargetPlatform TargetPlatform) noexcept
	{
		switch( TargetPlatform )
		{
		case ETargetPlatform::Windows:
		{
			return "dll";
		}
		case ETargetPlatform::Linux:
		{
			return "so";
		}
		default:
		{
			return "";
		}
		}
	}
};