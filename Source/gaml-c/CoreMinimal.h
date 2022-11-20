// Copyright 2022 GrosSlava.

#pragma once




#include <string>
#include <vector>


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