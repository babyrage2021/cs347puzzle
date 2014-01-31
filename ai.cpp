
/*how b Tree would work for frontier
  pointer to parent and pointed to by child
  
  

AI::AI(string fileName, bool outputFlags, int ai)
{
  game.setUp(filename, outputFlags);
  numWrigglers = game.getNumWrigglers();
  
}

void AI::BFTS()
{
  //initalize
  

  // check frontier is empty
  // goal test
  
  //gen moves start
  int row, col, depth =0;
  bool isGoal = false;
  do
  {  
    for(int i = 0; i < numWrigglers; i++)
    {
      Wriggler w =  game.getWriggler(i);
      
      for(int j = 0; j < 2; j++)//2 is the number of parts head/tail
      {
        col = w.locs[j][0];
        row = w.locs[j][1];
        
        if(game.checkMap(col + 1, row))
        {
          Node.setUp(index, j, col, row, depth + 1);
          //add move here
        }
        
        if(game.checkMap(col, row + 1))
        {
          // add move here
        }
        
        if(game.checkMap(col - 1, row))
        {
          // add move here
        }
        
        if(game.checkMap(col, row - 1))
        {
          // add move here
        }
      }//inner for
    }//outer for
    
  }while(++depth <= MAXDEPTH && isGoal == false);  
  
  
  return;
}
*/