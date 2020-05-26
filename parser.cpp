/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

    #include "AST.h"
    Program *astRoot;
    extern int yylineno;
    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n at line:%d\n", s, yylineno); }


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 297 "parser.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 310 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   357

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNRULES -- Number of states.  */
#define YYNSTATES  271

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    17,    23,    25,    28,
      30,    36,    41,    43,    45,    47,    49,    51,    54,    56,
      59,    61,    66,    68,    70,    72,    74,    76,    80,    84,
      89,    95,    99,   106,   110,   113,   115,   120,   124,   126,
     129,   131,   134,   136,   141,   144,   147,   149,   151,   153,
     158,   164,   169,   173,   177,   179,   183,   185,   189,   193,
     196,   198,   200,   204,   208,   210,   214,   216,   218,   220,
     222,   224,   226,   228,   230,   232,   234,   238,   245,   251,
     253,   258,   260,   265,   270,   276,   279,   281,   286,   291,
     300,   302,   304,   310,   313,   315,   320,   325,   328,   332,
     334,   338,   342,   346,   350,   354,   358,   360,   364,   368,
     372,   374,   378,   382,   386,   390,   392,   394,   399,   401,
     406,   408,   412,   415,   418,   423,   427,   431,   433,   435
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      66,     0,    -1,    67,    68,    16,    -1,    38,     7,    21,
      -1,    70,    98,    -1,    70,    98,    -1,    71,    72,    75,
      85,    88,    -1,   122,    -1,    25,    73,    -1,   122,    -1,
      73,   121,    58,    74,    21,    -1,   121,    58,    74,    21,
      -1,     8,    -1,     9,    -1,     3,    -1,    11,    -1,    10,
      -1,    44,    76,    -1,   122,    -1,    76,    77,    -1,    77,
      -1,   121,    58,    78,    21,    -1,    79,    -1,    80,    -1,
      81,    -1,     6,    -1,   121,    -1,    12,    84,    13,    -1,
      74,    20,    74,    -1,    55,    74,    20,    74,    -1,    55,
      74,    20,    55,    74,    -1,   121,    20,   121,    -1,    22,
      14,    79,    15,    35,    78,    -1,    39,    82,    29,    -1,
      82,    83,    -1,    83,    -1,    84,    18,    78,    21,    -1,
      84,    17,     7,    -1,     7,    -1,    46,    86,    -1,   122,
      -1,    86,    87,    -1,    87,    -1,    84,    18,    78,    21,
      -1,    88,    89,    -1,    88,    91,    -1,    89,    -1,    91,
      -1,   122,    -1,    90,    21,    69,    21,    -1,    31,   121,
      93,    18,    79,    -1,    92,    21,    69,    21,    -1,    37,
     121,    93,    -1,    12,    94,    13,    -1,   122,    -1,    94,
      21,    95,    -1,    95,    -1,    96,    18,    79,    -1,    97,
      18,    79,    -1,    46,    84,    -1,    84,    -1,    99,    -1,
      23,   100,    29,    -1,   100,   101,    21,    -1,   122,    -1,
       8,    18,   102,    -1,   102,    -1,   103,    -1,   104,    -1,
      99,    -1,   105,    -1,   107,    -1,   108,    -1,   109,    -1,
     111,    -1,   114,    -1,     7,    19,   116,    -1,     7,    14,
     116,    15,    19,   116,    -1,     7,    16,     7,    19,   116,
      -1,     7,    -1,     7,    12,   120,    13,    -1,     5,    -1,
       5,    12,   115,    13,    -1,    64,    12,   119,    13,    -1,
      33,   116,    42,   101,   106,    -1,    28,   101,    -1,   122,
      -1,    40,   100,    45,   116,    -1,    47,   116,    26,   101,
      -1,    30,     7,    19,   116,   110,   116,    26,   101,    -1,
      43,    -1,    27,    -1,    24,   116,    35,   112,    29,    -1,
     112,   113,    -1,   113,    -1,    74,    18,   101,    21,    -1,
       7,    18,   101,    21,    -1,    32,     8,    -1,   115,    17,
     116,    -1,   116,    -1,   116,    60,   117,    -1,   116,    61,
     117,    -1,   116,    62,   117,    -1,   116,    63,   117,    -1,
     116,    58,   117,    -1,   116,    59,   117,    -1,   117,    -1,
     117,    54,   118,    -1,   117,    55,   118,    -1,   117,    56,
     118,    -1,   118,    -1,   118,    50,   119,    -1,   118,    51,
     119,    -1,   118,    52,   119,    -1,   118,    53,   119,    -1,
     119,    -1,   121,    -1,   121,    12,   120,    13,    -1,     4,
      -1,     4,    12,   120,    13,    -1,    74,    -1,    12,   116,
      13,    -1,    49,   119,    -1,    55,   119,    -1,     7,    14,
     116,    15,    -1,     7,    16,     7,    -1,   120,    17,   116,
      -1,   116,    -1,     7,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   155,   156,   157,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYS_CON", "SYS_FUNCT", "SYS_PROC",
  "SYS_TYPE", "N_ID", "INTEGER", "REAL", "STRING", "CHAR", "N_LP", "RP",
  "LB", "RB", "DOT", "COMMA", "COLON", "ASSIGN", "DOTDOT", "SEMI", "ARRAY",
  "BBEGIN", "CASE", "CONST", "DO", "DOWNTO", "ELSE", "END", "FOR",
  "FUNCTION", "GOTO", "IF", "IN", "OF", "PACKED", "PROCEDURE", "PROGRAM",
  "RECORD", "REPEAT", "SET", "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE",
  "WITH", "NOT", "MUL", "DIV", "MOD", "AND", "PLUS", "MINUS", "OR", "XOR",
  "EQ", "NE", "GE", "GT", "N_LE", "N_LT", "READ", "$accept", "program",
  "program_head", "routine", "sub_routine", "routine_head", "label_part",
  "const_part", "const_expr_list", "const_value", "type_part",
  "type_decl_list", "type_definition", "type_decl", "simple_type_decl",
  "array_type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "name_list", "var_part", "var_decl_list", "var_decl", "routine_part",
  "function_decl", "function_head", "procedure_decl", "procedure_head",
  "parameters", "para_decl_list", "para_type_list", "var_para_list",
  "val_para_list", "routine_body", "compound_stmt", "stmt_list", "stmt",
  "non_label_stmt", "assign_stmt", "proc_stmt", "if_stmt", "else_clause",
  "repeat_stmt", "while_stmt", "for_stmt", "direction", "case_stmt",
  "case_expr_list", "case_expr", "goto_stmt", "expression_list",
  "expression", "expr", "term", "factor", "args_list", "NAME", "empty", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    67,    68,    69,    70,    71,    72,    72,
      73,    73,    74,    74,    74,    74,    74,    75,    75,    76,
      76,    77,    78,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    80,    81,    82,    82,    83,    84,    84,    85,
      85,    86,    86,    87,    88,    88,    88,    88,    88,    89,
      90,    91,    92,    93,    93,    94,    94,    95,    95,    96,
      97,    98,    99,   100,   100,   101,   101,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   103,   103,   103,   104,
     104,   104,   104,   104,   105,   106,   106,   107,   108,   109,
     110,   110,   111,   112,   112,   113,   113,   114,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   120,   120,   121,   122
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     1,     2,     1,
       5,     4,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     4,
       5,     3,     6,     3,     2,     1,     4,     3,     1,     2,
       1,     2,     1,     4,     2,     2,     1,     1,     1,     4,
       5,     4,     3,     3,     1,     3,     1,     3,     3,     2,
       1,     1,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     5,     1,
       4,     1,     4,     4,     5,     2,     1,     4,     4,     8,
       1,     1,     5,     2,     1,     4,     4,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     1,     1,     4,     1,     4,
       1,     3,     2,     2,     4,     3,     3,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   129,     0,     1,     0,     0,   129,     7,
       3,     2,   129,     4,    61,     0,   129,     9,     0,    64,
     128,     8,     0,     0,   129,    18,    81,    79,     0,     0,
      62,     0,     0,     0,   129,     0,     0,    69,     0,    66,
      67,    68,    70,    71,    72,    73,    74,    75,     0,     0,
      17,    20,     0,     0,   129,    40,     0,     0,     0,     0,
       0,     0,    14,   118,   128,    12,    13,    16,    15,     0,
       0,     0,   120,     0,   106,   110,   115,   116,     0,    97,
       0,     0,     0,     0,    63,     0,     0,    19,     0,    38,
       0,    39,    42,     0,     0,     6,    46,     0,    47,     0,
      48,     0,    99,   127,     0,     0,     0,    76,    65,     0,
       0,     0,     0,   122,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    25,     0,     0,
       0,     0,     0,     0,    22,    23,    24,    26,     0,     0,
      41,   129,   129,    44,    45,   129,   129,    82,     0,    80,
       0,     0,     0,     0,     0,   125,   121,     0,     0,     0,
      94,   104,   105,   100,   101,   102,   103,   107,   108,   109,
     111,   112,   113,   114,     0,     0,   129,    87,    88,    83,
      10,     0,     0,     0,    35,     0,     0,     0,    21,     0,
      37,     0,     0,     0,    54,    52,     0,     0,     0,    98,
     126,     0,    78,   119,   124,     0,     0,    92,    93,   117,
      91,    90,     0,     0,    84,    86,    27,     0,    33,    34,
       0,     0,    28,    31,    43,     0,    60,     0,    56,     0,
       0,     0,    49,     5,    51,    77,     0,     0,     0,    85,
       0,     0,     0,    29,    59,    53,     0,     0,     0,    50,
      96,    95,     0,     0,    36,    30,    55,    57,    58,    89,
      32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   206,   207,     8,    16,    21,    72,
      24,    50,    51,   143,   144,   145,   146,   193,   194,    90,
      54,    91,    92,    95,    96,    97,    98,    99,   203,   237,
     238,   239,   240,    13,    37,    18,    38,    39,    40,    41,
      42,   224,    43,    44,    45,   222,    46,   169,   170,    47,
     101,   103,    74,    75,    76,   104,    77,     9
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -177
static const yytype_int16 yypact[] =
{
       6,    25,    50,  -177,    38,  -177,    41,    40,    47,  -177,
    -177,  -177,  -177,  -177,  -177,    73,    53,  -177,    22,  -177,
    -177,    73,    49,    73,    63,  -177,   101,    52,   102,   221,
    -177,   116,   118,   221,  -177,   221,   123,  -177,   107,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,    79,   122,
      73,  -177,    81,   135,   -17,  -177,   221,   221,   221,   150,
     221,   187,  -177,   148,    87,  -177,  -177,  -177,  -177,   221,
     221,   221,  -177,   251,    37,    24,  -177,   149,   143,  -177,
     235,    82,   178,   221,  -177,   122,   153,  -177,   246,  -177,
      67,   135,  -177,    73,    73,   -17,  -177,   154,  -177,   155,
    -177,     8,   281,   281,    11,   220,   159,   281,  -177,   221,
     221,   172,   201,  -177,  -177,   327,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   158,   221,   158,   167,   162,  -177,  -177,   135,   173,
     135,   122,   177,   181,  -177,  -177,  -177,   179,   196,   246,
    -177,   194,   194,  -177,  -177,  -177,  -177,  -177,   221,  -177,
     221,   189,   221,    20,   229,  -177,  -177,   191,   203,   318,
    -177,    37,    37,    37,    37,    37,    37,    24,    24,    24,
    -177,  -177,  -177,  -177,    36,   257,   195,   281,  -177,  -177,
    -177,    43,   161,    10,  -177,   127,   225,   122,  -177,    73,
    -177,   226,     2,   228,  -177,  -177,   244,    40,   248,   281,
     281,   221,   281,  -177,  -177,   158,   158,  -177,  -177,  -177,
    -177,  -177,   221,   158,  -177,  -177,  -177,   252,  -177,  -177,
     246,   140,  -177,  -177,  -177,   135,   233,     5,  -177,   254,
     255,   161,  -177,  -177,  -177,   281,   253,   278,   245,  -177,
     231,   301,   122,  -177,   233,  -177,     2,   161,   161,  -177,
    -177,  -177,   158,   246,  -177,  -177,  -177,  -177,  -177,  -177,
    -177
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,  -177,  -177,  -177,   119,   299,  -177,  -177,  -177,   -45,
    -177,  -177,   273,  -147,  -176,  -177,  -177,  -177,   131,  -135,
    -177,  -177,   240,  -177,   237,  -177,   238,  -177,   193,  -177,
      90,  -177,  -177,   147,    -6,   321,  -121,   295,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   188,  -177,
    -177,   -22,   232,    -5,    28,   -87,   -15,     7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      22,    14,   201,   191,    86,   195,    48,    73,    52,    89,
     186,    80,   188,    82,    93,    17,   227,    89,   255,    19,
      94,   157,   163,    25,   159,   158,   256,    26,   160,    27,
      28,    55,     4,   213,   102,    52,   105,   160,   107,   228,
     135,    19,   184,   142,     1,    12,    29,   112,   235,   219,
       5,    30,    31,   160,    32,    33,   226,    11,   195,    10,
     148,   100,    34,    12,    57,   259,    58,   236,    59,    35,
     168,    60,    15,   147,   125,   126,   127,   128,   151,   152,
      20,   267,   268,   251,   148,   149,    36,    26,   164,    27,
      28,   122,   123,   124,   246,   247,   196,    23,   113,   114,
     254,   110,   249,   111,   142,    12,    29,    49,   185,    53,
     187,   134,    31,    56,    32,    33,   270,   177,   178,   179,
      61,   236,    34,    78,   168,    62,    79,   132,    84,    35,
      65,    66,    67,    68,   147,    83,   209,    85,   210,    88,
     212,   269,    89,    62,   148,   230,    36,   142,    65,    66,
      67,    68,   232,   180,   181,   182,   183,   106,   204,   204,
     109,   129,   130,    26,    62,    27,    28,   137,    20,    65,
      66,    67,    68,   138,   136,   155,   156,   147,   162,   165,
     189,    12,    29,   190,   233,   142,   253,   192,    31,   245,
      32,    33,    26,   225,    27,   252,   142,   197,    34,   199,
     248,    14,   198,   200,   133,    35,   202,   265,   211,   215,
      12,    29,   142,   142,   166,   147,   141,    31,   142,    32,
      33,   216,    36,   223,    62,    63,   147,    34,    64,    65,
      66,    67,    68,    69,    35,   161,   116,   117,   118,   119,
     120,   121,   147,   147,   214,   231,   241,   234,   147,    62,
     148,    36,   137,    20,    65,    66,    67,    68,   138,   116,
     117,   118,   119,   120,   121,   242,   263,   250,   139,   244,
      70,   262,   257,   258,   260,   208,    71,   131,   116,   117,
     118,   119,   120,   121,   220,   140,   115,   116,   117,   118,
     119,   120,   121,   116,   117,   118,   119,   120,   121,   261,
     221,   141,     7,   116,   117,   118,   119,   120,   121,   116,
     117,   118,   119,   120,   121,   116,   117,   118,   119,   120,
     121,    62,   264,    87,   229,   167,    65,    66,    67,    68,
      62,   150,   153,   154,   167,    65,    66,    67,    68,   116,
     117,   118,   119,   120,   121,   205,   266,   217,   171,   172,
     173,   174,   175,   176,   243,    81,   108,   218
};

