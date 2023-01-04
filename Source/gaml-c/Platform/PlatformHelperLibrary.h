// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "../Compiler/CompilerConfig.h"




/*
	Helper library for platform specific features like extensions.
*/
struct FPlatformHelperLibrary
{
	/*
		Execute console command on platform.
		
		@return command exit code.
	*/
	static int RunConsoleCommand(const std::string& Command);




	/*
		Check that extension is any type of object file extension.
	*/
	static inline bool IsObjectFileExtension(const std::string& Extension) noexcept { return Extension == "obj" || Extension == "o"; }
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
		}

		return "";
	}
	/*
		@return array of all supported object file extensions.
	*/
	static inline std::vector<std::string> GetAllObjectFileExtensions() noexcept { return {"obj", "o"}; }


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
		}

		return "";
	}
	/*
		@return array of all supported executable file extensions.
	*/
	static inline std::vector<std::string> GetAllExecutableFileExtensions() noexcept { return {"exe", "out"}; }


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
		}

		return "";
	}
	/*
		@return array of all supported library file extensions.
	*/
	static inline std::vector<std::string> GetAllLibraryFileExtensions() noexcept { return {"dll", "so"}; }
};