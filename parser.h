#ifndef __PARSER_H__
#define __PARSER_H__

class Scanner;
class Node;

class Parser {
 public:
  Parser(Scanner & scanner) : scanner(scanner) {}

  Node * parse();

  void createSNode(token);

 private:
  Scanner & scanner;
};

#endif
