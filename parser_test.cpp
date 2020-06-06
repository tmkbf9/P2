#include <vector>
#include <assert.h>
#include <sstream>
#include <iostream>

#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "node.h"
#include "test_tree.h"

using namespace std;
/*
void test_smallest_valid_BNF() {
    istringstream is("program begin end");

    Scanner scanner(is, cerr);
    Parser parser();

    Node* rootNode = parser.parse(scanner);

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<B>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "BeginNode");
    assert(rootNode->subTrees[1]->subTrees[1]->nodeName == "EndNode");
}

void test_smallest_valid_BNF_with_V_before_B() {
    istringstream is("program var aa . begin end");

    Scanner scanner(is, cerr);
    Parser parser();

    Node* rootNode = parser.parse(scanner);

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
    Parser parser();

    Node* rootNode = parser.parse(scanner);

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
void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_I_node() {
    istringstream is("program begin if [ 12 > 5 ] begin end , # end");

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
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->nodeName == "<I>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenLiteral == "if");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->tk.tokenLiteral == "[");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[2]->nodeName == "<M>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[2]->subTrees[0]->nodeName == "<H>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[2]->subTrees[0]->subTrees[0]->nodeName == "<R>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[2]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenID == "NUMTK");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[3]->nodeName == "<Z>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[3]->subTrees[0]->tk.tokenLiteral == ">");
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

void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node_with_multiple_M_nodes() {
    istringstream is("program begin write 12 + 5 , # end");

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
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->subTrees[1]->tk.tokenLiteral == "+");
}

void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_E_node() {
    istringstream is("program begin let aa : 12 , # end");

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
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->nodeName == "<E>");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[0]->tk.tokenLiteral == "let");
    assert(rootNode->subTrees[1]->subTrees[1]->subTrees[0]->subTrees[0]->subTrees[1]->tk.tokenID == "IDTK");
}

void test_smallest_valid_BNF_with_Two_V_nodes_before_B() {
    istringstream is("program var aa . var bb . begin end");

    Scanner scanner(is, cerr);
    token tk;
    Parser parser(scanner, tk);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
    assert(rootNode->subTrees[1]->nodeName == "<V>");
    assert(rootNode->subTrees[1]->subTrees[0]->nodeName == "VarNode");
    assert(rootNode->subTrees[1]->subTrees[1]->tk.tokenLiteral == "aa");
    assert(rootNode->subTrees[1]->subTrees[2]->tk.tokenLiteral == ".");
    assert(rootNode->subTrees[1]->subTrees[3]->nodeName == "<V>");
    assert(rootNode->subTrees[1]->subTrees[3]->subTrees[0]->tk.tokenLiteral == "var");
    assert(rootNode->subTrees[1]->subTrees[3]->subTrees[1]->tk.tokenLiteral == "bb");
    assert(rootNode->subTrees[1]->subTrees[3]->subTrees[2]->tk.tokenLiteral == ".");
}
//error testing
void test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node_cause_error() {
    istringstream is("program begin write # end");

    Scanner scanner(is, cerr);
    Parser parser(scanner);

    Node* rootNode = parser.parse();

    assert(rootNode->nodeName == "ERROR");
    assert(rootNode->tk.tokenLiteral == "#");
}
//print testing
void test_print_valid_BNF() {
    istringstream is("program \n var id1 . begin var id3. \n if [ id1 > 14 ] write id3 , , # end");
    ostringstream os;
    Scanner scanner(is, cerr);
    Parser parser(scanner);
    TestTree t;
    Node* rootNode = parser.parse();
    t.printTree(rootNode, os);
    cout << os.str();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
}
*/

void test_this_fails() {
  //    istringstream is("program \n var id1 . begin var id3. \n if [ id1 > 14 ] write id3 , , # end");
    istringstream is("program \n var id1 . begin var id3. end");
    ostringstream os;

    Scanner scanner(is, cerr);
    Parser parser;

    Node* rootNode = parser.parse(scanner);

    TestTree t;
    t.printTree(rootNode, os);
    cout << os.str();

    assert(rootNode->nodeName == "<S>");
    assert(rootNode->subTrees[0]->nodeName == "ProgramNode");
}


int main(int argc, char ** argv) {
    // test_smallest_valid_BNF();
    // test_smallest_valid_BNF_with_V_before_B();
    // test_smallest_valid_BNF_with_B_node_into_Q_node();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_B_node();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_A_node();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_I_node();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node_with_multiple_M_nodes();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_E_node();
    // test_smallest_valid_BNF_with_B_node_into_Q_node_into_T_node_into_W_node_cause_error();
    // test_print_smallest_valid_BNF();

    // failing test!
  test_this_fails();

    return 0;
}



