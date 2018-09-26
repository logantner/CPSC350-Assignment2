#include "ClassicBoundary.h"
#include "Boundary.h"

char ClassicBoundary::operator ()(int r, int c) const {
  if ( !isValidCoord(r,c) ) {
    throw "Coordinate out of bounds";
  }
  return '-';
}
