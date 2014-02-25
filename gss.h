//graph.h
#ifndef GSS_H
#define GSS_H
#include "move.h"
#include <queue>
#include <vector>
#include <functional>
#include <sstream>
//Graph Search Storage
class GSS
{
  private:
    priority_queue< Move, vector<Move>, std::greater<Move> > frontier;
    vector<unsigned int> ht;// unofficial hash table
    vector<Move> explored;
    int current; //loc in explored = explored.size-1
  public:
    GSS(){current = -1;}
    void getMoves(vector<Move> &list);//gets a list of moves from the current
    void insert(Move mv);//check for legal move here.
    Move getNext();// gets the node with the highest priority
    bool search(unsigned int &hsh) const;
    bool emptyFrontier() const {return frontier.empty(); }
    friend ostream& operator<<(ostream &os, GSS gss);
    int getParentHval(const int &index);
};

ostream& operator<<(ostream &os, GSS gss);

#endif
