#include <assert.h>
#include "node_factory.h"
#include "node.h"

void createSNode() {
  NodeFactory factory;

  Node * sNode = factory.createSNode();

  assert(sNode->nodeName == "<S>");
  assert(sNode->token) == NULL;
  assert(sNode->subTrees[0].nodeName == "program");
  assert(sNode->subTrees[1].nodeName == "<V>");
  assert(sNode->subTrees[2].nodeName == "<B>");
}

int main(int argc, char ** argv) {
  createSNode();
}


