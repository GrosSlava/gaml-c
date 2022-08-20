// Copyright 2022 GrosSlava.

#pragma once

#include <string>




/*
	Supported target platforms/
*/
enum class ETargetPlatform
{
	Undefined,
	Windows,
	Linux
};

/*
	Supported target architectures.
*/
enum class ETargetArch
{
	x86,
	x86_64,
	arm,
	arm_64
};
	


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
};


/*
	Determine current platform
*/
#if WIN32 || _WIN32 || WIN64 || _WIN64
	#if WIN64 || _WIN64
		#define WINDOWS_32 1
		#define WINDOWS_64 1
	#else
		#define WINDOWS_32 1
		#define WINDOWS_64 0
	#endif
	#define LINUX 0
#elif __linux__
	#define WINDOWS_32 0
	#define WINDOWS_64 0
	#define LINUX 1
#endif
