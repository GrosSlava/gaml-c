// Copyright 2022 GrosSlava.

#pragma once

#include "CompilerConfig.h"
#include "CompilerFileInfo.h"

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <chrono>




/*
	Helper library for common compiler operations.
*/
struct FCompilerHelperLibrary
{
public:

	template<class CODE>
	static inline size_t ClockCodeMilliseconds(CODE Lambda)
	{
		const auto LStartTime = std::chrono::high_resolution_clock::now();

		Lambda();

		const auto LStopTime = std::chrono::high_resolution_clock::now();
		const auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>(LStopTime - LStartTime);

		return Duration.count();
	}

	static inline std::string GetPrettyTimeStr(size_t MillisecondsCount)
	{
		const size_t LSeconds = MillisecondsCount / 1000;
		const size_t LMilliseconds = MillisecondsCount - LSeconds * 1000;
		const size_t LMinutes = LSeconds / 60;
		const size_t LHours = LMinutes / 60;

		return std::to_string(LHours) + ":" + std::to_string(LMinutes) + ":" + std::to_string(LSeconds) + "." + std::to_string(LMilliseconds / 100) + std::to_string(LMilliseconds / 10 % 10);
	}



	static inline void SplitFilePath(const std::string& FilePath, std::string& OutPathOnly, std::string& OutNameOnly, std::string& OutExtensionOnly)
	{
		const size_t FileExtensionDotPos = FilePath.find_last_of('.');
		const size_t FileExtensionLastSlashPos = FilePath.find_last_of(std::filesystem::path::preferred_separator);
		const size_t FileNameStart = FileExtensionLastSlashPos + 1; // if not found there will be 0

		OutPathOnly = FilePath.substr(0, FileNameStart);
		OutNameOnly = FilePath.substr(FileNameStart, FileExtensionDotPos - FileNameStart);
		OutExtensionOnly = FileExtensionDotPos == std::string::npos ? "" : FilePath.substr(FileExtensionDotPos + 1);
	}

	static inline FGamlFileInfo SplitFilePath(const std::string& FilePath)
	{
		FGamlFileInfo LResult;

		SplitFilePath(FilePath, LResult.PathToFileOnly, LResult.FileNameOnly, LResult.ExtensionOnly);
		return LResult;
	}

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

	static inline void GetAllGamlFilesInFolder(const std::string& Path, std::vector<FGamlFileInfo>& OutFilesInfo) 
	{
		GetAllFilesWithExtensionsInFolder(Path, {FCompilerConfig::COMPILE_FILE_EXTENSION, FCompilerConfig::HEADER_FILE_EXTENSION}, OutFilesInfo);
	}

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

	static std::string GetBestFolderName(const std::string& Path, const std::vector<std::string>& FoldersBestOrder)
	{
		for( const std::string& LFolderName : FoldersBestOrder )
		{
			if( !std::filesystem::exists(Path + (char)std::filesystem::path::preferred_separator + LFolderName) ) continue;
			return LFolderName;
		}

		return "";
	}

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

	static inline std::string MakeUpDirectoryStr(size_t UpCount)
	{
		std::string LResult = "";

		for( size_t i = 0; i < UpCount; ++i )
		{
			LResult += "..";
			LResult += std::filesystem::path::preferred_separator;
		}

		return LResult;
	}



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