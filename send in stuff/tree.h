#ifndef TREE_H
#define TREE_H

#define MAXDEPTH 5

#include "node.h"
/* Class Tree
// Description: is the class that has the queued tree in it
// purpose: to act as a tree to get parent nodes quickly and to get the next 
//          queue to be operated on*/

/* Tree()
// description: default constructor
// pre: none
// post: creates a queued tree
// param: none
// return: none*/

/* ~Tree()
// description: default destructor, runs clear
// pre: none
// post: removes all nodes from the tree
// param: none
// return: none*/

/* Node &getNext()
// description: gets the next node to have children generated for it
// pre: need to have at least 1 node in the tree (root)
// post: updates the current pointer to point to current's sibling
// param: none
// return: the next node to have things done on it*/

/* void insert(Node data)
// description: inserts a child node for the data
// pre: none
// post: increases the amount of children for the node
// param: the data
// return: none*/

/* void clear()
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
    
  public:
    
    Tree();
    ~Tree() {clear(); }
    Move getNext();
    void insert(Move move);
    void clear();
    
    void getMoveList(vector<Move> &list);
    
    friend ostream& operator<<(ostream& os, const Tree &tree);
};
ostream& operator<<(ostream& os, const Tree &tree);

#endif
