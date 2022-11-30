// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"

#include "CompilerConfig.h"
#include "CompilerFileInfo.h"

#include <filesystem>
#include <fstream>
#include <chrono>




/*
	Helper library for common compiler operations.
*/
struct FCompilerHelperLibrary
{
	/*
		Time code performance.

		@param Lambda - code to check.
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
	static inline std::string GetPrettyTimeStr(size_t MillisecondsCount) noexcept
	{
		const size_t LSeconds = MillisecondsCount / 1000;
		const size_t LMilliseconds = MillisecondsCount - LSeconds * 1000;
		const size_t LMinutes = LSeconds / 60;
		const size_t LHours = LMinutes / 60;

		return std::to_string(LHours) + ":" + std::to_string(LMinutes) + ":" + std::to_string(LSeconds) + "." + std::to_string(LMilliseconds / 100) + std::to_string(LMilliseconds / 10 % 10);
	}




	/*
		Split file path into Path/Name/Extension.

		@param FilePath - Path to file for splitting.
		@param OutPathOnly - Result of file path only.
		@param OutNameOnly - Result of file name only.
		@param OutExtensionOnly - Result of file extension only.
	*/
	static inline void SplitFilePath(const std::string& FilePath, std::string& OutPathOnly, std::string& OutNameOnly, std::string& OutExtensionOnly)
	{
		const size_t FileExtensionDotPos = FilePath.find_last_of('.');
		const size_t FileExtensionLastSlashPos = FilePath.find_last_of(std::filesystem::path::preferred_separator);
		const size_t FileNameStart = FileExtensionLastSlashPos + 1; // if not found there will be 0

		OutPathOnly = FilePath.substr(0, FileNameStart);
		OutNameOnly = FilePath.substr(FileNameStart, FileExtensionDotPos - FileNameStart);
		OutExtensionOnly = FileExtensionDotPos == std::string::npos ? "" : FilePath.substr(FileExtensionDotPos + 1);
	}
	/*
		Split file path into FGamlFileInfo.

		@param FilePath - Path to file for splitting.
	*/
	static inline FGamlFileInfo SplitFilePath(const std::string& FilePath)
	{
		FGamlFileInfo LResult;

		SplitFilePath(FilePath, LResult.PathToFileOnly, LResult.FileNameOnly, LResult.ExtensionOnly);
		return LResult;
	}
	/*
		Split file path by separator.

		@param FilePath - Path to file for splitting.
		@param OutParts - Result of split.
		@param Separator - Char for separate(not included into split parts).
	*/
	static inline void SplitPathToParts(const std::string& FilePath, std::vector<std::string>& OutParts, char Separator = std::filesystem::path::preferred_separator)
	{ 
		OutParts.clear();

		size_t LPrevOffset = 0;
		size_t LOffset = FilePath.find_first_of(Separator, 0);
		while( LOffset != std::string::npos )
		{
			OutParts.push_back(FilePath.substr(LPrevOffset, LOffset - LPrevOffset));
			LPrevOffset = LOffset + 1;
			LOffset = FilePath.find_first_of(Separator, LPrevOffset);
		}
		OutParts.push_back(FilePath.substr(LPrevOffset, LOffset - LPrevOffset));
	}

	/*
		Concatanate paths by platform specific delimiter.

		@param Lhs - Left hand string to concatanate.
		@param Rhs - Right hand string to concatanate.
		@param Separator - Separetor to concatanate.
	*/
	static inline std::string CatPaths(const std::string& Lhs, const std::string Rhs, char Separator = std::filesystem::path::preferred_separator) 
	{ 
		if( Lhs.empty() ) return Rhs;
		if( Rhs.empty() ) return Lhs;

		std::string LResult = Lhs;
		if( LResult.back() != Separator && Rhs.at(0) != Separator )
		{
			LResult += Separator;
		}
		else if( LResult.back() == Separator && Rhs.at(0) == Separator )
		{
			LResult.resize(LResult.size() - 1);
		}
		LResult += Rhs;

		return LResult;
	}

	/*
		Concatanate array of path parts by given separator.

		@param Parts - Array of path parts.
		@param IncludeEndSeparator - If true then path will be ended by separator.
		@param Separator - Char to separate path parts.
	*/
	static inline std::string MakePathFromParts(const std::vector<std::string>& Parts, bool IncludeEndSeparator = false, char Separator = std::filesystem::path::preferred_separator)
	{
		std::string LResult = "";

		for( const std::string& LPart : Parts )
		{
			LResult = CatPaths(LResult, LPart, Separator);
		}
		if( LResult.size() > 0 && !IncludeEndSeparator && LResult.back() == Separator )
		{
			LResult.resize(LResult.size() - 1); // without separator
		}

		return LResult;
	}

	/*
		Make "up" path. It can be see like "../../../"

		@param UpCount - Count of directories to up.
	*/
	static inline std::string MakeUpDirectoryStr(size_t UpCount)
	{
		if( UpCount == 0 ) return "";

		std::string LResult = "";
		const std::string LUp = std::string("..") + static_cast<char>(std::filesystem::path::preferred_separator);

		LResult.reserve(UpCount * LUp.size());
		for( size_t i = 0; i < UpCount; ++i )
		{
			LResult += LUp;
		}
		
		return LResult;
	}




	/*
		Find all files with specific extension in given folder and it's subfolders.

		@param Path - Path to directory to search.
		@param AvailableExtensions - Array of extensions to search.
		@param OutFilesInfo - Result of the file search.
	*/
	static inline void GetAllFilesWithExtensionsInFolder(const std::string& Path, const std::vector<std::string>& AvailableExtensions, std::vector<FGamlFileInfo>& OutFilesInfo)
	{
		OutFilesInfo.clear();
		if( !std::filesystem::exists(Path) ) return;


		for( const std::filesystem::directory_entry& LEntry : std::filesystem::recursive_directory_iterator(Path) )
		{
			if( !LEntry.is_regular_file() ) continue;

			FGamlFileInfo LGamlFileInfo = SplitFilePath(LEntry.path().string());
			for( const std::string LAvailableExtension : AvailableExtensions )
			{
				if( LGamlFileInfo.ExtensionOnly == LAvailableExtension )
				{
					OutFilesInfo.push_back(LGamlFileInfo);
					break;
				}
			}
		}
	}
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
	static std::string GetFirstFolderName(const std::string& Path) 
	{
		if( !std::filesystem::exists(Path) ) return "";

		for( const std::filesystem::directory_entry& LEntry : std::filesystem::directory_iterator(Path) )
		{
			if( !LEntry.is_directory() ) continue;

			return LEntry.path().filename().string();
		}

		return "";
	}
	/*
		@return first existing folder from FoldersBestOrder.
	*/
	static std::string GetBestFolderName(const std::string& Path, const std::vector<std::string>& FoldersBestOrder)
	{
		for( const std::string& LFolderName : FoldersBestOrder )
		{
			if( !std::filesystem::exists(Path + (char)std::filesystem::path::preferred_separator + LFolderName) ) continue;
			return LFolderName;
		}

		return "";
	}

	

	/*
		Read file into string.

		@param File - opened file to read.
		@param OutFileSource - Result string.
	*/
	static inline void ReadAllFileToStr(std::ifstream& File, std::string& OutFileSource)
	{
		OutFileSource.clear();
		if( !File.is_open() ) return;

		const size_t LFileSize = File.seekg(0, std::ios::end).tellg();
		File.seekg(0);

		OutFileSource.resize(LFileSize);
		File.read(&OutFileSource[0], LFileSize);
		File.close();
	}
};