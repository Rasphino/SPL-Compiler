#include "CodeGen.h"
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

using namespace llvm;
using namespace CodeGen;

void CodeGenContext::readFunc() {
  std::vector<llvm::Type *> arg_types;
  arg_types.push_back(llvm::Type::getInt8PtrTy(MyContext));
  auto func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(MyContext), arg_types, true);
  read = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, llvm::Twine("scanf"),
                                module);
  read->setCallingConv(llvm::CallingConv::C);
}

void CodeGenContext::printFunc() {
  std::vector<llvm::Type *> printf_arg_types;
  printf_arg_types.push_back(llvm::Type::getInt8PtrTy(MyContext));
  auto func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(MyContext), printf_arg_types, true);
  print = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, llvm::Twine("printf"),
                                 module);
  print->setCallingConv(llvm::CallingConv::C);
}

void CodeGenContext::generateCode(AST::Node *root, const std::string &outputFilename) {
  std::cout << "Generating code...\n";

  // Create the top level interpreter function to call as entry
  std::vector<llvm::Type *> argTypes;
  llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getInt32Ty(MyContext), makeArrayRef(argTypes),
                                                      false);
  // change GlobalValue::InternalLinkage into ExternalLinkage
  llvm::Function *mainFunction = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, "main", module);
  llvm::BasicBlock *bblock = llvm::BasicBlock::Create(MyContext, "entry", mainFunction, nullptr);


  // create print read ord chr
  printFunc();
  readFunc();

  // Push a new variable/basicBlock context
  pushBlock(bblock);
  blocksStack.top()->function = mainFunction;
  root->codeGen(*this);

  llvm::ReturnInst::Create(MyContext, ConstantInt::get(Type::getInt32Ty(MyContext), llvm::APInt(32, 0, false)),currentBlock());
  popBlock();

  while (!blocksStack.empty())
    popBlock();

  std::cout << "Code is generated.\n";

  std::cout << "code is gen~~~\n";
  llvm::outs() << *module;
  std::cout << "code is gen~!~\n";
  std::error_code ErrInfo;

  // output
  llvm::raw_ostream *out = new llvm::raw_fd_ostream(outputFilename, ErrInfo, llvm::sys::fs::F_None);
  *out << *module;
  out->flush();
  delete out;

  ////生成可执行文件
  // Initialize the target registry etc.

  outputCode("output.s", false);
  outputCode("aarch64.s", true);
}

void CodeGenContext::outputCode(const std::string& filename, bool aarch64) const {
  InitializeAllTargetInfos();
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmParsers();
  InitializeAllAsmPrinters();

  std::string CPU = aarch64 ? "" : "generic";
  std::string TargetTriple = aarch64 ? "aarch64-pc-linux" : sys::getDefaultTargetTriple();
  module->setTargetTriple(TargetTriple);

  std::string error;
  auto target = TargetRegistry::lookupTarget(TargetTriple, error);

  if (!target) {
    errs() << error;
    return;
  }

  auto Features = "";

  TargetOptions opt;
  auto RM = Optional<Reloc::Model>();
  auto targetMachine = target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

  module->setDataLayout(targetMachine->createDataLayout());

  std::error_code EC;
  raw_fd_ostream dest(filename, EC, sys::fs::F_None);

  if (EC) {
    errs() << "Could not open file: " << EC.message();
    return;
  }

  legacy::PassManager pass;
  auto fileType = LLVMTargetMachine::CodeGenFileType::CGFT_AssemblyFile;
  if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
    errs() << "targetMachine can't emit a file of this type";
    return;
  }

  pass.run(*module);
  dest.flush();
  outs() << "Wrote " << filename << "\n";
}