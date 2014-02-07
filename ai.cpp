//Programmer: Ryan Hoffman
//Date: 2/2/14
//Description: cpp file for the ai class
#include "ai.h"

AI::AI(string fileName, int outputFlags)
{
  board.setup(fileName, false);
  numWrigglers = board.getNumWrigglers();
  outFlag = outputFlags;
  outFlag = false;
  Move move(-1, 0, HEAD, -1, -1);
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

void AI::getMoves(Wriggle wr, int index, Parts part, int depth)
{
  
  Move mv;
  int ind  = wr.length - 1;//head or tail basicly
  mv.index = index;
  mv.part  = part;
  mv.depth = depth;
  
  if(part == HEAD)
  {
    ind = 0;
  }
  
  mv.dcol = wr.locations[ind][COL];
  mv.drow = wr.locations[ind][ROW];
  
  if(board.testCoords(++mv.dcol, mv.drow))
  {
    if (outFlag == true)
    {
      cout<<"found move: "<<mv<<" "<<mv.depth<<".\n";
    }
    tree.insert(mv);

   
  }
  
  if(board.testCoords(mv.dcol-=2, mv.drow))
  {
    if (outFlag == true)
    {
      cout<<"found move: "<<mv<<" "<<mv.depth<<".\n";
    }
    tree.insert(mv);
  }
  
  if(board.testCoords(++mv.dcol, ++mv.drow))
  {
    if (outFlag == true)
    {
      cout<<"found move: "<<mv<<" "<<mv.depth<<".\n";
    }
    tree.insert(mv);
  }
  
  if(board.testCoords(mv.dcol, mv.drow-=2))
  {
    if (outFlag == true)
    {
      cout<<"found move: "<<mv<<" "<<mv.depth<<".\n";
    }
    tree.insert(mv);
  }
  
  return;
}

int AI::DFS(int maxDepth)
{// done needs to be tested
  Game origBoard = board;
  Wriggle wr;
  vector<Move> moveList;
  int depth = 1;
  bool isRoot = true;
  Move mv;
  do
  {
    if(outFlag == true)
    {
      cout<<"\nloop starting--------------------------\n";
    }
    
    board = origBoard;
    
    //gets move here
    if(isRoot == false)
    {
      do
      {
        mv = tree.LIFO();
        depth = mv.depth+1;
        
        if(mv.index == -11)// bool root was checked here
        {//gave a dummy node, empty frontier test
          board = origBoard;
          return -1;
        }
        else if(board.isGoal() == true)
        {//goal test
          break;//breaks to print moves
        }
      }while(mv.depth > maxDepth);
      
    }
    else
    {
      isRoot = false;
    }
  
  
    tree.getMoveList(moveList);
    
    //generates map here
    while(!moveList.empty())
    {
      if (outFlag == true)
      {
        cout<<"mlMv:"<<moveList[moveList.size()-1]<<"\n";
      }
      
      board.moveWriggler(moveList[moveList.size()-1]);
      moveList.pop_back();
    }
    

    
    if (outFlag == true)
    {
      cout<<"\n";
      board.print();
      
    }
    
    for(int i = numWrigglers -1; i >= 0; i--)
    {//move generation here
      wr = board.getWriggler(i);
      getMoves(wr, i, HEAD, depth);
      getMoves(wr, i, TAIL, depth);
    }
  }
  while(!board.isGoal());//may want to change this
  
  //print moves and the map
  tree.getMoveList(moveList);
  int retVal = moveList.size();
  while(!moveList.empty())
  {
    cout<<moveList[moveList.size()-1]<<"\n"; 
    moveList.pop_back();
  }
  
  cout<<"\n";
  board.print();
  
  return retVal;
}

int AI::IDDFS(int maxDepth)
{
  int retVal,depth = 0;  
  Move move(-1, 0, HEAD, -1, -1);
  
  while(depth < 50)
  { 
    if (outFlag == true)
    {
      cout<<"\n\n\n------------------------------------running DFS w/ depth:";
      cout<<depth<<endl;
    }
    retVal = DFS(depth);
    tree.clear();
    tree.insert(move);
    depth++;
    if(retVal >= 0)
    {
      break;
    }
  }
  return retVal;
}