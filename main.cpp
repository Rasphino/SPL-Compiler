#include <iostream>
#include <fstream>

#include <fmt/core.h>
#include <fmt/printf.h>

#include "AST.h"
#include "CodeGen.h"
#include "parser.tab.hh"

extern FILE *yyin;
extern AST::Program *astRoot;

extern int yyparse();

std::ofstream astOut;
int AST::Node::idCount = 0;

void printAST(AST::Node *node) {
  auto children = node->getChildren();
  std::string info = node->getInfo();
  for (auto child : children) {
    if (child) {
      astOut << fmt::sprintf(R"({ key: %d, text: "%s%s%s", fill: "#f8f8f8", stroke: "#000000", parent: %d },)",
                                child->id,
                                child->getName(),
                                info.empty() ? "" : " : ",
                                info,
                                node->id)
             << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  std::string sourcePath;
  auto sourceFile = sourcePath + argv[1];
  std::cout << "input file: " << sourceFile << std::endl;
  yyin = fopen(sourceFile.c_str(), "r");
  yyparse();

  auto root = astRoot;
  //visualize
  astOut.open("ast.json", std::ios::out | std::ios::trunc);
  astOut << "var nodeDataArray = [ " << std::endl
         << fmt::sprintf(R"({ key: %d, text: "%s", fill: "#f8f8f8", stroke: "#000000" }, )",
                         root->id, root->getName()) << std::endl;
  std::cout << "begin draw ast" << std::endl;
  root->traverse(printAST, [](AST::Node *){});
  std::cout << "finish draw ast" << std::endl;
  astOut << "]" << std::endl;
  astOut.close();

  CodeGen::CodeGenContext context;
  context.generateCode(root, "output.ll");
  return 0;
}
