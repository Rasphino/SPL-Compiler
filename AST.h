#ifndef SPLC_NODE_H
#define SPLC_NODE_H

#include <iostream>
#include <map>
#include <llvm/IR/Value.h>
#include "NodePredeclaration.h"
#include "codegen.h"
#include "ConstTable.h"

class CodeGenContext;

class Node {
public:
    static int idCount;
    int id;

    virtual ~Node() = default;

    virtual llvm::Value *codeGen(CodeGenContext &context) { return 0; }

    virtual std::vector<Node *> getChildren() = 0;

    virtual void traverse(std::function<void(Node *)> pre, std::function<void(Node *)> post) {
        try {
            pre(this);
            for (auto i : this->getChildren())
                if (i != nullptr)
                    i->traverse(pre, post);
            post(this);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        } catch (...) {
            std::cout << "unknown exception during traversal" << std::endl;
        }
    }

    virtual std::string getName() {
        std::string id = typeid(*this).name();
        while (!id.empty() && isdigit(id[0]))
            id = id.substr(1);
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

    Program(ProgramHead *programHead, Routine *routine) : programHead(programHead), routine(routine) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(programHead);
        ch.emplace_back(routine);
        return ch;
    }
};

class ProgramHead : public AbstractStatement {
public:
    std::string id;

    explicit ProgramHead(std::string id) : id(std::move(id)) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        return ch;
    }

    std::string getInfo() override {
        return id;
    }
};


class Routine : public AbstractStatement {
public:

    RoutineHead *routineHead{};
    RoutineBody *routineBody{};

    Routine(RoutineHead *routineHead, RoutineBody *routineBody) : routineHead(routineHead), routineBody(routineBody) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(routineHead);
        ch.emplace_back(routineBody);
        return ch;
    }
};

class SubRoutine : public AbstractStatement {
public:

    RoutineHead *routineHead{};
    RoutineBody *routineBody{};

    SubRoutine(RoutineHead *routineHead, RoutineBody *routineBody) : routineHead(routineHead),
                                                                     routineBody(routineBody) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(routineHead);
        ch.emplace_back(routineBody);
        return ch;
    }

    void clearConstTable(ConstTable &table);
};

class RoutineHead : public AbstractStatement {
public:

    LabelPart *labelPart;
    ConstPart *constPart;
    TypePart *typePart;
    VarPart *varPart;
    RoutinePart *routinePart;

    RoutineHead(LabelPart *labelPart, ConstPart *constPart, TypePart *typePart, VarPart *varPart,
                RoutinePart *routinePart) : labelPart(labelPart), constPart(constPart), typePart(typePart),
                                            varPart(varPart), routinePart(routinePart) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(labelPart);
        ch.emplace_back(constPart);
        ch.emplace_back(typePart);
        ch.emplace_back(varPart);
        ch.emplace_back(routinePart);
        return ch;
    }
};

class LabelPart : public AbstractStatement {
public:

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        return ch;
    }
};

class ConstPart : public AbstractStatement {
public:

    ConstExprList *constExprList{}; // might be nullptr

    explicit ConstPart(ConstExprList *constExprList) : constExprList(constExprList) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(constExprList);
        return ch;
    }
};

class ConstExprList : public AbstractStatement {
public:

    std::string name;
    ConstExprList *preList{};
    ConstValue *value{};

    ConstExprList(std::string name, ConstExprList *preList, ConstValue *value) : name(std::move(name)),
                                                                                 preList(preList),
                                                                                 value(value) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(value);
        return ch;
    }

    std::string getInfo() override {
        return name;
    }


    void addToConstTable(ConstTable &table);

    void removeFromConstTable(ConstTable &table);
};

class ConstValue : public AbstractExpression {
public:
    static const int T_INTEGER = 1;
    static const int T_REAL = 2;
    static const int T_CHAR = 3;
    static const int T_SYS_CON = 4;
    //todo: does char/string exist?
    //don't exist in yacc, but there is chr() function.
    static const int T_STRING = 5;

