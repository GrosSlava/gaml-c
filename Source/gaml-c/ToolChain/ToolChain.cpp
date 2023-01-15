// Copyright 2022 - 2023 GrosSlava.

#include "ToolChain.h"

#include "GamlFileInfo.h"
#include "CompilerHelperLibrary.h"

#include "Compiler.h"
#include "Linker/Linker.h"

#include "Logger/ErrorLogger.h"





// clang-format off
void FToolChain::Process
(
	const std::vector<FGamlFileInfo>& SourceFilePaths,
	const std::vector<std::string>& ObjectFilesPaths,
	const std::vector<std::string>& LibsFilesPaths,
	const FCompileOptions& CompileOptions
)
// clang-format on
{
	CurrentCompileOptions = CompileOptions;

	if( SourceFilePaths.empty() && ObjectFilesPaths.empty() )
	{
		FErrorLogger::Raise(EErrorMessageType::NO_FILES_TO_COMPILE, "", 0, 0, 0, CurrentCompileOptions);
		return;
	}


	//.......................Compile source files.........................//

	const size_t LCompilationTime = FCompilerHelperLibrary::ClockCodeMilliseconds(
		[this, &SourceFilePaths, &ObjectFilesPaths, &LibsFilesPaths]()
		{
			std::vector<std::string> LCompiledObjectFiles;
			CompileSourceFiles(SourceFilePaths, LCompiledObjectFiles);

			if( !CurrentCompileOptions.NoLinking )
			{
				LCompiledObjectFiles.insert(LCompiledObjectFiles.end(), ObjectFilesPaths.begin(), ObjectFilesPaths.end());
				LinkProgram(ObjectFilesPaths, LibsFilesPaths);
			}
		});

	//....................................................................//


	if( CurrentCompileOptions.ShowCompileTime && !CurrentCompileOptions.Silent )
	{
		FCompileLogger::MessageText("Compilation time " + FCompilerHelperLibrary::GetPrettyTimeStr(LCompilationTime));
	}
}





void FToolChain::CompileSourceFiles(const std::vector<FGamlFileInfo>& SourceFilePaths, std::vector<std::string>& OutObjectFilesPaths)
{
	const std::string LSourceFilesCountText = std::to_string(SourceFilePaths.size());

	FCompiler LCompiler;

	for( size_t i = 0; i < SourceFilePaths.size(); ++i )
	{
		const std::string LObjectFilePath = LCompiler.Process(SourceFilePaths[i], CurrentCompileOptions);
		if( !LObjectFilePath.empty() )
		{
			OutObjectFilesPaths.push_back(LObjectFilePath);
		}

		if( CurrentCompileOptions.ShowProgress && !CurrentCompileOptions.Silent )
		{
			const std::string LIndexText = std::to_string(i + 1);
			const std::string LProgressString = "[" + LIndexText + "/" + LSourceFilesCountText + "] " + SourceFilePaths[i].GetFileFullPath();

			FCompileLogger::MessageText(LProgressString);
		}
	}
}

void FToolChain::LinkProgram(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths)
{
	FLinker LLinker;
	LLinker.Process(ObjectFilesPaths, LibsFilesPaths, CurrentCompileOptions);
}
