#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>

#include "parser.h"
#include "node.h"
#include "scanner.h"
#include "token.h"

using namespace std;

Node * Parser::parse(Scanner & scanner) {
  validParse = true;
  token lookaheadToken = scanner.scanner();

  AvailableTokens tokens(scanner, lookaheadToken);

  return createSNode(tokens);
}

Node * Parser::createSNode(AvailableTokens & availableTokens) {
  Node * newNode = new Node("<S>");
  int nodeCount = 0;
  
  token currentToken = availableTokens.nextToken();
  if(currentToken.tokenLiteral == "program") {
    Node * programNode = new Node("ProgramNode", currentToken);
    newNode->addSubtree(programNode, nodeCount++);

    string nextTokenLiteral = availableTokens.lookaheadToken().tokenLiteral;
    
    if(nextTokenLiteral == "var") {
      Node * vNode = createVNode(availableTokens);
      newNode->addSubtree(vNode, nodeCount++);
    }
    
    nextTokenLiteral = availableTokens.lookaheadToken().tokenLiteral;

    if(nextTokenLiteral == "begin") {
      Node * bNode = createBNode(availableTokens);
      newNode->addSubtree(bNode, nodeCount++);

      if(availableTokens.lookaheadToken().tokenID != "EOFTK") {
          validParse = false; 
      }
    } 
  }    
  
  if ((nodeCount == 0 || nodeCount == 1) && validParse) {
    validParse = false;
    errTk = currentToken;
  }

  if (!validParse) {
      newNode = new Node("ERROR", errTk);
  }

  return newNode;
}

Node* Parser::createBNode(AvailableTokens & availableTokens) {
    Node * newNode = new Node("<B>");
    int nodeCount = 0;

    token currentToken = availableTokens.nextToken();
    
    if (currentToken.tokenLiteral == "begin") {
        Node* beginNode = new Node("BeginNode", currentToken);
        newNode->addSubtree(beginNode, nodeCount++);

	string nextTokenLiteral = availableTokens.lookaheadToken().tokenLiteral;
        if (nextTokenLiteral == "var") {
            Node * vNode = createVNode(availableTokens);
            newNode->addSubtree(vNode, nodeCount++);
        }

	nextTokenLiteral = availableTokens.lookaheadToken().tokenLiteral;
        if (nextTokenLiteral == "scan" ||
	    nextTokenLiteral == "write" ||
	    nextTokenLiteral == "begin" ||
	    nextTokenLiteral == "if" ||
	    nextTokenLiteral == "repeat" ||
	    nextTokenLiteral == "let") {
	  // Node* qNode = createQNode(availableTokens);
	  // newNode->addSubtree(qNode, nodeCount++);
        }

	currentToken = availableTokens.nextToken();
        if (currentToken.tokenLiteral == "end")
        {
	  Node* endNode = new Node("EndNode", currentToken);
	  newNode->addSubtree(endNode, nodeCount++);
        }
    }

    if ((nodeCount == 0 || nodeCount == 1) && validParse) {
        validParse = false;
        errTk = currentToken;
    }

    return newNode;
}

Node* Parser::createVNode(AvailableTokens & availableTokens) {
    Node* newNode = new Node("<V>");
    int nodeCount = 0;

    token currentToken = availableTokens.nextToken();
    
    if (currentToken.tokenLiteral == "var") {
        Node* varNode = new Node("VarNode", currentToken);
        newNode->addSubtree(varNode, nodeCount++);

        currentToken = availableTokens.nextToken();

        if (currentToken.tokenID == "IDTK") {
            Node* identifierNode = new Node("IdentifierNode", currentToken);
            newNode->addSubtree(identifierNode, nodeCount++);

            currentToken = availableTokens.nextToken();
            if (currentToken.tokenLiteral == ".") {
                Node* periodNode = new Node("PeriodNode", currentToken);
                newNode->addSubtree(periodNode, nodeCount++);

		string nextTokenLiteral = availableTokens.lookaheadToken().tokenLiteral;
                if (nextTokenLiteral == "var") {
                    Node* vNode = createVNode(availableTokens);
                    newNode->addSubtree(vNode, nodeCount++);
                }
            }
        }
    }

    if (nodeCount != 4 && nodeCount != 3 && validParse) {
        validParse = false;
        errTk = currentToken;
    }

    return newNode;
}

// Node * Parser::createMNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<M>");
//     int nodeCount = 0;

//     Node* hNode = createHNode(availableTokens);
//     newNode->addSubtree(hNode, nodeCount++);

//     currentToken = scanner.scanner();

//     if (currentToken.tokenLiteral == "+") {
//         Node* plusNode = new Node("PlusNode", currentToken);
//         newNode->addSubtree(plusNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "-") {
//         Node* minusNode = new Node("MinusNode", currentToken);
//         newNode->addSubtree(minusNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "/") {
//         Node* divideNode = new Node("DivideNode", currentToken);
//         newNode->addSubtree(divideNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "*") {
//         Node* multiplyNode = new Node("MultiplyNode", currentToken);
//         newNode->addSubtree(multiplyNode, nodeCount++);
//     }

