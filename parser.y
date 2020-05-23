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

%token ID // ... TODO

%start program

%%

program         : program_head routine DOT  {}
                ;
program_head    : PROGRAM ID SEMI           {}
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
const_value     : INT                       {}
                | READ                      {}
                | CHAR                      {}
                | STR                       {}
                | SYS_CON {}
                ;

type_part       : TYPE type_decl_list       {}
                |  // empty
                ;
type_decl_list  : type_decl_list type_definition    {}
                | type_definition           {}
                ;
type_definition : ID EQ type_decl SEMI      {}
                ;
type_decl       : simple_type_decl          {}
                | array_type_decl           {}
                | record_type_decl          {}
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


%%

