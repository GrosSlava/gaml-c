// Copyright 2022 - 2023 GrosSlava.

#include "Linker.h"

#include "CompilerConfig.h"

#include "Platform/PlatformHelperLibrary.h"
#include "Platform/GenericPlatform.h"





void FLinker::Process(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths)
{
	if( ObjectFilesPaths.empty() )
	{
		return;
	}

	FirstFileInfo.SetFromPath(ObjectFilesPaths[0]);

	RunThirdPartyLinker(ObjectFilesPaths, LibsFilesPaths);
}



void FLinker::RunThirdPartyLinker(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths)
{
	const std::string ExecutableFileExtension = FPlatformHelperLibrary::GetPlatformExecutableFileExtension(FCoreObjects::CompileOptions.TargetPlatform);
	const std::string SharedLibraryFileExtension = FPlatformHelperLibrary::GetPlatformSharedLibraryFileExtension(FCoreObjects::CompileOptions.TargetPlatform);
	const std::string StaticLibraryFileExtension = FPlatformHelperLibrary::GetPlatformStaticLibraryFileExtension(FCoreObjects::CompileOptions.TargetPlatform);

	if( ExecutableFileExtension.empty() || SharedLibraryFileExtension.empty() || StaticLibraryFileExtension.empty() )
	{
		RaiseError(EErrorMessageType::CANT_LINK_TO_TARGET_PLATFORM, "");
	}

	switch (FCoreObjects::CompileOptions.BuildType)
	{
	case EBuildType::Executable:
	{
		FGenericPlatform::RunThirdPartyLinker(GetOutputFilePath(ExecutableFileExtension), ObjectFilesPaths, LibsFilesPaths);
		break;
	}
	case EBuildType::SharedLibrary:
	{
		FGenericPlatform::RunThirdPartyLinker(GetOutputFilePath(SharedLibraryFileExtension), ObjectFilesPaths, LibsFilesPaths);
		break;
	}
	case EBuildType::StaticLibrary:
	{
		FGenericPlatform::RunThirdPartyLinker(GetOutputFilePath(StaticLibraryFileExtension), ObjectFilesPaths, LibsFilesPaths);
		break;
	}
	}
}
