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
    cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
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
        }

        if (startingToken.tokenLiteral == "end")
        {
            Node* endNode = new Node("EndNode", startingToken);
            newNode->addSubtree(endNode, nodeCount++);
        }
    }

    if (nodeCount == 0 || nodeCount == 1) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}
Node* Parser::createVNode(token& startingToken) {
    Node* newNode = new Node("<V>");
    int nodeCount = 0;

    if (startingToken.tokenLiteral == "var") {
        Node* varNode = new Node("VarNode", startingToken);
        newNode->addSubtree(varNode, nodeCount++);

        startingToken = scanner.scanner();

        if (startingToken.tokenID == "IDTK") {
            Node* identifierNode = new Node("IdentifierNode", startingToken);
            newNode->addSubtree(identifierNode, nodeCount++);

            startingToken = scanner.scanner();
            string literal = startingToken.tokenLiteral;

            if (startingToken.tokenLiteral == ".") {
                Node* periodNode = new Node("PeriodNode", startingToken);
                newNode->addSubtree(periodNode, nodeCount++);

                startingToken = scanner.scanner();
                string literal = startingToken.tokenLiteral;

                if (literal == "var") {
                    Node* vNode = createVNode(startingToken);
                    newNode->addSubtree(vNode, nodeCount++);
                    startingToken = scanner.scanner();
                }
            }
        }
    }

    if (nodeCount != 4 && nodeCount != 3) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}

Node* Parser::createMNode(token& startingToken) {
    Node* newNode = new Node("<M>");
    int nodeCount = 0;

    Node* hNode = createHNode(startingToken);
    newNode->addSubtree(hNode, nodeCount++);

    startingToken = scanner.scanner();

    if (startingToken.tokenLiteral == "+") {
        Node* plusNode = new Node("PlusNode", startingToken);
        newNode->addSubtree(plusNode, nodeCount++);
    }
    else if (startingToken.tokenLiteral == "-") {
        Node* minusNode = new Node("MinusNode", startingToken);
        newNode->addSubtree(minusNode, nodeCount++);
    }
    else if (startingToken.tokenLiteral == "/") {
        Node* divideNode = new Node("DivideNode", startingToken);
        newNode->addSubtree(divideNode, nodeCount++);
    }
    else if (startingToken.tokenLiteral == "*") {
        Node* multiplyNode = new Node("MultiplyNode", startingToken);
        newNode->addSubtree(multiplyNode, nodeCount++);
    }

    if (nodeCount == 2) {
        startingToken = scanner.scanner();
        Node* mNode = createMNode(startingToken);
        newNode->addSubtree(mNode, nodeCount++);
    }


    if (nodeCount != 1 && nodeCount != 3) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}
Node* Parser::createHNode(token& startingToken) {
    Node* newNode = new Node("<H>");
    int nodeCount = 0;

    if (startingToken.tokenLiteral == "&") {
        Node* ampersandNode = new Node("AmpersandNode", startingToken);
        newNode->addSubtree(ampersandNode, nodeCount++);
        startingToken = scanner.scanner();
    }

    if (startingToken.tokenID == "IDTK" || startingToken.tokenID == "NUMTK") {
        Node* rNode = createRNode(startingToken);
        newNode->addSubtree(rNode, nodeCount++);
    }

    if (nodeCount != 1 && nodeCount != 2) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}

Node* Parser::createRNode(token& startingToken) {
    Node* newNode = new Node("<R>");
    int nodeCount = 0;

    if (startingToken.tokenID == "IDTK") {
        Node* identifierNode = new Node("IdentifierNode", startingToken);
        newNode->addSubtree(identifierNode, nodeCount++);
    }
    else  if (startingToken.tokenID == "NUMTK") {
        Node* numberNode = new Node("NumberNode", startingToken);
        newNode->addSubtree(numberNode, nodeCount++);
    }

    if (nodeCount != 1) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}

