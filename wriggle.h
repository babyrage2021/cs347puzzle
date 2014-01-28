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

enum parts{ HEAD = 0, TAIL = 1};
enum coords{ COLUMN = 0, COL = 0, ROW = 1};


// holds information about a wriggle
struct Wriggle
{
  int locs[2][2];//[parts][coords]
  int sections; //num sections incl head and tail
  void setUp(int data[][2], int sections);//done not tested
};

ostream& operator<<(ostream& os, Wriggle &w);//done need to test

#endif
