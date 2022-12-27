// Copyright 2022 GrosSlava.

#pragma once




// clang-format off
#if WINDOWS_32 || WINDOWS_64
    #include "WindowsPlatform.h"
#elif LINUX
    #include "LinuxPlatform.h"
#else
    #error "Invalid platform"
#endif
// clang-format on
