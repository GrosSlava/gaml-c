// Copyright 2022 GrosSlava.

#pragma once

#include "../CoreMinimal.h"




/*
	Information about file in separate form.
*/
struct FGamlFileInfo
{
public:

	inline FGamlFileInfo() { }
	inline FGamlFileInfo(const std::string& InPathToFileOnly, const std::string& InFileNameOnly, const std::string& InExtensionOnly) :
		PathToFileOnly(InPathToFileOnly), FileNameOnly(InFileNameOnly), ExtensionOnly(InExtensionOnly)
	{
	}



public:

	/*
		@return original concatanated path.
	*/
	inline std::string GetFileFullPath() const noexcept { return PathToFileOnly + FileNameOnly + "." + ExtensionOnly; }




public:

	/*
		Only path with end by separator.
	*/
	std::string PathToFileOnly = "";
	/*
		Only name of file.
	*/
	std::string FileNameOnly = "";
	/*
		Only file extension.
	*/
	std::string ExtensionOnly = "";
};