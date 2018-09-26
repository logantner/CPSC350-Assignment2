#ifndef _CLASSIC_BOUNDARY_H
#define _CLASSIC_BOUNDARY_H

#include "Boundary.h"
#include "Grid.h"

class ClassicBoundary : public Boundary {
public:
  ClassicBoundary(const Grid& g) : Boundary(g) {}
  char operator ()(int,int) const;
};

#endif
