//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description: header file for the wiggle class
#ifndef WRIGGLE_H
#define WRIGGLE_H

#define MAX 10
#define MAXWIGGLES 9

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

enum Parts{ HEAD = 0, TAIL = 1, ERROR = 2};
enum Coords{ COLUMN = 0, COL = 0, ROW = 1};
enum Directions{UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3, INVALID = 4};

// holds information about a wriggle
struct Wriggle
{
  vector< vector<int> > locations;
  int length;
  void clear() { length = 0; locations.clear(); }
  void moveHead(int col, int row);
  void moveTail(int col, int row);
  void movePart(int col, int row, Parts part);
};

ostream& operator<<(ostream& os, Wriggle &w);//done need to test

struct Move
{
  int index;
  Parts part;
  int dcol;
  int drow;
  
};

ostream& operator<<(ostream& os, const Move &mv);
#endif
