
#include "wriggle.h"

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

void Wriggle::moveHead(int col, int row)
{
  vector<int> temp (2,0);
  temp[0] = col;
  temp[1] = row;
  locations.insert(locations.begin(), temp);
  locations.pop_back();//removes prev tail
}

void Wriggle::moveTail(int col, int row)
{
  vector<int> temp (2,0);
  temp[0] = col;
  temp[1] = row;
  locations.push_back(temp);//adds tail on back
  locations.erase(locations.begin());//removes prev head
}

void Wriggle::movePart(int col, int row, Parts part)
{
  if(part == HEAD)
  {
    moveHead(col, row);
  }
  else
  {
    moveTail(col, row);
  }
}

ostream& operator<<(ostream& os, const Move &mv)
{
  os<<mv.index<<" "<<mv.part<<" "<<mv.dcol<<" "<<mv.drow;
  
  return os;
}