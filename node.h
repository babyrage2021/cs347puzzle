//Programmer: Ryan Hoffman
//Date: 2/2/14
//Description: header file for the Node class which is used as a binary tree 
//             node in the tree class
#ifndef NODE_H
#define NODE_H

#include <vector>

#include "game.h"
#define OUTFLAG 0 //used in tree.h. in process of getting rid of it

// description: this is a node on the binary tree
struct Node
{ 
  Node(){numChildren = 0; currentChild = -1;}
  
  Move move;
  
  //-----stuff for tree-----
  Node *p; //parent
  Node *s; //sibling
  
  vector<Node*> children; // vector of pointers to all of its children nodes
  int numChildren; // total number of children that it has
  int currentChild; // child that it is going to next for LIFO() in the tree
                    // class
};

#endif