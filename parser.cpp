#include <cstddef>
#include <string>
#include <iostream>
#include "parser.h"
#include "node.h"
#include "scanner.h"
#include "token.h"

using namespace std;

Node * Parser::parse() {
  token startingToken = scanner.scanner();

  return createSNode(startingToken);
}

Node * Parser::createSNode(token & startingToken) {
  Node * newNode = new Node("<S>");
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

    if(startingToken.tokenLiteral == "begin") {
      Node * bNode = createBNode(startingToken);
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

Node* Parser::createBNode(token& startingToken) {
    Node * newNode = new Node("<B>");
    int nodeCount = 0;

    if (startingToken.tokenLiteral == "begin") {
        Node* beginNode = new Node("BeginNode", startingToken);
        newNode->addSubtree(beginNode, nodeCount++);

        startingToken = scanner.scanner();
        string literal = startingToken.tokenLiteral;

        if (literal == "var") {
            Node * vNode = createVNode(startingToken);
            newNode->addSubtree(vNode, nodeCount++);
            startingToken = scanner.scanner();
        }

        if (literal == "scan" || literal == "write" || literal == "begin" || literal == "if" || literal == "repeat" || literal == "let") {
            Node* qNode = createQNode(startingToken);
            newNode->addSubtree(qNode, nodeCount++);
            startingToken = scanner.scanner();
        }

        if (literal == "end")
        {
            Node* beginNode = new Node("BeginNode", startingToken);
            newNode->addSubtree(beginNode, nodeCount++);
        }
    }

    if (nodeCount == 0 || nodeCount == 1) {
        cerr << "error encountered at line " << startingToken.linenumber << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}
Node* Parser::createVNode(token& startingToken) {
    return NULL;
}
Node* Parser::createQNode(token& startingToken) {
    return NULL;
}