//     if (nodeCount == 2) {
//         currentToken = scanner.scanner();
//         Node* mNode = createMNode(availableTokens);
//         newNode->addSubtree(mNode, nodeCount++);
//     }


//     if ((nodeCount != 1 && nodeCount != 3) && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }

//     return newNode;
// }
// Node* Parser::createHNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<H>");
//     int nodeCount = 0;

//     if (currentToken.tokenLiteral == "&") {
//         Node* ampersandNode = new Node("AmpersandNode", currentToken);
//         newNode->addSubtree(ampersandNode, nodeCount++);
//         currentToken = scanner.scanner();
//     }

//     if (currentToken.tokenID == "IDTK" || currentToken.tokenID == "NUMTK") {
//         Node* rNode = createRNode(availableTokens);
//         newNode->addSubtree(rNode, nodeCount++);
//     }

//     if ((nodeCount != 1 && nodeCount != 2) && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }

//     return newNode;
// }

// Node* Parser::createRNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<R>");
//     int nodeCount = 0;

//     if (currentToken.tokenID == "IDTK") {
//         Node* identifierNode = new Node("IdentifierNode", currentToken);
//         newNode->addSubtree(identifierNode, nodeCount++);
//     }
//     else  if (currentToken.tokenID == "NUMTK") {
//         Node* numberNode = new Node("NumberNode", currentToken);
//         newNode->addSubtree(numberNode, nodeCount++);
//     }

//     if (nodeCount != 1 && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }

//     return newNode;
// }

// Node* Parser::createQNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<Q>");
//     int nodeCount = 0;

//     Node* tNode = createTNode(availableTokens);
//     newNode->addSubtree(tNode, nodeCount++);

//     currentToken = scanner.scanner();

//     if (currentToken.tokenLiteral == "#") {
//         Node* poundNode = new Node("PoundNode", currentToken);
//         newNode->addSubtree(poundNode, nodeCount++);

//         currentToken = scanner.scanner();
//         string literal = currentToken.tokenLiteral;

//         if (literal == "scan" || literal == "write" || literal == "begin" || literal == "if" || literal == "repeat" || literal == "let") {
//             Node* qNode = createQNode(availableTokens);
//             newNode->addSubtree(qNode, nodeCount++);
//         }
//     }

//     if ((nodeCount != 2 && nodeCount != 3) && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }

//     return newNode;
// }

// Node* Parser::createTNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<T>");
//     int nodeCount = 0;
//     bool bNodeCreated = false;

//     if (currentToken.tokenLiteral == "scan") {
//         Node* aNode = createANode(availableTokens);
//         newNode->addSubtree(aNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "write") {
//         Node* wNode = createWNode(availableTokens);
//         newNode->addSubtree(wNode, nodeCount++);
//     } 
//     else if (currentToken.tokenLiteral == "begin") {
//         Node* bNode = createBNode(availableTokens);
//         newNode->addSubtree(bNode, nodeCount++);
//         bNodeCreated = true;
//     }
//     else if (currentToken.tokenLiteral == "if") {
//         Node* iNode = createINode(availableTokens);
//         newNode->addSubtree(iNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "repeat") {
//         Node* gNode = createGNode(availableTokens);
//         newNode->addSubtree(gNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "let") {
//         Node* eNode = createENode(availableTokens);
//         newNode->addSubtree(eNode, nodeCount++);
//     }

//     if (currentToken.tokenLiteral == "," && bNodeCreated == false) {
//         Node* commaNode = new Node("CommaNode", currentToken);
//         newNode->addSubtree(commaNode, nodeCount++);
//     }

//     if (((nodeCount != 2 && bNodeCreated == false) || (nodeCount != 1 && bNodeCreated == true)) && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }

//     return newNode;
// }

// Node* Parser::createANode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<A>");
//     int nodeCount = 0;

//     if (currentToken.tokenLiteral == "scan") {
//         Node* scanNode = new Node("ScanNode", currentToken);
//         newNode->addSubtree(scanNode, nodeCount++);
//         currentToken = scanner.scanner();

//         if (currentToken.tokenID == "IDTK") {
//             Node* identifierNode = new Node("IdentifierNode", currentToken);
//             newNode->addSubtree(identifierNode, nodeCount++);
//             currentToken = scanner.scanner();
//         }
//         else if (currentToken.tokenID == "NUMTK") {
//             Node* numberNode = new Node("NumberNode", currentToken);
//             newNode->addSubtree(numberNode, nodeCount++);
//             currentToken = scanner.scanner();
//         }
//     }

//     if (nodeCount != 2 && validParse) {
//         validParse = false;
//         newNode = new Node("ERROR", currentToken);
//     }

//     return newNode;
// }

// Node* Parser::createWNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<W>");
//     int nodeCount = 0;

//     if (currentToken.tokenLiteral == "write") {
//         Node* writeNode = new Node("WriteNode", currentToken);
//         newNode->addSubtree(writeNode, nodeCount++);
//         currentToken = scanner.scanner();

//     }

