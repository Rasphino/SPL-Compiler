#ifndef SPLC_CODEGEN_H
#define SPLC_CODEGEN_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <utility>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>

#include "ASTPredeclaration.h"
#include "AST.h"
#include "ConstTable.h"

static llvm::LLVMContext MyContext;

class FuncParams {
public:
    std::vector<int> position;
};

class CodeGenBlock {
public:
    llvm::BasicBlock *basicBlock;
    CodeGenBlock *preBlock;
    llvm::Function *function;
    std::map<std::string, llvm::Value *> locals;
    std::map<std::string, TypeDecl *> varTypes;
    std::map<std::string, TypeDecl *> types;
    std::set<std::string> references;
    std::string outputFilename;

    explicit CodeGenBlock(llvm::BasicBlock *block, CodeGenBlock *preBlock) : basicBlock(block), preBlock(preBlock) {}
};

class CodeGenContext {
public:
    std::stack<CodeGenBlock *> blocksStack;
    llvm::Module *module;
    std::map<std::string, FuncParams> funcParams;
    ConstTable constTable;
    bool isGlobal;

    llvm::Function *print;
    llvm::Function *read;

    CodeGenContext() : module(new llvm::Module("main", MyContext)), print(nullptr), isGlobal(true) {}

    ~CodeGenContext() {
      delete module;
    }

    void pushBlock(llvm::BasicBlock *block) {
      CodeGenBlock *top = blocksStack.empty() ? nullptr : blocksStack.top();
      blocksStack.push(new CodeGenBlock(block, top));
    }

    void popBlock() {
      CodeGenBlock *top = blocksStack.top();
      blocksStack.pop();
      delete top;
    }

    CodeGenBlock *isReference(const std::string &var) {
      CodeGenBlock *p = blocksStack.top();
      while (p) {
        if (p->references.find(var) != p->references.end())
          return p;
        p = p->preBlock;
      }
      return nullptr;
    }

    CodeGenBlock *isType(const std::string &t) {
      CodeGenBlock *p = blocksStack.top();
      while (p) {
        if (p->types.find(t) != p->types.end())
          return p;
        p = p->preBlock;
      }
      return nullptr;
    }

    CodeGenBlock *isVariable(const std::string &v) {
      CodeGenBlock *p = blocksStack.top();
      while (p) {
        if (p->locals.find(v) != p->locals.end())
          return p;
        p = p->preBlock;
      }
      return nullptr;
    }

    std::map<std::string, llvm::Value *> &local() { return blocksStack.top()->locals; };

    std::map<std::string, TypeDecl *> &varType() { return blocksStack.top()->varTypes; };

    std::set<std::string> &reference() { return blocksStack.top()->references; };

    std::map<std::string, TypeDecl *> &type() { return blocksStack.top()->types; };

    llvm::BasicBlock *currentBlock() { return blocksStack.top()->basicBlock; }

    void generateCode(Node *root, const std::string &outputFilename);

    void outputCode(const std::string& filename, bool mips) const;
    void readFunc();
    void printFunc();
};

#endif //SPLC_CODEGEN_H
