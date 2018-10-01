#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "Simulation.h"
#include "Grid.h"
#include "Boundary.h"
#include "ClassicBoundary.h"
#include "DoughnutBoundary.h"
#include "MirrorBoundary.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void Simulation::setSpecs() {
  // Query the user for a grid to initialize, the desired boundary mode, and
  // options for wait time between each generation.
  setGridConfig();
  setBoundaryMode();
  setTiming();
}

void Simulation::setGridConfig() {
  string config;
  cout << "Would you like a [random] configuration, or a [file] configuration? ";
  cin >> config;

  while (config != "random" and config != "file") {
    cout << "Invalid choice. Enter 'random' or 'file': ";
    cin >> config;
  }

  if (config == "random") {
    createRandomGrid();
  }
  else if (config == "file") {
    createGridFromFile();
  }
  else {
    throw "Invalid configuration";
  }
}

void Simulation::createRandomGrid() {
  unsigned int rows, cols;
  float lifeProb;

  cout << "How many rows would you like? ";
  cin >> rows;
  cout << "And how many columns would you like? ";
  cin >> cols;
  cout << "Finally, give the decimal probability of life for each cell: ";
  cin >> lifeProb;

  while (lifeProb > 1 or lifeProb < 0) {
    cout << "Remember, the probability must be between 0 and 1: ";
    cin >> lifeProb;
  }

  grid = Grid(rows, cols, lifeProb);
}

void Simulation::createGridFromFile() {
  string fileName = queryFileName();

  if (fileName == "back") {
    // Return to the start of the configuration process
    setGridConfig();
  }
  else {
    grid = Grid(fileName);
  }
}

string Simulation::queryFileName() const {
  string fileName;
  cout << "Please provide the file name or directory: ";
  cin >> fileName;

  while (!validFileName(fileName) and fileName != "back") {
    cout << "Sorry, this file does not exist. "
         << "Try another file name, or [back] to go back: ";
    cin >> fileName;
  }

  return fileName;
}

bool Simulation::validFileName(string name) const {
  // Returns true if the provided string exists as a file in the current dir
  std::ifstream file (name);
  if ( file.is_open() ) {
    return true;
    file.close();
  }
  return false;
}

void Simulation::setBoundaryMode() {
  string bType = queryBoundaryType();

  if (bType == "classic") {
    boundary = new ClassicBoundary(grid);
  }
  else if (bType == "doughnut") {
    boundary = new DoughnutBoundary(grid);
  }
  else if (bType == "mirror") {
    boundary = new MirrorBoundary(grid);
  }
  else {
    throw "Invalid Boundary Type";
  }
}

string Simulation::queryBoundaryType() const {
  string bType;
  cout << "Would you like the grid to have a [classic], [doughnut] or "
       << "[mirror] boundary? ";
  cin >> bType;

  while (bType != "classic" and bType != "doughnut" and bType != "mirror") {
    cout << "Please choose either 'classic', 'doughnut' or 'mirror': ";
    cin >> bType;
  }

  return bType;
}

void Simulation::setTiming() {
  // Sets the private fields 'waitForPrompt' and 'waitTime', which determine
  // (respectively) whether the simulation must wait for a prompt between each
  // life generation, and how many seconds the simulation should pause between
  // generations.

  string prompt;
  cout << "Would you like to be prompted between each generation? ";
  cin >> prompt;

  while (prompt != "yes" and prompt != "y" and prompt != "no" and prompt != "n") {
    cout << "Please enter 'yes' or 'no': ";
    cin >> prompt;
  }

  waitForPrompt = (prompt == "yes" or prompt == "y");

  if (!waitForPrompt) {
    cout << "How many seconds would you like to pause between generations? ";
    cin >> waitTime;
  }
}

void Simulation::start() {
  // Runs through and displays multiple rounds of the game of life, pausing
  // between each round and stopping only when an ending condition is met
  while ( !endingCondition() ) {
    displayRound();
    pause();
    updateGrid();
    updateBoundary();
    generation++;
  }
  // Display one last round to make clear what the end condition was
  displayRound();
}

void Simulation::displayRound() const {
  // Displays the generation number, the current grid, and an extra line break
  // for visibility
  cout << generation << endl;
  grid.display();
  cout << endl;
}

void Simulation::pause() const {
  // Executes the user-specified pause (either awaiting a prompt from the
  // user, or a fixed time length)
  if (waitForPrompt) {
    std::getchar();
  }
  else {
    usleep((int)(1000000*waitTime));
  }
}

void Simulation::updateGrid() {
  // Creates a new temporary grid, stores the next round elements (life or
  // death) within this grid, and the overwrites the original grid. Also
  // calculates number of cells changed/made alive, used for the purposes of
  // ending conditions.

  numChanged = 0;
  numAlive = 0;
  Grid newGrid(grid.getRows(), grid.getCols());

  for (int row=0; row < grid.getRows(); ++row) {
    for (int col=0; col < grid.getCols(); ++col) {
      updateElement(newGrid, row, col);
    }
  }
  grid = newGrid;
}

void Simulation::updateElement(Grid& newGrid, int row, int col) {
  int liveCount = countLiveNeighbors(row, col);
  char curElement = grid(row, col);
  char nextElement = getNextElement(curElement, liveCount);

  if (curElement != nextElement) {
    numChanged++;
  }
  if (nextElement == 'X') {
    numAlive++;
  }

  newGrid(row, col) = nextElement;
}

int Simulation::countLiveNeighbors(int row, int col) const {
  // Count the number of live cells in the neighborhood of the specified cell
  int tot = 0;
  for (int r = row-1; r <= row+1; ++r) {
    for (int c = col-1; c <= col+1; ++c) {
      if (element(r,c) == 'X') {
        tot++;
      }
    }
  }
  // We have included the cell as its own neighbor. We correct for this by
  // subtracting 1 if the cell added to the liveCount.
  if (grid(row, col) == 'X') {
    tot--;
  }

  // I like precautions...
  if (tot > 8 or tot < 0) {
    throw "Invalid live neighbor count";
  }

  return tot;
}

char Simulation::element(int r, int c) const {
  // Returns either the grid or boundary element at specified coordinate (r,c)
  if ( grid.isValidCoord(r,c) ) {
    return grid(r,c);
  }
  else {
    return (*boundary)(r,c);
  }
}

char Simulation::getNextElement(char cur, int liveCount) const {
  // Returns the corresponding life or death character based on the current
  // state of the cell and the state of its neighbors (number alive).
  if (liveCount <= 1 or liveCount >= 4) {
    return '-';
  }
  if (liveCount == 3) {
    return ('X');
  }
  if (liveCount == 2) {
    return cur;
  }
  throw "Missing liveCount case";
}

void Simulation::updateBoundary() {
  boundary->setGrid(grid);
}

bool Simulation::endingCondition() const {
  // Check if all cells are dead, or if nothing has changed from the previous
  // round.
  return (numAlive == 0 or numChanged == 0);
}
