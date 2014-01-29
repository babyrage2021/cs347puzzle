//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description: header file for the AI class

#ifndef GAME_H
#define GAME_H


#include <fstream>

#include "wriggle.h"

//has ai func
// has funcs for map checking and interactions

enum{UP = -1, DOWN = 1, LEFT = -1, RIGHT = 1};
/* class Game
// Description: class that holds the gameboard and the wrigglers
// pre: see param, and board cant be larger then max( found in wriggler.h)
//      and wrigglers cant be larger then MAXWIGGLES (also found in wriggler.h)
// post: 
// param: for its constructor it needs a file to open and whether it should
//        give full outputs or only partial(errors, and stuff for script)*/

//////////////////////////////////////////////////////
//                 public funcs
//////////////////////////////////////////////////////
/* Game(string filename, bool outFlag)//done not tested
// description: constructor
// pre: none
// post: none
// param: the filename of the puzzle, and a flag to get output
//        of debugging things
// return: none*/

/* friend ostream& operator<<(ostream &os, Game &game);
// description: prints grid only done tested
// pre: none
// post: prints the gameboard to the screen
// param: reference to ostream and a reference to game
// return: reference to the ostearm*/  

/* bool onMap(int col, int row);// done not tested
// Description: tells whether it is on the map or not
// pre: need to have the number of columns and rows set
// post: none
// param: column and row
// return: true if it is on the map, false if it is off*/

/* bool checkMap(int col, int row);//done not checked
// Description: checks the map and sees if it is possible to move there
// pre: map must be up to date to use this, numCol and numRow need to be set
// post: none
// param: the col and row that you want to see available
// return: true if it can move there*/
   
/* void print();
// description: outputs the map, privater vars and wriggler info to the screen
// pre: need to have a map, wrigglers and assorted vars set up
// post: outputs the map, privater vars and wriggler info to the screen
// param: none
// return: nothing*/ 

//////////////////////////////////////////////////////
//                 private funcs
//////////////////////////////////////////////////////

/* void importGrid(string filename);//done tested
// description: run this to import the grid
// pre: none
// post: give you a grid that has everything in it as a string
// param: filename with extentsion
// return: none*/

/* void setupWrigglers();//done not tested
// Description: sets up the wriggles array with the number of sections and
//             where the head and tail are located
// pre: need to run import grid before running this
// post: sets up the wriggles array
// param: none
// return: none*/



class Game
{
  friend class AI; 

  private:
    int numCol;//     number of columns
    int numRow;//     number of rows
    int numWrigglers;// number of wriggles
    string grid[MAX][MAX];// the map of everything
    Wriggle wrigglers[MAXWIGGLES];// the wriggles class that has their info
    bool outputFlag; // flag on to output things in the funcs

  public:
    
    Game(string filename, bool outFlag);//done tested   
    friend ostream& operator<<(ostream &os, Game &game); //done tested 
    bool onMap(int col, int row);//     done tested
    bool checkMap(int col, int row);//  done tested
    void print();//                     done tested
    int getNumWrigglers() { return numWrigglers; }
    
    
  private:
    void importGrid(string filename);// done tested
    void setupWrigglers();//            done tested
    
    

};// class

/*description: converts a string to a number
//pre: none
//post: none
//param: the string that is to be converted to a number
//return: the number version of the string ie if given a "1" it will return a 1.
//        if it is not a number then it returns a 0*/
int retNumeric(string part);//done tested


ostream& operator<<(ostream &os, Game &game);//works. tested

#endif