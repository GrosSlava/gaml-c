// Copyright 2022 - 2023 GrosSlava.

#include "PlatformHelperLibrary.h"

#include <cstdlib>





int FPlatformHelperLibrary::RunConsoleCommand(const std::string& Command)
{
	return system(Command.c_str());
}
