#ifndef __PARSER_H__
#define __PARSER_H__

class Scanner;
class Node;
struct token;

class Parser {
 public:
  Parser(Scanner & scanner) : scanner(scanner) {}

  Node * parse();

  Node * createSNode(token &token);
  Node * createBNode(token &token);
  Node * createVNode(token &token);
  Node * createMNode(token& token);
  Node * createHNode(token& token);
  Node * createRNode(token& token);
  Node * createQNode(token &token);
  Node * createTNode(token& token);
  Node * createWNode(token& token);

 private:
  Scanner & scanner;
};

#endif
