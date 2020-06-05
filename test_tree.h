#ifndef __TEST_TREE_H__
#define __TEST_TREE_H__

#include <iosfwd>

class Node;

class TestTree {
 public:
  void printTree(Node * rootNode, std::ostream & os);
  void traversePreOrder(Node* rootNode, std::ostream & os, int depth);
};

#endif