    std::string value;
    int type{};

    ConstValue(std::string value, int type) : value(std::move(value)), type(type) {
        assert(type >= 1 && type <= 5);
        if (type == T_CHAR)
            this->value = this->value.substr(1, 1);
        //		no T_STRING
        //		if (type == T_STRING)
    }

    ConstValue *negate() {
        if (value == "-" || value.empty())
            return new ConstValue("", type);
        if (value[0] == '-')
            return new ConstValue(value.substr(1), type);
        else
            return new ConstValue("-" + value, type);
    }

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        return ch;
    }

    std::string getInfo() override {
        return std::to_string(type) + ":" + value;
    }
};

class TypePart : public AbstractStatement {
public:

    TypeDeclList *typeDeclList{};

    explicit TypePart(TypeDeclList *typeDeclList) : typeDeclList(typeDeclList) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(typeDeclList);
        return ch;
    }
};

class TypeDeclList : public AbstractStatement {
public:
    TypeDeclList *preList{};
    TypeDefinition *typeDefinition{};

    TypeDeclList(TypeDeclList *preList, TypeDefinition *typeDefinition) : preList(preList),
                                                                          typeDefinition(typeDefinition) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(typeDefinition);
        return ch;
    }
};

class TypeDefinition : public AbstractStatement {
public:
    std::string name;
    TypeDecl *typeDecl{};

    TypeDefinition(std::string name, TypeDecl *typeDecl) : name(std::move(name)), typeDecl(typeDecl) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(typeDecl);
        return ch;
    }

    std::string getInfo() override {
        return name;
    }
};

class TypeDecl : public AbstractStatement {
public:
    static const int T_SIMPLE_TYPE_DECLARE = 1;
    static const int T_ARRAY_TYPE_DECLARE = 2;
    static const int T_RECORD_TYPE_DECLARE = 3;

    int type{};
    SimpleTypeDecl *simpleTypeDecl{};
    ArrayTypeDecl *arrayTypeDecl{};
    RecordTypeDecl *recordTypeDecl{};

    explicit TypeDecl(SimpleTypeDecl *simpleTypeDecl) : simpleTypeDecl(simpleTypeDecl) { type = T_SIMPLE_TYPE_DECLARE; }

    explicit TypeDecl(ArrayTypeDecl *arrayTypeDecl) : arrayTypeDecl(arrayTypeDecl) { type = T_ARRAY_TYPE_DECLARE; }

    explicit TypeDecl(RecordTypeDecl *recordTypeDecl) : recordTypeDecl(recordTypeDecl) { type = T_RECORD_TYPE_DECLARE; }

    llvm::Type *getType(CodeGenContext &context, std::string name);


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(simpleTypeDecl);
        ch.emplace_back(arrayTypeDecl);
        ch.emplace_back(recordTypeDecl);
        return ch;
    }

//	int getLowerBound(const ConstTable &table) {
//		if(type == T_SIMPLE_TYPE_DECLARE) {
//
//		}
//	}
};

class SimpleTypeDecl : public AbstractStatement {
public:
    static const int T_SYS_TYPE = 1;
    static const int T_TYPE_NAME = 2;
    static const int T_ENUMERATION = 3;
    static const int T_RANGE = 4;
    static const int T_NAME_RANGE = 5;

    int type{};
    std::string sysType;
    std::string name;
    NameList *nameList{};
    //todo: manually handle negative signs?
    ConstValue *lowerBound{}, *upperBound{};
    std::string lowerName, upperName;

    SimpleTypeDecl(int type, const std::string &st) : type(type) {
        if (type == T_SYS_TYPE)
            sysType = st;
        if (type == T_TYPE_NAME)
            name = st;
        assert(type == T_SYS_TYPE || type == T_TYPE_NAME);
    }

