#include "AST.h"
#include <vector>
#include <string>
#include <fmt/core.h>
#include <fmt/format.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include "codegen.h"

using namespace llvm;
using namespace AST;
using namespace CodeGen;

static Value *GetArrayRef(CodeGenContext &context, const std::string &id, Expression *index);

static Value *GetRecordRef(CodeGenContext &context, const std::string &id, const std::string &recordId);

//static Value *GetArrayRef(CodeGenContext &context, Value *index, const std::string &id);

llvm::Value *Program::codeGen(CodeGenContext &context) {
    if (routine)
        routine->codeGen(context);
    return nullptr;
}

llvm::Value *Routine::codeGen(CodeGenContext &context) {
    routineHead->codeGen(context);
    routineBody->codeGen(context);
    return nullptr;
}

llvm::Value *RoutineHead::codeGen(CodeGenContext &context) {
    if (labelPart) labelPart->codeGen(context);
    if (constPart) constPart->codeGen(context);
    if (typePart) typePart->codeGen(context);
    if (varPart) varPart->codeGen(context);
    routinePart->codeGen(context);
    return nullptr;
}

llvm::Value *ConstPart::codeGen(CodeGenContext &context) {
    if (constExprList)
        return constExprList->codeGen(context);
    return nullptr;
}

llvm::Value *ConstExprList::codeGen(CodeGenContext &context) {
    if (preList) preList->codeGen(context); //顺序？从前往后？从后往前？
    auto var = value->codeGen(context);
    context.local()[name] = var;
    addToConstTable(context.constTable);
    return var;
}

void ConstExprList::addToConstTable(ConstTable &table) {
    switch (value->type) {
        case ConstValue::T_INTEGER:
            table.addInt(name, std::stoi(value->value));
            break;
        case ConstValue::T_REAL:
            table.addReal(name, std::stod(value->value));
            break;
        case ConstValue::T_CHAR:
            table.addChar(name, value->value[0]);
            break;
        default:
            std::cerr << fmt::format("ConstExprList::addToConstTable failed: unimplemented type {}\n", value->type);
            break;
    }
}

void ConstExprList::removeFromConstTable(ConstTable &table) {
    if (preList)
        preList->removeFromConstTable(table);
    table.remove(name);
}

llvm::Value *ConstValue::codeGen(CodeGenContext &context) {
    switch (type) {
        case ConstValue::T_INTEGER:
            return ConstantInt::get(Type::getInt32Ty(MyContext), std::stoi(value), true);
        case ConstValue::T_CHAR:
            return ConstantInt::get(Type::getInt8Ty(MyContext), value.at(0), false);
        case ConstValue::T_REAL:
            return llvm::ConstantFP::get(MyContext, llvm::APFloat(std::stod(value)));
        case ConstValue::T_SYS_CON:
            if (value == "maxint")
                return ConstantInt::get(Type::getInt32Ty(MyContext), 2147483647, true);
            else if (value == "true")
                return ConstantInt::get(Type::getInt1Ty(MyContext), 1, true);
            else if (value == "false")
                return ConstantInt::get(Type::getInt1Ty(MyContext), 0, true);
            return nullptr;
        default:
            return nullptr;
    }
}

llvm::Value *TypePart::codeGen(CodeGenContext &context) {
    if (typeDeclList)
        return typeDeclList->codeGen(context);
    return nullptr;
}

llvm::Value *TypeDeclList::codeGen(CodeGenContext &context) {
    if (preList)
        preList->codeGen(context);
    return typeDefinition->codeGen(context);
}

llvm::Value *TypeDefinition::codeGen(CodeGenContext &context) {
    switch (typeDecl->type) {
        case TypeDecl::T_SIMPLE_TYPE_DECLARE: {
            if (typeDecl->simpleTypeDecl->type == SimpleTypeDecl::T_TYPE_NAME) {
                auto b = context.isType(typeDecl->simpleTypeDecl->name);
                if (b)
                    context.type()[name] = b->types[typeDecl->simpleTypeDecl->name];
                else
                    context.type()[name] = typeDecl;
            } else {
                context.type()[name] = typeDecl;
            }
            break;
        }
        case TypeDecl::T_ARRAY_TYPE_DECLARE:
            context.type()[name] = typeDecl;
            break;
        case TypeDecl::T_RECORD_TYPE_DECLARE:
            context.type()[name] = typeDecl;
            typeDecl->recordTypeDecl->getType(context, name);
            break;
        default:
            break;
    }
    return nullptr;
}

llvm::Value *VarPart::codeGen(CodeGenContext &context) {
    if (varDeclList) {
        varDeclList->codeGen(context);
        context.isGlobal = false;
    }
    return nullptr;
}

llvm::Value *VarDeclList::codeGen(CodeGenContext &context) {
    if (preList)
        preList->codeGen(context);//顺序？从前往后？从后往前？
    return varDecl->codeGen(context);
}

llvm::Value *VarDecl::codeGen(CodeGenContext &context) {
    NameList *n = nameList;
    while (n) {
        // how to get type
        llvm::Type *t = typeDecl->getType(context, "");
        if (!t) {
            std::cerr << fmt::format("VarDecl::codeGen failed: undefined type.\n");
            exit(1);
        } else {
            Value *alloc;
            if (context.isGlobal) {
                auto zero = Constant::getNullValue(t);
                alloc = new llvm::GlobalVariable(*context.module, t, false,
                        llvm::GlobalValue::ExternalLinkage, zero, n->name);
            } else {
                alloc = new AllocaInst(t, 0, n->name, context.currentBlock());
            }
            context.local()[n->name] = alloc;
            context.varType()[n->name] = typeDecl;

            if (typeDecl->type == TypeDecl::T_SIMPLE_TYPE_DECLARE &&
                typeDecl->simpleTypeDecl->type == SimpleTypeDecl::T_TYPE_NAME) {
                auto b = context.isType(typeDecl->simpleTypeDecl->name);
                if (b)
                    context.varType()[n->name] = b->types[typeDecl->simpleTypeDecl->name];
            }
        }
        n = n->nameList;
    }
    return nullptr;
}

llvm::Type *TypeDecl::getType(CodeGenContext &context, std::string name) {
    if (type == T_SIMPLE_TYPE_DECLARE)
        return simpleTypeDecl->getType(context);
    else if (type == T_ARRAY_TYPE_DECLARE)
        return arrayTypeDecl->getType(context);
    else if (type == T_RECORD_TYPE_DECLARE)
        return recordTypeDecl->getType(context, name);
    return nullptr;
};

