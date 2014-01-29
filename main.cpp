//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description:

#include <time.h>
#include "game.h"

/* notes:
top left - 0.0
format col, row
output must be exact

File Format: col, row, num wiggles
  grid

Game:
  bring head or tail of wiggler 0 to bottom right
  can be moved by head or tail
  directions are cardinal( UDLR)
  cant pass through:
    walls
    other wigglers
    parts of its self
    edge of map

Grid:
  e = empty Space
  x = wallc
  U,D,L,R= wiggler head w/ direction to next
  ^,V,<,> = internal segments
  tail is the index of the wiggler. 0 needs to get to goal

Display:
  time that the ai took to run // none need to test
  display num moves
  every move in in a row consisting of:
    wriggler id, head/tail moving, coords to dest
  sol to final state
*/
// arg order: puzzle file, flag to turn on all output(0,1), 
//            ai to use(defaults to newest{0})
int main(int argc, char* argv[])
{
  time_t start = time(0);
  string filename;
  int usedAi;
  bool specialOutputs = true;
  
  // argument checking stuff
  if(argc > 3)
  {//adds ai to use
    //TODO
  }
  
  if(argc > 2)
  {//output flag
    //TODO
  }
  
  if(argc > 1)
  {//filename given
    filename = argv[1];
  }
  else
  {// in case no filename is given it gives it a file to read from
    cout<<"Error in main.cpp: No file given using default file"<<endl;
    filename = "puzzle1.txt";
  }
  
  Game gameboard(filename,specialOutputs);
  
  cout<<"gameboard created"<<endl<<gameboard<<endl;
  
  
  // move list:
  // format: id, head/tail, destination
  
  
  //map
  if(specialOutputs == true)
  {
    cout << "Time the program has been running: ";
  }

  cout<<difftime(time(0), start)<< endl;
  
  //num moves here
  
  
  return 0;
}