// Copyright 2022 - 2023 GrosSlava.

#include "Compiler.h"
#include "CompilerConfig.h"

#include "Token/Token.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/ProgramSymbols.h"
#include "SemanticAnalyzer/SemanticAnalyser.h"

#include "Generator/GeneratorBase.h"
#include "Generator/ReduceC/ReduceCGenerator.h"
#include "Generator/LLVM/LLVMGenerator.h"

#include <fstream>





std::string FCompiler::Process(const std::string& FilePath, const FCompileOptions& Options)
{
	return Process(FGamlFileInfo(FilePath), Options);
}

std::string FCompiler::Process(const FGamlFileInfo& InFileInfo, const FCompileOptions& Options)
{
	FileInfo = InFileInfo;
	CurrentOptions = Options;

	if( FileInfo.ExtensionOnly != FCompilerConfig::COMPILE_FILE_EXTENSION )
	{
		LogError(EErrorStage::INITIALIZATION, EErrorType::WARNING, "", "File with extension '" + FileInfo.ExtensionOnly + "' can't be compiled!", 0, 0);
		return "";
	}


	std::string LSourceCode;
	if( !Open(LSourceCode) ) return ""; // read code

	std::vector<Token> LTokens;
	if( !ProcessLexer(LSourceCode, LTokens) ) return ""; // get lexemes and check it's correctness
	if( CurrentOptions.DumpLexemes )
	{
		DumpLexemes(LTokens);
	}

	FProgramInfo LProgramInfo;
	if( !ProcessParser(LTokens, LProgramInfo) ) return ""; // analize syntax correctness and generate ast
	if( !ProcessSemantic(LProgramInfo) ) return "";		   // analize ast by semantic
	if( CurrentOptions.DumpModuleDependencies )
	{
		DumpModuleDependencies(LProgramInfo);
	}

	std::string CompiledObjectFilePath = "";
	if( !GenerateCode(LProgramInfo, CompiledObjectFilePath) ) return ""; // generate c-code based on ast

	return CompiledObjectFilePath;
}





bool FCompiler::Open(std::string& OutCode)
{
	const bool LOpenSuccess = FCompilerHelperLibrary::ReadAllFileToStr(FileInfo.GetFileFullPath(), OutCode);
	if( !LOpenSuccess )
	{
		LogError(EErrorStage::INITIALIZATION, EErrorType::WARNING, "", "File '" + FileInfo.GetFileFullPath() + "' not found!", 0, 0);
		return false;
	}

	return true;
}

bool FCompiler::ProcessLexer(const std::string& Code, std::vector<Token>& OutTokens)
{
	FLexer LLexer;
	LLexer.Process(Code, FileInfo, CurrentOptions, OutTokens);

	return true;
}

bool FCompiler::ProcessParser(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo)
{
	FParser LParser;
	LParser.Process(Tokens, FileInfo, CurrentOptions, true, OutProgramInfo);

	return true;
}

bool FCompiler::ProcessSemantic(FProgramInfo& ProgramInfo)
{
	FSemanticAnalyser LSemanticAnalyser;
	LSemanticAnalyser.Process(FileInfo, CurrentOptions, ProgramInfo);

	return true;
}

bool FCompiler::GenerateCode(const FProgramInfo& ProgramInfo, std::string& OutCompiledObjectFilePath)
{
	BaseGenerator* LGenerator = CreateCodeGenerator();
	if( LGenerator == nullptr )
	{
		return false;
	}

	const bool LSuccess = LGenerator->GenerateCode(FileInfo, CurrentOptions, ProgramInfo, OutCompiledObjectFilePath);
	delete LGenerator;

	return LSuccess;
}





void FCompiler::DumpLexemes(const std::vector<Token>& Tokens)
{
	if( Tokens.empty() ) return;


	const std::string LFilePath = GetCompilerOutputDir(FileInfo.FileNameOnly + "_lexemes.txt");

	std::ofstream LFile(LFilePath);
	if( !LFile.is_open() )
	{
		LogError(EErrorStage::INITIALIZATION, EErrorType::WARNING, FileInfo.FileNameOnly, "Can't create file '" + LFilePath + "'!", 0, 0);
		return;
	}

	size_t LLineIndex = Tokens[0].GetLine();
	for( const Token& LToken : Tokens )
	{
		if( LToken.GetLine() != LLineIndex )
		{
			LLineIndex = LToken.GetLine();
			LFile.put('\n');
		}

		// clang-format off
		const std::string LTypeStr = 	"[" + 
										LToken.GetTypeAsStr() + 
										" \"" + LToken.GetLexeme() + "\" " + 
										std::to_string(LToken.GetLine()) + ":" +
										std::to_string(LToken.GetPos()) + 
										"] ";
		// clang-format on

		LFile.write(LTypeStr.c_str(), LTypeStr.size());
	}

	LFile.close();
}

void FCompiler::DumpModuleDependencies(const FProgramInfo& ProgramInfo)
{
	const std::string LFilePath = GetCompilerOutputDir(FileInfo.FileNameOnly + "_dependencies.txt");

	std::ofstream LFile(LFilePath);
	if( !LFile.is_open() )
	{
		LogError(EErrorStage::INITIALIZATION, EErrorType::WARNING, FileInfo.FileNameOnly, "Can't create file '" + LFilePath + "'!", 0, 0);
		return;
	}


	std::string LStr = "";
	LStr.reserve(2048);

	LStr += "Main module name: " + ProgramInfo.MainModuleName + "\n";
	for( const std::pair<std::string, FModuleInfo>& LImportedModulePair : ProgramInfo.ImportedModulesInfo )
	{
		LStr += LImportedModulePair.first + ": ";

		for( size_t i = 0; i < LImportedModulePair.second.RequiredModulesNames.size(); ++i )
		{
			LStr += LImportedModulePair.second.RequiredModulesNames[i];
			if( i + 1 < LImportedModulePair.second.RequiredModulesNames.size() ) LStr += ", ";
		}

		LStr += "\n";
	}

	LFile.write(LStr.c_str(), LStr.size());
	LFile.close();
}





BaseGenerator* FCompiler::CreateCodeGenerator() const noexcept
{
	switch( CurrentOptions.CodeGenerationType )
	{
	case ECodeGenerationType::ReduceC: return new ReduceCGenerator();
	case ECodeGenerationType::LLVM: return new LLVMGenerator();
	}

	LogError(EErrorStage::INITIALIZATION, EErrorType::ERROR, "", "!!!UNDEFINED CODE GENERATOR TYPE!!!", 0, 0);
	return nullptr;
}
