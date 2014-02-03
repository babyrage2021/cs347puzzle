#ifndef AI_H
#define AI_H

#include <vector>

#include "tree.h"

class AI
{
  private:
    Tree tree;
    Game board;
    int numWrigglers;
    bool outFlag;
    
    void getMoves(Wriggle w, int index, Parts part);
    
  public:
    //hw 1
    int BFTS();
    AI();
    AI(string fileName, int outputFlags);

};

#endif
