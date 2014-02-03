//Programmer: Ryan Hoffman
//Date: 1/27/14
//description: holds the functions for the AI class and its friend funcs
#include "game.h"
//////////////////////////////////////////////////////////////////////////
//                                     Public functions
//////////////////////////////////////////////////////////////////////////
Game::Game(const string &filename, const bool &outFlag)
{
  setup(filename, outFlag);
}

void swap(Game &a, Game & other)
{
  using std::swap;
  swap(a.numCol, other.numCol);
  swap(a.numRow, other.numRow);
  swap(a.numWrigglers, other.numWrigglers);
  swap(a.outputFlag, other.outputFlag);
  swap(a.wrigglers, other.wrigglers);
  swap(a.grid, other.grid);
}

Game& Game::operator=(Game other)
{ 
  if(this != &other)
  {//self assignment check
    swap(*this, other);
  }
  
  return *this;
}

void Game::setup(const string &filename, const bool &outFlag)
{
  outputFlag = outFlag;// setup to output or not
  importGrid(filename);// sets up the grid
  setupWrigglers();// set up the wriggles
  return;
}

void Game::print(ostream &os)
{
  for(int i = 0; i < numRow; i++)
  {
    for(int j = 0; j< numCol; j++)
    {
      os<<grid[j][i]<<" ";
    }
    os<<endl;
  }
}

// how this works is it goes through and puts the head/tail section in the
// empty space extending its length by 1. then calls itself recursivly and 
// on the second half shrinks itself
void Game::moveWriggler(Move mv)
{
  moveWriggler(mv.index, mv.part, mv.dcol, mv.drow);
  return;
}

void Game::moveWriggler(int index, Parts part, int newCol, int newRow)
{
  
  // error handling to prevent walking off the arrays
  if(index < 0 || index >= numWrigglers)
  {
    cout<<"Error: Game::moveWriggler: index is not valid. index: "<<index;
    cout<<endl;
    exit(EXIT_FAILURE);
  }
  else if(part < 0 || part > 1)
  {
    cout<<"Error: Game::moveWriggler: part given is not valid. part: "<<part;
    cout<<endl;
    exit(EXIT_FAILURE);
  }
  else if(!onMap(newCol, newRow))
  {//should ensure that the space is empty
    cout<<"Error: Game::moveWriggler: column or row was not on the map";
    cout<<""<<newCol<<", "<<newRow<<endl;
    exit(EXIT_FAILURE);
  }
  
  int oldCol, oldRow;
  int len = wrigglers[index].length-1;
  if(part == HEAD)
  {
    oldCol = wrigglers[index].locations[0][COL];
    oldRow = wrigglers[index].locations[0][ROW];
  }
  else
  {
    oldCol = wrigglers[index].locations[len][COL];
    oldRow = wrigglers[index].locations[len][ROW];
  }
  
  
  if(grid[newCol][newRow] != "e")
  {//moving in on itself
    string newSpace;
    
    //makes the new space correct 
    if(part == HEAD)
    {
      // space is already occupied by a direction
      newSpace = convert(grid[newCol][newRow]);
    }
    else
    {
      newSpace = getString(index);
    }
    
    grid[newCol][newRow] = newSpace;
    grid[oldCol][oldRow] = "e";
    return;
  }
  else
  {//not moving in on itself
    
    int newoCol, newoRow;
    int ind;//index is head or tail for the next part
    Parts newPart;
    string newBodyPiece;
    if(part == HEAD)
    {
      grid[oldCol][oldRow] = convert(grid[oldCol][oldRow]);
      newBodyPiece = getDirection(oldCol, oldRow, newCol, newRow);
      grid[newCol][newRow] = newBodyPiece;
      newPart = TAIL;
      ind = len;
    }
    else
    { 
      //get direction returns a head piece and convert converts it to a body
      newBodyPiece = getDirection(newCol, newRow, oldCol, oldRow);

      grid[oldCol][oldRow] = convert(newBodyPiece);
      grid[newCol][newRow] = getString(index);
      
      newPart = HEAD;
      ind = 2;// so it can have 1 subtracted from it and have head moved
              // onto that space
    }
    
    newoCol = wrigglers[index].locations[ind-1][COL];
    newoRow = wrigglers[index].locations[ind-1][ROW];
    moveWriggler(index, newPart, newoCol, newoRow);
    wrigglers[index].movePart(newCol, newRow, part);
  }//else
  
  if(outputFlag == true)
  {
      cout<<"move wriggler done================"<<endl;
      print();
      cout<<"move's board is printed"<<endl;
  }
  
}//func

