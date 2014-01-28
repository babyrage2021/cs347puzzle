//Programmer: Ryan Hoffman
//Date: 1/27/14
//Description: header file for the wiggle class
#ifndef WRIGGLE_H
#define WRIGGLE_H
#include <iostream>
using namespace std;

enum Parts( HEAD = 0, TAIL = 1);
enum coords( COLUMN = 0, COL = 0, ROW = 1);


// holds information about a wriggle
struct Wriggle
{
  int locs[2][2];//[parts][coords]
  int sections; //num sections incl head and tail
  void setUp(int data[][], int sections);
  friend ostream& operator<<(ostream os, Wriggle w);
}


ostream& operator<<(ostream os, Wriggle w);//done need to test

#endif
