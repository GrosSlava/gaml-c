// Copyright 2022 GrosSlava.

#include "CompilerConfig.h"





// set your target platform for cross compiler
// clang-format off
#if WINDOWS_32 || WINDOWS_64
    const ETargetPlatform FCompilerConfig::DEFAULT_TARGET_PLATFORM = ETargetPlatform::Windows;
#elif LINUX
    const ETargetPlatform FCompilerConfig::DEFAULT_TARGET_PLATFORM = ETargetPlatform::Linux;
#else
    const ETargetPlatform FCompilerConfig::DEFAULT_TARGET_PLATFORM = ETargetPlatform::Undefined;
#endif
// clang-format on

// set your arch for cross compiler
// clang-format off
#if WINDOWS_64
    const ETargetArch FCompilerConfig::DEFAULT_TARGET_ARCH = ETargetArch::x86_64;
#elif WINDOWS_32
    const ETargetArch FCompilerConfig::DEFAULT_TARGET_ARCH = ETargetArch::x86;
#elif LINUX
    const ETargetArch FCompilerConfig::DEFAULT_TARGET_ARCH = ETargetArch::x86_64;
#else
    const ETargetArch FCompilerConfig::DEFAULT_TARGET_ARCH = ETargetArch::x86_64;
#endif
// clang-format on


const std::string FCompilerConfig::COMPILE_FILE_EXTENSION = "gaml";
const std::string FCompilerConfig::HEADER_FILE_EXTENSION = "gh";

const std::string FCompilerConfig::COMPILER_NAME = "gaml-c";
const std::string FCompilerConfig::COMPILER_VERSION = "0.1.0";
const std::string FCompilerConfig::LANGUAGE_VERSION = "1";

const std::string FCompilerConfig::RESERVED_MAIN_MODULE_NAME = "main";

const std::string FCompilerConfig::RESERVED_INIT_MODULE_FUNCTION_NAME = "init_module_internal";
const std::string FCompilerConfig::RESERVED_USER_INIT_MODULE_FUNCTION_NAME = "init_module";
const std::string FCompilerConfig::RESERVED_DEINIT_MODULE_FUNCTION_NAME = "deinit_module_internal";
const std::string FCompilerConfig::RESERVED_USER_DEINIT_MODULE_FUNCTION_NAME = "deinit_module";
const std::string FCompilerConfig::RESERVED_PROGRAM_INIT_FUNCTION_NAME = "init";
const std::string FCompilerConfig::RESERVED_PROGRAM_DEINIT_FUNCTION_NAME = "deinit";
const std::string FCompilerConfig::RESERVED_CONSOLE_ENTRY_POINT_FUNCTION_NAME = "main";
const std::string FCompilerConfig::RESERVED_WINDOW_ENTRY_POINT_FUNCTION_NAME = "WinMain";

const char FCompilerConfig::COMPILE_NAME_SEPARATOR = '@';