llvm::Type *SimpleTypeDecl::getType(CodeGenContext &context) {
    switch (type) {
        case T_SYS_TYPE: {
            if (sysType == "boolean")
              return llvm::Type::getInt1Ty(MyContext);
            else if (sysType == "char")
              return llvm::Type::getInt8Ty(MyContext);
            else if (sysType == "integer")
              return llvm::Type::getInt32Ty(MyContext);
            else if (sysType == "real")
              return llvm::Type::getDoubleTy(MyContext);
            else
              return nullptr;
        }
        case T_TYPE_NAME: {
            if (name == "boolean")
              return llvm::Type::getInt1Ty(MyContext);
            else if (name == "char")
              return llvm::Type::getInt1Ty(MyContext);
            else if (name == "integer")
              return llvm::Type::getInt32Ty(MyContext);
            else if (sysType == "real")
              return llvm::Type::getDoubleTy(MyContext);
            if (context.module->getTypeByName(name))
              return context.module->getTypeByName(name);
            CodeGenBlock *p = context.blocksStack.top();
            while (p) {
              if (p->types.find(name) == p->types.end()) {
                p = p->preBlock;
                continue;
              }
              return p->types.at(name)->getType(context, name);
            }
            return nullptr;
        }
        default:
            break;
    }
    return nullptr;
};

llvm::Type *ArrayTypeDecl::getType(CodeGenContext &context) {
    return llvm::ArrayType::get(elementType->getType(context, ""), range->getRange(context.constTable));
}


llvm::Type *RecordTypeDecl::getType(CodeGenContext &context, std::string &name) {
    if (context.module->getTypeByName(name))
        return context.module->getTypeByName(name);
    FieldDeclList *f = fieldDeclList;
    std::vector<Type *> argList;
    while (f) {
        NameList *n = f->fieldDecl->nameList;
        while (n) {
            argList.push_back(f->fieldDecl->typeDecl->getType(context, ""));
            n = n->nameList;
        }
        f = f->preList;
    }
    StructType *structType;
    if (!name.empty())
        structType = StructType::create(MyContext, makeArrayRef(argList), name);
    else
        structType = StructType::create(MyContext, makeArrayRef(argList));
    return structType;
}

llvm::Value *RoutinePart::codeGen(CodeGenContext &context) {
    if (routinePart)
        routinePart->codeGen(context);
    if (type == T_ROUTINE_FUNC)
        functionDecl->codeGen(context);
    if (type == T_ROUTINE_PROC)
        procedureDecl->codeGen(context);
    if (type == T_EMPTY)
        return nullptr;
    if (type == T_PROC)
        return procedureDecl->codeGen(context);
    if (type == T_FUNC)
        return functionDecl->codeGen(context);
    return nullptr;
}

llvm::Value *FunctionDecl::codeGen(CodeGenContext &context) {
    CodeGenBlock *parent = context.blocksStack.top();
    std::vector<Type *> argTypes;
    ParaDeclList *p = functionHead->parameters->paraDeclList;
    while (p) {
        NameList *n;
        if (p->paraTypeList->type == ParaTypeList::T_VAL) {
            n = p->paraTypeList->valParaList->nameList;
            while (n) {
                argTypes.push_back(p->paraTypeList->typeDecl->getType(context));
                n = n->nameList;
            }
        } else {
            n = p->paraTypeList->varParaList->nameList;
            while (n) {
                argTypes.push_back(Type::getInt32PtrTy(MyContext)); // or switch??
                n = n->nameList;
            }
        }

        p = p->paraDeclList;
    } // 反正倒序定义的到时候倒序访问应该不成问题假装
    FunctionType *ftype = FunctionType::get(functionHead->returnType->getType(context), makeArrayRef(argTypes), false);
    Function *function = Function::Create(ftype, llvm::GlobalValue::InternalLinkage, functionHead->name,
                                          context.module);
    BasicBlock *bblock = BasicBlock::Create(MyContext, "entry", function, nullptr);
    context.pushBlock(bblock);
    context.blocksStack.top()->function = function;
    p = functionHead->parameters->paraDeclList;
    llvm::Value *arg_value;
    auto args_values = function->arg_begin();
    //    std::vector<llvm::Value *> var;
    std::vector<int> place;
    int i = 0;
    while (p) {
        NameList *n;
        if (p->paraTypeList->type == ParaTypeList::T_VAL) {
            n = p->paraTypeList->valParaList->nameList;
        } else {
            n = p->paraTypeList->varParaList->nameList;
        }
        while (n) {
            if (p->paraTypeList->type == ParaTypeList::T_VAR) {
                AllocaInst *alloc = new AllocaInst(Type::getInt32PtrTy(MyContext), 0, n->name,
                                                   context.currentBlock()); // or switch ??
                context.local()[n->name] = alloc;
                context.varType()[n->name] = new TypeDecl(p->paraTypeList->typeDecl);
                context.reference().insert(n->name);
                //                var.push_back(go);
                place.push_back(i);
                new llvm::StoreInst(args_values, alloc, false, context.currentBlock());
            } else {
                AllocaInst *alloc = new AllocaInst(p->paraTypeList->typeDecl->getType(context), 0, n->name,
                                                   context.currentBlock()); // 那个1是干什么的呢
                context.local()[n->name] = alloc;
                context.varType()[n->name] = new TypeDecl(p->paraTypeList->typeDecl);
                new llvm::StoreInst(args_values, alloc, false, context.currentBlock());
            }
            i++;
            args_values++;
            n = n->nameList;
        }
        p = p->paraDeclList;
    }
    if (context.funcParams.find(functionHead->name) != context.funcParams.end()) {
        std::cout << "Error, redeclare function: " << functionHead->name;
        exit(0);
    }
    //    context.funcParams[functionHead->name].storePlace = var;
    context.funcParams[functionHead->name].position = place;
    AllocaInst *alloc = new AllocaInst(functionHead->returnType->getType(context), 0, functionHead->name,
                                       context.currentBlock()); // 那个1是干什么的呢
    context.local()[functionHead->name] = alloc;
    context.varType()[functionHead->name] = new TypeDecl(functionHead->returnType);

    subRoutine->codeGen(context);

    // Load return value
    auto retVal = new LoadInst(alloc, "", false, context.currentBlock());
    llvm::ReturnInst::Create(MyContext, retVal, context.currentBlock());
    context.popBlock();

    while (context.blocksStack.top() != parent)
        context.popBlock();

    return function;
}

