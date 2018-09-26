#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <string>
#include "Grid.h"
#include "Boundary.h"

class Simulation {
public:
  Simulation() : generation(0) { }
  void setSpecs();
  void start();

private:
  Grid grid;
  Boundary* boundary;

  bool waitForPrompt;
  float waitTime;
  int generation;
  int numChanged;
  int numAlive;

  // Query and configuration methods
  void setGridConfig();
  void createRandomGrid();
  void createGridFromFile();
  std::string queryFileName() const;
  bool validFileName(std::string) const;
  void setBoundaryMode();
  std::string queryBoundaryType() const;
  void setTiming();

  // Display methods
  void displayRound() const;
  void pause() const;

  // Update methods
  void updateGrid();
  void updateBoundary();
  void updateElement(Grid&, int, int);
  int countLiveNeighbors(int, int) const;
  char element(int, int) const;
  char getNextElement(char, int) const;
  bool endingCondition() const;
};

#endif
