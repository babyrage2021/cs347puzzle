
#include "wriggle.h"
void Wriggle::setUp(int data[][2], int section)
{
  locs[HEAD][COL] = data[HEAD][COL];
  locs[HEAD][ROW] = data[HEAD][ROW];
  locs[TAIL][COL] = data[TAIL][COL];
  locs[TAIL][ROW] = data[TAIL][ROW];
  sections = section;
  
  return;
}

ostream& operator<<(ostream& os, Wriggle& w)
{
  os<<"[("<< w.locs[0][0]<<","<<w.locs[0][1]<<")(";
  os<<w.locs[1][0]<<","<<w.locs[1][1]<<") sect:";
  os<<w.sections<<"] ";
  return os;
}