llvm::Value *ProcedureDecl::codeGen(CodeGenContext &context) {
    CodeGenBlock *parent = context.blocksStack.top();
    std::vector<Type *> argTypes;
    ParaDeclList *p = procedureHead->parameters->paraDeclList;
    while (p) {
        NameList *n;
        if (p->paraTypeList->type == ParaTypeList::T_VAL) {
            n = p->paraTypeList->valParaList->nameList;
            while (n) {
                argTypes.push_back(p->paraTypeList->typeDecl->getType(context));
                n = n->nameList;
            }
        } else {
            n = p->paraTypeList->varParaList->nameList;
            while (n) {
                argTypes.push_back(Type::getInt32PtrTy(MyContext)); // or switch??
                n = n->nameList;
            }
        }

        p = p->paraDeclList;
    } // 反正倒序定义的到时候倒序访问应该不成问题假装
    FunctionType *ftype = FunctionType::get(Type::getVoidTy(MyContext), makeArrayRef(argTypes), false);
    Function *function = Function::Create(ftype, llvm::GlobalValue::InternalLinkage, procedureHead->name,
                                          context.module);
    BasicBlock *bblock = BasicBlock::Create(MyContext, "entry", function, nullptr);
    context.pushBlock(bblock);
    context.blocksStack.top()->function = function;
    p = procedureHead->parameters->paraDeclList;
    llvm::Value *arg_value;
    auto args_values = function->arg_begin();
    //    std::vector<llvm::Value *> var;
    std::vector<int> place;
    int i = 0;
    while (p) {
        NameList *n;
        if (p->paraTypeList->type == ParaTypeList::T_VAL) {
            n = p->paraTypeList->valParaList->nameList;
        } else {
            n = p->paraTypeList->varParaList->nameList;
        }
        while (n) {
            if (p->paraTypeList->type == ParaTypeList::T_VAR) {
                AllocaInst *alloc = new AllocaInst(Type::getInt32PtrTy(MyContext), 0, n->name,
                                                   context.currentBlock()); // or switch ??
                context.local()[n->name] = alloc;
                context.varType()[n->name] = new TypeDecl(p->paraTypeList->typeDecl);
                context.reference().insert(n->name);
                //                var.push_back(go);
                place.push_back(i);
                new llvm::StoreInst(args_values, alloc, false, context.currentBlock());
            } else {
                AllocaInst *alloc = new AllocaInst(p->paraTypeList->typeDecl->getType(context), 0, n->name,
                                                   context.currentBlock()); // 那个1是干什么的呢
                context.local()[n->name] = alloc;
                context.varType()[n->name] = new TypeDecl(p->paraTypeList->typeDecl);
                new llvm::StoreInst(args_values, alloc, false, context.currentBlock());
            }
            i++;
            args_values++;
            n = n->nameList;
        }
        p = p->paraDeclList;
    }
    if (context.funcParams.find(procedureHead->name) != context.funcParams.end()) {
        std::cout << "Error, redeclare procedure: " << procedureHead->name;
        exit(0);
    }
    //    context.funcParams[procedureHead->name].storePlace = var;
    context.funcParams[procedureHead->name].position = place;

    subRoutine->codeGen(context);

    // Load return value
    //    auto retVal = new LoadInst(alloc, "", false, context.currentBlock());
    //    llvm::ReturnInst::Create(MyContext, retVal, bblock
    //    );
    llvm::ReturnInst::Create(MyContext, nullptr, context.currentBlock());
    context.popBlock();

    while (context.blocksStack.top() != parent)
        context.popBlock();

    return function;
}

llvm::Value *SubRoutine::codeGen(CodeGenContext &context) {
    routineHead->codeGen(context);
    routineBody->codeGen(context);
    clearConstTable(context.constTable);
    return nullptr;
}

void SubRoutine::clearConstTable(ConstTable &table) {
    if (routineHead->constPart->constExprList)
        routineHead->constPart->constExprList->removeFromConstTable(table);
};

llvm::Value *RoutineBody::codeGen(CodeGenContext &context) {
    return compoundStmt->codeGen(context);
}

llvm::Value *CompoundStmt::codeGen(CodeGenContext &context) {
    return stmtList->codeGen(context);
}

llvm::Value *StmtList::codeGen(CodeGenContext &context) {
    if (preList)
        preList->codeGen(context);
    if (stmt)
        stmt->codeGen(context);
    return nullptr;
}

llvm::Value *Stmt::codeGen(CodeGenContext &context) {
    nonLabelStmt->codeGen(context);
    return nullptr;
}

llvm::Value *NonLabelStmt::codeGen(CodeGenContext &context) {
    switch (type) {
        case T_ASSIGN:
            return assignStmt->codeGen(context);
        case T_PROC:
            return procStmt->codeGen(context);
        case T_IF:
            return ifStmt->codeGen(context);
        case T_REPEAT:
            return repeatStmt->codeGen(context);
        case T_CASE:
            return caseStmt->codeGen(context);
        case T_COMPOUND:
            return compoundStmt->codeGen(context);
        case T_GOTO:
            return gotoStmt->codeGen(context);
        case T_FOR:
            return forStmt->codeGen(context);
        case T_WHILE:
            return whileStmt->codeGen(context);
        default:
            return nullptr;
    }
}

void getPrintArgs(std::vector<llvm::Value *> &printf_args, std::string &printf_format, ExpressionList *p,
                  CodeGenContext &context) {
    if (p) {
        if (p->preList)
            getPrintArgs(printf_args, printf_format, p->preList, context);
        auto arg_val = p->expression->codeGen(context);
        if (arg_val->getType() == llvm::Type::getInt32Ty(MyContext)) {
            printf_format += "%d ";
            //            std::cout << "SysFuncCall write variable previous name" << arg_val->getName().str() << std::endl;
            printf_args.push_back(arg_val);
        } else if (arg_val->getType()->isDoubleTy() /*== llvm::Type::getDoubleTy(llvm::getGlobalContext())*/) {
            printf_format += "%lf ";
            printf_args.push_back(arg_val);
        } else if (arg_val->getType() == Type::getInt8Ty(MyContext)) {
            printf_format += "%c ";
            printf_args.push_back(arg_val);
        } else if (arg_val->getType() == Type::getInt1Ty(MyContext)) {
            printf_format += "%d ";
            printf_args.push_back(arg_val);
        } else if (arg_val->getType() == llvm::Type::getInt8PtrTy(MyContext)) {
            assert("print string" == "not implemented");
        }
    }
}

