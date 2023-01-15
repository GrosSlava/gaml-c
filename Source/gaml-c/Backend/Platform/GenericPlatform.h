// Copyright 2022 - 2023 GrosSlava.

#pragma once




// clang-format off
#if WINDOWS_32 || WINDOWS_64
	#include "Windows/WindowsPlatform.h"
#elif LINUX
	#include "Linux/LinuxPlatform.h"
#else
	#error "Invalid platform"
#endif
// clang-format on