//     Node* mNode = createMNode(availableTokens);
//     newNode->addSubtree(mNode, nodeCount++);

//     if (nodeCount != 2 && validParse) {
//         validParse = false;
//         newNode = new Node("ERROR", currentToken);
//     }
//     return newNode;
// }

// Node* Parser::createINode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<I>");
//     int nodeCount = 0;

//     if (currentToken.tokenLiteral == "if") {
//         Node* ifNode = new Node("IfNode", currentToken);
//         newNode->addSubtree(ifNode, nodeCount++);
//         currentToken = scanner.scanner();

//         if (currentToken.tokenLiteral == "[") {
//             Node* openBracketNode = new Node("OpenBracketNode", currentToken);
//             newNode->addSubtree(openBracketNode, nodeCount++);
//             currentToken = scanner.scanner();

//             Node* mNode = createMNode(availableTokens);
//             newNode->addSubtree(mNode, nodeCount++);

//             Node* zNode = createZNode(availableTokens);
//             newNode->addSubtree(zNode, nodeCount++);
//             currentToken = scanner.scanner();

//             mNode = createMNode(availableTokens);
//             newNode->addSubtree(mNode, nodeCount++);

//             if (currentToken.tokenLiteral == "]") {
//                 Node* closedBracketNode = new Node("closedBracketNode", currentToken);
//                 newNode->addSubtree(closedBracketNode, nodeCount++);
//                 currentToken = scanner.scanner();

//                 Node* tNode = createTNode(availableTokens);
//                 newNode->addSubtree(tNode, nodeCount++);
//                 currentToken = scanner.scanner();
//             }
//         }
//     }

//     if (nodeCount != 7 && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }
//     return newNode;
// }

// Node* Parser::createGNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<I>");
//     int nodeCount = 0;

//     if (currentToken.tokenLiteral == "repeat") {
//         Node* repeatNode = new Node("repeatNode", currentToken);
//         newNode->addSubtree(repeatNode, nodeCount++);
//         currentToken = scanner.scanner();

//         if (currentToken.tokenLiteral == "[") {
//             Node* openBracketNode = new Node("OpenBracketNode", currentToken);
//             newNode->addSubtree(openBracketNode, nodeCount++);
//             currentToken = scanner.scanner();

//             Node* mNode = createMNode(availableTokens);
//             newNode->addSubtree(mNode, nodeCount++);

//             Node* zNode = createZNode(availableTokens);
//             newNode->addSubtree(zNode, nodeCount++);
//             currentToken = scanner.scanner();

//             mNode = createMNode(availableTokens);
//             newNode->addSubtree(mNode, nodeCount++);

//             if (currentToken.tokenLiteral == "]") {
//                 Node* closedBracketNode = new Node("closedBracketNode", currentToken);
//                 newNode->addSubtree(closedBracketNode, nodeCount++);
//                 currentToken = scanner.scanner();

//                 Node* tNode = createTNode(availableTokens);
//                 newNode->addSubtree(tNode, nodeCount++);
//                 currentToken = scanner.scanner();
//             }
//         }
//     }

//     if (nodeCount != 7 && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }
//     return newNode;
// }

// Node* Parser::createENode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<E>");
//     int nodeCount = 0;

//     if (currentToken.tokenLiteral == "let") {
//         Node* letNode = new Node("LetNode", currentToken);
//         newNode->addSubtree(letNode, nodeCount++);
//         currentToken = scanner.scanner();

//         if (currentToken.tokenID == "IDTK") {
//             Node* identifierNode = new Node("IdentifierNode", currentToken);
//             newNode->addSubtree(identifierNode, nodeCount++);
//             currentToken = scanner.scanner();

//             if (currentToken.tokenLiteral == ":") {
//                 Node* colonNode = new Node("ColonNode", currentToken);
//                 newNode->addSubtree(colonNode, nodeCount++);
//                 currentToken = scanner.scanner();

//                 Node* mNode = createMNode(availableTokens);
//                 newNode->addSubtree(mNode, nodeCount++);
//             }
//         }
//     }

//     return newNode;
// }
// Node* Parser::createZNode(AvailableTokens & availableTokens) {
//     Node* newNode = new Node("<Z>");
//     int nodeCount = 0;

//     if (currentToken.tokenLiteral == "<") {
//         Node* lessNode = new Node("LessNode", currentToken);
//         newNode->addSubtree(lessNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == ">") {
//         Node* greaterNode = new Node("GreaterNode", currentToken);
//         newNode->addSubtree(greaterNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == ":") {
//         Node* colonNode = new Node("ColonNode", currentToken);
//         newNode->addSubtree(colonNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "=") {
//         Node* equalsNode = new Node("EqualsNode", currentToken);
//         newNode->addSubtree(equalsNode, nodeCount++);
//     }
//     else if (currentToken.tokenLiteral == "==") {
//         Node* assNode = new Node("AssNode", currentToken);
//         newNode->addSubtree(assNode, nodeCount++);
//     }


//     if (nodeCount != 1 && validParse) {
//         validParse = false;
//         errTk = currentToken;
//     }
//     return newNode;
// }