bool Game::onMap( int col,  int row) const
{
  return !(col < 0 || col >= numCol || row < 0 || row >= numRow);
}

bool Game::testCoords(int col, int row) const
{
  return (onMap(col, row) && grid[col][row] == "e" );
}

Wriggle Game::getWriggler(const int &index)
{
  if(index >= numWrigglers || index < 0 || index > MAXWIGGLES)
  {
    cout << "Error in game::getWriggler: invalid index"<<index<<endl;
    exit(EXIT_FAILURE);  
  }
  
  return wrigglers[index];
}

bool Game::operator==(Game &rhs) const
{
  if(!(this -> numCol == rhs.numCol && this -> numRow == rhs.numRow
    && this -> numWrigglers == rhs.numWrigglers))
  {
    return false;
  
  }
  else
  {
    for(int i = 0; i <= rhs.numCol; i++)
    {
      for(int j = 0; j <= rhs.numRow; j++)
      {
        if(!(this -> grid[i][j] == rhs.grid[i][j]))
        {// if the position at the grid location is different
          return false;
        }
      }
    }
  
  }
  
  return true;

}

bool Game::isGoal()
{
  return (wrigglers[0].locations[0][COL] == numCol -1 
       && wrigglers[0].locations[0][ROW] == numRow -1)
       ||(wrigglers[0].locations[wrigglers[0].length-1][COL] == numCol -1 
       && wrigglers[0].locations[wrigglers[0].length-1][ROW] == numRow -1);
}

//////////////////////////////////////////////////////////////////////////
//                                     Private functions
//////////////////////////////////////////////////////////////////////////
// does not do anything with the wiggles
void Game::importGrid(const string& filename)
{ 
  if(outputFlag == true)
  { 
    cout<<"Game::importGrid start. Filename: "<<filename<<endl;
  }
  
  string item;
  int colCounter = 0;
  int rowCounter = 0;
  
  ifstream fin;
  fin.open(filename.c_str());
  
  //top row of the file
  fin >> numCol;
  fin >> numRow;
  fin >> numWrigglers;
  
  wrigglers.resize(numWrigglers);
  
  if(outputFlag == true)
  { 
    cout<<"Top of file done. Beginning grid import. ";
    cout<<"Columns: "<<numCol<<", Rows: "<<numRow;
    cout<<", Wrigglers: "<<numWrigglers<<endl;
  }
  
  // Grid Inport starts here
  while( fin >> item )
  {
    // puts item in grid
    grid[colCounter][rowCounter] = item;
    
    colCounter++;
    //increases the columns and resets the counter if it is going to a new row
    if(colCounter >= numCol)
    {
      colCounter=0;
      rowCounter++;
      
    }
  
  }//while loop
  
  fin.close();
  
  if(outputFlag == true)
  { 
    cout<<"Game::importGrid done"<<endl;
  }
  
  return;
}//importGrid

