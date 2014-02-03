//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description: header file for the game class which handles the gameboard

#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <sstream>

#include "wriggle.h"

/* class Game
// Description: class that holds the gameboard and the wrigglers
// pre: see param, and board cant be larger then max( found in wriggler.h)
//      and wrigglers cant be larger then MAXWIGGLES (also found in wriggler.h)
// post: 
// param: for its constructor it needs a file to open and whether it should
//        give full outputs or only partial(errors, and stuff for script)*/

/*
// description: blank
// pre:
// post:
// param:
// return: */
//////////////////////////////////////////////////////
//                 public funcs
//////////////////////////////////////////////////////
/* Game();
// description: default constructor
// pre: none
// post:sets up the class
// param: none
// return: none*/

/* Game(const string &filename, const bool &outFlag)
// description: constructor
// pre: none
// post: none
// param: the filename of the puzzle, and a flag to get output
//        of debugging things
// return: none*/

//friend ostream& operator<<(ostream &os, Game game); 
// for documentation for this see below the class

/* friend void swap(Game &a, Game & other);
// description: its a swap function
// pre: none
// post: none
// param: 2 games
// return: none */

/* Game & operator=( Game g);
// description: assignment operator. it calls the swap func
// pre: none
// post: none
// param: a game that is passed by value
// return: reference to the lhs*/

/* void setUp(const string &filename, const bool &outFlag);
// description: sets up the wriggler class
// pre: none
// post: wriggler class is set up
// param: the file with the extension, and a flag that allows the class to
//        output more things
// return: none*/

/* void print();
// description: outputs the map, privater vars and wriggler info to the screen
// pre: need to have a map, wrigglers and assorted vars set up
// post: outputs the map, privater vars and wriggler info to the screen
// param: none
// return: nothing*/ 

/* void moveWriggler(int index, int part, int newCol, int newRow);
// description: moves a wriggler on the map.
// pre: need to have a map set up. the total distance moved must be 1
// post: moves a wriggler on the map
// param: index is the index of the wriggler, part is the part that you want
//        to move, newCol, newRow are the col and row that you want to move to
// return: none*/
    
/* bool onMap(const int &col, const int &row);
// Description: tells whether it is on the map or not. also no error stuff
// pre: need to have the number of columns and rows set
// post: none
// param: column and row
// return: true if it is on the map, false if it is off*/

/* int adjCoords(const string &loc, int &col, int &row);
// description: it adjusts the coords to be the next space if the space is
//              pointing at another space
// pre: none
// post: changes row and col to be the new position
// param: the current loc and the row and column
// return: integer direction from the enum in wiggle.h*/
       
/* int getNumWrigglers()
// description: gets the number of wrigglers
// pre: need to have done the setup stuff
// post: none
// param: none
// return:the number of wriggler*/

/* Wriggle getWriggler(const int &index);
// description: returns the wriggler at the index. has error checking
// pre: none, but you should probably have the wrigglers setup
// post: none
// param: the index to it
// return: */

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
  private:
    int numCol;//     number of columns
    int numRow;//     number of rows
    int numWrigglers;// number of wriggles
    string grid[MAX][MAX];// the map of everything
    vector<Wriggle> wrigglers;// the wriggles class that has their info
    bool outputFlag; // flag on to output things in the funcs
    int adjCoords(const string &loc, int &col, int &row);//tested works
    void importGrid(const string &filename);// done tested
    void setupWrigglers();//            done tested
    
  public:
    
    Game() { numCol = numRow = numWrigglers = 0; }
    Game(const string &filename, const bool &outFlag);//done tested
    
    friend ostream& operator<<(ostream &os, Game game); //done tested 
    friend void swap(Game &a, Game & other);//works tested
    
    Game & operator=(Game g);//works tested
    
    void setup(const string &filename, const bool &outFlag); // works tested
    void print(ostream &os = cout);//                     done tested
    void moveWriggler(int index, Parts part, int newCol, int newRow);
    void moveWriggler(Move mv); // calls the other one. this just converts it
    bool onMap(int col, int row) const;//     done tested
    
    //sim to check map but no potential for crashes
    // true if it can move there
    bool testCoords(int col, int row) const;
    
    int getNumWrigglers() { return numWrigglers; } //works tested
    Wriggle getWriggler(const int &index); //works tested
    
    bool operator==(Game &rhs) const;//appears to work needs more testing
    
    // true if wriggler is at the goal TODO
    bool isGoal();
    
};// class

/* Description: turns an int into a string
// pre: none
// post: none
// param: int that you want converted to a string
// return:*/
string getString(const int &part); //works tested

/* Description: returns true if it is a head piece
// pre: none
// post: none
// param: string to be tested if it is a head
// return:true if it is a head piece false if not*/
bool isHead(const string &s);// works tested

/* Description: returns true if a body piece
// pre: none
// post: none
// param: string that is the body piece
// return:see description*/
bool isBody(const string &gridLoc);//works tested

/* Description: converts body pieces to head pieces
// pre: none
// post: none
// param: a string that is to be converted
// return: the converted string*/
string convert(const string &part);//works tested

/*description: converts a string to a number
//pre: none
//post: none
//param: the string that is to be converted to a number
//return: the number version of the string ie if given a "1" it will return a 1.
//        if it is not a number then it returns a 0*/
int retNumeric(const string &part);//done tested

/* ostream& operator<<(ostream &os, Game &game);
// description: prints grid only done tested
// pre: none
// post: prints the gameboard to the screen
// param: reference to ostream and a reference to game
// return: reference to the ostearm*/  
ostream& operator<<(ostream &os, Game game);//works. tested

string getDirection(int cola, int rowa, int colb, int rowb);

#endif