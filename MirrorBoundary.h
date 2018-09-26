#ifndef _MIRROR_BOUNDARY_H
#define _MIRROR_BOUNDARY_H

#include "Boundary.h"
#include "Grid.h"

class MirrorBoundary : public Boundary {
public:
  MirrorBoundary(const Grid& g) : Boundary(g) {}
  char operator ()(int,int) const;
};

#endif
