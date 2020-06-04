#include <vector>
#include <assert.h>
#include <sstream>
#include <iostream>

#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "node.h"

using namespace std;
void test_smallest_valid_BNF() {
    istringstream is("program begin end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "EndNode");
}

void test_smallest_valid_BNF_with_V_before_B() {
    istringstream is("program var aa . begin end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<V>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "VarNode");
    assert(rootNode->subTrees[1]->subTrees[1]->tk.tokenLiteral == "aa");
    assert(rootNode->subTrees[1]->subTrees[2]->tk.tokenLiteral == ".");
}
void test_smallest_valid_BNF_with_B_node_into_Q_node() {
    istringstream is("program begin begin end # end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "<Q>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->nodeName == "<T>");
    assert(rootNode->subTrees[1]->subTrees[2]->nodeName == "EndNode");
}

void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node() {
    istringstream is("program begin begin end # end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "<Q>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->nodeName == "<T>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[1]->tk.tokenLiteral == "#");
    //assert(rootNode->subTrees[1]->subTrees[2]->nodeName == "EndNode");
}

void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_B_node() {
    istringstream is("program begin begin end # end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "<Q>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->nodeName == "<T>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[1]->tk.tokenLiteral == "#");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenLiteral == "begin");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->tk.tokenLiteral == "end");
    assert(rootNode->subTrees[1]->subTrees[2]->nodeName == "EndNode");
}

void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node() {
    istringstream is("program begin write 12 , # end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "<Q>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->nodeName == "<T>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[1]->tk.tokenLiteral == "#");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->nodeName == "<W>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenLiteral == "write");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->nodeName == "<M>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->subTrees[0]->nodeName == "<H>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->subTrees[0]->subTrees[0]->nodeName == "<R>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenID == "NUMTK");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[1]->tk.tokenLiteral == ",");
    assert(rootNode->subTrees[1]->subTrees[2]->nodeName == "EndNode");
}
void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_A_node() {
    istringstream is("program begin scan aa , # end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "<Q>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->nodeName == "<T>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[1]->tk.tokenLiteral == "#");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->nodeName == "<A>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenLiteral == "scan");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->tk.tokenLiteral == "aa");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[1]->tk.tokenLiteral == ",");
    assert(rootNode->subTrees[1]->subTrees[2]->nodeName == "EndNode");
}
//error testing
void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node_cause_error() {
    istringstream is("program begin write aa , # end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "<Q>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->nodeName == "<T>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[1]->tk.tokenLiteral == "#");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->nodeName == "<W>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenLiteral == "write");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1] == NULL);
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[1]->tk.tokenLiteral == ",");
    assert(rootNode->subTrees[1]->subTrees[2]->nodeName == "EndNode");
}


int main(int argc, char ** argv) {
    test_smallest_valid_BNF();
    test_smallest_valid_BNF_with_V_before_B();
    test_smallest_valid_BNF_with_B_node_into_Q_node();
    test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node();
    test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_B_node();
    test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node();
    test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_A_node();
    //test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node_cause_error();



    return 0;
}



