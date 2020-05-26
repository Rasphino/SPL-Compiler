/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SYS_CON = 258,
     SYS_FUNCT = 259,
     SYS_PROC = 260,
     SYS_TYPE = 261,
     N_ID = 262,
     INTEGER = 263,
     REAL = 264,
     STRING = 265,
     CHAR = 266,
     N_LP = 267,
     RP = 268,
     LB = 269,
     RB = 270,
     DOT = 271,
     COMMA = 272,
     COLON = 273,
     ASSIGN = 274,
     DOTDOT = 275,
     SEMI = 276,
     ARRAY = 277,
     BBEGIN = 278,
     CASE = 279,
     CONST = 280,
     DO = 281,
     DOWNTO = 282,
     ELSE = 283,
     END = 284,
     FOR = 285,
     FUNCTION = 286,
     GOTO = 287,
     IF = 288,
     IN = 289,
     OF = 290,
     PACKED = 291,
     PROCEDURE = 292,
     PROGRAM = 293,
     RECORD = 294,
     REPEAT = 295,
     SET = 296,
     THEN = 297,
     TO = 298,
     TYPE = 299,
     UNTIL = 300,
     VAR = 301,
     WHILE = 302,
     WITH = 303,
     NOT = 304,
     MUL = 305,
     DIV = 306,
     MOD = 307,
     AND = 308,
     PLUS = 309,
     MINUS = 310,
     OR = 311,
     XOR = 312,
     EQ = 313,
     NE = 314,
     GE = 315,
     GT = 316,
     N_LE = 317,
     N_LT = 318,
     READ = 319
   };
#endif
/* Tokens.  */
#define SYS_CON 258
#define SYS_FUNCT 259
#define SYS_PROC 260
#define SYS_TYPE 261
#define N_ID 262
#define INTEGER 263
#define REAL 264
#define STRING 265
#define CHAR 266
#define N_LP 267
#define RP 268
#define LB 269
#define RB 270
#define DOT 271
#define COMMA 272
#define COLON 273
#define ASSIGN 274
#define DOTDOT 275
#define SEMI 276
#define ARRAY 277
#define BBEGIN 278
#define CASE 279
#define CONST 280
#define DO 281
#define DOWNTO 282
#define ELSE 283
#define END 284
#define FOR 285
#define FUNCTION 286
#define GOTO 287
#define IF 288
#define IN 289
#define OF 290
#define PACKED 291
#define PROCEDURE 292
#define PROGRAM 293
#define RECORD 294
#define REPEAT 295
#define SET 296
#define THEN 297
#define TO 298
#define TYPE 299
#define UNTIL 300
#define VAR 301
#define WHILE 302
#define WITH 303
#define NOT 304
#define MUL 305
#define DIV 306
#define MOD 307
#define AND 308
#define PLUS 309
#define MINUS 310
#define OR 311
#define XOR 312
#define EQ 313
#define NE 314
#define GE 315
#define GT 316
#define N_LE 317
#define N_LT 318
#define READ 319




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 10 "parser.y"
{
    Node *node;
    Program *program;
    ProgramHead *programHead;
    Routine *routine;
    RoutineHead *routineHead;
    SubRoutine *subRoutine;
    LabelPart *labelPart;
    ConstPart *constPart;
    ConstExprList *constExprList;
    ConstValue *constValue;
    TypePart *typePart;
    TypeDeclList *typeDeclList;
    TypeDefinition *typeDefinition;
    TypeDecl *typeDecl;
    SimpleTypeDecl *simpleTypeDecl;
    ArrayTypeDecl *arrayTypeDecl;
    RecordTypeDecl *recordTypeDecl;
    FieldDeclList *fieldDeclList;
    FieldDecl *fieldDecl;
    NameList *nameList;
    VarPart *varPart;
    VarDeclList *varDeclList;
    VarDecl *varDecl;
    RoutinePart *routinePart;
    FunctionDecl *functionDecl;
    FunctionHead *functionHead;
    ProcedureDecl *procedureDecl;
    ProcedureHead *procedureHead;
    Parameters *parameters;
    ParaDeclList *paraDeclList;
    ParaTypeList *paraTypeList;
    VarParaList *varParaList;
    ValParaList *valParaList;
    RoutineBody *routineBody;
    CompoundStmt *compoundStmt;
    StmtList *stmtList;
    Stmt *stmt;
    NonLabelStmt *nonLabelStmt;
    AssignStmt *assignStmt;
    ProcStmt *procStmt;
    IfStmt *ifStmt;
    ElseClause *elseClause;
    RepeatStmt *repeatStmt;
    WhileStmt *whileStmt;
    ForStmt *forStmt;
    Direction *direction;
    CaseStmt *caseStmt;
    CaseExprList *caseExprList;
    CaseExpr *caseExpr;
    GotoStmt *gotoStmt;
    ExpressionList *expressionList;
    Expression *expression;
    Expr *expr;
    Term *term;
    Factor *factor;
    ArgsList *argsList;

    AbstractStatement *abstractStatement;
    AbstractExpression *abstractExpression;

    std::string *string;
    int token;
}
/* Line 1529 of yacc.c.  */
#line 242 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

