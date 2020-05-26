//
// Created by 徐维亚 on 05/06/2018.
//

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
#include "AST.h"
#include "ConstTable.h"

static llvm::LLVMContext MyContext;

class Node;

class FunctionHead;

class FuncVars {
public:
    std::vector<llvm::Value *> storePlace;
    std::vector<int> position;
};

class CodeGenBlock {
public:
    llvm::BasicBlock *block;
    CodeGenBlock *preBlock;
    llvm::Function *function;
    std::map<std::string, llvm::Value *> locals;
    std::map<std::string, TypeDecl *> varTypes;
    std::map<std::string, TypeDecl *> types;
    std::set<std::string> references;
    std::string outputFilename;

    explicit CodeGenBlock(llvm::BasicBlock *block, CodeGenBlock *preBlock) : block(block), preBlock(preBlock) {}
};

class CodeGenContext {
public:
    std::stack<CodeGenBlock *> blocks;
    llvm::Module *module;
    std::map<std::string, FuncVars> funcVars;
    ConstTable constTable;
    bool isGlobal;

    CodeGenContext() : module(new llvm::Module("main", MyContext)), print(nullptr), isGlobal(true) {}

    ~CodeGenContext() {
        delete module;
    }

    void pushBlock(llvm::BasicBlock *block) {
        CodeGenBlock *top = nullptr;
        if (!blocks.empty()) {
            top = blocks.top();
        }
        blocks.push(new CodeGenBlock(block, top));
    }

    void popBlock() {
        CodeGenBlock *top = blocks.top();
        blocks.pop();
        delete top;
    }

    CodeGenBlock * isReferece(const std::string & var) {
        CodeGenBlock * p = blocks.top();
        while (p) {
            if(p->references.find(var)!= p->references.end())
                return p;
            p = p->preBlock;
        }
        return nullptr;
    }

    CodeGenBlock * isType(const std::string & t) {
        CodeGenBlock * p = blocks.top();
        while (p) {
            if(p->types.find(t)!= p->types.end())
                return p;
            p = p->preBlock;
        }
        return nullptr;
    }

    CodeGenBlock * isVariable(const std::string & v) {
        CodeGenBlock * p = blocks.top();
        while (p) {
            if(p->locals.find(v)!= p->locals.end())
                return p;
            p = p->preBlock;
        }
        return nullptr;
    }

    std::map<std::string, llvm::Value *> &local() { return blocks.top()->locals; };

    std::map<std::string, TypeDecl *> &varType() { return blocks.top()->varTypes; };

    std::set<std::string> &reference() { return blocks.top()->references; };

    std::map<std::string, TypeDecl *> &type() { return blocks.top()->types; };

    llvm::BasicBlock *currentBlock() { return blocks.top()->block; }

    void generateCode(Node *root, const std::string &outputFilename);

    void outputCode(const char *filename, bool mips);
    void CreateRead();
    void CreatePrint();
    llvm::Function *print;
    llvm::Function *read;
};

#endif //SPLC_CODEGEN_H