void getReadArgs(std::vector<llvm::Value *> &printf_args, std::string &printf_format, Factor *f,
                 CodeGenContext &context) {
    if (f) {
//        if (p->preList)
//            getReadArgs(printf_args, printf_format, p->preList, context);
        Value *arg_val;
        Type *type;
//        assert(p->expression->expr->term->factor); // 输入必须是简单的东西
        switch (f->type) {
            case Factor::T_NAME: {
                arg_val = f->codeGen(context);
                type = arg_val->getType();
                auto b = context.isReference(f->name);
                if (b) {
                    arg_val = new LoadInst(context.isVariable(f->name)->locals[f->name], "", context.currentBlock());
                } else {
                    arg_val = context.isVariable(
                            f->name)->locals[f->name];
                }
                break;
            }
            case Factor::T_ID_DOT_ID: {
                arg_val = f->codeGen(context);
                type = arg_val->getType();
                arg_val = GetRecordRef(context, f->id, f->recordId);
                break;
            }
            case Factor::T_ID_EXPR: {
                arg_val = GetArrayRef(context, f->id, f->expression);
                type = context.isVariable(f->id)->varTypes[f->id]->arrayTypeDecl->elementType->getType(context, "");
                break;
            }
            default:
                assert("read type" == "not support");
                return;
        }
        if (type == llvm::Type::getInt32Ty(MyContext)) {
            printf_format += "%d";
            //            std::cout << "SysFuncCall write variable previous name" << arg_val->getName().str() << std::endl;
            printf_args.push_back(arg_val);
        } else if (type->isDoubleTy() /*== llvm::Type::getDoubleTy(llvm::getGlobalContext())*/) {
            printf_format += "%lf";
            printf_args.push_back(arg_val);
        } else if (type == Type::getInt8Ty(MyContext)) {
            printf_format += "%c";
            printf_args.push_back(arg_val);
        } else if (type == Type::getInt1Ty(MyContext)) {
            printf_format += "%d";
            printf_args.push_back(arg_val);
        } else if (type == llvm::Type::getInt8PtrTy(MyContext)) {
            assert("read string" == "not implemented");
        }
    }
}

llvm::Value *funcGen(CodeGenContext &context, std::string &procId, ArgsList *argsList) {
    Function *function = context.module->getFunction(procId);
    if (function == nullptr) {
        std::cout << "Function/procedure called but not declared: " << procId << std::endl;
        exit(0);
    }
    std::vector<Value *> args;
    auto p = argsList;
    int k = 0;
    auto j = context.funcParams[procId].position.begin();
    while (p) {
        if (j != context.funcParams[procId].position.end() && k == *j) {
            auto zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(MyContext));

            std::vector<llvm::Value *> indices;
            indices.push_back(zero);
            //            indices.push_back(zero);

            //            auto tmp = new llvm::LoadInst(*i, "", false, context.currentBlock()); // ??
            if (!p->expression || p->expression->type != Expression::T_EXPR ||
                p->expression->expr->type != Expr::T_TERM ||
                p->expression->expr->term->type != Term::T_FACTOR ||
                (p->expression->expr->term->factor->type != Factor::T_NAME &&
                 p->expression->expr->term->factor->type != Factor::T_ID_DOT_ID &&
                 p->expression->expr->term->factor->type != Factor::T_ID_EXPR)) {
                std::cout << "Reference must pass a variable." << std::endl;
                exit(0);
            }
            if (p->expression->expr->term->factor->type == Factor::T_NAME) {
                auto name = p->expression->expr->term->factor->name;
                if (context.constTable.isConst(name)) {
                    assert("const value" == "should not be referenced");
                }
                auto b = context.blocksStack.top();
                while (b) {
                    if (b->locals.find(name) == b->locals.end()) {
                        b = b->preBlock;
                        continue;
                    }
                    GetElementPtrInst *var_ref;
                    if (context.isReference(name)) {
                        auto tmp = new LoadInst(b->locals[name], "", false, context.currentBlock());
                        var_ref = GetElementPtrInst::Create(nullptr,
                                                            tmp,
                                                            makeArrayRef(indices), "",
                                                            context.currentBlock());
                    } else {
                        var_ref = GetElementPtrInst::Create(nullptr,
                                                            b->locals[name],
                                                            makeArrayRef(indices), "",
                                                            context.currentBlock());
                    }
                    args.push_back(var_ref);
                    break;
                }
            } else if (p->expression->expr->term->factor->type == Factor::T_ID_DOT_ID) {
                GetElementPtrInst *var_ref = GetElementPtrInst::Create(Type::getInt32Ty(MyContext),
                                                                       GetRecordRef(context,
                                                                                    p->expression->expr->term->factor->id,
                                                                                    p->expression->expr->term->factor->recordId),
                                                                       makeArrayRef(indices), "",
                                                                       context.currentBlock());
                args.push_back(var_ref);
            } else {
                GetElementPtrInst *var_ref = GetElementPtrInst::Create(Type::getInt32Ty(MyContext),
                                                                       GetArrayRef(context,
                                                                                   p->expression->expr->term->factor->id,
                                                                                   p->expression->expr->term->factor->expression),
                                                                       makeArrayRef(indices), "",
                                                                       context.currentBlock());
                args.push_back(var_ref);
            }
            j++;
        } else {
            args.push_back(p->expression->codeGen(context));
        }
        p = p->preList;
        k++;


    }

    auto call = llvm::CallInst::Create(function, llvm::makeArrayRef(args), "", context.currentBlock());


    return call;
}

