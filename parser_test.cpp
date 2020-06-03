#include <vector>
#include <assert.h>
#include <sstream>
#include <iostream>

#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "node.h"

using namespace std;
void test_smallest_valid_BNF() {
    istringstream is("program begin end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    //assert(rootNode->subTrees[1];
}
void programKeywordOnlyIsInvalidProgram() {
  static string programText = "program";
  istringstream inputStream(programText.c_str());
  
  //  string errorMessage = parser.parse(inputStream, errorStream);

}

int main(int argc, char ** argv) {
    test_smallest_valid_BNF();

    return 0;
}



