// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CompilerConfig.h"




/**
	Helper library for platform specific features like extensions.
*/
struct FPlatformHelperLibrary
{
	/**
		Check that extension is any type of object file extension.
	*/
	static inline bool IsObjectFileExtension(const std::string& Extension) noexcept { return Extension == "obj" || Extension == "o"; }
	/**
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
		}

		return "";
	}
	/**
		@return array of all supported object file extensions.
	*/
	static inline std::vector<std::string> GetAllObjectFileExtensions() noexcept { return {"obj", "o"}; }


	/**
		Check that extension is any type of executable file extension.
	*/
	static inline bool IsExecutableFileExtension(const std::string& Extension) noexcept { return Extension == "exe" || Extension == "out"; }
	/**
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
		}

		return "";
	}
	/**
		@return array of all supported executable file extensions.
	*/
	static inline std::vector<std::string> GetAllExecutableFileExtensions() noexcept { return {"exe", "out"}; }


	/**
		Check that extension is any type of shared library file extension.
	*/
	static inline bool IsSharedLibraryFileExtension(const std::string& Extension) noexcept { return Extension == "dll" || Extension == "so"; }
	/**
		@return shared library file extension for TargetPlatform, if supported.
	*/
	static inline std::string GetPlatformSharedLibraryFileExtension(ETargetPlatform TargetPlatform) noexcept
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
		}

		return "";
	}
	/**
		@return array of all supported shared library file extensions.
	*/
	static inline std::vector<std::string> GetAllSharedLibraryFileExtensions() noexcept { return {"dll", "so"}; }


	/**
		Check that extension is any type of static library file extension.
	*/
	static inline bool IsStaticLibraryFileExtension(const std::string& Extension) noexcept { return Extension == "lib" || Extension == "a"; }
	/**
		@return static library file extension for TargetPlatform, if supported.
	*/
	static inline std::string GetPlatformStaticLibraryFileExtension(ETargetPlatform TargetPlatform) noexcept
	{
		switch( TargetPlatform )
		{
		case ETargetPlatform::Windows:
		{
			return "lib";
		}
		case ETargetPlatform::Linux:
		{
			return "a";
		}
		}

		return "";
	}
	/**
		@return array of all supported static library file extensions.
	*/
	static inline std::vector<std::string> GetAllStaticLibraryFileExtensions() noexcept { return {"lib", "a"}; }
};