llvm::Value *ProcStmt::codeGen(CodeGenContext &context) {
    if (type == T_SIMPLE || type == T_SIMPLE_ARGS) {
        return funcGen(context, procId, argsList);
    } else if (type == T_SYS_PROC_EXPR) {
        if (sysProc == "write" || sysProc == "writeln") {
            std::string printf_format;
            std::vector<llvm::Value *> printf_args;

            ExpressionList *p = expressionList;
            getPrintArgs(printf_args, printf_format, p, context);
            if (sysProc == "writeln")
                printf_format += "\n";
            //            else printf_format = printf_format.substr(0, printf_format.size()-1);
            //            std::cout << printf_format << std::endl;

            auto printf_format_const = llvm::ConstantDataArray::getString(MyContext, printf_format, true);
            auto format_string_var = new llvm::GlobalVariable(*context.module,
                                                              llvm::ArrayType::get(llvm::IntegerType::get(MyContext, 8),
                                                                                   printf_format.size() + 1), true,
                                                              llvm::GlobalValue::PrivateLinkage, printf_format_const,
                                                              ".str");
            auto zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(MyContext));

            std::vector<llvm::Constant *> indices;
            indices.push_back(zero);
            indices.push_back(zero);
            auto var_ref = llvm::ConstantExpr::getGetElementPtr(
                    llvm::ArrayType::get(llvm::IntegerType::get(MyContext, 8), printf_format.size() + 1),
                    format_string_var,
                    indices);

            printf_args.insert(printf_args.begin(), var_ref);
            auto call = llvm::CallInst::Create(context.print, llvm::makeArrayRef(printf_args), "",
                                               context.currentBlock());
            return call;
        }
    } else if (type == T_READ) {
        std::string printf_format;
        std::vector<llvm::Value *> printf_args;

        Factor *p = factor;
        getReadArgs(printf_args, printf_format, p, context);

        auto printf_format_const = llvm::ConstantDataArray::getString(MyContext, printf_format, true);
        auto format_string_var = new llvm::GlobalVariable(*context.module,
                                                          llvm::ArrayType::get(llvm::IntegerType::get(MyContext, 8),
                                                                               printf_format.size() + 1), true,
                                                          llvm::GlobalValue::PrivateLinkage, printf_format_const,
                                                          ".str");
        auto zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(MyContext));

        std::vector<llvm::Constant *> indices;
        indices.push_back(zero);
        indices.push_back(zero);
        auto var_ref = llvm::ConstantExpr::getGetElementPtr(
                llvm::ArrayType::get(llvm::IntegerType::get(MyContext, 8), printf_format.size() + 1),
                format_string_var,
                indices);

        printf_args.insert(printf_args.begin(), var_ref);
        auto call = llvm::CallInst::Create(context.read, llvm::makeArrayRef(printf_args), "",
                                           context.currentBlock());
        return call;
    }
    return nullptr;
}

TypeDecl *RecordTypeDecl::findName(const std::string & s) {
    TypeDecl *t;
    FieldDeclList *x = fieldDeclList;
    while (x) {
        auto n = x->fieldDecl->nameList;
        while (n) {
            if(n->name == s) return x->fieldDecl->typeDecl;
            n = n->nameList;
        }
        x = x->preList;
    }
    return nullptr;
}

llvm::Value *AssignStmt::codeGen(CodeGenContext &context) {
    CodeGenBlock *b = context.blocksStack.top();
    while (b) {
        if (b->locals.find(id) == b->locals.end()) {
            b = b->preBlock;
            continue;
        }
        if (context.constTable.isConst(id)) {
            assert("const value" == "should not be changed");
        }
        if (b->locals[id] == nullptr) {
            std::cout << "Uninitialize variable: " << id << std::endl;
        }
        if (type == T_SIMPLE) {
            if (context.isReference(id)) {
                auto tmp = new llvm::LoadInst(b->locals[id], "", false, context.currentBlock());
                auto r = rhs->codeGen(context);
                if(r->getType() != b->varTypes[id]->getType(context, "")){
                    assert("Assign stmt error" == "left and right has different types");
                }
                return new llvm::StoreInst(r, tmp, false, context.currentBlock());
            }
            return new llvm::StoreInst(rhs->codeGen(context), b->locals[id], false, context.currentBlock());
        } else if (type == T_ARRAY) {
            auto r = rhs->codeGen(context);
            if(r->getType() != b->varTypes[id]->arrayTypeDecl->elementType->getType(context, "")){
                assert("Assign stmt error" == "left and right has different types");
            }
            return new llvm::StoreInst(r, GetArrayRef(context, id, index), false,
                                       context.currentBlock());
        } else {
            auto r = rhs->codeGen(context);
            if(r->getType() != b->varTypes[id]->recordTypeDecl->findName(id)->getType(context, "")){
                assert("Assign stmt error" == "left and right has different types");
            }
            return new StoreInst(r, GetRecordRef(context, id, recordId), false,
                                 context.currentBlock());
        }
    }
    return nullptr;
}

llvm::Value *CaseStmt::codeGen(CodeGenContext &context) {
    Function *currentFuction = context.blocksStack.top()->function;
    Value *condition = expression->codeGen(context);
    BasicBlock *bmerge = BasicBlock::Create(MyContext, "mergeStmt", currentFuction);
    if (caseExprList) caseExprList->codeGen(context, condition, bmerge);
    llvm::BranchInst::Create(bmerge, context.currentBlock());
    context.popBlock();
    context.pushBlock(bmerge);
    context.blocksStack.top()->function = currentFuction;
    return nullptr;
}

llvm::Value *CaseExprList::codeGen(CodeGenContext &context, Value *condition, BasicBlock *bmerge) {
    if (preList) preList->codeGen(context, condition, bmerge);
    if (caseExpr) return caseExpr->codeGen(context, condition, bmerge);
    return nullptr;
}

llvm::Value *CaseExpr::codeGen(CodeGenContext &context, Value *condition, BasicBlock *bmerge) {
    Function *currentFuction = context.blocksStack.top()->function;
    BasicBlock *btrue = BasicBlock::Create(MyContext, "thenStmt", currentFuction);
    BasicBlock *bfalse = BasicBlock::Create(MyContext, "elseStmt", currentFuction);
//    BasicBlock *bmerge = BasicBlock::Create(MyContext, "mergeStmt", currentFuction);
    Value *cmp;
    if (type == T_CONST) cmp = constValue->codeGen(context);
    else {
        if (context.isReference(id)) {
            cmp = new llvm::LoadInst(context.isVariable(id)->locals[id], "", false, context.currentBlock());
            cmp = new llvm::LoadInst(cmp, "", false, context.currentBlock());
        } else
            cmp = new llvm::LoadInst(context.isVariable(id)->locals[id], "", false, context.currentBlock());
    }
    auto res = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ,
                                     cmp, condition, "", context.currentBlock());
    llvm::Instruction *ret = llvm::BranchInst::Create(btrue, bfalse, res, context.currentBlock());
    context.pushBlock(btrue);
    context.blocksStack.top()->function = currentFuction;
    stmt->codeGen(context);
    llvm::BranchInst::Create(bmerge, context.currentBlock());
    context.popBlock();
    context.pushBlock(bfalse);
    context.blocksStack.top()->function = currentFuction;
    return nullptr;
}


