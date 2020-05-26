//
// Created by QZQ on 2018/6/9.
//
#include "AST.h"
#include "parser.hpp"

extern int yyparse();

extern FILE *yyin;
extern Program *astRoot;


const std::string systemFunctionFile = "system.spl";

RoutinePart *newRoutinePartAST(const std::string &filePath) {
	yyin = fopen((filePath).c_str(), "r");
	yyparse();
	return astRoot->routine->routineHead->routinePart;
}

void installSystemFunctions(Program *root) {
	auto routinePart = root->routine->routineHead->routinePart;
	while (routinePart->routinePart)
		routinePart = routinePart->routinePart;
	std::cout << routinePart << std::endl;
	if (routinePart)
		routinePart->routinePart = newRoutinePartAST(systemFunctionFile);
	else
		root->routine->routineHead->routinePart = newRoutinePartAST(systemFunctionFile);
}
