// Copyright 2022 - 2023 GrosSlava.

#include "CompilerFileInfo.h"
#include "CompilerHelperLibrary.h"





void FGamlFileInfo::SetFromPath(const std::string& FilePath)
{
	FCompilerHelperLibrary::SplitFilePath(FilePath, PathToFileOnly, FileNameOnly, ExtensionOnly);
}