llvm::Value *IfStmt::codeGen(CodeGenContext &context) {
    Function *currentFuction = context.blocksStack.top()->function;
    Value *condition = expression->codeGen(context);
    BasicBlock *btrue = BasicBlock::Create(MyContext, "thenStmt", currentFuction);
    BasicBlock *bfalse = BasicBlock::Create(MyContext, "elseStmt", currentFuction);
    BasicBlock *bmerge = BasicBlock::Create(MyContext, "mergeStmt", currentFuction);
    llvm::Instruction *ret = llvm::BranchInst::Create(btrue, bfalse, condition, context.currentBlock());
    context.pushBlock(btrue);
    context.blocksStack.top()->function = currentFuction;

    stmt->codeGen(context);
    llvm::BranchInst::Create(bmerge, context.currentBlock());
    context.popBlock();
    context.pushBlock(bfalse);
    context.blocksStack.top()->function = currentFuction;
    if (elseClause)
        elseClause->codeGen(context);
    llvm::BranchInst::Create(bmerge, context.currentBlock());
    context.popBlock();
    context.pushBlock(bmerge);
    context.blocksStack.top()->function = currentFuction;
    return ret;
}

llvm::Value *ElseClause::codeGen(CodeGenContext &context) {
    if (stmt)
        return stmt->codeGen(context);
    else
        return nullptr;
}

llvm::Value *WhileStmt::codeGen(CodeGenContext &context) {
    Function *currentFuction = context.blocksStack.top()->function;
    BasicBlock *sloop = BasicBlock::Create(MyContext, "startloop", currentFuction);
    BasicBlock *bloop = BasicBlock::Create(MyContext, "loopStmt", currentFuction);
    BasicBlock *bexit = BasicBlock::Create(MyContext, "eixtStmt", currentFuction);

    llvm::BranchInst::Create(sloop, context.currentBlock());
    context.pushBlock(sloop);
    context.blocksStack.top()->function = currentFuction;
    Value *test = whileCondition->codeGen(context);
    llvm::Instruction *ret = llvm::BranchInst::Create(bloop, bexit, test, context.currentBlock());
    context.popBlock();
    context.pushBlock(bloop);
    context.blocksStack.top()->function = currentFuction;
    stmt->codeGen(context);
    llvm::BranchInst::Create(sloop, context.currentBlock());
    context.popBlock();
    context.pushBlock(bexit);
    context.blocksStack.top()->function = currentFuction;
    //    context.popBlock(); // ??
    return ret;
}

llvm::Value *RepeatStmt::codeGen(CodeGenContext &context) {
    Function *currentFuction = context.blocksStack.top()->function;
    BasicBlock *bloop = BasicBlock::Create(MyContext, "loopStmt", currentFuction);
    BasicBlock *bexit = BasicBlock::Create(MyContext, "eixtStmt", currentFuction);
    llvm::BranchInst::Create(bloop, context.currentBlock());

    context.pushBlock(bloop);
    context.blocksStack.top()->function = currentFuction;

    stmtList->codeGen(context);
    Value *test = untilCondition->codeGen(context);
    llvm::Instruction *ret = llvm::BranchInst::Create(bexit, bloop, test, context.currentBlock());
    context.popBlock();

    context.pushBlock(bexit);
    context.blocksStack.top()->function = currentFuction;

    //    context.popBlock(); // ??
    return ret;
}

llvm::Value *Expression::codeGen(CodeGenContext &context) {
    Value *res = nullptr;
    if (type == T_EXPR) {
        res = expr->codeGen(context);
    } else {
        Value *op1_val = expression->codeGen(context);
        Value *op2_val = expr->codeGen(context);
        if (op1_val->getType() == Type::getDoubleTy(MyContext) || op2_val->getType() == Type::getDoubleTy(MyContext)) {
            if (op1_val->getType() != Type::getDoubleTy(MyContext)) {
                op1_val = CastInst::Create(
                        CastInst::getCastOpcode(op1_val, true, Type::getDoubleTy(MyContext), true), op1_val,
                        Type::getDoubleTy(MyContext), "", context.currentBlock());
            }
            if (op2_val->getType() != Type::getDoubleTy(MyContext)) {
                op2_val = CastInst::Create(
                        CastInst::getCastOpcode(op2_val, true, Type::getDoubleTy(MyContext), true), op2_val,
                        Type::getDoubleTy(MyContext), "", context.currentBlock());
            }
        }
        switch (type) {
            case T_EQ:
                res = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ,
                                            op1_val, op2_val, "", context.currentBlock());
                break;
            case T_NE:
                res = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE,
                                            op1_val, op2_val, "", context.currentBlock());
                break;
            case T_LT:
                res = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLT,
                                            op1_val, op2_val, "", context.currentBlock());
                break;
            case T_GT:
                res = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGT,
                                            op1_val, op2_val, "", context.currentBlock());
                break;
            case T_LE:
                res = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLE,
                                            op1_val, op2_val, "", context.currentBlock());
                break;
            case T_GE:
                res = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGE,
                                            op1_val, op2_val, "", context.currentBlock());
                break;
            default:
                res = nullptr;
                break;
        }
    }
    //    lastValue = res;
    return res;
}

llvm::Value *Expr::codeGen(CodeGenContext &context) {
    if (type == T_TERM)
        return term->codeGen(context);
    Value *op1_val = expr->codeGen(context);
    Value *op2_val = term->codeGen(context);
    if (op1_val->getType() == Type::getDoubleTy(MyContext) || op2_val->getType() == Type::getDoubleTy(MyContext)) {
        if (op1_val->getType() != Type::getDoubleTy(MyContext)) {
            op1_val = CastInst::Create(
                    CastInst::getCastOpcode(op1_val, true, Type::getDoubleTy(MyContext), true), op1_val,
                    Type::getDoubleTy(MyContext), "", context.currentBlock());
        }
        if (op2_val->getType() != Type::getDoubleTy(MyContext)) {
            op2_val = CastInst::Create(
                    CastInst::getCastOpcode(op2_val, true, Type::getDoubleTy(MyContext), true), op2_val,
                    Type::getDoubleTy(MyContext), "", context.currentBlock());
        }
    }
    assert(op1_val->getType() == op2_val->getType());
    switch (type) {
        case T_PLUS:
            if (op1_val->getType() == Type::getDoubleTy(MyContext))
                return llvm::BinaryOperator::Create(llvm::Instruction::FAdd,
                                                    op1_val, op2_val, "", context.currentBlock());
            else
                return llvm::BinaryOperator::Create(llvm::Instruction::Add,
                                                    op1_val, op2_val, "", context.currentBlock());
        case T_MINUS:
            if (op1_val->getType() == Type::getDoubleTy(MyContext))
                return llvm::BinaryOperator::Create(llvm::Instruction::FSub,
                                                    op1_val, op2_val, "", context.currentBlock());
            else
                return llvm::BinaryOperator::Create(llvm::Instruction::Sub,
                                                    op1_val, op2_val, "", context.currentBlock());
        case T_OR:
            return llvm::BinaryOperator::Create(llvm::Instruction::Or,
                                                op1_val, op2_val, "", context.currentBlock());
        default:
            return nullptr;
    }
}

