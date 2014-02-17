//Programmer: Ryan Hoffman
//Date: 2/2/14
//Description: header file for the tree class. needs node to work right.
//             node may need Move but that can be changed easily

#ifndef TREE_H
#define TREE_H

#include "node.h"

//#define MAXDEPTH 5 //consider delete

/* Class Tree
// Description: is the class that has the queued tree in it
// purpose: to act as a tree to get parent nodes quickly and to get the next 
//          queue to be operated on

// Tree()
// description: default constructor
// pre: none
// post: creates a queued tree
// param: none
// return: none

// ~Tree()
// description: default destructor, runs clear()
// pre: none
// post: removes all nodes from the tree
// param: none
// return: none

// move &getNext() AND Move LIFO();
// description: gets the next node to have children generated for it
// pre: need to have at least 1 node in the tree (root)
// post: updates the current pointer to point to current's sibling
// param: none
// return: the next move to have things done on it

// void insert(Node data)
// description: inserts a child node for the data
// pre: none
// post: increases the amount of children for the node
// param: the data
// return: none

// void clear()
// description: deletes the whole tree 
// pre: none
// post: see description
// param: none
// return: none*/
class Tree
{
  private:

    Node *root; // root of the tree
    Node *current; // current node being added to
    Node *prev; // pointer to the previous data put into the tree
    int OUTFLAG;//flag to output more stuff
  public:
    
    Tree(int of = 0);
    ~Tree() {clear(); }
    Move getNext();
    Move LIFO();
    void insert(Move move);
    void clear();
    void getMoveList(vector<Move> &list);
};

#endif
