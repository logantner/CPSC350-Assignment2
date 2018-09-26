#include <iostream>
#include "DoughnutBoundary.h"
// #include "Boundary.h"

char DoughnutBoundary::operator ()(int r, int c) const {
  if ( !isValidCoord(r,c) ) {
    throw "Coordinate out of bounds";
  }

  int rows = grid.getRows();
  int cols = grid.getCols();

  if (r == -1) {
    r = rows - 1;
  }
  else if (r == rows) {
    r = 0;
  }

  if (c == -1) {
    c = cols - 1;
  }
  else if (c == cols) {
    c = 0;
  }

  return grid(r,c);
  // return grid(((r%rows) + rows) % rows, ((c%cols) + cols) % cols);
}
