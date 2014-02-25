#ifndef MOVE_H
#define MOVE_H

#include "wriggle.h"

// description: holds all of the information about a move.
//              considering adding prev space as well
struct Move
{
  Move();
  Move(int ind, int de, Parts pt, int dc, int dr);
  
  int index;
  int depth;
  int dcol;
  int drow;
  Parts part;
  int hVal; // set in getGraphMoves();
  vector<Wriggle> wrigglers; // fully updated list of wrigglers
                             // including the move, used for determining
                             // GSS searching and stuff
  // managed by GSS
  int parent;
  void setupWrigglers(vector<Wriggle>& wr);
  void setup(int ind, int de, Parts pt, int dc, int dr);
  Move &operator=(Move rhs);
  bool operator==(Move rhs) const;
};

ostream& operator<<(ostream& os, const Move &mv);

static bool operator<(const Move &lhs, const Move &rhs) {return lhs.hVal < rhs.hVal; }
static bool operator>(const Move &lhs, const Move &rhs) {return lhs.hVal > rhs.hVal; }
//bool operator()(const Move &lhs, const Move &rhs) {return lhs.hVal < rhs.hVal; }
#endif
