//
// Created by 徐维亚 on 05/06/2018.
//

#include "codegen.h"
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Instructions.h>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;


void CodeGenContext::CreateRead() {
	std::vector<llvm::Type *> arg_types;
	arg_types.push_back(llvm::Type::getInt8PtrTy(MyContext));
	auto printf_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(MyContext), arg_types, true);
	read = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage, llvm::Twine("scanf"),
										  module);
	read->setCallingConv(llvm::CallingConv::C);
}

void CodeGenContext::CreatePrint() {
	std::vector<llvm::Type *> printf_arg_types;
	printf_arg_types.push_back(llvm::Type::getInt8PtrTy(MyContext));
	auto printf_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(MyContext), printf_arg_types, true);
	print = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage, llvm::Twine("printf"),
								   module);
	print->setCallingConv(llvm::CallingConv::C);
}

void CodeGenContext::generateCode(Node *root, const std::string &outputFilename) {
	std::cout << "Generating code...\n";

	/* Create the top level interpreter function to call as entry */
	std::vector<llvm::Type *> argTypes;
	llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getInt32Ty(MyContext), makeArrayRef(argTypes),
														false);
	// change GlobalValue::InternalLinkage into ExternalLinkage
	llvm::Function *mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, "main", module);
	llvm::BasicBlock *bblock = llvm::BasicBlock::Create(MyContext, "entry", mainFunction, nullptr);


	// create print read ord chr
	CreatePrint();
	CreateRead();
	// create read


	/* Push a new variable/block context */
	pushBlock(bblock);
	blocks.top()->function = mainFunction;
	root->codeGen(*this);

	llvm::ReturnInst::Create(MyContext, ConstantInt::get(Type::getInt32Ty(MyContext), llvm::APInt(32, 0, false)),currentBlock());
	popBlock();

	while (!blocks.empty())
		popBlock();
	// popBlock();

	/* Print the bytecode in a human-readable format
	   to see if our program compiled properly
	 */
	std::cout << "Code is generated.\n";

	// write IR to stderr
	std::cout << "code is gen~~~\n";
	//    module->dump();
	llvm::outs() << *module;
	std::cout << "code is gen~!~\n";
	std::error_code ErrInfo;

	// output
	llvm::raw_ostream *out = new llvm::raw_fd_ostream(outputFilename, ErrInfo, llvm::sys::fs::F_None);
	*out << *module;
	//    llvm::WriteBitcodeToFile(module, *out);
	out->flush();
	delete out;

	////生成可执行文件
	// Initialize the target registry etc.

	outputCode("output.s", false);
	outputCode("mips.s", true);
}

void CodeGenContext::outputCode(const char *filename, bool mips) {
	InitializeAllTargetInfos();
	InitializeAllTargets();
	InitializeAllTargetMCs();
	InitializeAllAsmParsers();
	InitializeAllAsmPrinters();
	std::string TargetTriple;

	if (mips)
		TargetTriple = "mips-apple-darwin17.6.0";
	else
		TargetTriple = sys::getDefaultTargetTriple();
	module->setTargetTriple(TargetTriple);

	std::string Error;
	auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

	if (!Target) {
		errs() << Error;
		return;
	}

	std::string CPU; // mips1 for mips: llvm-as < /dev/null | llc -march=x86-64 -mattr=help
	if (mips)
		CPU = "";
	else
		CPU = "generic";
	auto Features = "";

	TargetOptions opt;
	auto RM = Optional<Reloc::Model>();
	auto TheTargetMachine =
			Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

	module->setDataLayout(TheTargetMachine->createDataLayout());

	//	auto filename = "output.s";
	std::error_code EC;
	raw_fd_ostream dest(filename, EC, sys::fs::F_None);

	if (EC) {
		errs() << "Could not open file: " << EC.message();
		return;
	}

	legacy::PassManager pass;
	auto FileType = CodeGenFileType::CGFT_AssemblyFile;
	if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
		errs() << "TheTargetMachine can't emit a file of this type";
		return;
	}

	pass.run(*module);
	dest.flush();
	outs() << "Wrote " << filename << "\n";
}