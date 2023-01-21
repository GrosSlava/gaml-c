// Copyright 2022 - 2023 GrosSlava.

#pragma once

#include "CoreMinimal.h"

#include "CompilerConfig.h"

#include <fstream>
#include <filesystem>
#include <chrono>




struct FGamlFileInfo;



/*
	Helper library for common compiler operations.
*/
struct FCompilerHelperLibrary
{
	//.........................................................Misc........................................................//

	/*
		Time code performance.

		@param Lambda - Code to check.
	*/
	template<class CODE>
	static inline size_t ClockCodeMilliseconds(CODE Lambda)
	{
		const auto LStartTime = std::chrono::high_resolution_clock::now();

		Lambda();

		const auto LStopTime = std::chrono::high_resolution_clock::now();
		const auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>(LStopTime - LStartTime);

		return Duration.count();
	}

	/*
		@param MillisecondsCount - Time in milliseconds.
		@return formatted current time.
	*/
	static std::string GetPrettyTimeStr(size_t MillisecondsCount) noexcept;

	/*
		Execute console command on platform.
		
		@return command exit code.
	*/
	static int RunConsoleCommand(const std::string& Command);

	//.....................................................................................................................//


	//.....................................................Path............................................................//

	/*
		Split file path into Path/Name/Extension.

		@param FilePath - Path to file for splitting.
		@param OutPathOnly - Result of file path only.
		@param OutNameOnly - Result of file name only.
		@param OutExtensionOnly - Result of file extension only.
	*/
	static void SplitFilePath(const std::string& FilePath, std::string& OutPathOnly, std::string& OutNameOnly, std::string& OutExtensionOnly);

	/*
		Split file path by separator.

		@param FilePath - Path to file for splitting.
		@param OutParts - Result of split.
		@param Separator - Char for separate(not included into split parts).
	*/
	static void SplitPathToParts(const std::string& FilePath, std::vector<std::string>& OutParts, char Separator = std::filesystem::path::preferred_separator);

	/*
		Concatanate paths by platform specific delimiter.

		@param Lhs - Left hand string to concatanate.
		@param Rhs - Right hand string to concatanate.
		@param Separator - Separetor to concatanate.
	*/
	static std::string CatPaths(const std::string& Lhs, const std::string Rhs, char Separator = std::filesystem::path::preferred_separator);

	// clang-format off
	/*
		Concatanate array of path parts by given separator.

		@param Parts - Array of path parts.
		@param IncludeEndSeparator - If true then path will be ended by separator.
		@param Separator - Char to separate path parts.
	*/
	static std::string MakePathFromParts
	(
		const std::vector<std::string>& Parts, bool IncludeEndSeparator = false, 
		char Separator = std::filesystem::path::preferred_separator
	);
	// clang-format on

	/*
		Make "up" path. It can be see like "../../../"

		@param UpCount - Count of directories to up.
	*/
	static std::string MakeUpDirectoryStr(size_t UpCount);

	//.....................................................................................................................//


	//...................................................Files.............................................................//

	// clang-format off
	/*
		Find all files with specific extension in given folder and it's subfolders.

		@param Path - Path to directory to search.
		@param AvailableExtensions - Array of extensions to search.
		@param OutFilesInfo - Result of the file search.
	*/
	static void GetAllFilesWithExtensionsInFolder
	(
		const std::string& Path, const std::vector<std::string>& AvailableExtensions, 
		std::vector<FGamlFileInfo>& OutFilesInfo
	);
	// clang-format on

	/*
		Find all files with GAML extension in given folder and it's subfolders (search both of sources and headers).
	*/
	static inline void GetAllGamlFilesInFolder(const std::string& Path, std::vector<FGamlFileInfo>& OutFilesInfo)
	{
		GetAllFilesWithExtensionsInFolder(Path, {FCompilerConfig::COMPILE_FILE_EXTENSION, FCompilerConfig::HEADER_FILE_EXTENSION}, OutFilesInfo);
	}

	/*
		@param Path - Directory to search.
		@return first folder name from given directory.
	*/
	static std::string GetFirstFolderName(const std::string& Path);

	/*
		@return first existing folder from FoldersBestOrder.
	*/
	static std::string GetBestFolderName(const std::string& Path, const std::vector<std::string>& FoldersBestOrder);

	/*
		Read file into string.

		@param FilePath - Path to file.
		@param OutFileSource - Result string.
		@return success.
	*/
	static bool ReadAllFileToStr(const std::string& FilePath, std::string& OutFileSource);
	/*
		Read file into string.

		@param File - Opened file.
		@param OutFileSource - Result string.
		@return success.
	*/
	static bool ReadAllFileToStr(std::ifstream& File, std::string& OutFileSource);

	//.....................................................................................................................//
};