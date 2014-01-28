//Programmer: Ryan Hoffman
//Date: 1/27/14
//description: holds the functions for the AI class and its friend funcs
#include "game.h"
//////////////////////////////////////////////////////////////////////////
//                                     Public functions
//////////////////////////////////////////////////////////////////////////
Game::Game(string Filename, bool outFlag)
{
  outputFlag = outFlag;// setup to output or not
  importGrid(filename);// sets up the grid
  setupWrigglers();// set up the wriggles
}

//////////////////////////////////////////////////////////////////////////
//                                     Private functions
//////////////////////////////////////////////////////////////////////////
// does not do anything with the wiggles
void Game::importGrid(string filename)
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
  fin >> numWigglers;
  if(numCol <= 0 || numCol >= MAX || numRow <= 0 || numRow >= MAX)
  {
    cout<<"Error: Game::inportGrid: the rows or the columns are outside";
    cout<<"the accepted range. col: "<<numCol<<", row:"<<numRow;
    cout<<", wrigglers: "<<numWigglers<<endl;
    exit(EXIT_FAILURE);
  }
  
  if(outputFlag == true)
  { 
    cout<<"Top of file done. Beginning grid import. ";
    cout<<"Columns: "<<numCol<<", Rows: "<<numRow;
    cout<<", Wrigglers: "<<numWigglers<<endl;
  }
  
  int counter = 0;
  // Grid Inport starts here
  while( fin >> item )
  {
  cout<<counter++<<" "<<colCounter<<" "<<rowCounter<<endl;
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
    cout<<"Game::setupWriggles start. number wrigglers: "<<numWigglers<<endl;
  }

  string gridLoc;// the value of that square of the grid
  int sections = 0;// number of sections of a wriggler
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
      if( gridLoc == "U" || gridLoc == "D" || gridLoc == "L" || gridLoc == "R")
      {
        if(outputFlag == true)
        {
          cout<<"Found a head section. space:"<<gridLoc<<" (";
          cout<<i<<", "<<j<<")"<<endl;
        }
       
        countWrigglers++;        
        sections = 1; // includes head
        int col = headTailLocs[HEAD][COL] = i;
        int row = headTailLocs[HEAD][ROW] = j;
        
        // adjusts the row and col so it can get the next section
        if( gridLoc == "U" )
        {//up
          row--; 
          
          if(outputFlag == true)
          {
            cout<<"next section is up"<<endl;
          }
        }
        else if( gridLoc == "D" )
        {//down
          row++;
          if(outputFlag == true)
          {
            cout<<"next section is down"<<endl;
          }
        }
        else if( gridLoc == "L" )
        {//left right
          col--;
          if(outputFlag == true)
          {
            cout<<"next section is left"<<endl;
          }
        }
        else
        {// right
          col++;
          if(outputFlag == true)
          {
            cout<<"next section is right"<<endl;
          }
        }

        if(onMap(col, row) == false)
        {// in case of a bad map or some other type of error
            cout<<"Error: Game::setupWriggler: The column or row is not on";
            cout<<"the map. ("<<col<<", "<<row<<")";
            exit(EXIT_FAILURE);
        }
        
        if(outputFlag == true)
        {
          cout<<"Top Section done. Starting middle section."<<endl;
        }
        
        // middle section
        gridLoc = grid[col][row];
        while( gridLoc == "^" || gridLoc == "v" || gridLoc == "<"
            || gridLoc == ">" )
        {
          sections++;
          // adjusts the row and col so it can get the next section
          if( gridLoc == "^" )
          {// up
            row--;        
            if(outputFlag == true)
            {
              cout<<"next section is up"<<endl;
            }
          }
          else if( gridLoc == "v" )
          {//down
            row++;
            if(outputFlag == true)
            {
              cout<<"next section is down"<<endl;
            }
          }
          else if( gridLoc == "<" )
          {//left
            col--;
            if(outputFlag == true)
            {
              cout<<"next section is left"<<endl;
            }
          }
          else
          {// right
            if(outputFlag == true)
            {
              cout<<"next section is right"<<endl;
            }
            col++;
          }
          
          gridLoc = grid[col][row];
        }
        
        if(outputFlag == true)
        {
          cout<<"middle section done. end section starting."<<endl;
        }
        
        // end section
        int index = retNumeric( grid[col][row] );
        
        if(index <= -1 || index >= MAXWIGGLES)
        {// error stuff
          cout<<"Error in Game::setupWrigglers: unable to find next section";
          cout<<"wriggler index: "<<index<<endl;
          exit(EXIT_FAILURE);
        }
        sections++;
        headTailLocs[TAIL][COL] = col;
        headTailLocs[TAIL][ROW] = row;
        
        // sets up the wriggler
        wrigglers[index].setUp(headTailLocs, sections);
      }//if head sec
    }// inner for
  }// outer for
  
  if(countWrigglers != numWigglers)
  {
    cout<<"Error in Game::setupWrigglers: ";
    cout<<"number of wrigglers is not equal to the amount that was";
    cout<<" counted. \n countWrigglers: "<<countWrigglers<<" , ";
    cout<<"numWiggles: "<<numWigglers<<endl;
    exit(EXIT_FAILURE);
  }
  
  if(outputFlag == true)
  {
    cout<<"Game::setupWriggles stop. number wrigglers: "<<numWigglers;
  }
  return;
}//func

bool Game::checkMap(int col, int row)
{
  bool returnVal = true;
  if( !onMap(col, row) )
  {//checks for off the map
    cout << "Error in ai.cpp-checkMap: off map" << endl;
    returnVal = false;
  }
  else if(grid[col][row] != "e")
  {// checks full space
    cout<<"Error in ai.cpp-checkMap: space not empty" << endl;
    returnVal = false;
  }
  
  return returnVal;
}

bool Game::onMap(int col, int row)
{
  return !(col < 0 || col >= numCol || row < 0 || row >= numCol);

}

//////////////////////////////////////////////////////////////////////////
//                                     other functions
//////////////////////////////////////////////////////////////////////////

int retNumeric(string part)
{
  string temp;
  for( int i = 0; i < 10; i++)
  { 
    temp = i;
    if( part == temp )//need to check this
    {
      return i;
    }
  }  
  
  return -1;
}

ostream& operator<<(ostream &os, Game &game)
{
  for(int i = 0; i < game.numRow; i++)
  {
    for(int j = 0; j< game.numCol; j++)
    {
      os<<game.grid[j][i]<<" ";
    }
    os<<endl;
  }
  
  return os;
}