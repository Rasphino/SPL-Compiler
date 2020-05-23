%{
#include <iostream>
// TODO

void yyerror(char *s) {
    std::cerr << s << std::endl;
}
%}

%union {
    // TODO
}

%token 
    ID STRING INTEGER REAL CHAR
    LP RP LB RB DOTDOT COMMA COLON SEMI
    DOT PLUS MINUS MUL LT LE EQ NE GT GE ASSIGN
    AND OR NOT DIV MOD
    ARRAY BEGIN CASE CONST DO DOWNTO ELSE END FOR FUNCTION GOTO
    IF IN OF PACKED PROCEDURE PROGRAM READ RECORD REPEAT SET THEN
    TO TYPE UNTIL VAR WHILE WITH
    SYS_CON SYS_FUNCT SYS_PROC SYS_TYPE
    
%type   // TODO
%nterm  // TODO
    

%start program

%%

program         : program_head routine DOT  {}
                ;
program_head    : PROGRAM ID SEMI           { $$ = $2 }
                ;
routine         : routine_head routine_body {}
                ;
sub_routine     : routine_head routine_body {}
                ;

routine_head    : label_part const_part type_part var_part routine_part
                                            {}
                ;
label_part      : ; // empty
const_part      : CONST const_expr_list     {}
                |   // empty
                ;
const_expr_list : const_expr_list ID EQ const_value SEMI
                                            {}
                | ID EQ const_value SEMI    {}
                ;
const_value     : INTEGER                   { $$ = $1 }
                | REAL                      { $$ = $1 }
                | CHAR                      { $$ = $1 }
                | STRING                    { $$ = $1 }
                | SYS_CON                   { $$ = $1 }
                ;

type_part       : TYPE type_decl_list       {}
                |  // empty
                ;
type_decl_list  : type_decl_list type_definition    {}
                | type_definition           {}
                ;
type_definition : ID EQ type_decl SEMI      {}
                ;
type_decl       : simple_type_decl          { $$ = $1 }
                | array_type_decl           { $$ = $1 }
                | record_type_decl          { $$ = $1 }
                ;
simple_type_decl: SYS_TYPE                  {}
                | ID                        {}
                | LP name_list RP           {}
                | const_value DOTDOT const_value    {}
                | MINUS const_value DOTDOT const_value  {}
                | MINUS const_value DOTDOT MINUS const_value    {}
                | ID DOTDOT ID              {}
                ;
array_type_decl : ARRAY LB simple_type_decl RB OF type_decl {}
                ;
record_type_decl: RECORD field_decl_list END    {}
                ;
field_decl_list : field_decl_list field_decl    {}
                | field_decl                {}
                ;
field_decl      : name_list COLON type_decl SEMI    {}
                ;
name_list       : name_list COMMA ID        {}
                | ID                        {}
                ;

var_part        : VAR var_decl_list         {}
                |   // empty
                ;
var_decl_list   : var_decl_list var_decl    {}
                | var_decl                  {}
                ;
var_decl        : name_list COLON type_decl SEMI    {}
                ;
                
routine_part    : routine_part function_decl    {}
                | routine_part procedure_decl   {}
                | function_decl             {}
                | procedure_decl            {}
                |   // empty
                ;
function_decl   : function_head SEMI sub_routine SEMI   {}
                ;
function_head   : FUNCTION ID parameters COLON simple_type_decl {}
                ;
procedure_decl  : procedure_head SEMI sub_routine SEMI  {}
                ;
procedure_head  : PROCEDURE ID parameters   {}
                ;
parameters      : LP para_decl_list RP      {}
                |   // empty
                ;
para_decl_list  : para_decl_list SEMI para_type_list    {}
                | para_type_list            {}
                ;
para_type_list  : var_para_list COLON simple_type_decl  {}
                | val_para_list COLON simple_type_decl  {}
                ;
var_para_list   : VAR name_list             {}
                ;
val_para_list   : name_list                 {}
                ;

routine_body    : compound_stmt             {}
                ;
compound_stmt   : BEGIN stmt_list END       {}
                ;
stmt_list       : stmt_list stmt SEMI       {}
                |   // empty
                ;
stmt            : INTEGER COLON non_label_stmt  {}
                | non_label_stmt            {}
                ;
non_label_stmt  : assign_stmt               { $$ = $1 }
                | proc_stmt                 { $$ = $1 }
                | compound_stmt             { $$ = $1 }
                | if_stmt                   { $$ = $1 }
                | repeat_stmt               { $$ = $1 }
                | while_stmt                { $$ = $1 }
                | for_stmt                  { $$ = $1 }
                | case_stmt                 { $$ = $1 }
                | goto_stmt                 { $$ = $1 }
                ;
assign_stmt     : ID ASSIGN expression      {}
                | ID LB expression RB ASSIGN expression {}
                | ID DOT ID ASSIGN expression   {}
                ;
proc_stmt       : ID                        {}
                | ID LP args_list RP        {}
                | SYS_PROC                  {}
                | SYS_PROC LP expression_list RP    {}
                | READ LP factor RP         {}
                ;
if_stmt         : IF expression THEN stmt else_clause   {}
                ;
else_clause     : ELSE stmt                 { $$ = $2 }
                |   // empty
                ;
repeat_stmt     : REPEAT stmt_list UNTIL expression {}
                ;
while_stmt      : WHILE expression DO stmt  {}
                ;
for_stmt        : FOR ID ASSIGN expression direction expression DO stmt
                                            {}
                ;
direction       : TO                        { $$ = $1 }
                | DOWNTO                    { $$ = $1 }
                ;
case_stmt       : CASE expression OF case_expr_list END {}
                ;
case_expr_list  : case_expr_list case_expr  {}
                | case_expr                 {}
                ;
case_expr       : const_value COLON stmt SEMI   {}
                | ID COLON stmt SEMI        {}
                ;
goto_stmt       : GOTO INTEGER              {}
                ;
expression_list : expression_list COMMA expression  {}
                | expression                {}
                ;
expression      : expression GE expr        {}
                | expression GT expr        {}
                | expression LE expr        {}
                | expression LT expr        {}
                | expression EQ expr        {}
                | expression NE expr        {}
                | expr                      {}
                ;
expr            : expr PLUS term            {}
                | expr MINUS term           {}
                | expr OR term              {}
                | term                      {}
                ;
term            : term MUL factor           {}
                | term DIV factor           {}
                | term MOD factor           {}
                | term AND factor           {}
                | term                      {}
                ;
factor          : ID                        {}
                | ID LP args_list RP         {}
                | SYS_FUNCT                 {}
                | SYS_FUNCT LP args_list RP  {}
                | const_value               {}
                | LP expression RP          {}
                | NOT factor                {}
                | MINUS factor              {}
                | ID LB expression RB       {}
                | ID DOT ID                 {}
                ;
args_list       : args_list COMMA expression{}
                | expression                {}
                ;
%%