    explicit SimpleTypeDecl(NameList *nameList) : nameList(nameList), type(T_ENUMERATION) {}

    SimpleTypeDecl(ConstValue *lowerBound, ConstValue *upperBound) : lowerBound(lowerBound),
                                                                     upperBound(upperBound), type(T_RANGE) {}

    SimpleTypeDecl(std::string lowerName, std::string upperName) : lowerName(std::move(lowerName)),
                                                                   upperName(std::move(upperName)),
                                                                   type(T_NAME_RANGE) {}

    llvm::Type *getType(CodeGenContext &context);

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

    ArrayTypeDecl(SimpleTypeDecl *range, TypeDecl *elementType) : range(range), elementType(elementType) {}

    llvm::Type *getType(CodeGenContext &context);

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(range);
        ch.emplace_back(elementType);
        return ch;
    }

    int getLowerBound(const ConstTable &table) {
        return range->getLowerBound(table);
    }

};

class RecordTypeDecl : public AbstractStatement {
public:
    FieldDeclList *fieldDeclList{};

    explicit RecordTypeDecl(FieldDeclList *fieldDeclList) : fieldDeclList(fieldDeclList) {}

    llvm::Type *getType(CodeGenContext &context, std::string &name);

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(fieldDeclList);
        return ch;
    }

    TypeDecl *findName(const std::string & s);
};

class FieldDeclList : public AbstractStatement {
public:
    FieldDeclList *preList{};
    FieldDecl *fieldDecl{};

    FieldDeclList(FieldDeclList *preList, FieldDecl *fieldDecl) : preList(preList), fieldDecl(fieldDecl) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(fieldDecl);
        return ch;
    }
};

class FieldDecl : public AbstractStatement {
public:
    NameList *nameList{};
    TypeDecl *typeDecl{};

    FieldDecl(NameList *nameList, TypeDecl *typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(nameList);
        ch.emplace_back(typeDecl);
        return ch;
    }
};

class NameList : public AbstractStatement {
public:
    NameList *nameList;
    std::string name;

    NameList(NameList *nameList, std::string name) : nameList(nameList), name(std::move(name)) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(nameList);
        return ch;
    }

    std::string getInfo() override {
        return name;
    }
};

class VarPart : public AbstractStatement {
public:
    VarDeclList *varDeclList{};

    explicit VarPart(VarDeclList *varDeclList) : varDeclList(varDeclList) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(varDeclList);
        return ch;
    }
};

class VarDeclList : public AbstractStatement {
public:
    VarDeclList *preList{};
    VarDecl *varDecl{};

    VarDeclList(VarDeclList *preList, VarDecl *varDecl) : preList(preList), varDecl(varDecl) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(varDecl);
        return ch;
    }
};

class VarDecl : public AbstractStatement {
public:
    NameList *nameList{};
    TypeDecl *typeDecl{};

    VarDecl(NameList *nameList, TypeDecl *typeDecl) : nameList(nameList), typeDecl(typeDecl) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(nameList);
        ch.emplace_back(typeDecl);
        return ch;
    }
};

class RoutinePart : public AbstractStatement {
public:
    //todo: don't know what it is
    static const int T_ROUTINE_FUNC = 1;
    static const int T_ROUTINE_PROC = 2;
    static const int T_FUNC = 3;
    static const int T_PROC = 4;
    static const int T_EMPTY = 5;

    int type{};
    RoutinePart *routinePart{};
    FunctionDecl *functionDecl{};
    ProcedureDecl *procedureDecl{};

    RoutinePart(RoutinePart *routinePart, FunctionDecl *functionDecl) : routinePart(routinePart),
                                                                        functionDecl(
                                                                                functionDecl) { type = T_ROUTINE_FUNC; }

    RoutinePart(RoutinePart *routinePart, ProcedureDecl *procedureDecl) : routinePart(routinePart),
                                                                          procedureDecl(
                                                                                  procedureDecl) { type = T_ROUTINE_PROC; }