static const yytype_uint16 yycheck[] =
{
      15,     7,   149,   138,    49,   140,    21,    29,    23,     7,
     131,    33,   133,    35,    31,     8,   192,     7,    13,    12,
      37,    13,   109,    16,    13,    17,    21,     5,    17,     7,
       8,    24,     7,    13,    56,    50,    58,    17,    60,    29,
      85,    34,   129,    88,    38,    23,    24,    69,    46,    13,
       0,    29,    30,    17,    32,    33,    13,    16,   193,    21,
      17,    54,    40,    23,    12,   241,    14,   202,    16,    47,
     115,    19,    25,    88,    50,    51,    52,    53,    93,    94,
       7,   257,   258,   230,    17,    18,    64,     5,   110,     7,
       8,    54,    55,    56,   215,   216,   141,    44,    70,    71,
     235,    14,   223,    16,   149,    23,    24,    58,   130,    46,
     132,    83,    30,    12,    32,    33,   263,   122,   123,   124,
      18,   256,    40,     7,   169,     3,     8,    45,    21,    47,
       8,     9,    10,    11,   149,    12,   158,    58,   160,    58,
     162,   262,     7,     3,    17,    18,    64,   192,     8,     9,
      10,    11,   197,   125,   126,   127,   128,     7,   151,   152,
      12,    12,    19,     5,     3,     7,     8,     6,     7,     8,
       9,    10,    11,    12,    21,    21,    21,   192,    19,     7,
      13,    23,    24,    21,   199,   230,   231,    14,    30,   211,
      32,    33,     5,   186,     7,    55,   241,    20,    40,    20,
     222,   207,    21,     7,    26,    47,    12,   252,    19,    18,
      23,    24,   257,   258,    13,   230,    55,    30,   263,    32,
      33,    18,    64,    28,     3,     4,   241,    40,     7,     8,
       9,    10,    11,    12,    47,    15,    58,    59,    60,    61,
      62,    63,   257,   258,    15,    20,    18,    21,   263,     3,
      17,    64,     6,     7,     8,     9,    10,    11,    12,    58,
      59,    60,    61,    62,    63,    21,    35,    15,    22,    21,
      49,    26,    18,    18,    21,   156,    55,    42,    58,    59,
      60,    61,    62,    63,    27,    39,    35,    58,    59,    60,
      61,    62,    63,    58,    59,    60,    61,    62,    63,    21,
      43,    55,     3,    58,    59,    60,    61,    62,    63,    58,
      59,    60,    61,    62,    63,    58,    59,    60,    61,    62,
      63,     3,    21,    50,   193,     7,     8,     9,    10,    11,
       3,    91,    95,    95,     7,     8,     9,    10,    11,    58,
      59,    60,    61,    62,    63,   152,   256,    29,   116,   117,
     118,   119,   120,   121,   207,    34,    61,   169
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    66,    67,     7,     0,    68,    70,    71,   122,
      21,    16,    23,    98,    99,    25,    72,   122,   100,   122,
       7,    73,   121,    44,    75,   122,     5,     7,     8,    24,
      29,    30,    32,    33,    40,    47,    64,    99,   101,   102,
     103,   104,   105,   107,   108,   109,   111,   114,   121,    58,
      76,    77,   121,    46,    85,   122,    12,    12,    14,    16,
      19,    18,     3,     4,     7,     8,     9,    10,    11,    12,
      49,    55,    74,   116,   117,   118,   119,   121,     7,     8,
     116,   100,   116,    12,    21,    58,    74,    77,    58,     7,
      84,    86,    87,    31,    37,    88,    89,    90,    91,    92,
     122,   115,   116,   116,   120,   116,     7,   116,   102,    12,
      14,    16,   116,   119,   119,    35,    58,    59,    60,    61,
      62,    63,    54,    55,    56,    50,    51,    52,    53,    12,
      19,    42,    45,    26,   119,    74,    21,     6,    12,    22,
      39,    55,    74,    78,    79,    80,    81,   121,    17,    18,
      87,   121,   121,    89,    91,    21,    21,    13,    17,    13,
      17,    15,    19,   120,   116,     7,    13,     7,    74,   112,
     113,   117,   117,   117,   117,   117,   117,   118,   118,   118,
     119,   119,   119,   119,   120,   116,   101,   116,   101,    13,
      21,    84,    14,    82,    83,    84,    74,    20,    21,    20,
       7,    78,    12,    93,   122,    93,    69,    70,    69,   116,
     116,    19,   116,    13,    15,    18,    18,    29,   113,    13,
      27,    43,   110,    28,   106,   122,    13,    79,    29,    83,
      18,    20,    74,   121,    21,    46,    84,    94,    95,    96,
      97,    18,    21,    98,    21,   116,   101,   101,   116,   101,
      15,    78,    55,    74,    84,    13,    21,    18,    18,    79,
      21,    21,    26,    35,    21,    74,    95,    79,    79,   101,
      78
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 154 "parser.y"
    {astRoot = new Program((yyvsp[(1) - (3)].programHead), (yyvsp[(2) - (3)].routine));;}
    break;

  case 3:
#line 155 "parser.y"
    {(yyval.programHead) = new ProgramHead(*(yyvsp[(2) - (3)].string));;}
    break;

  case 4:
#line 156 "parser.y"
    {(yyval.routine) = new Routine((yyvsp[(1) - (2)].routineHead), (yyvsp[(2) - (2)].routineBody));;}
    break;

  case 5:
#line 157 "parser.y"
    {(yyval.subRoutine) = new SubRoutine((yyvsp[(1) - (2)].routineHead), (yyvsp[(2) - (2)].routineBody));;}
    break;

  case 6:
#line 159 "parser.y"
    {(yyval.routineHead) = new RoutineHead((yyvsp[(1) - (5)].labelPart), (yyvsp[(2) - (5)].constPart), (yyvsp[(3) - (5)].typePart), (yyvsp[(4) - (5)].varPart), (yyvsp[(5) - (5)].routinePart));;}
    break;

  case 7:
#line 160 "parser.y"
    {(yyval.labelPart) = new LabelPart();;}
    break;

  case 8:
#line 161 "parser.y"
    {(yyval.constPart) = new ConstPart((yyvsp[(2) - (2)].constExprList));;}
    break;

  case 9:
#line 162 "parser.y"
    {(yyval.constPart) = new ConstPart(nullptr);}
    break;

  case 10:
#line 163 "parser.y"
    {(yyval.constExprList) = new ConstExprList(*(yyvsp[(2) - (5)].string), (yyvsp[(1) - (5)].constExprList), (yyvsp[(4) - (5)].constValue));;}
    break;

  case 11:
#line 164 "parser.y"
    {(yyval.constExprList) = new ConstExprList(*(yyvsp[(1) - (4)].string), nullptr, (yyvsp[(3) - (4)].constValue));;}
    break;

  case 12:
#line 165 "parser.y"
    {(yyval.constValue) = new ConstValue(*(yyvsp[(1) - (1)].string), ConstValue::T_INTEGER);;}
    break;

  case 13:
#line 166 "parser.y"
    {(yyval.constValue) = new ConstValue(*(yyvsp[(1) - (1)].string), ConstValue::T_REAL);;}
    break;

  case 14:
#line 167 "parser.y"
    {(yyval.constValue) = new ConstValue(*(yyvsp[(1) - (1)].string), ConstValue::T_SYS_CON);;}
    break;

  case 15:
#line 168 "parser.y"
    {(yyval.constValue) = new ConstValue(*(yyvsp[(1) - (1)].string), ConstValue::T_CHAR);;}
    break;

  case 16:
#line 169 "parser.y"
    {(yyval.constValue) = new ConstValue(*(yyvsp[(1) - (1)].string), ConstValue::T_STRING);;}
    break;

  case 17:
#line 170 "parser.y"
    {(yyval.typePart) = new TypePart((yyvsp[(2) - (2)].typeDeclList));;}
    break;

  case 18:
#line 171 "parser.y"
    {(yyval.typePart) = new TypePart(nullptr);;}
    break;

  case 19:
#line 172 "parser.y"
    {(yyval.typeDeclList) = new TypeDeclList((yyvsp[(1) - (2)].typeDeclList), (yyvsp[(2) - (2)].typeDefinition));;}
    break;

  case 20:
#line 173 "parser.y"
    {(yyval.typeDeclList) = new TypeDeclList(nullptr, (yyvsp[(1) - (1)].typeDefinition));;}
    break;

  case 21:
#line 174 "parser.y"
    {(yyval.typeDefinition) = new TypeDefinition(*(yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].typeDecl));;}
    break;

  case 22:
#line 175 "parser.y"
    {(yyval.typeDecl) = new TypeDecl((yyvsp[(1) - (1)].simpleTypeDecl));;}
    break;

  case 23:
#line 176 "parser.y"
    {(yyval.typeDecl) = new TypeDecl((yyvsp[(1) - (1)].arrayTypeDecl));;}
    break;

  case 24:
#line 177 "parser.y"
    {(yyval.typeDecl) = new TypeDecl((yyvsp[(1) - (1)].recordTypeDecl));;}
    break;

  case 25:
#line 178 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl(SimpleTypeDecl::T_SYS_TYPE, *(yyvsp[(1) - (1)].string));;}
    break;

  case 26:
#line 179 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl(SimpleTypeDecl::T_TYPE_NAME, *(yyvsp[(1) - (1)].string));;}
    break;

  case 27:
#line 180 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(2) - (3)].nameList));;}
    break;

  case 28:
#line 181 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(1) - (3)].constValue), (yyvsp[(3) - (3)].constValue));;}
    break;

  case 29:
#line 182 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(2) - (4)].constValue)->negate(), (yyvsp[(4) - (4)].constValue));;}
    break;

  case 30:
#line 183 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(2) - (5)].constValue)->negate(), (yyvsp[(5) - (5)].constValue)->negate());;}
    break;

  case 31:
#line 184 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl(*(yyvsp[(1) - (3)].string), *(yyvsp[(3) - (3)].string));;}
    break;

  case 32:
#line 185 "parser.y"
    {(yyval.arrayTypeDecl) = new ArrayTypeDecl((yyvsp[(3) - (6)].simpleTypeDecl), (yyvsp[(6) - (6)].typeDecl));;}
    break;

  case 33:
#line 186 "parser.y"
    {(yyval.recordTypeDecl) = new RecordTypeDecl((yyvsp[(2) - (3)].fieldDeclList));;}
    break;

  case 34:
#line 187 "parser.y"
    {(yyval.fieldDeclList) = new FieldDeclList((yyvsp[(1) - (2)].fieldDeclList), (yyvsp[(2) - (2)].fieldDecl));;}
    break;

  case 35:
#line 188 "parser.y"
    {(yyval.fieldDeclList) = new FieldDeclList(nullptr, (yyvsp[(1) - (1)].fieldDecl));;}
    break;

  case 36:
#line 189 "parser.y"
    {(yyval.fieldDecl) = new FieldDecl((yyvsp[(1) - (4)].nameList), (yyvsp[(3) - (4)].typeDecl));;}
    break;

  case 37:
#line 190 "parser.y"
    {(yyval.nameList) = new NameList((yyvsp[(1) - (3)].nameList), *(yyvsp[(3) - (3)].string));;}
    break;

  case 38:
#line 191 "parser.y"
    {(yyval.nameList) = new NameList(nullptr, *(yyvsp[(1) - (1)].string));;}
    break;

  case 39:
#line 192 "parser.y"
    {(yyval.varPart) = new VarPart((yyvsp[(2) - (2)].varDeclList));;}
    break;

  case 40:
#line 193 "parser.y"
    {(yyval.varPart) = new VarPart(nullptr);;}
    break;

  case 41:
#line 194 "parser.y"
    {(yyval.varDeclList) = new VarDeclList((yyvsp[(1) - (2)].varDeclList), (yyvsp[(2) - (2)].varDecl));;}
    break;

  case 42:
#line 195 "parser.y"
    {(yyval.varDeclList) = new VarDeclList(nullptr, (yyvsp[(1) - (1)].varDecl));;}
    break;

  case 43:
#line 196 "parser.y"
    {(yyval.varDecl) = new VarDecl((yyvsp[(1) - (4)].nameList), (yyvsp[(3) - (4)].typeDecl));;}
    break;

  case 44:
#line 198 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (2)].routinePart), (yyvsp[(2) - (2)].functionDecl));;}
    break;

  case 45:
#line 199 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (2)].routinePart), (yyvsp[(2) - (2)].procedureDecl));;}
    break;

  case 46:
#line 200 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (1)].functionDecl));;}
    break;

  case 47:
#line 201 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (1)].procedureDecl));;}
    break;

  case 48:
#line 202 "parser.y"
    {(yyval.routinePart) = new RoutinePart(RoutinePart::T_EMPTY);;}
    break;

  case 49:
#line 203 "parser.y"
    {(yyval.functionDecl) = new FunctionDecl((yyvsp[(1) - (4)].functionHead), (yyvsp[(3) - (4)].subRoutine));;}
    break;

  case 50:
#line 204 "parser.y"
    {(yyval.functionHead) = new FunctionHead(*(yyvsp[(2) - (5)].string), (yyvsp[(3) - (5)].parameters), (yyvsp[(5) - (5)].simpleTypeDecl));;}
    break;

  case 51:
#line 205 "parser.y"
    {(yyval.procedureDecl) = new ProcedureDecl((yyvsp[(1) - (4)].procedureHead), (yyvsp[(3) - (4)].subRoutine));;}
    break;

  case 52:
#line 206 "parser.y"
    {(yyval.procedureHead) = new ProcedureHead(*(yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].parameters));;}
    break;

  case 53:
#line 207 "parser.y"
    {(yyval.parameters) = new Parameters((yyvsp[(2) - (3)].paraDeclList));;}
    break;

  case 54:
#line 208 "parser.y"
    {(yyval.parameters) = new Parameters(nullptr);;}
    break;

  case 55:
#line 209 "parser.y"
    {(yyval.paraDeclList) = new ParaDeclList((yyvsp[(1) - (3)].paraDeclList), (yyvsp[(3) - (3)].paraTypeList));;}
    break;

  case 56:
#line 210 "parser.y"
    {(yyval.paraDeclList) = new ParaDeclList(nullptr, (yyvsp[(1) - (1)].paraTypeList));;}
    break;

  case 57:
#line 211 "parser.y"
    {(yyval.paraTypeList) = new ParaTypeList((yyvsp[(1) - (3)].varParaList), (yyvsp[(3) - (3)].simpleTypeDecl));;}
    break;

  case 58:
#line 212 "parser.y"
    {(yyval.paraTypeList) = new ParaTypeList((yyvsp[(1) - (3)].valParaList), (yyvsp[(3) - (3)].simpleTypeDecl));;}
    break;

  case 59:
#line 213 "parser.y"
    {(yyval.varParaList) = new VarParaList((yyvsp[(2) - (2)].nameList));;}
    break;

  case 60:
#line 214 "parser.y"
    {(yyval.valParaList) = new ValParaList((yyvsp[(1) - (1)].nameList));;}
    break;

  case 61:
#line 216 "parser.y"
    {(yyval.routineBody) = new RoutineBody((yyvsp[(1) - (1)].compoundStmt));;}
    break;

  case 62:
