#ifndef __TEST_TREE_H__
#define __TEST_TREE_H__

#include <iosfwd>

class Node;

class TestTree {
 public:
  void print(Node * rootNode, std::ostream & os);
};

#endif
