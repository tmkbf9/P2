#ifndef __PARSER_H__
#define __PARSER_H__

class Scanner;
class Node;
struct token;

class Parser {
 public:
  Parser(Scanner & scanner, token & token) : scanner(scanner), errTk(token) {}

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
  bool validParse = true;
  token& errTk;
};

#endif