llvm::Value *Term::codeGen(CodeGenContext &context) {
    if (type == T_FACTOR)
        return factor->codeGen(context);
    if (type == T_FACTOR)
        return factor->codeGen(context);
    Value *op1_val = term->codeGen(context);
    Value *op2_val = factor->codeGen(context);
    if (op1_val->getType() == Type::getDoubleTy(MyContext) || op2_val->getType() == Type::getDoubleTy(MyContext)) {
        if (op1_val->getType() != Type::getDoubleTy(MyContext)) {
            op1_val = CastInst::Create(
                    CastInst::getCastOpcode(op1_val, true, Type::getDoubleTy(MyContext), true), op1_val,
                    Type::getDoubleTy(MyContext), "", context.currentBlock());
        }
        if (op2_val->getType() != Type::getDoubleTy(MyContext)) {
            op2_val = CastInst::Create(
                    CastInst::getCastOpcode(op2_val, true, Type::getDoubleTy(MyContext), true), op2_val,
                    Type::getDoubleTy(MyContext), "", context.currentBlock());
        }
    }
    assert(op1_val->getType() == op2_val->getType());
    switch (type) {
        case T_MUL:
            if (op1_val->getType() == Type::getDoubleTy(MyContext)) {
                return llvm::BinaryOperator::Create(llvm::Instruction::FMul,
                                                    op1_val, op2_val, "", context.currentBlock());
            } else
                return llvm::BinaryOperator::Create(llvm::Instruction::Mul,
                                                    op1_val, op2_val, "", context.currentBlock());
        case T_DIV:
            if (op1_val->getType() == Type::getInt32Ty(MyContext))
                return llvm::BinaryOperator::Create(llvm::Instruction::SDiv,
                                                    op1_val, op2_val, "", context.currentBlock());
            else
                return llvm::BinaryOperator::Create(llvm::Instruction::FDiv, op1_val, op2_val, "",
                                                    context.currentBlock());
        case T_AND:
            return llvm::BinaryOperator::Create(llvm::Instruction::And,
                                                op1_val, op2_val, "", context.currentBlock());
        case T_MOD:
            return llvm::BinaryOperator::Create(llvm::Instruction::SRem,
                                                op1_val, op2_val, "", context.currentBlock());
        default:
            return nullptr;
    }
}

llvm::Value *Factor::codeGen(CodeGenContext &context) {
    auto p = context.blocksStack.top();
    switch (type) {
        case T_NAME: {
            while (p) {
                if (p->locals.find(name) == p->locals.end()) {
                    p = p->preBlock;
                    continue;
                }
                if (p->locals[name] == nullptr) {
                    std::cout << "Uninitialize variable: " << name << std::endl;
                }
                if (context.constTable.isConst(name))
                    return p->locals[name];
                if (context.isReference(name)) {
                    auto tmp = new llvm::LoadInst(p->locals[name], "", false, context.currentBlock());
                    return new llvm::LoadInst(tmp, "", false, context.currentBlock());
                }
                return new llvm::LoadInst(p->locals[name], "", false, context.currentBlock()); // ??
            }
            std::cout << "Undefined variable: " << name << std::endl;
            exit(1);
        }
        case T_CONST:
            return constValue->codeGen(context);
        case T_EXPR:
            return expression->codeGen(context);
        case T_NOT_FACTOR: {
            Value *tmp;
            assert(factor->type == T_NAME);
            Function *currentFuction = context.blocksStack.top()->function;
            Value *v = factor->codeGen(context);
            BasicBlock *btrue = BasicBlock::Create(MyContext, "thenStmt", context.blocksStack.top()->function);
            BasicBlock *bfalse = BasicBlock::Create(MyContext, "elseStmt", context.blocksStack.top()->function);
            BasicBlock *bmerge = BasicBlock::Create(MyContext, "mergeStmt", context.blocksStack.top()->function);
            llvm::Instruction *ret = llvm::BranchInst::Create(btrue, bfalse, v, context.currentBlock());
            context.pushBlock(btrue);
            context.blocksStack.top()->function = currentFuction;
            if (v->getType() == Type::getDoubleTy(MyContext)) {
                tmp = ConstantFP::get(MyContext, llvm::APFloat(0.0));
            } else {
                tmp = ConstantInt::get(MyContext, llvm::APInt(32, 0, false));
            }
            llvm::BranchInst::Create(bmerge, context.currentBlock());
            context.popBlock();
            context.pushBlock(bfalse);
            context.blocksStack.top()->function = currentFuction;
            if (v->getType() == Type::getDoubleTy(MyContext)) {
                tmp = ConstantFP::get(MyContext, llvm::APFloat(1.0));
            } else {
                tmp = ConstantInt::get(MyContext, llvm::APInt(32, 1, false));
            }
            llvm::BranchInst::Create(bmerge, context.currentBlock());
            context.popBlock();
            context.pushBlock(bmerge);
            context.blocksStack.top()->function = currentFuction;

            return tmp; // not finished
        }
        case T_NAME_ARGS:
            return funcGen(context, name, argsList);
        case T_MINUS_FACTOR: {
            auto val_2 = factor->codeGen(context);
            if (val_2->getType() == Type::getDoubleTy(MyContext)) {
                return BinaryOperator::Create(Instruction::FSub, ConstantFP::get(MyContext, llvm::APFloat(0.0)),
                                              val_2, "", context.currentBlock());
            } else
                return BinaryOperator::Create(Instruction::Sub,
                                              ConstantInt::get(val_2->getType(), llvm::APInt(32, 0, false)), val_2,
                                              "",
                                              context.currentBlock());

            //            auto e = new Expr(2, new Expr(new Term(new Factor(new ConstValue(0, 1)))), new Term(factor));
        }
        case T_ID_DOT_ID:
            return new LoadInst(GetRecordRef(context, id, recordId), "", false, context.currentBlock());
        case T_ID_EXPR:
            return new LoadInst(GetArrayRef(context, id, expression), "", false, context.currentBlock());
        case T_SYS_FUNCT_ARGS:
            if (sysFunction == "chr") {
                auto intV = argsList->expression->codeGen(context);
                return CastInst::CreateIntegerCast(intV, Type::getInt8Ty(MyContext), false, "",
                                                   context.currentBlock());
            } else if (sysFunction == "ord") {
                auto chrV = argsList->expression->codeGen(context);
                return CastInst::CreateIntegerCast(chrV, Type::getInt32Ty(MyContext), true, "",
                                                   context.currentBlock());
            }
            break;
        default:
            return nullptr;
    }
    return nullptr;
}

