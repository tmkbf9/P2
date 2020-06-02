#ifndef __NODEFACTORY_H__
#define __NODEFACTORY_H__

class Node;

class NodeFactory {
 public:
  NodeFactory() {}

  Node * createSNode(Node * programNode, Node * vNode, Node * bNode) const;
};

#endif
