#ifndef __PARSER_H__
#define __PARSER_H__

#include "token.h"

class Scanner;
class Node;

class Parser {
 public:
  Parser(Scanner & scanner) : scanner(scanner), errTk(), validParse(true) {}

  Node * parse();

  Node * createSNode(token &token);
  Node * createBNode(token &token);
  Node * createVNode(token &token);
  Node * createMNode(token& token);
  Node * createHNode(token& token);
  Node * createRNode(token& token);
  Node * createQNode(token &token);
  Node * createTNode(token& token);
  Node * createANode(token& token);
  Node * createWNode(token& token);
  Node * createINode(token& token);
  Node * createGNode(token& token);
  Node * createENode(token& token);
  Node * createZNode(token& token);

 private:
  Scanner & scanner;
  bool validParse;
  token errTk;
};

#endif
