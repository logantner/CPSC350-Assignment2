#ifndef _DOUGHNUT_BOUNDARY_H
#define _DOUGHNUT_BOUNDARY_H

#include "Boundary.h"
#include "Grid.h"

class DoughnutBoundary : public Boundary {
public:
  DoughnutBoundary(const Grid& g) : Boundary(g) {}
  char operator ()(int,int) const;
};

#endif
