//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description: header file for the AI class

#ifndef GAME_H
#define GAME_H

#define MAX 10
#define MAXWIGGLES 9

#include <fstream>

#include <string>
#include "wriggle.h"

//has ai func
// has funcs for map checking and interactions

enum(UP = -1, DOWN = 1, LEFT = -1, RIGHT = 1);

class Game
{
  friend class AI;  
  private:
    int numCol;//     number of columns
    int numRow;//     number of rows
    int numWiggles;// number of wriggles
    String[MAX][MAX] grid;// the map of everything
    Wriggle wrigglers[MAXWIGGLES];// the wriggles class that has their info
    bool outputFlag; // flag on to output things in the funcs
  
  public:
    /* description: constructor
    // pre: none
    // post: none
    // param: the filename of the puzzle, and a flag to get output
    //        of debugging things
    // return: none*/
    Game(string Filename, bool outFlag);//done not tested

    /*prints grid only WIP*/
    friend ostream& operator<<(ostream os, Game game);  
  
  private:
    /*description: run this to import the grid
    //pre: none
    //post: give you a grid that has everything in it as a string
    //param: filename with extentsion
    // return: none*/
    void importGrid(string filename);//done not checked    
    
    /*Description: sets up the wriggles array with the number of sections and
    //             where the head and tail are located
    // pre: need to run import grid before running this
    // post: sets up the wriggles array
    // param: none
    // return: none*/
    void setupWrigglers();//done not tested
    
    /* Description: checks the map and sees if it is possible to move there
    // pre: map must be up to date to use this, numCol and numRow need to be set
    // post: none
    // param: the col and row that you want to see available
    // return: true if it can move there*/
    bool checkMap(int col, int row);//done not checked
    
    /*Description: tells whether it is on the map or not
    // pre: need to have the number of columns and rows set
    // post: none
    // param: column and row
    // return: true if it is on the map, false if it is off*/
    bool onMap(int col, int row);// done not tested

}// class

/*description: converts a string to a number
//pre: none
//post: none
//param: the string that is to be converted to a number
//return: the number version of the string ie if given a "1" it will return a 1.
//        if it is not a number then it returns a -1*/
int retNumeric(string part);//done not tested


ostream& operator<<(ostream os, Game game);

#endif