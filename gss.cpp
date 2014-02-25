#include "gss.h"
//move needs to be fully setup - parent
void GSS::insert(Move mv)
{
  if(mv.index >= 0)
  {
    mv.wrigglers[mv.index].movePart(mv.dcol, mv.drow, mv.part);
  }
  stringstream ss;
  string toHash = "";
  for(int i = 0; i < mv.wrigglers.size(); i++)
  {
    for(int j = 0; j < mv.wrigglers[i].locations.size(); j++)
    {
      ss<<mv.wrigglers[i].locations[j][0];
      toHash.append(ss.str());
      ss<<mv.wrigglers[i].locations[j][1];
      toHash.append(ss.str());
    }
  }
  string str = toHash;
  unsigned int fnv_prime = 0x811C9DC5;
  unsigned int hash = 0;
  for(std::size_t i = 0; i < str.length(); i++)
  {
    hash *= fnv_prime;
    hash ^= str[i];
  }
  
  //parent is explored.size()-1 b/c it was just added
  if(explored.empty() == true && frontier.empty() == true)
  {// empty structure
    mv.parent = -1;
    frontier.push(mv);
    ht.push_back(hash);
  }
  else if(search(hash) == false)
  {
    mv.parent = explored.size() - 1;
    frontier.push(mv);
    ht.push_back(hash);
  }
  else
  {
    return;
  }
  //otherwise insert failed b/c it was already in the fontier/explored
}

Move GSS::getNext()
{//done works 
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
{//done works
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
bool GSS::search(unsigned int &hsh) const
{// done works
  bool retVal = false;
  for(int i = 0; i < ht.size() && retVal == false; i++)
  {
    if(ht[i] == hsh)
    {
      retVal = true;
    }
  }
  
  //priority_queue< Move, vector<Move>, std::greater<Move> > temp = frontier;
  // while( temp.empty() == false && retVal == false)
  // {
    // if(temp.top() == mv)
    // {
      // retVal = true;
    // }
    
    // temp.pop();
  // }
  
  // for(unsigned int i = 0; (i < explored.size() - 1 && retVal == false); i++)
  // {//check
    // if(explored[i] == mv)
    // {
      // retVal = true;
    // }
  // }
  
  return retVal;
}

ostream& operator<<(ostream &os, GSS gss)
{
  priority_queue< Move, vector<Move>, std::greater<Move> > tempf = gss.frontier;
  os<<"outputting frontier:\n";
  int j = 0;
  while(tempf.empty() == false)
  {
    os<<tempf.top()<<",";
    tempf.pop();
    if((j+ 1)% 10 == 0)
    {
      os<<"\n";
    }
  }
  os<<"\noutputting explored set:\n";
  for(unsigned int i = 0; i < gss.explored.size() -1; i++)
  {
    os<<gss.explored[i]<<", ";
    if((i+ 1)% 10 == 0)
    {
      os<<"\n";
    }
  }
  
  
  // os<<"\nPrinted hash table";
  
  // for(unsigned int i = 0; i < gss.ht.size() -1; i++)
  // {
    // os<<gss.ht[i]<<", ";
    // if((i+ 1)% 10 == 0)
    // {
      // os<<"\n";
    // }
  // }
  
  os<<"/n";
  return os;

}

int GSS::getParentHval(const int &index)
{
  int retVal;
  if(index > 0 && index < explored.size())
  {
    retVal = explored[index].hVal;
  }
  else
  {
    retVal = -1;
  }
  
  return retVal;
}