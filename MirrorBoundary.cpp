#include <iostream>
#include "MirrorBoundary.h"
#include "Boundary.h"

using std::max; using std::min;

char MirrorBoundary::operator ()(int r, int c) const {
  if ( !isValidCoord(r,c) ) {
    throw "Coordinate out of bounds";
  }

  r = max(0, min(grid.getRows()-1, r) );
  c = max(0, min(grid.getCols()-1, c) );

  return grid(r, c);
}
