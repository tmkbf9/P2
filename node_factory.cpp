#include <cstddef>
#include "node_factory.h"
#include "node.h"

Node * NodeFactory::createSNode(Node * programNode, Node * vNode, Node * bNode) const {
  Node * node = new Node("<S>", NULL);

  node->addSubtree(programNode, 0);
  node->addSubtree(vNode, 1);
  node->addSubtree(bNode, 2);

  return node;
}