    explicit RoutinePart(FunctionDecl *functionDecl) : functionDecl(functionDecl) { type = T_FUNC; }

    explicit RoutinePart(ProcedureDecl *procedureDecl) : procedureDecl(procedureDecl) { type = T_PROC; }

    explicit RoutinePart(int type) : type(type) { assert(type == T_EMPTY); }

    llvm::Value *codeGen(CodeGenContext &context) override;

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

    FunctionDecl(FunctionHead *functionHead, SubRoutine *subRoutine) : functionHead(functionHead),
                                                                       subRoutine(subRoutine) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(functionHead);
        ch.emplace_back(subRoutine);
        return ch;
    }
};

class FunctionHead : public AbstractStatement {
public:
    std::string name;
    Parameters *parameters{};
    SimpleTypeDecl *returnType{};

    FunctionHead(std::string name, Parameters *parameters, SimpleTypeDecl *returnType) : name(std::move(name)),
                                                                                         parameters(parameters),
                                                                                         returnType(
                                                                                                 returnType) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(parameters);
        ch.emplace_back(returnType);
        return ch;
    }

    std::string getInfo() override {
        return name;
    }
};

class ProcedureDecl : public AbstractStatement {
public:
    ProcedureHead *procedureHead{};
    SubRoutine *subRoutine{};

    ProcedureDecl(ProcedureHead *procedureHead, SubRoutine *subRoutine) : procedureHead(procedureHead),
                                                                          subRoutine(subRoutine) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(procedureHead);
        ch.emplace_back(subRoutine);
        return ch;
    }
};

class ProcedureHead : public AbstractStatement {
public:
    std::string name;
    Parameters *parameters;

    ProcedureHead(std::string name, Parameters *parameters) : name(std::move(name)), parameters(parameters) {}


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(parameters);
        return ch;
    }


    std::string getInfo() override {
        return name;
    }
};

class Parameters : public AbstractStatement {
public:
    ParaDeclList *paraDeclList{};

    explicit Parameters(ParaDeclList *paraDeclList) : paraDeclList(paraDeclList) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(paraDeclList);
        return ch;
    }
};

class ParaDeclList : public AbstractStatement {
public:
    ParaDeclList *paraDeclList{};
    ParaTypeList *paraTypeList{};

    ParaDeclList(ParaDeclList *paraDeclList, ParaTypeList *paraTypeList) : paraDeclList(paraDeclList),
                                                                           paraTypeList(paraTypeList) {}


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(paraDeclList);
        ch.emplace_back(paraTypeList);
        return ch;
    }
};

class ParaTypeList : public AbstractStatement {
public:
    static const int T_VAR = 1;
    static const int T_VAL = 2;

    int type{};
    VarParaList *varParaList{};
    ValParaList *valParaList{};
    SimpleTypeDecl *typeDecl{};

    ParaTypeList(VarParaList *varParaList, SimpleTypeDecl *typeDecl) : varParaList(varParaList),
                                                                       typeDecl(typeDecl) { type = T_VAR; }

    ParaTypeList(ValParaList *valParaList, SimpleTypeDecl *typeDecl) : valParaList(valParaList),
                                                                       typeDecl(typeDecl) { type = T_VAL; }


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

    explicit VarParaList(NameList *nameList) : nameList(nameList) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(nameList);
        return ch;
    }
};

class ValParaList : public AbstractStatement {
public:
    NameList *nameList{};

    explicit ValParaList(NameList *nameList) : nameList(nameList) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(nameList);
        return ch;
    }
};

class RoutineBody : public AbstractStatement {
public:
    CompoundStmt *compoundStmt{};

    explicit RoutineBody(CompoundStmt *compoundStmt) : compoundStmt(compoundStmt) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(compoundStmt);
        return ch;
    }
};

class CompoundStmt : public AbstractStatement {
public:
    StmtList *stmtList{};

