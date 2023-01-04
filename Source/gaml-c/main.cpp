// Copyright 2022 - 2023 GrosSlava.

#include "Compiler/Compiler.h"
#include "Compiler/CompilerOptions.h"
#include "Compiler/CompilerFileInfo.h"
#include "Compiler/CompilerHelperLibrary.h"

#include "Linker/Linker.h"

#include "Logger/ErrorLogger.h"





void CompileSourceFiles(const std::vector<FGamlFileInfo>& SourceFilePaths, const FCompileOptions& CompileOptions, std::vector<std::string>& OutObjectFilesPaths)
{
	const std::string LSourceFilesCountText = std::to_string(SourceFilePaths.size());

	Compiler LCompiler;

	for( size_t i = 0; i < SourceFilePaths.size(); ++i )
	{
		const std::string LObjectFilePath = LCompiler.Process(SourceFilePaths[i], CompileOptions);
		if( !LObjectFilePath.empty() )
		{
			OutObjectFilesPaths.push_back(LObjectFilePath);
		}

		if( CompileOptions.ShowProgress && !CompileOptions.Silent )
		{
			const std::string LIndexText = std::to_string(i + 1);
			const std::string LProgressString = "[" + LIndexText + "/" + LSourceFilesCountText + "] " + SourceFilePaths[i].GetFileFullPath();

			FCompileLogger::MessageText(LProgressString);
		}
	}
}

void LinkProgram(const std::vector<std::string>& ObjectFilesPaths, const std::vector<std::string>& LibsFilesPaths, const FCompileOptions& CompileOptions)
{
	if( CompileOptions.NoLinking ) return;

	Linker LLinker;
	LLinker.Process(ObjectFilesPaths, LibsFilesPaths, CompileOptions);
}




/*
	gaml-c entry point.
*/
int main(int argc, char** argv)
{
	FCompileOptions LCompileOptions;

	std::vector<FGamlFileInfo> LSourceFilePaths;
	std::vector<std::string> LObjectFilesPaths;
	std::vector<std::string> LLibsFilesPaths;


	//..........................Parse options.............................//

	ParseInputOptions(argc, argv, LCompileOptions, LSourceFilePaths, LObjectFilesPaths, LLibsFilesPaths);

	if( LSourceFilePaths.empty() && LObjectFilesPaths.empty() )
	{
		FErrorLogger::Raise(EErrorMessageType::NO_FILES_TO_COMPILE, "", 0, 0, 0, LCompileOptions);
	}

	//....................................................................//


	//.......................Compile source files.........................//

	const size_t LCompilationTime = FCompilerHelperLibrary::ClockCodeMilliseconds(
		[&LSourceFilePaths, &LObjectFilesPaths, &LLibsFilesPaths, &LCompileOptions]()
		{
			CompileSourceFiles(LSourceFilePaths, LCompileOptions, LObjectFilesPaths);
			LinkProgram(LObjectFilesPaths, LLibsFilesPaths, LCompileOptions);
		});

	//....................................................................//


	if( LCompileOptions.ShowCompileTime && !LCompileOptions.Silent )
	{
		FCompileLogger::MessageText("Compilation time " + FCompilerHelperLibrary::GetPrettyTimeStr(LCompilationTime));
	}

	return 0;
}