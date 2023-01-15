// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CoreEnums.h"




/*
	List of compiler config options to edit.
*/
struct FCompilerConfig
{
	/*
		Default target platform for this compiler.
	*/
	const static ETargetPlatform DEFAULT_TARGET_PLATFORM;
	/*
		Default target architecture for this compiler.
	*/
	const static ETargetArch DEFAULT_TARGET_ARCH;

	/*
		Extension of compilable files.
	*/
	const static std::string COMPILE_FILE_EXTENSION;
	/*
		Extension of header file.
	*/
	const static std::string HEADER_FILE_EXTENSION;

	/*
		Name of compiler.
	*/
	const static std::string COMPILER_NAME;
	/*
		Compiler version.
		Major.Minor.Path
	*/
	const static std::string COMPILER_VERSION;
	/*
		Version of language.
	*/
	const static std::string LANGUAGE_VERSION;

	/*
		Default name of module which can be compiled into an executable file.
	*/
	const static std::string RESERVED_MAIN_MODULE_NAME;

	/*
		Reserved name of function of module init generated code.
	*/
	const static std::string RESERVED_INIT_MODULE_FUNCTION_NAME;
	/*
		Reserved name of user function of module init code.
	*/
	const static std::string RESERVED_USER_INIT_MODULE_FUNCTION_NAME;
	/*
		Reserved name of function of module deinit generated code.
	*/
	const static std::string RESERVED_DEINIT_MODULE_FUNCTION_NAME;
	/*
		Reserved name of user function of module init code.
	*/
	const static std::string RESERVED_USER_DEINIT_MODULE_FUNCTION_NAME;
	/*
		Reserved name of function of program init code.
	*/
	const static std::string RESERVED_PROGRAM_INIT_FUNCTION_NAME;
	/*
		Reserved name of function of program deinit code.
	*/
	const static std::string RESERVED_PROGRAM_DEINIT_FUNCTION_NAME;
	/*
		Reserved name of function of console program entry point.
	*/
	const static std::string RESERVED_CONSOLE_ENTRY_POINT_FUNCTION_NAME;
	/*
		Reserved name of function of window program entry point.
	*/
	const static std::string RESERVED_WINDOW_ENTRY_POINT_FUNCTION_NAME;

	/*
		Separetor for compile names.
	*/
	const static char COMPILE_NAME_SEPARATOR;
};