    explicit CompoundStmt(StmtList *stmtList) : stmtList(stmtList) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(stmtList);
        return ch;
    }
};

class StmtList : public AbstractStatement {
public:
    StmtList *preList{};
    Stmt *stmt{}; // NOTICE: fixme: might be nullptr, due to the grammar given...

    StmtList(StmtList *preList, Stmt *stmt) : preList(preList), stmt(stmt) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(stmt);
        return ch;
    }
};

class Stmt : public AbstractStatement {
public:
    static const int T_LABELED = 1;
    static const int T_UNLABELED = 2;

    int type{};
    NonLabelStmt *nonLabelStmt{};

    Stmt(int type, NonLabelStmt *nonLabelStmt) : type(type), nonLabelStmt(nonLabelStmt) {
        assert(type == T_LABELED || type == T_UNLABELED);
    }

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(nonLabelStmt);
        return ch;
    }
};

class NonLabelStmt : public AbstractStatement {
public:
    static const int T_ASSIGN = 1;
    static const int T_PROC = 2;
    static const int T_IF = 3;
    static const int T_REPEAT = 4;
    static const int T_WHILE = 5;
    static const int T_FOR = 6;
    static const int T_CASE = 7;
    static const int T_GOTO = 8;
    static const int T_COMPOUND = 9;

    int type{};
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

    explicit NonLabelStmt(CompoundStmt *compoundStmt) : compoundStmt(compoundStmt), type(T_COMPOUND) {}

    explicit NonLabelStmt(IfStmt *ifStmt) : ifStmt(ifStmt) { type = T_IF; }

    explicit NonLabelStmt(RepeatStmt *repeatStmt) : repeatStmt(repeatStmt) { type = T_REPEAT; }

    explicit NonLabelStmt(WhileStmt *whileStmt) : whileStmt(whileStmt) { type = T_WHILE; }

    explicit NonLabelStmt(ForStmt *forStmt) : forStmt(forStmt) { type = T_FOR; }

    explicit NonLabelStmt(CaseStmt *caseStmt) : caseStmt(caseStmt) { type = T_CASE; }

    explicit NonLabelStmt(GotoStmt *gotoStmt) : gotoStmt(gotoStmt) { type = T_GOTO; }

    llvm::Value *codeGen(CodeGenContext &context) override;

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
    static const int T_SIMPLE = 1;
    static const int T_ARRAY = 2;
    static const int T_RECORD = 3;

    int type{};
    std::string id;
    Expression *rhs;
    Expression *index{};
    std::string recordId;

    AssignStmt(std::string id, Expression *rhs) : id(std::move(id)), rhs(rhs), type(T_SIMPLE) {}

    AssignStmt(std::string id, Expression *index, Expression *rhs) : id(std::move(id)), rhs(rhs), index(index),
                                                                     type(T_ARRAY) {}

    AssignStmt(std::string id, std::string recordId, Expression *rhs) : id(std::move(id)), rhs(rhs),
                                                                        recordId(std::move(recordId)),
                                                                        type(T_RECORD) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(rhs);
        ch.emplace_back(index);
        return ch;
    }


    std::string getInfo() override {
        return id + "=..";
    }
};

class ProcStmt : public AbstractStatement {
public:
    static const int T_SIMPLE = 1;
    static const int T_SIMPLE_ARGS = 2;
    static const int T_SYS_PROC = 3;
    static const int T_SYS_PROC_EXPR = 4;
    //fixme: what's read ??
    static const int T_READ = 5;

    int type{};
    std::string procId;
    ArgsList *argsList{};
    std::string sysProc;
    ExpressionList *expressionList{};

    //fixme: read(factor) ??
    Factor *factor{};

    ProcStmt(int type, const std::string &st) : type(type) {
        assert(type == T_SIMPLE || type == T_SYS_PROC);
        if (type == T_SIMPLE)
            procId = st;
        else
            sysProc = st;
    }

