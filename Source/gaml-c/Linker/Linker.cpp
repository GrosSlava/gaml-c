// Copyright 2022 GrosSlava.

#include "Linker.h"

#include "../Compiler/CompilerConfig.h"

#include "../Platform/PlatformHelperLibrary.h"
#include "../Platform/GenericPlatform.h"





void Linker::Process(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths, const FCompileOptions& Options)
{
	if( ObjectFilesPaths.empty() ) return;


	CurrentCompileOptions = Options;
	FirstFileInfo = FCompilerHelperLibrary::SplitFilePath(ObjectFilesPaths[0]);


	RunThirdPartyLinker(ObjectFilesPaths, LibsFilesPaths);
}



void Linker::RunThirdPartyLinker(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths)
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
