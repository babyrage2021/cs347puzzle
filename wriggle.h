//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description: header file for the wiggle class
#ifndef WRIGGLE_H
#define WRIGGLE_H

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

#define MAX 10       //consider delete
#define MAXWIGGLES 9 //consider delete
enum Parts{ HEAD = 0, TAIL = 1, ERROR = 2};
enum Coords{ COLUMN = 0, COL = 0, ROW = 1};
enum Directions{UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, INVALID = 4};

//description holds information about a wriggle
struct Wriggle
{
  vector< vector<int> > locations;
  int length;
  
  void clear() { length = 0; locations.clear(); }
  void moveHead(int col, int row);
  void moveTail(int col, int row);
  void movePart(int col, int row, Parts part);
  void getPartLoc(int &col, int &row, Parts part);
  void getIndexLoc(int &col, int &row, int index);
  
  Wriggle &operator=(Wriggle rhs);//calls swap
  bool operator==(Wriggle rhs) const;
  bool operator!=(Wriggle rhs) const;// calls ==
};

void swap(Wriggle &a, Wriggle &b);
ostream& operator<<(ostream& os, Wriggle &w);
#endif
