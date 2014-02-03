#ifndef NODE_H
#define NODE_H

#include "game.h"
#define OUTFLAG 0
#include <vector>

struct Node
{ 
  Node(){numChildren = 0;}
  Move move;
  //stuff for tree
  Node *p; //parent
  Node *s; //sibling
  vector<Node*> children;
  int numChildren;
  
};

#endif