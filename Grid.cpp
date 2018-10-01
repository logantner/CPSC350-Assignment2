#include <iostream>
#include <fstream>
#include <string>
#include "Grid.h"

Grid::Grid(std::string fName) {
  // Initialize data based on the contents of provided file directory
  std::ifstream inFile (fName);
  inFile >> numRows >> numCols;
  inFile.ignore();

  initializeData();
  writeDataFromFile(inFile);

  inFile.close();
}

Grid::Grid(int rows, int cols) : numRows(rows), numCols(cols) {
  // Initialize data of specified dimension, but does not assign specific cells
  initializeData();
}

Grid::Grid(int rows, int cols, float lifeProb) : numRows(rows), numCols(cols)  {
  // Initialize data of specified dimension, assigning initiL life cells
  // randomly based on the provided probability
  initializeData();
  writeDataRandomly(lifeProb);
}

void Grid::initializeData() {
  // Checks the row and columns fields and creates a new 2D array without
  // setting any default values
  data = new char*[numRows];
  for (int i=0; i<numRows; ++i) {
    data[i] = new char[numCols];
  }
}

void Grid::writeDataFromFile(std::ifstream& f) {
  // Writes into data array from a specified file
  for (int r=0; r < numRows; ++r) {
    for (int c=0; c < numCols; ++c) {
      f >> data[r][c];
      // f.get(data[r][c]);
    }
    f.ignore(); // Skips to the end of current line
  }
}

void Grid::writeDataRandomly(float lifeProb) {
  // Given a probability of life, assigns an initial state to each cell in
  // the data array
  for (int r=0; r<numRows; ++r) {
    for (int c=0; c<numCols; ++c) {
      data[r][c] = randomCell(lifeProb);
    }
  }
}

char Grid::randomCell(float lifeProb) const {
  // Returns the life char with specified probability; otherwise returns the
  // death char.
  float roll = (float)rand()/RAND_MAX;
  if (roll < lifeProb) {
    return 'X';
  }
  return '-';
}

Grid::~Grid() {
  // Safely deletes the 2D data array, one row at a time.
  for (int i=0; i<numRows; ++i) {
    delete[] data[i];
  }
  delete[] data;
}

Grid::Grid(const Grid& g) {
  numRows = g.numRows;
  numCols = g.numCols;
  initializeData();

  for (int r=0; r < numRows; ++r) {
    for (int c=0; c < numCols; ++c) {
      data[r][c] = g.data[r][c];
    }
  }
}

Grid& Grid::operator = (const Grid& g) {
  numRows = g.numRows;
  numCols = g.numCols;
  initializeData();

  for (int r=0; r < numRows; ++r) {
    for (int c=0; c < numCols; ++c) {
      data[r][c] = g.data[r][c];
    }
  }

  return *this;
}

void Grid::display() const {
  // Write the contents of the data array to the terminal, one char at a time.
  for (int r=0; r < numRows; ++r) {
    for (int c=0; c < numCols; ++c) {
      std::cout << data[r][c];
    }
    std::cout << std::endl;
  }
}

bool Grid::isValidCoord(int r, int c) const {
  // Returns true if the coordinate could be contained within the current grid.
  return (r >= 0 and c >= 0 and r < numRows and c < numCols);
}
