#include <iostream>
#include "Boundary.h"
#include "Grid.h"

using std::cout;
using std::endl;

Boundary::Boundary(const Grid& g) {
  grid = g;
}

bool Boundary::isValidCoord(int r, int c) const {
  if (r < -1 or r > grid.getRows()) {
    return false;
  }
  if (c < -1 or c > grid.getCols()) {
    return false;
  }
  return ( r == -1 or c == -1 or r == grid.getRows() or c == grid.getCols() );
}

void Boundary::setGrid(const Grid& newGrid) {
  grid = newGrid;
}

void Boundary::display() {
  for (int r = -1; r <= grid.getRows(); ++r) {
    for (int c = -1; c <= grid.getCols(); ++c) {
      if (grid.isValidCoord(r,c)) {
        cout << ' ';
      } else {
        cout << (*this)(r,c);
      }
    }
    cout << endl;
  }
}
