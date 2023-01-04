// Copyright 2022 GrosSlava.

#include "Compiler.h"
#include "CompilerConfig.h"

#include "../Token/Token.h"
#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"
#include "../Parser/ProgramSymbols.h"
#include "../SemanticAnalyzer/SemanticAnalyser.h"

#include "../Generator/GeneratorBase.h"
#include "../Generator/ReduceC/ReduceCGenerator.h"
#include "../Generator/LLVM/LLVMGenerator.h"

#include <fstream>





std::string Compiler::Process(const std::string& FilePath, const FCompileOptions& Options)
{
	return Process(FGamlFileInfo(FilePath), Options);
}

std::string Compiler::Process(const FGamlFileInfo& InFileInfo, const FCompileOptions& Options)
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

	FProgramInfo LProgramInfo;
	if( !ProcessParser(LTokens, LProgramInfo) ) return ""; // analize syntax correctness and generate ast
	if( !ProcessSemantic(LProgramInfo) ) return "";		   // analize ast by semantic

	std::string CompiledObjectFilePath = "";
	if( !GenerateCode(LProgramInfo, CompiledObjectFilePath) ) return ""; // generate c-code based on ast

	return CompiledObjectFilePath;
}






bool Compiler::Open(std::string& OutCode)
{
	std::ifstream LFile(FileInfo.GetFileFullPath(), std::ios::binary);
	if( !LFile.is_open() )
	{
		LogError(EErrorStage::INITIALIZATION, EErrorType::WARNING, "", "File '" + FileInfo.GetFileFullPath() + "' not found!", 0, 0);
		return false;
	}

	FCompilerHelperLibrary::ReadAllFileToStr(LFile, OutCode);

	return true;
}

bool Compiler::ProcessLexer(const std::string& Code, std::vector<Token>& OutTokens)
{
	Lexer LLexer;
	LLexer.Process(Code, FileInfo, CurrentOptions, OutTokens);

	if( CurrentOptions.DumpLexemes )
	{
		DumpLexemes(OutTokens);
	}

	return true;
}

bool Compiler::ProcessParser(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo)
{
	Parser LParser;
	LParser.Process(Tokens, FileInfo, CurrentOptions, true, OutProgramInfo);

	if( CurrentOptions.DumpModuleDependencies )
	{
		DumpModuleDependencies(OutProgramInfo);
	}

	return true;
}

bool Compiler::ProcessSemantic(FProgramInfo& ProgramInfo)
{
	SemanticAnalyser LSemanticAnalyser;
	LSemanticAnalyser.Process(FileInfo, CurrentOptions, ProgramInfo);

	return true;
}

bool Compiler::GenerateCode(const FProgramInfo& ProgramInfo, std::string& OutCompiledObjectFilePath)
{
	BaseGenerator* LGenerator = CreateCodeGenerator();
	if( LGenerator == nullptr ) return false;


	const bool LSuccess = LGenerator->GenerateCode(FileInfo, CurrentOptions, ProgramInfo, OutCompiledObjectFilePath);
	delete LGenerator;

	return LSuccess;
}





void Compiler::DumpLexemes(const std::vector<Token>& Tokens)
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

void Compiler::DumpModuleDependencies(const FProgramInfo& ProgramInfo)
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





BaseGenerator* Compiler::CreateCodeGenerator() const noexcept
{
	switch( CurrentOptions.CodeGenerationType )
	{
	case ECodeGenerationType::ReduceC: return new ReduceCGenerator();
	case ECodeGenerationType::LLVM: return new LLVMGenerator();
	}

	LogError(EErrorStage::INITIALIZATION, EErrorType::ERROR, "", "!!!UNDEFINED CODE GENERATOR TYPE!!!", 0, 0);
	return nullptr;
}
