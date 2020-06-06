#ifndef SPLC_NODE_H
#define SPLC_NODE_H

#include <iostream>
#include <map>
#include <regex>

#include <llvm/IR/Value.h>

#include "ASTPredeclaration.h"
#include "CodeGen.h"
#include "ConstTable.h"

namespace CodeGen {
    class CodeGenContext;
}

namespace AST {
    class Node {
    public:
        static int idCount;
        int id;
        std::vector<Node *> _children;

        virtual ~Node() = default;

        virtual llvm::Value *codeGen(CodeGen::CodeGenContext &context) { return nullptr; }

        virtual std::vector<Node *> getChildren() {
          return _children;
        };

        virtual void traverse(std::function<void(Node *)> pre, std::function<void(Node *)> post) {
          try {
            pre(this);
            for (auto i : this->getChildren())
              if (i != nullptr)
                i->traverse(pre, post);
            post(this);
          } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
          }
        }

        virtual std::string getName() {
          std::string id = typeid(*this).name();
          std::smatch matchResult;
          if (std::regex_match(id, matchResult, std::regex("N3AST[0-9]*(.*)E"))) {
            return matchResult[1].str();
          }
          return id;
        }

        virtual std::string getInfo() { return ""; }

        Node() {
          id = ++idCount;
        }

    };

    class AbstractExpression : public Node {
    };

    class AbstractStatement : public Node {
    };

    class Program : public AbstractStatement {
    public:

        ProgramHead *programHead{};
        Routine *routine{};

        Program(ProgramHead *programHead, Routine *routine) : programHead(programHead), routine(routine) {
          _children.emplace_back(programHead);
          _children.emplace_back(routine);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class ProgramHead : public AbstractStatement {
    public:
        std::string id;

        explicit ProgramHead(std::string id) : id(std::move(id)) {}

        std::string getInfo() override {
          return id;
        }
    };


    class Routine : public AbstractStatement {
    public:

        RoutineHead *routineHead{};
        RoutineBody *routineBody{};

        Routine(RoutineHead *routineHead, RoutineBody *routineBody) : routineHead(routineHead), routineBody(routineBody) {
          _children.emplace_back(routineHead);
          _children.emplace_back(routineBody);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class SubRoutine : public AbstractStatement {
    public:

        RoutineHead *routineHead{};
        RoutineBody *routineBody{};

        SubRoutine(RoutineHead *routineHead, RoutineBody *routineBody) : routineHead(routineHead), routineBody(routineBody) {
          _children.emplace_back(routineHead);
          _children.emplace_back(routineBody);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        void clearConstTable(ConstTable &table);
    };

    class RoutineHead : public AbstractStatement {
    public:

        LabelPart *labelPart;
        ConstPart *constPart;
        TypePart *typePart;
        VarPart *varPart;
        RoutinePart *routinePart;

        RoutineHead(LabelPart *labelPart, ConstPart *constPart, TypePart *typePart, VarPart *varPart, RoutinePart *routinePart) :
                labelPart(labelPart), constPart(constPart), typePart(typePart), varPart(varPart), routinePart(routinePart) {
          _children.emplace_back(labelPart);
          _children.emplace_back(constPart);
          _children.emplace_back(typePart);
          _children.emplace_back(varPart);
          _children.emplace_back(routinePart);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class LabelPart : public AbstractStatement {
    };

    class ConstPart : public AbstractStatement {
    public:

        ConstExprList *constExprList{};

        explicit ConstPart(ConstExprList *constExprList) : constExprList(constExprList) {
          _children.emplace_back(constExprList);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class ConstExprList : public AbstractStatement {
    public:

        std::string name;
        ConstExprList *preList{};
        ConstValue *value{};

        ConstExprList(std::string name, ConstExprList *preList, ConstValue *value) :
                name(std::move(name)), preList(preList), value(value) {
          _children.emplace_back(preList);
          _children.emplace_back(value);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::string getInfo() override {
          return name;
        }

        void addToConstTable(ConstTable &table);

        void removeFromConstTable(ConstTable &table);
    };

// TODO: hacks needed
    class ConstValue : public AbstractExpression {
    public:
        enum {T_INTEGER, T_REAL, T_CHAR, T_SYS_CON, T_STRING} type;

        std::string value;

        ConstValue(std::string value, decltype(type) type) : value(std::move(value)), type(type) {
          if (type == T_CHAR)
            this->value = this->value.substr(1, 1);
        }

        ConstValue *negate() {
          if (value == "-" || value.empty())
            return new ConstValue("", type);
          if (value[0] == '-')
            return new ConstValue(value.substr(1), type);
          else
            return new ConstValue("-" + value, type);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::string getInfo() override {
          return std::to_string(type) + ":" + value;
        }
    };

    class TypePart : public AbstractStatement {
    public:

        TypeDeclList *typeDeclList{};

        explicit TypePart(TypeDeclList *typeDeclList) : typeDeclList(typeDeclList) {
          _children.emplace_back(typeDeclList);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class TypeDeclList : public AbstractStatement {
    public:
        TypeDeclList *preList{};
        TypeDefinition *typeDefinition{};

        TypeDeclList(TypeDeclList *preList, TypeDefinition *typeDefinition) :
                preList(preList), typeDefinition(typeDefinition) {
          _children.emplace_back(preList);
          _children.emplace_back(typeDefinition);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class TypeDefinition : public AbstractStatement {
    public:
        std::string name;
        TypeDecl *typeDecl{};

        TypeDefinition(std::string name, TypeDecl *typeDecl) : name(std::move(name)), typeDecl(typeDecl) {
          _children.emplace_back(typeDecl);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::string getInfo() override {
          return name;
        }
    };

    class TypeDecl : public AbstractStatement {
    public:
        enum {T_SIMPLE_TYPE_DECLARE, T_ARRAY_TYPE_DECLARE, T_RECORD_TYPE_DECLARE} type;

        SimpleTypeDecl *simpleTypeDecl{};
        ArrayTypeDecl *arrayTypeDecl{};
        RecordTypeDecl *recordTypeDecl{};

        explicit TypeDecl(SimpleTypeDecl *simpleTypeDecl) : simpleTypeDecl(simpleTypeDecl) {
          type = T_SIMPLE_TYPE_DECLARE;
          _children.emplace_back(simpleTypeDecl);
        }

        explicit TypeDecl(ArrayTypeDecl *arrayTypeDecl) : arrayTypeDecl(arrayTypeDecl) {
          type = T_ARRAY_TYPE_DECLARE;
          _children.emplace_back(arrayTypeDecl);
        }

        explicit TypeDecl(RecordTypeDecl *recordTypeDecl) : recordTypeDecl(recordTypeDecl) {
          type = T_RECORD_TYPE_DECLARE;
          _children.emplace_back(recordTypeDecl);
        }

        llvm::Type *getType(CodeGen::CodeGenContext &context, std::string name);

    };

    class SimpleTypeDecl : public AbstractStatement {
    public:
        enum {T_SYS_TYPE, T_TYPE_NAME, T_ENUMERATION, T_RANGE, T_NAME_RANGE} type;

        std::string sysType;
        std::string name;
        NameList *nameList{};
        ConstValue *lowerBound{}, *upperBound{};
        std::string lowerName, upperName;

        SimpleTypeDecl(decltype(type) type, const std::string &st) : type(type) {
          if (type == T_SYS_TYPE)
            sysType = st;
          if (type == T_TYPE_NAME)
            name = st;
          assert(type == T_SYS_TYPE || type == T_TYPE_NAME);
        }

        explicit SimpleTypeDecl(NameList *nameList) : nameList(nameList), type(T_ENUMERATION) {}

        SimpleTypeDecl(ConstValue *lowerBound, ConstValue *upperBound) :
                lowerBound(lowerBound), upperBound(upperBound), type(T_RANGE) {

        }

        SimpleTypeDecl(std::string lowerName, std::string upperName) :
                lowerName(std::move(lowerName)), upperName(std::move(upperName)), type(T_NAME_RANGE) {

        }

        llvm::Type *getType(CodeGen::CodeGenContext &context);

        std::vector<Node *> getChildren() override {
          auto ch = std::vector<Node *>();
          ch.emplace_back(nameList);
          ch.emplace_back(lowerBound);
          ch.emplace_back(upperBound);
          return ch;
        }

        int getRange(const ConstTable &table) {
          assert(type == T_RANGE || type == T_NAME_RANGE);
          if (type == T_RANGE) {
            assert(upperBound->type == ConstValue::T_INTEGER);
            assert(lowerBound->type == ConstValue::T_INTEGER);
            return std::stoi(upperBound->value) - std::stoi(lowerBound->value) + 1;
          } else {
            return table.getInt(upperName) - table.getInt(lowerName) + 1;
          }
        }

        int getLowerBound(const ConstTable &table) {
          assert(type == T_RANGE || type == T_NAME_RANGE);
          if (type == T_RANGE) {
            assert(upperBound->type == ConstValue::T_INTEGER);
            assert(lowerBound->type == ConstValue::T_INTEGER);
            return std::stoi(lowerBound->value);
          } else {
            return table.getInt(lowerName);
          }
        }
    };

    class ArrayTypeDecl : public AbstractStatement {
    public:
        SimpleTypeDecl *range{};
        TypeDecl *elementType{};

        ArrayTypeDecl(SimpleTypeDecl *range, TypeDecl *elementType) : range(range), elementType(elementType) {
          _children.emplace_back(range);
          _children.emplace_back(elementType);
        }

        llvm::Type *getType(CodeGen::CodeGenContext &context);

        int getLowerBound(const ConstTable &table) {
          return range->getLowerBound(table);
        }

    };

    class RecordTypeDecl : public AbstractStatement {
    public:
        FieldDeclList *fieldDeclList{};

        explicit RecordTypeDecl(FieldDeclList *fieldDeclList) : fieldDeclList(fieldDeclList) {
          _children.emplace_back(fieldDeclList);
        }

        llvm::Type *getType(CodeGen::CodeGenContext &context, std::string &name);

        TypeDecl *findName(const std::string &s);
    };

    class FieldDeclList : public AbstractStatement {
    public:
        FieldDeclList *preList{};
        FieldDecl *fieldDecl{};

        FieldDeclList(FieldDeclList *preList, FieldDecl *fieldDecl) : preList(preList), fieldDecl(fieldDecl) {
          _children.emplace_back(preList);
          _children.emplace_back(fieldDecl);
        }
    };

    class FieldDecl : public AbstractStatement {
    public:
        NameList *nameList{};
        TypeDecl *typeDecl{};

        FieldDecl(NameList *nameList, TypeDecl *typeDecl) : nameList(nameList), typeDecl(typeDecl) {
          _children.emplace_back(nameList);
          _children.emplace_back(typeDecl);
        }
    };

    class NameList : public AbstractStatement {
    public:
        NameList *nameList;
        std::string name;

        NameList(NameList *nameList, std::string name) : nameList(nameList), name(std::move(name)) {
          _children.emplace_back(nameList);
        }

        std::string getInfo() override {
          return name;
        }
    };

    class VarPart : public AbstractStatement {
    public:
        VarDeclList *varDeclList{};

        explicit VarPart(VarDeclList *varDeclList) : varDeclList(varDeclList) {
          _children.emplace_back(varDeclList);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class VarDeclList : public AbstractStatement {
    public:
        VarDeclList *preList{};
        VarDecl *varDecl{};

        VarDeclList(VarDeclList *preList, VarDecl *varDecl) : preList(preList), varDecl(varDecl) {
          _children.emplace_back(preList);
          _children.emplace_back(varDecl);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class VarDecl : public AbstractStatement {
    public:
        NameList *nameList{};
        TypeDecl *typeDecl{};

        VarDecl(NameList *nameList, TypeDecl *typeDecl) : nameList(nameList), typeDecl(typeDecl) {
          _children.emplace_back(nameList);
          _children.emplace_back(typeDecl);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class RoutinePart : public AbstractStatement {
    public:
        enum {T_ROUTINE_FUNC, T_ROUTINE_PROC, T_FUNC, T_PROC, T_EMPTY} type;

        RoutinePart *routinePart{};
        FunctionDecl *functionDecl{};
        ProcedureDecl *procedureDecl{};

        RoutinePart(RoutinePart *routinePart, FunctionDecl *functionDecl) :
                routinePart(routinePart), functionDecl(functionDecl) {
          type = T_ROUTINE_FUNC;
        }

        RoutinePart(RoutinePart *routinePart, ProcedureDecl *procedureDecl) :
                routinePart(routinePart), procedureDecl(procedureDecl) {
          type = T_ROUTINE_PROC;
        }

        explicit RoutinePart(FunctionDecl *functionDecl) : functionDecl(functionDecl) {
          type = T_FUNC;
        }

        explicit RoutinePart(ProcedureDecl *procedureDecl) : procedureDecl(procedureDecl) {
          type = T_PROC;
        }

        explicit RoutinePart(decltype(type) type) : type(type) {
          assert(type == T_EMPTY);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::vector<Node *> getChildren() override {
          auto ch = std::vector<Node *>();
          ch.emplace_back(routinePart);
          ch.emplace_back(functionDecl);
          ch.emplace_back(procedureDecl);
          return ch;
        }
    };

    class FunctionDecl : public AbstractStatement {
    public:
        FunctionHead *functionHead{};
        SubRoutine *subRoutine{};

        FunctionDecl(FunctionHead *functionHead, SubRoutine *subRoutine) :
                functionHead(functionHead), subRoutine(subRoutine) {
          _children.emplace_back(functionHead);
          _children.emplace_back(subRoutine);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class FunctionHead : public AbstractStatement {
    public:
        std::string name;
        Parameters *parameters{};
        SimpleTypeDecl *returnType{};

        FunctionHead(std::string name, Parameters *parameters, SimpleTypeDecl *returnType) :
                name(std::move(name)), parameters(parameters), returnType(returnType) {
          _children.emplace_back(parameters);
          _children.emplace_back(returnType);
        }

        std::string getInfo() override {
          return name;
        }
    };

    class ProcedureDecl : public AbstractStatement {
    public:
        ProcedureHead *procedureHead{};
        SubRoutine *subRoutine{};

        ProcedureDecl(ProcedureHead *procedureHead, SubRoutine *subRoutine) :
                procedureHead(procedureHead), subRoutine(subRoutine) {
          _children.emplace_back(procedureHead);
          _children.emplace_back(subRoutine);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class ProcedureHead : public AbstractStatement {
    public:
        std::string name;
        Parameters *parameters;

        ProcedureHead(std::string name, Parameters *parameters) :
                name(std::move(name)), parameters(parameters) {
          _children.emplace_back(parameters);
        }

        std::string getInfo() override {
          return name;
        }
    };

    class Parameters : public AbstractStatement {
    public:
        ParaDeclList *paraDeclList{};

        explicit Parameters(ParaDeclList *paraDeclList) : paraDeclList(paraDeclList) {
          _children.emplace_back(paraDeclList);
        }
    };

    class ParaDeclList : public AbstractStatement {
    public:
        ParaDeclList *paraDeclList{};
        ParaTypeList *paraTypeList{};

        ParaDeclList(ParaDeclList *paraDeclList, ParaTypeList *paraTypeList) :
                paraDeclList(paraDeclList), paraTypeList(paraTypeList) {
          _children.emplace_back(paraDeclList);
          _children.emplace_back(paraTypeList);
        }
    };

    class ParaTypeList : public AbstractStatement {
    public:
        enum {T_VAR, T_VAL} type;

        VarParaList *varParaList{};
        ValParaList *valParaList{};
        SimpleTypeDecl *typeDecl{};

        ParaTypeList(VarParaList *varParaList, SimpleTypeDecl *typeDecl) :
                varParaList(varParaList), typeDecl(typeDecl) {
          type = T_VAR;
        }

        ParaTypeList(ValParaList *valParaList, SimpleTypeDecl *typeDecl) :
                valParaList(valParaList), typeDecl(typeDecl) {
          type = T_VAL;
        }

        std::vector<Node *> getChildren() override {
          auto ch = std::vector<Node *>();
          ch.emplace_back(varParaList);
          ch.emplace_back(valParaList);
          ch.emplace_back(typeDecl);
          return ch;
        }
    };

    class VarParaList : public AbstractStatement {
    public:
        NameList *nameList{};

        explicit VarParaList(NameList *nameList) : nameList(nameList) {
          _children.emplace_back(nameList);
        }
    };

    class ValParaList : public AbstractStatement {
    public:
        NameList *nameList{};

        explicit ValParaList(NameList *nameList) : nameList(nameList) {
          _children.emplace_back(nameList);
        }
    };

    class RoutineBody : public AbstractStatement {
    public:
        CompoundStmt *compoundStmt{};

        explicit RoutineBody(CompoundStmt *compoundStmt) : compoundStmt(compoundStmt) {
          _children.emplace_back(compoundStmt);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class CompoundStmt : public AbstractStatement {
    public:
        StmtList *stmtList{};

        explicit CompoundStmt(StmtList *stmtList) : stmtList(stmtList) {
          _children.emplace_back(stmtList);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class StmtList : public AbstractStatement {
    public:
        StmtList *preList{};
        Stmt *stmt{};

        StmtList(StmtList *preList, Stmt *stmt) : preList(preList), stmt(stmt) {
          _children.emplace_back(preList);
          _children.emplace_back(stmt);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class Stmt : public AbstractStatement {
    public:
        enum {T_LABELED, T_UNLABELED} type;

        NonLabelStmt *nonLabelStmt{};

        Stmt(decltype(type) type, NonLabelStmt *nonLabelStmt) : type(type), nonLabelStmt(nonLabelStmt) {
          assert(type == T_LABELED || type == T_UNLABELED);
          _children.emplace_back(nonLabelStmt);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

// fixme: shit!
    class NonLabelStmt : public AbstractStatement {
    public:
        enum {T_ASSIGN, T_PROC, T_IF, T_REPEAT, T_WHILE, T_FOR, T_CASE, T_GOTO, T_COMPOUND} type;

        AssignStmt *assignStmt{};
        ProcStmt *procStmt{};
        CompoundStmt *compoundStmt{};
        IfStmt *ifStmt{};
        RepeatStmt *repeatStmt{};
        WhileStmt *whileStmt{};
        ForStmt *forStmt{};
        CaseStmt *caseStmt{};
        GotoStmt *gotoStmt{};

        explicit NonLabelStmt(AssignStmt *assignStmt) : assignStmt(assignStmt) { type = T_ASSIGN; }

        explicit NonLabelStmt(ProcStmt *procStmt) : procStmt(procStmt) { type = T_PROC; }

        explicit NonLabelStmt(CompoundStmt *compoundStmt) : compoundStmt(compoundStmt),
                                                            type(T_COMPOUND) {}

        explicit NonLabelStmt(IfStmt *ifStmt) : ifStmt(ifStmt) { type = T_IF; }

        explicit NonLabelStmt(RepeatStmt *repeatStmt) : repeatStmt(repeatStmt) { type = T_REPEAT; }

        explicit NonLabelStmt(WhileStmt *whileStmt) : whileStmt(whileStmt) { type = T_WHILE; }

        explicit NonLabelStmt(ForStmt *forStmt) : forStmt(forStmt) { type = T_FOR; }

        explicit NonLabelStmt(CaseStmt *caseStmt) : caseStmt(caseStmt) { type = T_CASE; }

        explicit NonLabelStmt(GotoStmt *gotoStmt) : gotoStmt(gotoStmt) { type = T_GOTO; }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::vector<Node *> getChildren() override {
          auto ch = std::vector<Node *>();
          ch.emplace_back(assignStmt);
          ch.emplace_back(procStmt);
          ch.emplace_back(compoundStmt);
          ch.emplace_back(ifStmt);
          ch.emplace_back(repeatStmt);
          ch.emplace_back(whileStmt);
          ch.emplace_back(forStmt);
          ch.emplace_back(caseStmt);
          ch.emplace_back(gotoStmt);
          return ch;
        }
    };

    class AssignStmt : public AbstractStatement {
    public:
        enum {T_SIMPLE, T_ARRAY, T_RECORD} type;

        std::string id;
        Expression *rhs;
        Expression *index{};
        std::string recordId;

        AssignStmt(std::string id, Expression *rhs) : id(std::move(id)), rhs(rhs), type(T_SIMPLE) {}

        AssignStmt(std::string id, Expression *index, Expression *rhs) :
                id(std::move(id)), rhs(rhs), index(index), type(T_ARRAY) {
          _children.emplace_back(rhs);
          _children.emplace_back(index);
        }

        AssignStmt(std::string id, std::string recordId, Expression *rhs) :
                id(std::move(id)), rhs(rhs), recordId(std::move(recordId)), type(T_RECORD) {
          _children.emplace_back(rhs);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::string getInfo() override {
          return id + "=..";
        }
    };

    class ProcStmt : public AbstractStatement {
    public:
        enum {T_SIMPLE, T_SIMPLE_ARGS, T_SYS_PROC, T_SYS_PROC_EXPR, T_READ} type;

        std::string procId;
        ArgsList *argsList{};
        std::string sysProc;
        ExpressionList *expressionList{};

        Factor *factor{};

        ProcStmt(decltype(type) type, const std::string &st) : type(type) {
          assert(type == T_SIMPLE || type == T_SYS_PROC);
          if (type == T_SIMPLE)
            procId = st;
          else
            sysProc = st;
        }

        ProcStmt(std::string procId, ArgsList *argsList) : procId(std::move(procId)),
                                                           argsList(argsList),
                                                           type(T_SIMPLE_ARGS) {
          _children.emplace_back(argsList);
        }

        ProcStmt(std::string sysProc, ExpressionList *expressionList) : sysProc(std::move(sysProc)),
                                                                        expressionList(expressionList),
                                                                        type(T_SYS_PROC_EXPR) {
          _children.emplace_back(expressionList);
        }

        explicit ProcStmt(Factor *factor) : factor(factor), type(T_READ) {}

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::string getInfo() override {
          if (!procId.empty())
            return procId;
          if (!sysProc.empty())
            return sysProc;
          return "";
        }
    };

    class IfStmt : public AbstractStatement {
    public:
        Expression *expression{};
        Stmt *stmt{};
        ElseClause *elseClause{};

        IfStmt(Expression *expression, Stmt *stmt, ElseClause *elseClause) :
                expression(expression), stmt(stmt), elseClause(elseClause) {
          _children.emplace_back(expression);
          _children.emplace_back(stmt);
          _children.emplace_back(elseClause);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class ElseClause : public AbstractStatement {
    public:
        Stmt *stmt{};

        explicit ElseClause(Stmt *stmt) : stmt(stmt) {
          _children.emplace_back(stmt);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class RepeatStmt : public AbstractStatement {
    public:
        StmtList *stmtList{};
        Expression *untilCondition{};

        RepeatStmt(StmtList *stmtList, Expression *untilCondition) : stmtList(stmtList),
                                                                     untilCondition(untilCondition) {
          _children.emplace_back(stmtList);
          _children.emplace_back(untilCondition);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class WhileStmt : public AbstractStatement {
    public:
        Expression *whileCondition{};
        Stmt *stmt{};

        WhileStmt(Expression *whileCondition, Stmt *stmt) : whileCondition(whileCondition),
                                                            stmt(stmt) {
          _children.emplace_back(whileCondition);
          _children.emplace_back(stmt);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class ForStmt : public AbstractStatement {
    public:
        std::string loopId;
        Expression *firstBound;
        Direction *direction;
        Expression *secondBound;
        Stmt *stmt;

        ForStmt(std::string loopId, Expression *firstBound, Direction *direction,
                Expression *secondBound, Stmt *stmt)
                : loopId(std::move(loopId)), firstBound(firstBound), direction(direction),
                  secondBound(secondBound), stmt(stmt) {
          _children.emplace_back(firstBound);
          _children.emplace_back(direction);
          _children.emplace_back(secondBound);
          _children.emplace_back(stmt);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::string getInfo() override {
          return loopId;
        }
    };

    class Direction : public AbstractStatement {
    public:
        enum {T_TO, T_DOWNTO} type;

        explicit Direction(decltype(type) type) : type(type) { assert(type == T_TO || type == T_DOWNTO); }
    };

    class CaseStmt : public AbstractStatement {
    public:
        Expression *expression{};
        CaseExprList *caseExprList{};

        CaseStmt(Expression *expression, CaseExprList *caseExprList) : expression(expression),
                                                                       caseExprList(caseExprList) {
          _children.emplace_back(expression);
          _children.emplace_back(caseExprList);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class CaseExprList : public AbstractStatement {
    public:
        CaseExprList *preList{};
        CaseExpr *caseExpr;

        CaseExprList(CaseExprList *preList, CaseExpr *caseExpr) : preList(preList),
                                                                  caseExpr(caseExpr) {
          _children.emplace_back(preList);
          _children.emplace_back(caseExpr);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context, llvm::Value *condition, llvm::BasicBlock *bmerge);
    };

    class CaseExpr : public AbstractStatement {
    public:
        enum {T_CONST, T_ID} type;

        ConstValue *constValue{};
        std::string id;
        Stmt *stmt;

        CaseExpr(ConstValue *constValue, Stmt *stmt) : constValue(constValue), stmt(stmt), type(T_CONST) {}

        CaseExpr(std::string id, Stmt *stmt) : id(std::move(id)), stmt(stmt), type(T_ID) {}


        std::vector<Node *> getChildren() override {
          auto ch = std::vector<Node *>();
          ch.emplace_back(constValue);
          ch.emplace_back(stmt);
          return ch;
        }


        std::string getInfo() override {
          return id.empty() ? "" : id;
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context, llvm::Value *condition, llvm::BasicBlock *bmerge);

    };

    class GotoStmt : public AbstractStatement {
    public:
        ConstValue *address;

        explicit GotoStmt(const std::string &address) : address(new ConstValue(address, ConstValue::T_INTEGER)) {
          _children.emplace_back(this->address);
        }
    };

    class ExpressionList : public AbstractExpression {
    public:
        ExpressionList *preList{};
        Expression *expression{};

        ExpressionList(ExpressionList *preList, Expression *expression) : preList(preList),
                                                                          expression(expression) {
          _children.emplace_back(preList);
          _children.emplace_back(expression);
        }
    };

    class Expression : public AbstractExpression {
    public:
        enum {T_EQ, T_NE, T_GE, T_GT, T_LE, T_LT, T_EXPR} type;

        Expression *expression{};
        Expr *expr{};

        Expression(decltype(type) type, Expression *expression, Expr *expr) : type(type), expression(expression), expr(expr) {
          _children.emplace_back(expression);
          _children.emplace_back(expr);
        }

        explicit Expression(Expr *expr) : expr(expr), type(T_EXPR) {}

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class Expr : public AbstractExpression {
    public:
        enum {T_PLUS, T_MINUS, T_OR, T_TERM} type;

        Expr *expr{};
        Term *term{};

        Expr(decltype(type) type, Expr *expr, Term *term) : type(type), expr(expr), term(term) {}

        explicit Expr(Term *term) : term(term), type(T_TERM) {
          _children.emplace_back(expr);
          _children.emplace_back(term);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class Term : public AbstractExpression {
    public:
        enum {T_MUL, T_DIV, T_MOD, T_AND, T_FACTOR} type;

        Term *term{};
        Factor *factor{};

        Term(decltype(type) type, Term *term, Factor *factor) : type(type), term(term), factor(factor) {
          _children.emplace_back(term);
          _children.emplace_back(factor);
        }

        explicit Term(Factor *factor) : factor(factor), type(T_FACTOR) {
          _children.emplace_back(factor);
        }

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;
    };

    class Factor : public AbstractExpression {
    public:
        enum {
            T_NAME, T_NAME_ARGS, T_SYS_FUNCT, T_SYS_FUNCT_ARGS, T_CONST, T_EXPR, T_NOT_FACTOR,
            T_MINUS_FACTOR, T_ID_EXPR, T_ID_DOT_ID
        } type;

        std::string name;
        ArgsList *argsList{};
        std::string sysFunction;
        ConstValue *constValue{};
        Expression *expression{};
        Factor *factor{};
        std::string id;
        std::string recordId;


        std::string getInfo() override {
          if (!name.empty())
            return name;
          if (!sysFunction.empty())
            return sysFunction;
          if (!recordId.empty())
            return id + "[" + recordId + "]=..";
          if (!id.empty())
            return id + "=..";
          return "";
        }

        Factor(decltype(type) type, const std::string &st) : type(type) {
          assert(type == T_NAME || type == T_SYS_FUNCT);
          if (type == T_NAME)
            name = st;
          else {
            sysFunction = st;
          }
        }

        Factor(decltype(type) type, const std::string &st, ArgsList *argsList) : type(type), argsList(argsList) {
          assert(type == T_NAME_ARGS || type == T_SYS_FUNCT_ARGS);
          if (type == T_NAME_ARGS)
            name = st;
          else {
            sysFunction = st;
            if (st == "succ" || st == "abs" || st == "odd" || st == "pred" || st == "sqr" || st == "sqrt") {
              name = st + "__";
              this->type = T_NAME_ARGS;
            }
          }
        }

        explicit Factor(ConstValue *constValue) : constValue(constValue), type(T_CONST) {}

        explicit Factor(Expression *expression) : expression(expression), type(T_EXPR) {}

        Factor(decltype(type) type, Factor *factor) : type(type), factor(factor) {
          assert(type == T_NOT_FACTOR || type == T_MINUS_FACTOR);
        }

        Factor(std::string id, Expression *expression) : expression(expression), id(std::move(id)),
                                                         type(T_ID_EXPR) {}

        Factor(std::string id, std::string recordId) : id(std::move(id)), recordId(std::move(recordId)),
                                                       type(T_ID_DOT_ID) {}

        llvm::Value *codeGen(CodeGen::CodeGenContext &context) override;

        std::vector<Node *> getChildren() override {
          auto ch = std::vector<Node *>();
          ch.emplace_back(argsList);
          ch.emplace_back(constValue);
          ch.emplace_back(expression);
          ch.emplace_back(factor);
          return ch;
        }
    };

    class ArgsList : public AbstractStatement {
    public:
        ArgsList *preList;
        Expression *expression;

        ArgsList(ArgsList *preList, Expression *expression) : preList(preList), expression(expression) {
          _children.emplace_back(preList);
          _children.emplace_back(expression);
        }
    };
}

#endif //SPLC_NODE_H