    ProcStmt(std::string procId, ArgsList *argsList) : procId(std::move(procId)), argsList(argsList),
                                                       type(T_SIMPLE_ARGS) {}

    ProcStmt(std::string sysProc, ExpressionList *expressionList) : sysProc(std::move(sysProc)),
                                                                    expressionList(expressionList),
                                                                    type(T_SYS_PROC_EXPR) {}

    explicit ProcStmt(Factor *factor) : factor(factor), type(T_READ) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(argsList);
        ch.emplace_back(expressionList);
        return ch;
    }


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

    IfStmt(Expression *expression, Stmt *stmt, ElseClause *elseClause) : expression(expression), stmt(stmt),
                                                                         elseClause(elseClause) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(expression);
        ch.emplace_back(stmt);
        ch.emplace_back(elseClause);
        return ch;
    }
};

class ElseClause : public AbstractStatement {
public:
    Stmt *stmt{};

    explicit ElseClause(Stmt *stmt) : stmt(stmt) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(stmt);
        return ch;
    }
};

class RepeatStmt : public AbstractStatement {
public:
    StmtList *stmtList{};
    Expression *untilCondition{};

    RepeatStmt(StmtList *stmtList, Expression *untilCondition) : stmtList(stmtList), untilCondition(untilCondition) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(stmtList);
        ch.emplace_back(untilCondition);
        return ch;
    }
};

class WhileStmt : public AbstractStatement {
public:
    Expression *whileCondition{};
    Stmt *stmt{};

    WhileStmt(Expression *whileCondition, Stmt *stmt) : whileCondition(whileCondition), stmt(stmt) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(whileCondition);
        ch.emplace_back(stmt);
        return ch;
    }
};

class ForStmt : public AbstractStatement {
public:
    std::string loopId;
    Expression *firstBound;
    Direction *direction;
    Expression *secondBound;
    Stmt *stmt;

    ForStmt(std::string loopId, Expression *firstBound, Direction *direction, Expression *secondBound, Stmt *stmt)
            : loopId(std::move(loopId)), firstBound(firstBound), direction(direction), secondBound(secondBound),
              stmt(stmt) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(firstBound);
        ch.emplace_back(direction);
        ch.emplace_back(secondBound);
        ch.emplace_back(stmt);
        return ch;
    }


    std::string getInfo() override {
        return loopId;
    }
};

class Direction : public AbstractStatement {
public:
    static const int T_TO = 1;
    static const int T_DOWNTO = 2;
    int type{};

    explicit Direction(int type) : type(type) { assert(type == T_TO || type == T_DOWNTO); }

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        return ch;
    }
};

class CaseStmt : public AbstractStatement {
public:
    Expression *expression{};
    CaseExprList *caseExprList{};

    CaseStmt(Expression *expression, CaseExprList *caseExprList) : expression(expression), caseExprList(caseExprList) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(expression);
        ch.emplace_back(caseExprList);
        return ch;
    }

    llvm::Value *codeGen(CodeGenContext &context) override;

};

class CaseExprList : public AbstractStatement {
public:
    CaseExprList *preList{};
    CaseExpr *caseExpr;

    CaseExprList(CaseExprList *preList, CaseExpr *caseExpr) : preList(preList), caseExpr(caseExpr) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(caseExpr);
        return ch;
    }

    llvm::Value *codeGen(CodeGenContext &context, llvm::Value *condition, llvm::BasicBlock *bmerge);

};

class CaseExpr : public AbstractStatement {
public:
    static const int T_CONST = 1;
    static const int T_ID = 2;
    int type{};
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

    llvm::Value *codeGen(CodeGenContext &context, llvm::Value *condition, llvm::BasicBlock *bmerge);

};

class GotoStmt : public AbstractStatement {
public:
    ConstValue *address;

    explicit GotoStmt(const std::string &address) : address(new ConstValue(address, ConstValue::T_INTEGER)) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(address);
        return ch;
    }
};

