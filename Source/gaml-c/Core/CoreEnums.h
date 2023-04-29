// Copyright 2022 - 2023 GrosSlava.

#pragma once




/**
	Supported target platforms.
*/
enum class ETargetPlatform : unsigned char
{
	Undefined,
	Windows,
	Linux
};

/**
	Supported target architectures.
*/
enum class ETargetArch : unsigned char
{
	x86_64,
	AArch64
};

/**
	Types of code optimization.
*/
enum class EOptimizationLevel : unsigned char
{
	NoOptimization = 0,
	SizeOptimization = 1,
	SpeedOptimization = 2
};

/**
	Types of severity of the warning.
*/
enum class EWarningLevel : unsigned char
{
	NoWarnings = 0,
	SeriousWarning = 1,
	CommonWarning = 2,
	MinorWarning = 3
};

/**
	Severity of the error.
*/
enum class EErrorType : unsigned char
{
	ERROR,
	WARNING
};

/**
	Type of subsystem for which the executable file is intended.
*/
enum class ESubsystemType : unsigned char
{
	Console,
	Window
};

/**
	Type of program build.
*/
enum class EBuildType : unsigned char
{
	SharedLibrary,
	StaticLibrary,
	Executable
};