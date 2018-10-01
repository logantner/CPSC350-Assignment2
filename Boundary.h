#ifndef _BOUNDARY_H_
#define _BOUNDARY_H_

#include "Grid.h"

class Boundary {
public:
  Boundary(const Grid&);
  virtual ~Boundary() {}
  virtual char operator ()(int,int) const = 0;
  void setGrid(const Grid&);
  void display();
protected:
  Grid grid;
  bool isValidCoord(int, int) const;
};

#endif