// todo: expression or statement, does it matter?
class ExpressionList : public AbstractExpression {
public:
    ExpressionList *preList{};
    Expression *expression{};

    ExpressionList(ExpressionList *preList, Expression *expression) : preList(preList), expression(expression) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(expression);
        return ch;
    }
};

class Expression : public AbstractExpression {
public:
    static const int T_EQ = 1;
    static const int T_NE = 2;
    static const int T_GE = 3;
    static const int T_GT = 4;
    static const int T_LE = 5;
    static const int T_LT = 6;
    static const int T_EXPR = 7;
    int type;
    Expression *expression{};
    Expr *expr{};
//    llvm::Value *lastValue = nullptr;

    Expression(int type, Expression *expression, Expr *expr) : type(type), expression(expression), expr(expr) {
        assert(type >= 1 && type <= 6);
    }

    explicit Expression(Expr *expr) : expr(expr), type(T_EXPR) {}

    llvm::Value *codeGen(CodeGenContext &context) override;


    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(expression);
        ch.emplace_back(expr);
        return ch;
    }
};

class Expr : public AbstractExpression {
public:
    static const int T_PLUS = 1;
    static const int T_MINUS = 2;
    static const int T_OR = 3;
    static const int T_TERM = 4;

    int type;
    Expr *expr{};
    Term *term{};

    Expr(int type, Expr *expr, Term *term) : type(type), expr(expr), term(term) {
        assert(type >= 1 && type <= 3);
    }

    explicit Expr(Term *term) : term(term), type(T_TERM) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(expr);
        ch.emplace_back(term);
        return ch;
    }

};

class Term : public AbstractExpression {
public:
    static const int T_MUL = 1;
    static const int T_DIV = 2;
    static const int T_MOD = 3;
    static const int T_AND = 4;
    static const int T_FACTOR = 5;

    int type;
    Term *term{};
    Factor *factor{};

    Term(int type, Term *term, Factor *factor) : type(type), term(term), factor(factor) {
        assert(type >= 1 && type <= 4);
    }

    explicit Term(Factor *factor) : factor(factor), type(T_FACTOR) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(term);
        ch.emplace_back(factor);
        return ch;
    }
};

class Factor : public AbstractExpression {
public:
    static const int T_NAME = 1;
    static const int T_NAME_ARGS = 2;
    static const int T_SYS_FUNCT = 3;
    static const int T_SYS_FUNCT_ARGS = 4;
    static const int T_CONST = 5;
    static const int T_EXPR = 6;
    static const int T_NOT_FACTOR = 7;
    static const int T_MINUS_FACTOR = 8;
    static const int T_ID_EXPR = 9;
    static const int T_ID_DOT_ID = 10;

    int type;
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

    Factor(int type, const std::string &st) : type(type) {
        assert(type == T_NAME || type == T_SYS_FUNCT);
        if (type == T_NAME)
            name = st;
        else {
            sysFunction = st;
        }
    }

    Factor(int type, const std::string &st, ArgsList *argsList) : type(type), argsList(argsList) {
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

    Factor(int type, Factor *factor) : type(type), factor(factor) {
        assert(type == T_NOT_FACTOR || type == T_MINUS_FACTOR);
    }

    Factor(std::string id, Expression *expression) : expression(expression), id(std::move(id)), type(T_ID_EXPR) {}

    Factor(std::string id, std::string recordId) : id(std::move(id)), recordId(std::move(recordId)),
                                                   type(T_ID_DOT_ID) {}

    llvm::Value *codeGen(CodeGenContext &context) override;

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

    ArgsList(ArgsList *preList, Expression *expression) : preList(preList), expression(expression) {}

    std::vector<Node *> getChildren() override {
        auto ch = std::vector<Node *>();
        ch.emplace_back(preList);
        ch.emplace_back(expression);
        return ch;
    }
};

#endif //SPLC_NODE_H
