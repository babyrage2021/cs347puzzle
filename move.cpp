#include "move.h"

Move::Move()
{
  depth = dcol = drow = index = -1;
  hVal = 0;
  part = ERROR;
}

Move::Move(int ind, int de, Parts pt, int dc, int dr)
{
  index = ind;
  depth = de;
  part  = pt;
  dcol  = dc;
  drow  = dr;  
}

void Move::setupWrigglers(vector<Wriggle>& wr)
{
  wrigglers = wr;
  return;
}

void Move::setup(int ind, int de, Parts pt, int dc, int dr)
{
  index = ind;
  depth = de;
  part  = pt;
  dcol  = dc;
  drow  = dr;
  return;
}

Move& Move::operator=(Move rhs)
{//check
  index = rhs.index;
  depth = rhs.depth;
  part  = rhs.part;
  dcol  = rhs.dcol;
  drow  = rhs.drow;
  parent = rhs.parent;
  part = rhs.part;
  hVal = rhs.hVal;
  swap(wrigglers, rhs.wrigglers);
  
  return *this;
}

bool Move::operator==(Move rhs) const
{// chck
  //return wrigglers == rhs.wrigglers;
  for(unsigned int i = 0; i < rhs.wrigglers.size(); i++)
  {
    if(this-> wrigglers[i] != rhs.wrigglers[i])
    {
      return false;
    }
  
  }
  return true;
} 

ostream& operator<<(ostream& os, Wriggle& w)
{
  os<<"[";
  for(int i=0; i < w.length; i++)
  {
    os<<"("<<w.locations[i][COL]<<", "<<w.locations[i][ROW]<<") ";
  }
  
  os<<"]";
  
  return os;
}

ostream& operator<<(ostream& os, const Move &mv)
{
  os<<mv.index<<" "<<mv.part<<" "<<mv.dcol<<" "<<mv.drow;
  
  return os;
}