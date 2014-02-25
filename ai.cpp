//Programmer: Ryan Hoffman
//Date: 2/2/14
//Description: cpp file for the ai class
#include "ai.h"

AI::AI(string fileName, int outputFlags)
{
  board.setup(fileName, false);
  numWrigglers = board.getNumWrigglers();
  
  Move move(-1, 0, HEAD, -1, -1);//root
  tree.insert(move);
  move.parent = -1;
  vector<Wriggle> temp;
  board.getWrigglers(temp);
  move.setupWrigglers(temp);
  storage.insert(move);
  outFlag = false;
  UCGSMode = false;
  ALTHeuristicMode = outputFlags;
}

int AI::BFTS()
{
  //bool goal = false;
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
{
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
  
  while(depth < maxDepth)
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

int AI::GBFGS(int maxDepth, ofstream &fout)
{
  /*initialize frontier using initial problem state
  initialize explored set to be empty
  loop do
    - if empty(frontier) then return fail
    - choose leaf node and remove it from frontier // graph class does this
    - if chosen node contains goal state then return corresponding solution
    - add chosen node to explored set // graph class does this
    - expand chosen node and add resulting nodes to frontier only if not yet in
      frontier or explored set
    //lowest number is the next to be done */
  Game origBoard = board;
  Move mv, newMove;
  int col, row, depth = 0;

  do
  {
    do
    {
      mv = storage.getNext(); // gets the next node from frontier
      depth = mv.depth +1;
    } while (depth >= maxDepth);
    //gen map
    
    //fout<<"MV: "<<mv<<", Depth: "<<mv.depth<<", hval:"<<mv.hVal<<endl;
    vector<Move> moveList;
    
    board = origBoard; // resets the board 
    storage.getMoves(moveList);
    
    while(moveList.empty() == false)
    {
      board.moveWriggler(moveList[moveList.size()-1]);
      moveList.pop_back();
    }
    
    if(board.isGoal() == true)
    {
      board = origBoard;
      storage.getMoves(moveList);
      int numMoves = moveList.size();
      while(moveList.empty() == false)
      {
        fout<<moveList[moveList.size() -1]<<"\n";
        board.moveWriggler(moveList[moveList.size()-1]);
        //fout<<board<<endl<<endl;
        moveList.pop_back();
      }
      fout<<"\n";
      board.print(fout);  
      return numMoves;
    }
    
    //gen moves start
    vector<Wriggle> wr;
    board.getWrigglers(wr);
    newMove.setupWrigglers(wr);
    
    for(unsigned int i = 0; i < newMove.wrigglers.size(); i++)
    {
      newMove.wrigglers[i].getPartLoc(col, row, HEAD);//col, row are by ref
      newMove.setup(i, depth, HEAD, col, row);
      getGraphMoves(newMove);
      
      newMove.wrigglers[i].getPartLoc(col, row, TAIL);//col, row are by ref
      newMove.setup(i, depth, TAIL, col, row);
      getGraphMoves(newMove);
    }
    
  }while(storage.emptyFrontier() == false && depth <= maxDepth);//main loop, check
  fout<<"search failed"<<endl;
  fout<<depth<<endl;
  fout<<storage<<endl;


  return -1;
}

int AI::UCGS(int maxDepth, ofstream &fout)
{
  UCGSMode = true;
  return GBFGS( maxDepth, fout);
}

int AI::AStarGS(int maxDepth, ofstream &fout)
{//works
  Move mv, newMove;
  int col, row, depth;

  do
  {
    do
    {
      mv = storage.getNext(); // gets the next node from frontier
      depth = mv.depth + 1;
    } while (depth >= maxDepth);
    
  	//gen map start
    board.clearGrid();
    board.reSetup(mv.wrigglers); // clears the board and
	                             // adds the wrigglers to the board,
	                             // and sets them up
    
    if(board.isGoal() == true)
    {
      vector<Move> moveList;
      storage.getMoves(moveList);
      int numMoves = moveList.size();
      while(moveList.empty() == false)
      {
        fout<<moveList[moveList.size() -1]<<"\n";
        //board.moveWriggler(moveList[moveList.size()-1]);
        //fout<<board<<endl<<endl;
        moveList.pop_back();
      }
      fout<<"\n";
      board.print(fout);  
      return numMoves;
    }
    
    //gen moves start
    for(unsigned int i = 0; i < mv.wrigglers.size(); i++)
    {
      mv.wrigglers[i].getPartLoc(col, row, HEAD);//col, row are by ref
      mv.setup(i, depth, HEAD, col, row);
      getGraphMoves(mv);
      
      mv.wrigglers[i].getPartLoc(col, row, TAIL);//col, row are by ref
      mv.setup(i, depth, TAIL, col, row);
      getGraphMoves(mv);
    }
    
  }while(storage.emptyFrontier() == false && depth <= maxDepth);//main loop, check
  fout<<"search failed"<<endl;
  fout<<board<<endl;
  fout<<"depth: "<<depth<<endl;
  fout<<storage<<endl;

  return -1;
}

//needs gameboard w/o move done, will have a ucs mode which
// is AI::UCS and it calls GBFGS? or i might make another search
// func to do these
int AI::heuristic(Move &mv)
{
  int hv = 0;
  if(mv.index == 0)
  {
    hv = board.distToGoal(mv.dcol, mv.drow);
  }
  else
  {
    hv = board.distToGoal();
  }
  
  if(UCGSMode == true)
  {
    hv = mv.depth;
  }
  if(ALTHeuristicMode == 1 && hv != 0)
  {
    hv = hv + mv.depth + (mv.index * 10);
  }
  else if( hv == 0)
  {// if it is at the goal
    hv = 0; 
  }
  else
  {// otherwise
    hv = mv.depth + hv;
  }
  
  return hv;
}

void AI::getGraphMoves(Move &mv)
{
  if(board.testCoords(++mv.dcol, mv.drow))
  {
    mv.hVal = heuristic(mv);
    storage.insert(mv);
  }
  
  if(board.testCoords(mv.dcol-=2, mv.drow))
  {
    mv.hVal = heuristic(mv);
    storage.insert(mv);
  }
  
  if(board.testCoords(++mv.dcol, ++mv.drow))
  {
    mv.hVal = heuristic(mv);
    storage.insert(mv);
  }
  
  if(board.testCoords(mv.dcol, mv.drow-=2))
  {
    mv.hVal = heuristic(mv);
    storage.insert(mv);
  }
  return;
}
