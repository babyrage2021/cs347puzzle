//Programmer: Ryan Hoffman
//Date: 1/27/14
//description: holds the functions for the AI class and its friend funcs
#include "game.h"
//////////////////////////////////////////////////////////////////////////
//                                     Public functions
//////////////////////////////////////////////////////////////////////////
Game::Game(const string &filename, const bool &outFlag)
{
  setUp(filename, outFlag);
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

void Game::setUp(const string &filename, const bool &outFlag)
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
void Game::moveWriggler(int index, int part, int newCol, int newRow)
{
  if(outputFlag == true)
  {
    cout<<"moveWriggler start:"<<index<<", "<<part<<" "<<newCol<<" ";
    cout<< newRow<<endl;
  }
  
  int dir= 0;
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
  else if(!((abs( wrigglers[index].locs[part][COL] - newCol) != 1) ^
            (abs( wrigglers[index].locs[part][ROW] - newRow) != 1)))
  {// ^ = xor. i am saying if there is no movement or trying to move
   // diagionally then it triggers this error
    cout<<"Error: Game::moveWriggler: invalid movement. old (";
    cout<<"PART: "<<part<<" "<<wrigglers[index].locs[part][COL]<<",";
    cout<<wrigglers[index].locs[part][ROW]<<"). new ("<<newCol<<","<<newRow;
    cout<<")"<<endl;
    exit(EXIT_FAILURE);
  }
  
  int oldCol = wrigglers[index].locs[part][COL];
  int oldRow = wrigglers[index].locs[part][ROW];
  string newSpace;
  if(grid[newCol][newRow] != "e")
  {// moving in on itself or the second half of the move
    if(outputFlag == true)
    {
      cout<<"moveWriggler is moving in on itsSelf"<<endl;
    }
    
    newSpace = "e";
    grid[oldCol][oldRow] = newSpace;
    if(part == HEAD)
    {
      newSpace = convert(grid[newCol][newRow]);
    }
    else
    {
      newSpace = getString(index);
    }
    
    grid[newCol][newRow] = newSpace;
  }
  else
  {
    if(outputFlag == true)
    {
      cout<<"not moving in on itself"<<endl;
    }
    
    //gets direction
    if(oldCol > newCol)
    {// moving left
      if(outputFlag == true)
      {
        cout<<"moveW moving left"<<endl;
      }
      
      if(part == HEAD)
      {
        grid[newCol][newRow] = "R";
      }
      else
      {
        grid[oldCol][oldRow] = "<";
      }
    }
    else if(oldCol < newCol)
    {// moving right
      if(outputFlag == true)
      {
        cout<<"moveW moving right"<<endl;
      }
      
      if( part == HEAD)
      {
        grid[newCol][newRow] = "L";
      }
      else
      {
        grid[oldCol][oldRow] = ">";
      }
    }
    else if(oldRow > newRow)
    {// moving up
    
      if(outputFlag == true)
      {
        cout<<"moveW moving up"<<endl;
      }
    
      if( part == HEAD)
      {
        grid[newCol][newRow] = "D";
      }
      else
      {
        grid[oldCol][oldRow] = "^";
      }
    }
    else //if(oldRow < newRow)
    {// moving down
    
      if(outputFlag == true)
      {
        cout<<"moveW moving down"<<endl;
      }
      
      if( part == HEAD)
      {
        grid[newCol][newRow] = "U";
      }
      else
      {
        grid[oldCol][oldRow] = "v";
      }
    }
    
    if(outputFlag == true)
    {
      print();
      cout<<endl;
    }
    
    //here convert old C
    if(part == HEAD)
    {
      //sets up move for tail
      int col = oldCol, row = oldRow;
      grid[oldCol][oldRow] = convert(grid[oldCol][oldRow]);
      string gridLoc = grid[col][row];
      while( isBody(gridLoc))
      {
        oldCol = col;
        oldRow = row;
        // adjusts the row and col so it can get the next section
        adjCoords(gridLoc, col, row);
        gridLoc = grid[col][row];
      }
      
      moveWriggler(index, TAIL, oldCol, oldRow);
    }
    else
    {//for tail
      grid[newCol][newRow] = getString(index);
      int tempCol = wrigglers[index].locs[HEAD][COL];
      int tempRow = wrigglers[index].locs[HEAD][ROW];
      if(outputFlag == true)
      {
        print();
        cout<<endl;
      }
      adjCoords(grid[tempCol][tempRow], tempCol, tempRow);
      moveWriggler(index, HEAD, tempCol, tempRow);
    }
  }
  
  wrigglers[index].locs[part][COL] = newCol;
  wrigglers[index].locs[part][ROW] = newRow;
  
  if(outputFlag == true)
  {
    cout<<"moveWriggler stop:"<<index<<", "<<part<<" "<<newCol<<" ";
    cout<< newRow<<endl;
  }
}

bool Game::onMap(const int &col, const int &row)
{
  return !(col < 0 || col >= numCol || row < 0 || row >= numRow);
}

bool Game::checkMap(const int &col, const int &row)
{
  bool returnVal = true;
  if( !onMap(col, row) )
  {//checks for off the map
    cout << "Error in game.cpp-checkMap: off map" << endl;
    exit(EXIT_FAILURE);
  }
  else if(grid[col][row] != "e")
  {// checks full space
    if(outputFlag == true)
    {
      cout<<"Error in ai.cpp-checkMap: space not empty";
      cout<<"("<<col<<","<<row<<")"<<grid[col][row]<<endl;
    }
    
    returnVal = false;
  }
  
  return returnVal;
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

//tells me where the next section is and adj coords to get to it
int Game::adjCoords(const string &loc, int &col, int &row)
{
  int retVal;
  if(loc == "U" || loc == "^")
  {
    row--;
    if(outputFlag == true)
    {
      cout<<"next section is up"<<endl;
    }
    
    retVal = UP;
  }
  else if(loc == "R" || loc == ">")
  {
    col++;
    if(outputFlag == true)
    {
      cout<<"next section is Right"<<endl;
    }
    
    retVal = RIGHT;
  }
  else if(loc == "D" || loc == "v" || loc == "V")
  {
    row++;
    if(outputFlag == true)
    {
      cout<<"next section is down"<<endl;
    }
    
    retVal = DOWN;
  }
  else
  {
    col--;
    if(outputFlag == true)
    {
      cout<<"next section is left"<<endl;
    }
    
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
  
  if(numCol <= 0 || numCol >= MAX || numRow <= 0 || numRow >= MAX)
  {
    cout<<"Error: Game::inportGrid: the rows or the columns are outside";
    cout<<"the accepted range. col: "<<numCol<<", row:"<<numRow;
    cout<<", wrigglers: "<<numWrigglers<<endl;
    exit(EXIT_FAILURE);
  }
  
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
  
  //checking to make sure the grid was imported correctly
  if(colCounter != 0 && rowCounter != numRow && outputFlag == true)
  {
    cout << "Error in Game::importGrid: the rows or columns are not correct.";
    cout << endl;
  
  }

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

  string gridLoc;// the value of that square of the grid
  int headTailLocs[2][2];//[0=head, 1= tail][0=column, 1=row]
  int countWrigglers = 0; // for error checking
  
  // these 2 for loops search the grid for the head sections. once it
  // finds one then it follows the wriggler until it finds the tail
  for( int i = 0; i < numCol; i++)//col
  {
    for(int j = 0; j < numRow; j++)// row
    {
      gridLoc = grid[i][j];
      
      // if it is a head section
      if(isHead(gridLoc) == true)
      {
        if(outputFlag == true)
        {
          cout<<"Found a head section. space: "<<gridLoc<<" (";
          cout<<i<<", "<<j<<")"<<endl;
        }
       
        countWrigglers++; 
        
        int col = headTailLocs[HEAD][COL] = i;
        int row = headTailLocs[HEAD][ROW] = j;
        
        // adjusts the row and col so it can get the next section
        adjCoords(gridLoc, col, row);
        
        if(outputFlag == true)
        {
          cout<<"Top Section done. Starting middle section."<<endl;
        }
        
        // middle section
        gridLoc = grid[col][row];
        while( isBody(gridLoc))
        {
          // adjusts the row and col so it can get the next section
          adjCoords(gridLoc, col, row);
          gridLoc = grid[col][row];
        }
        
        if(outputFlag == true)
        {
          cout<<"middle section done. end section starting."<<endl;
        }
        
        // end section
        int index = retNumeric( grid[col][row] );
        
        if(index <= -1 || index >= numWrigglers)
        {// error stuff
          cout<<"Error in Game::setupWrigglers: unable to find next section";
          cout<<"wriggler index: "<<index<<endl;
          exit(EXIT_FAILURE);
        }
        
        headTailLocs[TAIL][COL] = col;
        headTailLocs[TAIL][ROW] = row;
        
        if(outputFlag == true)
        {
          cout<<"Found a tail section. space: "<<gridLoc<<" (";
          cout<<col<<", "<<row<<")"<<endl;
        }
        
        // sets up the wriggler
        wrigglers[index].setUp(headTailLocs);
      }//if head sec
    }// inner for
  }// outer for
  
  if(countWrigglers != numWrigglers)
  {
    cout<<"Error in Game::setupWrigglers: ";
    cout<<"number of wrigglers is not equal to the amount that was";
    cout<<" counted. \n countWrigglers: "<<countWrigglers<<" , ";
    cout<<"numWiggles: "<<numWrigglers<<endl;
    exit(EXIT_FAILURE);
  }
  
  if(outputFlag == true)
  {
    cout<<"Game::setupWriggles stop. number wrigglers: "<<numWrigglers<<endl;
  }
  
  return;
}//func

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
  else if(part == "L")
  {
    retVal = "<";
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

