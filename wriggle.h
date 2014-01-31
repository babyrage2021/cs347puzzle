//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description: header file for the wiggle class
#ifndef WRIGGLE_H
#define WRIGGLE_H

#define MAX 10
#define MAXWIGGLES 9

#include <iostream>
#include <cstdlib>

using namespace std;

enum Parts{ HEAD = 0, TAIL = 1};
enum Coords{ COLUMN = 0, COL = 0, ROW = 1};
enum Directions{UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};

// holds information about a wriggle
struct Wriggle
{
  int locs[2][2];//[parts][coords]
  void setUp(int data[][2]);//done not tested
};

ostream& operator<<(ostream& os, Wriggle &w);//done need to test

#endif
