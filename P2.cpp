#include <iostream>

#include "scanner.h"
#include "parser.h"
#include "test_tree.h"
#include "node.h"

using namespace std;

int main(int argc, char ** arvgv) {
  Scanner scanner(cin, cerr);
  Parser parser(scanner);
  TestTree printer;
  
  Node * rootNode = parser.parse();
  printer.print(rootNode, cout);

  return(0);
}