Node* Parser::createQNode(token& startingToken) {
    Node* newNode = new Node("<Q>");
    int nodeCount = 0;

    Node* tNode = createTNode(startingToken);
    newNode->addSubtree(tNode, nodeCount++);

    startingToken = scanner.scanner();

    if (startingToken.tokenLiteral == "#") {
        Node* poundNode = new Node("PoundNode", startingToken);
        newNode->addSubtree(poundNode, nodeCount++);

        startingToken = scanner.scanner();
        string literal = startingToken.tokenLiteral;

        if (literal == "scan" || literal == "write" || literal == "begin" || literal == "if" || literal == "repeat" || literal == "let") {
            Node* qNode = createQNode(startingToken);
            newNode->addSubtree(qNode, nodeCount++);
        }
    }

    if (nodeCount != 2 && nodeCount != 3) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}

Node* Parser::createTNode(token& startingToken) {
    Node* newNode = new Node("<T>");
    int nodeCount = 0;
    bool bNodeCreated = false;

    if (startingToken.tokenLiteral == "scan") {

    }
    else if (startingToken.tokenLiteral == "write") {
        Node* wNode = createWNode(startingToken);
        newNode->addSubtree(wNode, nodeCount++);
    } 
    else if (startingToken.tokenLiteral == "begin") {
        Node* bNode = createBNode(startingToken);
        newNode->addSubtree(bNode, nodeCount++);
        bNodeCreated = true;
    }
    else if (startingToken.tokenLiteral == "if") {

    }
    else if (startingToken.tokenLiteral == "repeat") {

    }
    else if (startingToken.tokenLiteral == "let") {

    }

    if (startingToken.tokenLiteral == "," && bNodeCreated == false) {
        Node* commaNode = new Node("CommaNode", startingToken);
        newNode->addSubtree(commaNode, nodeCount++);
    }

    if ((nodeCount != 2 && bNodeCreated == false) || (nodeCount != 1 && bNodeCreated == true)) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}

Node* Parser::createANode(token& startingToken) {
    Node* newNode = new Node("<A>");
    int nodeCount = 0;

    if (startingToken.tokenLiteral == "scan") {
        Node* scanNode = new Node("ScanNode", startingToken);
        newNode->addSubtree(scanNode, nodeCount++);
        startingToken = scanner.scanner();

        if (startingToken.tokenID == "IDTK") {
            Node* identifierNode = new Node("IdentifierNode", startingToken);
            newNode->addSubtree(identifierNode, nodeCount++);
            startingToken = scanner.scanner();
        }
        else if (startingToken.tokenID == "NUMTK") {
            Node* numberNode = new Node("NumberNode", startingToken);
            newNode->addSubtree(numberNode, nodeCount++);
            startingToken = scanner.scanner();
        }
    }

    if (nodeCount != 2) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }

    return newNode;
}

Node* Parser::createWNode(token& startingToken) {
    Node* newNode = new Node("<W>");
    int nodeCount = 0;

    if (startingToken.tokenLiteral == "write") {
        Node* writeNode = new Node("WriteNode", startingToken);
        newNode->addSubtree(writeNode, nodeCount++);
        startingToken = scanner.scanner();

    }

    Node* mNode = createMNode(startingToken);
    newNode->addSubtree(mNode, nodeCount++);

    if (nodeCount != 2) {
        cerr << "error encountered at: " << newNode->nodeName << ". Token: " << startingToken << endl;
        return NULL;
    }
    return newNode;
}

Node* Parser::createINode(token& startingToken) {
    Node* newNode = new Node("<I>");
    int nodeCount = 0;

    if (startingToken.tokenLiteral == "if") {
        Node* ifNode = new Node("IfNode", startingToken);
        newNode->addSubtree(ifNode, nodeCount++);
        startingToken = scanner.scanner();

        if (startingToken.tokenLiteral == "[") {
            Node* openBracketNode = new Node("OpenBracketNode", startingToken);
            newNode->addSubtree(openBracketNode, nodeCount++);
            startingToken = scanner.scanner();

            Node* mNode = createMNode(startingToken);
            newNode->addSubtree(mNode, nodeCount++);
            

        }
    }
    return newNode;
}
    