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
  Node * createQNode(token &token);

 private:
  Scanner & scanner;
};

#endif
