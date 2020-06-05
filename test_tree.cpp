#include <string>
#include <iostream>
#include "test_tree.h"
#include "token.h"
#include "node.h"

using namespace std;

namespace {
    string blanks(int count) {
        string blanks = "";

        for (int i = 0; i < count; i++) {
            blanks += "  ";
        }
        return blanks;
    }

    string correctOutput(Node* rootNode) {
        if (rootNode->nodeName.at(0) != '<') {
            return rootNode->nodeName + " Token: " + rootNode->tk.tokenLiteral + " Linenumber: " + to_string(rootNode->tk.linenumber);
        }
        return rootNode->nodeName;
    }
}

void TestTree::printTree(Node * rootNode, std::ostream & os) {
    traversePreOrder(rootNode, os, 0);
}
    
void TestTree::traversePreOrder(Node* rootNode, ostream& logFile, int depth) {
    if (rootNode == NULL) return;

    logFile << blanks(depth) << depth + 1 << " " << correctOutput(rootNode) << endl;

    for (int subTreeIndex = 0; subTreeIndex < rootNode->subTrees.size(); subTreeIndex++) {
        traversePreOrder(rootNode->subTrees[subTreeIndex], logFile, depth + 1);
    }
}

