#include "Simulation.h"
#include "Grid.h"

int main(int argc, char** argv) {

  Simulation sim;
  sim.setSpecs();
  sim.start();

  return 0;
}