#line 217 "parser.y"
    {(yyval.compoundStmt) = new CompoundStmt((yyvsp[(2) - (3)].stmtList));;}
    break;

  case 63:
#line 218 "parser.y"
    {(yyval.stmtList) = new StmtList((yyvsp[(1) - (3)].stmtList), (yyvsp[(2) - (3)].stmt));;}
    break;

  case 64:
#line 219 "parser.y"
    {(yyval.stmtList) = new StmtList(nullptr, nullptr);;}
    break;

  case 65:
#line 220 "parser.y"
    {(yyval.stmt) = new Stmt(Stmt::T_LABELED, (yyvsp[(3) - (3)].nonLabelStmt));;}
    break;

  case 66:
#line 221 "parser.y"
    {(yyval.stmt) = new Stmt(Stmt::T_UNLABELED, (yyvsp[(1) - (1)].nonLabelStmt));;}
    break;

  case 67:
#line 222 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].assignStmt));;}
    break;

  case 68:
#line 223 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].procStmt));;}
    break;

  case 69:
#line 224 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].compoundStmt));;}
    break;

  case 70:
#line 225 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].ifStmt));;}
    break;

  case 71:
#line 226 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].repeatStmt));;}
    break;

  case 72:
#line 227 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].whileStmt));;}
    break;

  case 73:
#line 228 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].forStmt));;}
    break;

  case 74:
#line 229 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].caseStmt));;}
    break;

  case 75:
#line 230 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].gotoStmt));;}
    break;

  case 76:
#line 231 "parser.y"
    {(yyval.assignStmt) = new AssignStmt(*(yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].expression));;}
    break;

  case 77:
#line 232 "parser.y"
    {(yyval.assignStmt) = new AssignStmt(*(yyvsp[(1) - (6)].string), (yyvsp[(3) - (6)].expression), (yyvsp[(6) - (6)].expression));;}
    break;

  case 78:
#line 233 "parser.y"
    {(yyval.assignStmt) = new AssignStmt(*(yyvsp[(1) - (5)].string), *(yyvsp[(3) - (5)].string), (yyvsp[(5) - (5)].expression));;}
    break;

  case 79:
#line 234 "parser.y"
    {(yyval.procStmt) = new ProcStmt(ProcStmt::T_SIMPLE, *(yyvsp[(1) - (1)].string));;}
    break;

  case 80:
#line 235 "parser.y"
    {(yyval.procStmt) = new ProcStmt(*(yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].argsList));;}
    break;

  case 81:
#line 236 "parser.y"
    {(yyval.procStmt) = new ProcStmt(ProcStmt::T_SYS_PROC, *(yyvsp[(1) - (1)].string));;}
    break;

  case 82:
#line 237 "parser.y"
    {(yyval.procStmt) = new ProcStmt(*(yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].expressionList));;}
    break;

  case 83:
#line 238 "parser.y"
    {(yyval.procStmt) = new ProcStmt((yyvsp[(3) - (4)].factor));;}
    break;

  case 84:
#line 239 "parser.y"
    {(yyval.ifStmt) = new IfStmt((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].stmt), (yyvsp[(5) - (5)].elseClause));;}
    break;

  case 85:
#line 240 "parser.y"
    {(yyval.elseClause) = new ElseClause((yyvsp[(2) - (2)].stmt));;}
    break;

  case 86:
#line 241 "parser.y"
    {(yyval.elseClause) = new ElseClause(nullptr);;}
    break;

  case 87:
#line 242 "parser.y"
    {(yyval.repeatStmt) = new RepeatStmt((yyvsp[(2) - (4)].stmtList), (yyvsp[(4) - (4)].expression));;}
    break;

  case 88:
#line 243 "parser.y"
    {(yyval.whileStmt) = new WhileStmt((yyvsp[(2) - (4)].expression), (yyvsp[(4) - (4)].stmt));;}
    break;

  case 89:
#line 244 "parser.y"
    {(yyval.forStmt) = new ForStmt(*(yyvsp[(2) - (8)].string), (yyvsp[(4) - (8)].expression), (yyvsp[(5) - (8)].direction), (yyvsp[(6) - (8)].expression), (yyvsp[(8) - (8)].stmt));;}
    break;

  case 90:
#line 245 "parser.y"
    {(yyval.direction) = new Direction(Direction::T_TO);;}
    break;

  case 91:
#line 246 "parser.y"
    {(yyval.direction) = new Direction(Direction::T_DOWNTO);;}
    break;

  case 92:
#line 247 "parser.y"
    {(yyval.caseStmt) = new CaseStmt((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].caseExprList));;}
    break;

  case 93:
#line 248 "parser.y"
    {(yyval.caseExprList) = new CaseExprList((yyvsp[(1) - (2)].caseExprList), (yyvsp[(2) - (2)].caseExpr));;}
    break;

  case 94:
#line 249 "parser.y"
    {(yyval.caseExprList) = new CaseExprList(nullptr, (yyvsp[(1) - (1)].caseExpr));;}
    break;

  case 95:
#line 250 "parser.y"
    {(yyval.caseExpr) = new CaseExpr((yyvsp[(1) - (4)].constValue), (yyvsp[(3) - (4)].stmt));;}
    break;

  case 96:
