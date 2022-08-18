// Copyright 2022 GrosSlava.

#include "Compiler/Compiler.h"
#include "Compiler/CompilerOptions.h"
#include "Compiler/CompilerFileInfo.h"
#include "Compiler/CompilerHelperLibrary.h"
#include "Linker/Linker.h"
#include "Logger/ErrorLogger.h"

#include <string>
#include <vector>





int main(int argc, char** argv)
{
	FCompileOptions LCompileOptions;
	std::vector<FGamlFileInfo> LSourceFilePaths;
	std::vector<std::string> LObjectFilesPaths;
	std::vector<std::string> LLibsFilesPaths;

	LCompileOptions.PathToCompiler = argv[0];
	ParseInputOptions(argc - 1, argv + 1, LCompileOptions, LSourceFilePaths, LObjectFilesPaths, LLibsFilesPaths);

	if( LSourceFilePaths.empty() )
	{
		FErrorLogger::Raise(EErrorMessageType::NO_FILES_TO_COMPILE, "", 0, 0, LCompileOptions);
	}


	const size_t LCompilationTime = FCompilerHelperLibrary::ClockCodeMilliseconds
	(
		[&LSourceFilePaths, &LObjectFilesPaths, &LLibsFilesPaths, &LCompileOptions]()
		{
			Compiler LCompiler;
			
			for( size_t i = 0; i < LSourceFilePaths.size(); ++i )
			{
				const std::string LObjectFilePath = LCompiler.Process(LSourceFilePaths[i], LCompileOptions);
				if( !LObjectFilePath.empty() )
				{
					LObjectFilesPaths.push_back(LObjectFilePath);
				}

				if( LCompileOptions.ShowProgress && !LCompileOptions.Silent )
				{
					FCompileLogger::Message("[" + std::to_string(i + 1) + "/" + std::to_string(LSourceFilePaths.size()) + "] " + LSourceFilePaths[i].GetFileFullPath());
				}
			}
			if( !LCompileOptions.NoLinking )
			{
				Linker LLinker;
				LLinker.Process(LObjectFilesPaths, LLibsFilesPaths, LCompileOptions);
			}
		}
	);

	if( !LCompileOptions.Silent )
	{
		FCompileLogger::Message("Compilation time " + FCompilerHelperLibrary::GetPrettyTimeStr(LCompilationTime));
	}

	return 0;
}