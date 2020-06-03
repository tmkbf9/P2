#include <cstddef>
#include "parser.h"

Node * Parser::parse() {
  token startingToken = scanner.scanner();

  return createSToken(startingToken);
}

Node * Parser::createSToken(token & startingToken) {
  Node newNode = new Node("<S>");
  string literal = startingToken.tokenLiteral;
  int nodeCount = 0;
  
  if(literal == "program") {
    Node * programNode = new Node("ProgramNode", startingToken);
    newNode->addSubtree(programNode, nodeCount++);

    startingToken = scanner.scanner();
    
    if(startingToken.tokenLiteral == "var") {
      Node * vNode = createVNode(startingToken);
      newNode->addSubtree(vNode, nodeCount++);
      startingToken = scanner.scanner();
    }

    if(lookaheadToken.tokenLiteral == "begin") {
      Node * bNode = createBNode();
      newNode->addSubtree(bNode, nodeCount++);
      startingToken = scanner.scanner();

      if(startingToken.tokenID != "EOFTK") {
	cerr << "error encountered at line " << startingToken.linenumber << ". Token: " << startingToken << endl;
	return NULL;
      }
    } 
  }    
  
  if(nodeCount == 0 || nodeCount == 1) {
    cerr << "error encountered at line " << startingToken.linenumber << ". Token: " << startingToken << endl;
    return NULL;
  }

  return newNode;
}





