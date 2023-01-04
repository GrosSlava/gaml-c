// Copyright 2022 GrosSlava.

#include "CompilerFileInfo.h"
#include "CompilerHelperLibrary.h"





void FGamlFileInfo::SetFromPath(const std::string& FilePath)
{
    FCompilerHelperLibrary::SplitFilePath(FilePath, PathToFileOnly, FileNameOnly, ExtensionOnly);
}