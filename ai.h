// Programmer: Ryan Hoffman
// Date:
// Description: this file is the header file for the AI class which uses 
//              assorted ai's to solve the tjWriggle puzzles
#ifndef AI_H
#define AI_H

#include <vector>

#include "gss.h"
#include "game.h"
#include "tree.h"

/* class AI
// Description: is a class that uses a board and the tree classes to use an ai

// void getMoves()
// description: gets all of the moves for that part and that space and adds 
//              them to the tree
// pre: need to have the game board set up
// post: the tree size is larger and tree.insert() is called
// param: Wriggle wr, int inex, parts part, int depth;
// return: none

// int BFTS()
// description: AI that uses BFTS()
// pre: jneed to have the board set up
// post: solves the puzzle
// param: none
// return: num moves that it took

// int DFS(int maxDepth)
// description: depth first search. searches till it hits a depth
// pre: board set up
// post: can potentially solve the puzzle
// param: the maximum depth
// return: int that is the number of moves that it took

// int IDDFS(int maxDepth)
// description: uses Iterative Deepening Depth First Search to find a solution
//              via DFS(int depth) in a for loop with the depth increasing.
// pre: have the board set up
// post: solves it by using DFS()
// param: an int that si the maxDepth
// return: the number of moves that it took*/
class AI
{
  private:
    Tree tree;
    Game board;
    GSS  storage; // storage for the graph search
    int numWrigglers;
    bool outFlag;
    bool UCGSMode;
    int ALTHeuristicMode;
    void getMoves(Wriggle w, int index, Parts part, int depth = 0);
    void getGraphMoves(Move &mv);
    int heuristic(Move &mv);
  public:
    
    int BFTS();
    AI();
    AI(string fileName, int outputFlags);
    
    int DFS(int maxDepth);
    int IDDFS(int maxDepth = 3);
    
    int GBFGS(int maxDepth, ofstream &fout);
    int UCGS(int maxDepth, ofstream &fout);
	int AStarGS(int maxDepth, ofstream &fout);
};

#endif
