#include <iostream>
#include <stdio.h>
#include <fstream>
#include "AST.h"
#include "codegen.h"
#include "parser.hpp"

extern FILE *yyin;
extern Program *astRoot;

void installSystemFunctions(Program *root);

extern int yyparse();

std::ofstream astOut;
int Node::idCount = 0;

//to do: node->info() is not printed
void printAST(Node *node) {
    auto children = node->getChildren();
    std::string info = node->getInfo();
    for (auto child : children) {
        if (child)
	 astOut << "{ key: "<<child->id<<", text: \""<<child->getName()<<"\", fill: \"#f8f8f8\", stroke: \"#000000\","<<"parent:"<<node->id<<" }," << std::endl;
    }
}

void doNothing(Node *node) {}

int main(int argc, char **argv) {
    std::string sourcePath;
    auto sourceFile = sourcePath + argv[1];
    std::cout << "input file: " << sourceFile << std::endl;
    yyin = fopen(sourceFile.c_str(), "r");
    yyparse();

    auto root = astRoot;
    //	install system functions
	installSystemFunctions(root);
    //visualize
    astOut.open("ast.json", std::ios::out | std::ios::trunc);
    astOut << "var nodeDataArray = [ " << std::endl;
    astOut << "{ key: "<<root->id<<", text: \""<<root->getName()<<"\", fill: \"#f8f8f8\", stroke: \"#000000\" }," << std::endl;
    std::cout << "begin draw ast" << std::endl;
    root->traverse(printAST, doNothing);
    std::cout << "finish draw ast" << std::endl;
    astOut << "]" << std::endl;
    astOut.close();

    CodeGenContext context;
    context.generateCode(root, "output.ll");
    return 0;
}
