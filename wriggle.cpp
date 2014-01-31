
#include "wriggle.h"
void Wriggle::setUp(int data[][2])
{
  locs[HEAD][COL] = data[HEAD][COL];
  locs[HEAD][ROW] = data[HEAD][ROW];
  locs[TAIL][COL] = data[TAIL][COL];
  locs[TAIL][ROW] = data[TAIL][ROW];
  return;
}

ostream& operator<<(ostream& os, Wriggle& w)
{
  os<<"[("<< w.locs[HEAD][0]<<","<<w.locs[HEAD][1]<<")(";
  os<<w.locs[TAIL][0]<<","<<w.locs[TAIL][1]<<")] ";
  return os;
}