void Game::setupWrigglers()
{
  if(outputFlag == true)
  {
    cout<<"Game::setupWriggles start. number wrigglers: "<<numWrigglers<<endl;
  }
  
  string currentSpace;
  Wriggle currentWriggler;
  vector<int> temp;
  for(int i = 0; i < numCol; i++)
  {
    for(int j = 0; j < numRow; j++)
    {
      currentSpace = grid[i][j];
      if(isHead(currentSpace))
      {
        currentWriggler.clear();
        int row = j, col = i;

        do
        {
          temp.clear();
          temp.push_back(col);
          temp.push_back(row);
          currentWriggler.locations.push_back(temp);
          adjCoords(currentSpace, col, row);
          currentSpace = grid[col][row];
          
        }while(isBody(currentSpace));
    
        temp.clear();
        temp.push_back(col);
        temp.push_back(row);
        
        //tail section
        currentWriggler.locations.push_back(temp);
        
        currentWriggler.length = currentWriggler.locations.size();
        currentWriggler.locations.resize(currentWriggler.length);
        wrigglers[retNumeric(grid[col][row])] = currentWriggler;
      }
    }
  }
  
  if(outputFlag == true)
  {
    cout<<"Game::setupWriggles stop. number wrigglers: "<<numWrigglers<<endl;
  }
  
  wrigglers.resize(numWrigglers);
  return;
}//func


//tells me where the next section is and adj coords to get to it
int Game::adjCoords(const string &loc, int &col, int &row)
{
  int retVal;
  if(loc == "U" || loc == "^")
  {
    row--;
    retVal = UP;
  }
  else if(loc == "R" || loc == ">")
  {
    col++;
    retVal = RIGHT;
  }
  else if(loc == "D" || loc == "v" || loc == "V")
  {
    row++;
    retVal = DOWN;
  }
  else if(loc == "L" || loc == "<")
  {
    col--;
    retVal = LEFT;
  }
  
  if(!onMap(col,row))
  {//error checking
    cout<<"Error: Game::adjCords: new loc is off the map. ";
    cout<<"loc: "<<loc<<" ("<<col<<","<<row<<")"<<endl;
    exit(EXIT_FAILURE);
  }
  
  return retVal;
}

//////////////////////////////////////////////////////////////////////////
//                                     other functions
//////////////////////////////////////////////////////////////////////////
bool isHead(const string &s)
{
  return s == "U" || s == "R" || s == "D" || s == "L";
}

bool isBody(const string &gridLoc)
{
  return gridLoc == "^" || gridLoc == ">" || gridLoc == "v" || gridLoc == "<";
}

string convert(const string &part)
{
  string retVal;
  if(!isHead(part) && !isBody(part))
  {
    cout<<"Error in game.cpp convert: you are not converting a head or a body";
    cout<<" piece. the part is: "<<part<<endl;
    exit(EXIT_FAILURE);
  }
  else if(part == "U")
  {
    retVal = "^";
  }
  else if(part == "R")
  {
    retVal = ">";
  }
  else if(part == "D")
  {
    retVal = "v";
  }
  else if(part == "L")
  {
    retVal = "<";
  }
  else if(part == "^")
  {
    retVal = "U";
  }
  else if(part == ">")
  {
    retVal = "R";
  }
  else if(part == "v")
  {
    retVal = "D";
  }
  else if(part == "<")
  {
    retVal = "L";
  }
  else
  {
    retVal = "E";
    cout<<"THERE IS A PROBLEM HERE IN CONVERT PART="<<part<<"\\\\\\\\\\\\\\\\";
    cout<<endl;
  }

  return retVal;

}

int retNumeric(const string &part)
{
  return atoi(part.c_str());
}

string getString(const int &part)
{
  stringstream ss;
  ss<<part;
  return  ss.str();
  
}

ostream& operator<<(ostream &os, Game game)
{
  os<<"col: "<<game.numCol<<", rows: "<<game.numRow;
  os<<", num Wrigglers:"<<game.numWrigglers<<endl;
  
  for(int i = 0; i < game.numWrigglers; i++)
  {
    os<<i<<":"<<game.wrigglers[i]<<"\n";
  }
  
  game.print();
  return os;
}

string getDirection(int oldC, int oldR, int newC, int newR)
{
  if(!((abs(oldC - newC) != 1) ^
       (abs(oldR - newR) != 1)))
  {// incase it is trying to move more then 1 space or none at all
    return NULL;
  }
  else if( oldC > newC)
  {
    return "R";
  }
  else if( oldC < newC)
  {
    return "L";
  }
  else if( oldR > newR)
  {
    return "D";
  }
  else if(oldR < newR)
  {
    return "U";
  }
}
