//Programmer: Ryan Hoffman
//Date: 2/2/14
//Description: cpp file for the wriggle, and Move structs
#include "wriggle.h"

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

void Wriggle::getPartLoc(int &col, int &row, Parts part)
{
  if(part == HEAD)
  {
    col = locations[0][COL];
    row = locations[0][ROW];
  }
  else
  {
    col = locations[locations.size() - 1][COL];
    row = locations[locations.size() - 1][ROW];
  }
}

void Wriggle::getIndexLoc(int &col, int &row, int index)
{
  if(index > -1 && index < locations.size())
  {
    col = locations[index][0];
    row = locations[index][1];
  }
  
  return;
}

void swap(Wriggle &a, Wriggle &b)
{
  swap(a.length, b.length);
  swap(a.locations, b.locations);
  return;
}

Wriggle& Wriggle::operator=(Wriggle other)
{// need to check
  if(this != &other)
  {//self assignment check
    swap(*this, other);
  }
  
  return *this;
}

bool Wriggle::operator==(Wriggle rhs) const
{//need to check
  return this -> locations == rhs.locations;//slow.
  // bool retVal = true;
  // for(unsigned int i = 0; i < rhs.locations.size() - 1 && retVal == true; i++)
  // {
    // for(unsigned int j = 0; j < 2 && retVal == true; j++)
    // {// 0,1 being the parts
      // if(!(this -> locations[i][j] == rhs.locations[i][j]))
      // {// if the position at the grid location is different
        // retVal = false;
      // }
    // }
  // }
  
  //return retVal;
}

bool Wriggle::operator!=(Wriggle rhs) const
{//need to check
  return !(*this == rhs);
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