#line 251 "parser.y"
    {(yyval.caseExpr) = new CaseExpr(*(yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].stmt));;}
    break;

  case 97:
#line 252 "parser.y"
    {(yyval.gotoStmt) = new GotoStmt(*(yyvsp[(2) - (2)].string));;}
    break;

  case 98:
#line 253 "parser.y"
    {(yyval.expressionList) = new ExpressionList((yyvsp[(1) - (3)].expressionList), (yyvsp[(3) - (3)].expression));;}
    break;

  case 99:
#line 254 "parser.y"
    {(yyval.expressionList) = new ExpressionList(nullptr, (yyvsp[(1) - (1)].expression));;}
    break;

  case 100:
#line 255 "parser.y"
    {(yyval.expression) = new Expression(Expression::T_GE, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expr));;}
    break;

  case 101:
#line 256 "parser.y"
    {(yyval.expression) = new Expression(Expression::T_GT, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expr));;}
    break;

  case 102:
#line 257 "parser.y"
    {(yyval.expression) = new Expression(Expression::T_LE, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expr));;}
    break;

  case 103:
#line 258 "parser.y"
    {(yyval.expression) = new Expression(Expression::T_LT, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expr));;}
    break;

  case 104:
#line 259 "parser.y"
    {(yyval.expression) = new Expression(Expression::T_EQ, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expr));;}
    break;

  case 105:
#line 260 "parser.y"
    {(yyval.expression) = new Expression(Expression::T_NE, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expr));;}
    break;

  case 106:
#line 261 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (1)].expr));;}
    break;

  case 107:
#line 262 "parser.y"
    {(yyval.expr) = new Expr(Expr::T_PLUS, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].term));;}
    break;

  case 108:
#line 263 "parser.y"
    {(yyval.expr) = new Expr(Expr::T_MINUS, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].term));;}
    break;

  case 109:
#line 264 "parser.y"
    {(yyval.expr) = new Expr(Expr::T_OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].term));;}
    break;

  case 110:
#line 265 "parser.y"
    {(yyval.expr) = new Expr((yyvsp[(1) - (1)].term));;}
    break;

  case 111:
#line 266 "parser.y"
    {(yyval.term) = new Term(Term::T_MUL, (yyvsp[(1) - (3)].term), (yyvsp[(3) - (3)].factor));;}
    break;

  case 112:
#line 267 "parser.y"
    {(yyval.term) = new Term(Term::T_DIV, (yyvsp[(1) - (3)].term), (yyvsp[(3) - (3)].factor));;}
    break;

  case 113:
#line 268 "parser.y"
    {(yyval.term) = new Term(Term::T_MOD, (yyvsp[(1) - (3)].term), (yyvsp[(3) - (3)].factor));;}
    break;

  case 114:
#line 269 "parser.y"
    {(yyval.term) = new Term(Term::T_AND, (yyvsp[(1) - (3)].term), (yyvsp[(3) - (3)].factor));;}
    break;

  case 115:
#line 270 "parser.y"
    {(yyval.term) = new Term((yyvsp[(1) - (1)].factor));;}
    break;

  case 116:
#line 271 "parser.y"
    {(yyval.factor) = new Factor(Factor::T_NAME, *(yyvsp[(1) - (1)].string));;}
    break;

  case 117:
#line 272 "parser.y"
    {(yyval.factor) = new Factor(Factor::T_NAME_ARGS, *(yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].argsList));;}
    break;

  case 118:
#line 273 "parser.y"
    {(yyval.factor) = new Factor(Factor::T_SYS_FUNCT, *(yyvsp[(1) - (1)].string));;}
    break;

  case 119:
#line 274 "parser.y"
    {(yyval.factor) = new Factor(Factor::T_SYS_FUNCT_ARGS, *(yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].argsList));;}
    break;

  case 120:
#line 275 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (1)].constValue));;}
    break;

  case 121:
#line 276 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(2) - (3)].expression));;}
    break;

  case 122:
#line 277 "parser.y"
    {(yyval.factor) = new Factor(Factor::T_NOT_FACTOR, (yyvsp[(2) - (2)].factor));;}
    break;

  case 123:
#line 278 "parser.y"
    {(yyval.factor) = new Factor(Factor::T_MINUS_FACTOR, (yyvsp[(2) - (2)].factor));;}
    break;

  case 124:
#line 279 "parser.y"
    {(yyval.factor) = new Factor(*(yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].expression));;}
    break;

  case 125:
#line 280 "parser.y"
    {(yyval.factor) = new Factor(*(yyvsp[(1) - (3)].string), *(yyvsp[(3) - (3)].string));;}
    break;

  case 126:
#line 281 "parser.y"
    {(yyval.argsList) = new ArgsList((yyvsp[(1) - (3)].argsList), (yyvsp[(3) - (3)].expression));;}
    break;

  case 127:
#line 282 "parser.y"
    {(yyval.argsList) = new ArgsList(nullptr, (yyvsp[(1) - (1)].expression));;}
    break;

  case 128:
#line 283 "parser.y"
    {(yyval.string) = (yyvsp[(1) - (1)].string);}
    break;

  case 129:
#line 284 "parser.y"
    {;}
    break;


/* Line 1267 of yacc.c.  */
#line 2411 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 286 "parser.y"

