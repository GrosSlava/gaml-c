// Copyright 2022 - 2023 GrosSlava.

#include "Compiler.h"
#include "CompilerConfig.h"

#include "Token/Token.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/ProgramSymbols.h"
#include "SemanticAnalyzer/SemanticAnalyser.h"
#include "IR/IRInfo.h"

#include "Generator/GeneratorBase.h"
#include "Generator/LLVM/LLVMGenerator.h"

#include <fstream>





std::string FCompiler::Process(const FGamlFileInfo& InFileInfo)
{
	FileInfo = InFileInfo;

	if( FileInfo.ExtensionOnly != FCompilerConfig::COMPILE_FILE_EXTENSION )
	{
		LogError(EErrorType::WARNING, "", "File with extension '" + FileInfo.ExtensionOnly + "' can't be compiled!", 0, 0);
		return "";
	}

	// read code
	std::string LSourceCode;
	if( !Open(LSourceCode) ) return "";

	// get lexemes and check it's correctness
	std::vector<Token> LTokens;
	if( !ProcessLexer(LSourceCode, LTokens) ) return "";
	if( FCoreObjects::CompileOptions.DumpLexemes )
	{
		DumpLexemes(LTokens);
	}

	// analize syntax correctness and generate ast
	FProgramInfo LProgramInfo;
	if( !ProcessParser(LTokens, LProgramInfo) ) return "";
	if( FCoreObjects::CompileOptions.DumpAST )
	{
		DumpAST(LProgramInfo);
	}

	// analize ast by semantic
	if( !ProcessSemantic(LProgramInfo) ) return "";
	if( FCoreObjects::CompileOptions.DumpModuleDependencies )
	{
		DumpModuleDependencies(LProgramInfo);
	}

	// generate IR
	FIRInfo LIR;
	ProcessIR(LProgramInfo, LIR);
	if( FCoreObjects::CompileOptions.DumpIR )
	{
		DumpIR(LIR);
	}

	// generate code based on IR
	std::string CompiledObjectFilePath = "";
	if( !GenerateCode(LIR, CompiledObjectFilePath) ) return "";

	return CompiledObjectFilePath;
}





bool FCompiler::Open(std::string& OutCode)
{
	const bool LOpenSuccess = FCompilerHelperLibrary::ReadAllFileToStr(FileInfo.GetFileFullPath(), OutCode);
	if( !LOpenSuccess )
	{
		LogError(EErrorType::WARNING, "", "File '" + FileInfo.GetFileFullPath() + "' not found!", 0, 0);
		return false;
	}

	return true;
}

bool FCompiler::ProcessLexer(const std::string& Code, std::vector<Token>& OutTokens)
{
	FLexer LLexer;
	LLexer.Process(Code, FileInfo, OutTokens);

	return true;
}

bool FCompiler::ProcessParser(const std::vector<Token>& Tokens, FProgramInfo& OutProgramInfo)
{
	FParser LParser;
	LParser.Process(Tokens, FileInfo, true, OutProgramInfo);

	return true;
}

bool FCompiler::ProcessSemantic(FProgramInfo& ProgramInfo)
{
	FSemanticAnalyser LSemanticAnalyser;
	LSemanticAnalyser.Process(FileInfo, ProgramInfo);

	return true;
}

bool FCompiler::ProcessIR(FProgramInfo& ProgramInfo, FIRInfo& OutIR)
{
	//TODO
	return false;
}

bool FCompiler::GenerateCode(const FIRInfo& IRInfo, std::string& OutCompiledObjectFilePath)
{
	// hardcode select generator, no dynamic switch
	BaseGenerator* LGenerator = new LLVMGenerator();

	const bool LSuccess = LGenerator->GenerateCode(FileInfo, IRInfo, OutCompiledObjectFilePath);
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
		LogError(EErrorType::WARNING, FileInfo.FileNameOnly, "Can't create file '" + LFilePath + "'!", 0, 0);
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

void FCompiler::DumpAST(const FProgramInfo& ProgramInfo)
{
	const std::string LFilePath = GetCompilerOutputDir(FileInfo.FileNameOnly + "_ast.txt");

	std::ofstream LFile(LFilePath);
	if( !LFile.is_open() )
	{
		LogError(EErrorType::WARNING, FileInfo.FileNameOnly, "Can't create file '" + LFilePath + "'!", 0, 0);
		return;
	}

	for( const auto& LAssertInfo : ProgramInfo.StaticAsserts )
	{
		const std::string LAssertTree = LAssertInfo.CodeTree.GetTreeAsStr();

		LFile.write(LAssertTree.c_str(), LAssertTree.size());
		LFile.put('\n');
	}

	for( const auto& LClassInfo : ProgramInfo.Classes )
	{
		LFile.write(LClassInfo.first.c_str(), LClassInfo.first.size());
		LFile.write("\n:{\n", 4);
		for( const auto& LVariableInfo : LClassInfo.second.Variables )
		{
			LFile.write(LVariableInfo.first.c_str(), LVariableInfo.first.size());
			LFile.write(":\n", 2);
			const std::string LVariableTree = LVariableInfo.second.DefaultValueTree.GetTreeAsStr();
			LFile.write(LVariableTree.c_str(), LVariableTree.size());
		}
		LFile.write("}\n", 2);
	}

	for( const auto& LFunctionInfo : ProgramInfo.Functions )
	{
		LFile.write(LFunctionInfo.first.c_str(), LFunctionInfo.first.size());
		LFile.write(":\n[\n", 4);
		const std::string LFunctionTree = LFunctionInfo.second.SignatureInfo.StaticCodeTree.GetTreeAsStr();
		LFile.write(LFunctionTree.c_str(), LFunctionTree.size());
		LFile.write("]\n", 2);
	}

	for( const auto& LFunctionInfo : ProgramInfo.CompilingFunctionsAST )
	{
		LFile.write(LFunctionInfo.first.c_str(), LFunctionInfo.first.size());
		LFile.write(":\n{\n", 4);
		const std::string LFunctionTree = LFunctionInfo.second.FunctionCodeTree.GetTreeAsStr();
		LFile.write(LFunctionTree.c_str(), LFunctionTree.size());
		LFile.write("}\n", 2);
	}

	LFile.close();
}

void FCompiler::DumpModuleDependencies(const FProgramInfo& ProgramInfo)
{
	const std::string LFilePath = GetCompilerOutputDir(FileInfo.FileNameOnly + "_dependencies.txt");

	std::ofstream LFile(LFilePath);
	if( !LFile.is_open() )
	{
		LogError(EErrorType::WARNING, FileInfo.FileNameOnly, "Can't create file '" + LFilePath + "'!", 0, 0);
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

void FCompiler::DumpIR(const FIRInfo& IRInfo)
{
	//TODO
}
