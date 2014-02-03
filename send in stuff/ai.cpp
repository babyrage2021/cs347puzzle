

#include "ai.h"

AI::AI(string fileName, int outputFlags)
{
  board.setup(fileName, false);
  numWrigglers = board.getNumWrigglers();
  outFlag = outputFlags;
  outFlag = false;
  
  Move move;
  move.index = -1;
  move.part = HEAD;
  move.dcol = -1;
  move.drow = -1;
  tree.insert(move);
  
  if(outFlag == true)
  {
    cout<<"AI::AI() initialization done"<<endl;
  }
}

int AI::BFTS()
{
  bool goal = false;
  Game origBoard = board;
  Wriggle wr;
  int counter = 0;
  bool root = true;
  do
  {
    if(outFlag == true)
    {
      cout<<"loop starting--------------------------\n"<<endl;
    }
    board = origBoard;
    //gets node here
    
    Move mv = tree.getNext();

    if(mv.index == -10 && root == false)
    {//gave a dummy node, empty frontier test
      return -1;
    }
    
    root =false;
    
    if(outFlag == true)
    {
      cout<<"got the next node: "<<mv<<endl;
    }
    
    vector<Move> moveList;
    tree.getMoveList(moveList);
    
    //generates map here
    while(!moveList.empty())
    {
      if (outFlag == true)
      {
        cout<<"mlMv:"<<moveList[moveList.size()-1]<<endl;
      }
      
      board.moveWriggler(moveList[moveList.size()-1]);
      moveList.pop_back();
    }
    
    if(board.isGoal() == true)
    {//goal test
      break;
    }
    
    if (outFlag == true)
    {
      cout<<"moveList is emptied printing board:"<<endl;
      cout<<board<<endl;
      
    }
    
    for(int i = 0; i < numWrigglers; i++)
    {//move generation here
      wr = board.getWriggler(i);
      getMoves(wr, i, HEAD);
      getMoves(wr, i, TAIL);
    }
    counter++;
  }
  while(!board.isGoal());
  //print moves
  vector<Move> moveList;
  tree.getMoveList(moveList);
  int retVal = moveList.size();
  while(!moveList.empty())
  {
    cout<<moveList[moveList.size()-1]<<endl; 
    moveList.pop_back();
  }
  cout<<endl;
  board.print();
  // num moves. ret val
  
  
  
  //*/
  return retVal;
}

void AI::getMoves(Wriggle wr, int index, Parts part)
{//check this
  
  Move mv;
  int ind = wr.length - 1;//head or tail basicly
  mv.index = index;

  mv.part = part;
  
  if(part == HEAD)
  {
    ind = 0;
  }
  
  mv.dcol = wr.locations[ind][COL];
  mv.drow = wr.locations[ind][ROW];
  
  if(board.testCoords(mv.dcol + 1, mv.drow))
  {
    
    mv.dcol++;
    if (outFlag == true)
    {
      cout<<"found move, beginning insertion:"<<mv<<". ";
    }
    tree.insert(mv);

    mv.dcol--;
  }
  
  if(board.testCoords(mv.dcol - 1, mv.drow))
  {
    mv.dcol--;
    if (outFlag == true)
    {
      cout<<"found move, beginning insertion:"<<mv<<". ";
    }
    tree.insert(mv);
    mv.dcol++;
  }
  
  if(board.testCoords(mv.dcol, mv.drow + 1))
  {
    mv.drow++;
    if (outFlag == true)
    {
      cout<<"found move, beginning insertion:"<<mv<<". ";
    }
    tree.insert(mv);
    mv.drow--;
  }
  
  if(board.testCoords(mv.dcol, mv.drow - 1))
  {
    mv.drow--;
    if (outFlag == true)
    {
      cout<<"found move, beginning insertion:"<<mv<<". ";
    }
    tree.insert(mv);
    mv.drow++;
  }
  
  return;
}