static Value *GetRecordRef(CodeGenContext &context, const std::string &id, const std::string &recordId) {
    auto p = context.blocksStack.top();
    Value *ptr;
    std::vector<llvm::Value *> idxList;
    while (p) {
        if (p->locals.find(id) == p->locals.end()) {
            p = p->preBlock;
            continue;
        }
        if (p->locals[id] == nullptr) {
            std::cout << "Uninitialize variable: " << id << std::endl;
        }
        assert(p->varTypes[id]->type == TypeDecl::T_RECORD_TYPE_DECLARE);
        FieldDeclList *fieldDeclList = p->varTypes[id]->recordTypeDecl->fieldDeclList;
        int i = 0;
        bool flag = false;
        while (fieldDeclList && !flag) {
            NameList *n = fieldDeclList->fieldDecl->nameList;
            while (n) {
                if (n->name == recordId) {
                    flag = true;
                    break;
                }
                i++;
                n = n->nameList;
            }
            fieldDeclList = fieldDeclList->preList;
        }
        if (!flag) {
            assert("record id" == "not in record member");
        }
        auto first = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, false));
        auto second = llvm::ConstantInt::get(MyContext, llvm::APInt(32, i, false));
        idxList.push_back(first);
        idxList.push_back(second);
        //        ptr = p->locals[id]; // ??
        if (context.isReference(id)) {
            ptr = new llvm::LoadInst(p->locals[id], "", false, context.currentBlock());
            //                ptr = tmp;
        } else {
            ptr = p->locals[id]; // ??
        }
        Type *t = p->varTypes[id]->getType(context, id);
        GetElementPtrInst *elePtr = GetElementPtrInst::Create(nullptr, ptr, makeArrayRef(idxList), "",
                                                              context.currentBlock());
        return elePtr;
    }
    return nullptr;
}


static Value *GetArrayRef(CodeGenContext &context, const std::string &id, Expression *index) {
    auto idxList = std::vector<llvm::Value *>();
    idxList.push_back(llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, false)));
    auto p = context.blocksStack.top();
    while (p) {
        if (p->locals.find(id) == p->locals.end()) {
            p = p->preBlock;
            continue;
        }
        if (p->locals[id] == nullptr) {
            std::cout << "Uninitialize variable: " << id << std::endl;
        }
        //        assert(p->varTypes[id]->type == TypeDecl::T_ARRAY_TYPE_DECLARE);
        Value *ptr;
        if (context.isReference(id)) {
            ptr = new llvm::LoadInst(p->locals[id], "", false, context.currentBlock());
            //                ptr = tmp;
        } else {
            ptr = p->locals[id]; // ??
        }
        Type *t = p->varTypes[id]->getType(context, id);
        Value *lowerBound = llvm::ConstantInt::get(MyContext, llvm::APInt(32,
                                                                          p->varTypes[id]->arrayTypeDecl->range->getLowerBound(
                                                                                  context.constTable), false));
        auto second = llvm::BinaryOperator::Create(llvm::Instruction::Sub, index->codeGen(context),
                                                   lowerBound, "", context.currentBlock());
        idxList.push_back(second);
        GetElementPtrInst *elePtr = GetElementPtrInst::Create(t, ptr, makeArrayRef(idxList), "",
                                                              context.currentBlock());
        return elePtr;
    }
    return nullptr;
}

llvm::Value *ForStmt::codeGen(CodeGenContext &context) {
    Function *currentFuction = context.blocksStack.top()->function;
    BasicBlock *sloop = BasicBlock::Create(MyContext, "startloop", currentFuction);
    BasicBlock *bloop = BasicBlock::Create(MyContext, "loopStmt", currentFuction);
    BasicBlock *bexit = BasicBlock::Create(MyContext, "eixtStmt", currentFuction);
    //  initial for
    AssignStmt *initial = new AssignStmt(loopId, firstBound);
    initial->codeGen(context);
    llvm::BranchInst::Create(sloop, context.currentBlock());
    //  for test
    context.pushBlock(sloop);
    context.blocksStack.top()->function = currentFuction;

    auto *f = new Factor(Factor::T_NAME, loopId);
    Value *test = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ,
                                        f->codeGen(context), secondBound->codeGen(context), "",
                                        context.currentBlock());
    llvm::Instruction *ret = llvm::BranchInst::Create(bexit, bloop, test, context.currentBlock());
    context.popBlock();

    context.pushBlock(bloop);
    context.blocksStack.top()->function = currentFuction;
    stmt->codeGen(context);
    //update
    Factor *f1;
    auto int1 = new ConstValue("1", ConstValue::T_INTEGER);
    Value *update;
    if (direction->type == Direction::T_TO) {
        f1 = new Factor(Factor::T_NAME, loopId);
        update = llvm::BinaryOperator::Create(llvm::Instruction::Add,
                                              f1->codeGen(context), int1->codeGen(context), "",
                                              context.currentBlock());
    } else {
        f1 = new Factor(Factor::T_NAME, loopId);
        update = llvm::BinaryOperator::Create(llvm::Instruction::Sub,
                                              f1->codeGen(context), int1->codeGen(context), "",
                                              context.currentBlock());
    }
    CodeGenBlock *b = context.blocksStack.top();
    while (b) {
        if (b->locals.find(loopId) == b->locals.end()) {
            b = b->preBlock;
            continue;
        }
        if (context.isReference(loopId)) {
            auto tmp = new llvm::LoadInst(b->locals[loopId], "", false, context.currentBlock());
            return new llvm::StoreInst(update, tmp, false, context.currentBlock());
        }
        new llvm::StoreInst(update, b->locals[loopId], false, context.currentBlock());
        break;
    }
    llvm::BranchInst::Create(sloop, context.currentBlock());
    context.popBlock();

    context.pushBlock(bexit);
    context.blocksStack.top()->function = currentFuction;

    //    context.popBlock(); // ??
    stmt->codeGen(context); // why ? -- 因为包括右边的
    delete initial;
    delete f;
    delete int1;
    //    delete update;
    delete f1;
    return ret;
}
