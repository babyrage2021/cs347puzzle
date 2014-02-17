#include "gss.h"
//move needs to be fully setup - parent
void GSS::insert(Move mv)
{
  if(mv.index >= 0)
  {
    mv.wrigglers[mv.index].movePart(mv.dcol, mv.drow, mv.part);
  }
  
  //parent is explored.size()-1 b/c it was just added
  if(explored.empty() == true && frontier.empty() == true)
  {// empty structure
    mv.parent = -1;
    frontier.push(mv);
  }
  else if(search(mv) == false)
  {
    mv.parent = explored.size() - 1;
    frontier.push(mv);
  }
  //otherwise insert failed b/c it was already in the fontier/explored
}

Move GSS::getNext()
{//need to test
  Move temp;
  if(frontier.empty())
  {// empty frontier
    temp.index = -10;
  }
  else
  {
    temp = frontier.top();
    frontier.pop();
    explored.push_back(temp);
  }
  
  return temp;
}

void GSS::getMoves(vector<Move>& list)
{//need to test
  list.clear();
  if(explored.empty() == false)
  {
    Move temp;
    int parent = explored.size() - 1;
    do
    {
      temp = explored[parent];
      list.push_back(temp);
      parent = temp.parent; // must be done last to prevent seg faults
    }while(parent > -1);
    
    list.pop_back();//gets rid of root
  }
  
  return;
}

// true if it finds it, false otherwise
bool GSS::search(Move &mv) const
{// need to test
  bool retVal = false;
  priority_queue<Move> temp = frontier;
  
  while( temp.empty() == false && retVal == false)
  {
    if(temp.top() == mv)
    {
      retVal = true;
    }
    
    temp.pop();
  }
  
  for(unsigned int i = 0; (i < explored.size() - 1 && retVal == false); i++)
  {//check
    if(explored[i] == mv)
    {
      retVal = true;
    }
  }
  
  return retVal;
}

ostream& operator<<(ostream &os, GSS gss)
{
  priority_queue<Move> tempf = gss.frontier;
  os<<"outputting frontier:\n";
  while(tempf.empty() == false)
  {
    os<<tempf.top()<<"\n";
    tempf.pop();
  }
  os<<"\noutputting explored set:\n";
  for(unsigned int i = 0; i < gss.explored.size() -1; i++)
  {
    os<<gss.explored[i]<<"\n";
  }


  return os;

}