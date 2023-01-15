// Copyright 2022 - 2023 GrosSlava.

#include "Linker.h"

#include "CompilerConfig.h"

#include "Platform/PlatformHelperLibrary.h"
#include "Platform/GenericPlatform.h"





void FLinker::Process(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths, const FCompileOptions& Options)
{
	if( ObjectFilesPaths.empty() )
	{
		return;
	}

	CurrentCompileOptions = Options;
	FirstFileInfo.SetFromPath(ObjectFilesPaths[0]);

	RunThirdPartyLinker(ObjectFilesPaths, LibsFilesPaths);
}



void FLinker::RunThirdPartyLinker(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths)
{
	const std::string ExecutableFileExtension = FPlatformHelperLibrary::GetPlatformExecutableFileExtension(CurrentCompileOptions.TargetPlatform);
	const std::string LibraryFileExtension = FPlatformHelperLibrary::GetPlatformLibraryFileExtension(CurrentCompileOptions.TargetPlatform);
	const std::string OuptputFilePath = GetOutputFilePath(CurrentCompileOptions.IsDLL ? LibraryFileExtension : ExecutableFileExtension);

	if( ExecutableFileExtension.empty() || LibraryFileExtension.empty() )
	{
		RaiseError(EErrorMessageType::CANT_LINK_TO_TARGET_PLATFORM, "");
	}


	FGenericPlatform::RunThirdPartyLinker(CurrentCompileOptions, OuptputFilePath, ObjectFilesPaths, LibsFilesPaths);
}
