// Copyright 2022 - 2023 GrosSlava.

#include "CompilerHelperLibrary.h"

#include "GamlFileInfo.h"

#include <cstdlib>





//.........................................................Misc........................................................//

std::string FCompilerHelperLibrary::GetPrettyTimeStr(size_t MillisecondsCount) noexcept
{
	const size_t LSeconds = MillisecondsCount / 1000;
	const size_t LMilliseconds = MillisecondsCount - LSeconds * 1000;
	const size_t LMinutes = LSeconds / 60;
	const size_t LHours = LMinutes / 60;

	// clang-format off
	return 	std::to_string(LHours) + ":" + 
			std::to_string(LMinutes) + ":" + 
			std::to_string(LSeconds) + "." + 
			std::to_string(LMilliseconds / 100) + std::to_string(LMilliseconds / 10 % 10);
	// clang-format on
}

int FCompilerHelperLibrary::RunConsoleCommand(const std::string& Command)
{
	return system(Command.c_str());
}

//.....................................................................................................................//





//.....................................................Path............................................................//

void FCompilerHelperLibrary::SplitFilePath(const std::string& FilePath, std::string& OutPathOnly, std::string& OutNameOnly, std::string& OutExtensionOnly)
{
	const size_t FileExtensionDotPos = FilePath.find_last_of('.');
	const size_t FileExtensionLastSlashPos = FilePath.find_last_of(std::filesystem::path::preferred_separator);
	const size_t FileNameStart = FileExtensionLastSlashPos + 1; // if not found there will be 0

	OutPathOnly = FilePath.substr(0, FileNameStart);
	OutNameOnly = FilePath.substr(FileNameStart, FileExtensionDotPos - FileNameStart);
	OutExtensionOnly = FileExtensionDotPos == std::string::npos ? "" : FilePath.substr(FileExtensionDotPos + 1);
}

void FCompilerHelperLibrary::SplitPathToParts(const std::string& FilePath, std::vector<std::string>& OutParts, char Separator)
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

std::string FCompilerHelperLibrary::CatPaths(const std::string& Lhs, const std::string Rhs, char Separator)
{
	if( Lhs.empty() )
	{
		return Rhs;
	}
	if( Rhs.empty() )
	{
		return Lhs;
	}

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

std::string FCompilerHelperLibrary::MakePathFromParts(const std::vector<std::string>& Parts, bool IncludeEndSeparator, char Separator)
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

std::string FCompilerHelperLibrary::MakeUpDirectoryStr(size_t UpCount)
{
	if( UpCount == 0 )
	{
		return "";
	}

	std::string LResult = "";
	const std::string LUp = std::string("..") + static_cast<char>(std::filesystem::path::preferred_separator);

	LResult.reserve(UpCount * LUp.size());
	for( size_t i = 0; i < UpCount; ++i )
	{
		LResult += LUp;
	}

	return LResult;
}

//.....................................................................................................................//





//...................................................Files.............................................................//

// clang-format off
void FCompilerHelperLibrary::GetAllFilesWithExtensionsInFolder
(
	const std::string& Path, const std::vector<std::string>& AvailableExtensions, 
	std::vector<FGamlFileInfo>& OutFilesInfo
)
// clang-format on
{
	OutFilesInfo.clear();
	if( !std::filesystem::exists(Path) )
	{
		return;
	}

	for( const std::filesystem::directory_entry& LEntry : std::filesystem::recursive_directory_iterator(Path) )
	{
		if( !LEntry.is_regular_file() ) continue;

		FGamlFileInfo LGamlFileInfo(LEntry.path().string());
		for( const std::string& LAvailableExtension : AvailableExtensions )
		{
			if( LGamlFileInfo.ExtensionOnly == LAvailableExtension )
			{
				OutFilesInfo.push_back(LGamlFileInfo);
				break;
			}
		}
	}
}

std::string FCompilerHelperLibrary::GetFirstFolderName(const std::string& Path)
{
	if( !std::filesystem::exists(Path) )
	{
		return "";
	}

	for( const std::filesystem::directory_entry& LEntry : std::filesystem::directory_iterator(Path) )
	{
		if( LEntry.is_directory() )
		{
			return LEntry.path().filename().string();
		}
	}

	return "";
}

std::string FCompilerHelperLibrary::GetBestFolderName(const std::string& Path, const std::vector<std::string>& FoldersBestOrder)
{
	std::string LPath = Path;
	if( !LPath.empty() && LPath.back() != static_cast<char>(std::filesystem::path::preferred_separator) )
	{
		LPath += static_cast<char>(std::filesystem::path::preferred_separator);
	}

	for( const std::string& LFolderName : FoldersBestOrder )
	{
		if( std::filesystem::exists(LPath + LFolderName) )
		{
			return LFolderName;
		}
	}

	return "";
}

bool FCompilerHelperLibrary::ReadAllFileToStr(const std::string& FilePath, std::string& OutFileSource)
{
	std::ifstream LFile(FilePath, std::ios::binary);
	return ReadAllFileToStr(LFile, OutFileSource);
}

bool FCompilerHelperLibrary::ReadAllFileToStr(std::ifstream& File, std::string& OutFileSource)
{
	OutFileSource.clear();

	if( !File.is_open() )
	{
		return false;
	}

	const size_t LFileSize = File.seekg(0, std::ios::end).tellg();
	File.seekg(0);

	OutFileSource.resize(LFileSize);
	File.read(&OutFileSource[0], LFileSize);
	File.close();

	return true;
}

//.....................................................................................................................//