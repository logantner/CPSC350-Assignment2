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
  data = new char*[numRows];
  for (int i=0; i<numRows; ++i) {
    data[i] = new char[numCols];
  }
}

void Grid::writeDataFromFile(std::ifstream& f) {
  for (int r=0; r < numRows; ++r) {
    for (int c=0; c < numCols; ++c) {
      f.get(data[r][c]);
    }
    f.ignore();
  }
}

void Grid::writeDataRandomly(float lifeProb) {
  for (int r=0; r<numRows; ++r) {
    for (int c=0; c<numCols; ++c) {
      data[r][c] = randomCell(lifeProb);
    }
  }
}

char Grid::randomCell(float lifeProb) const {
  float roll = (float)rand()/RAND_MAX;
  if (roll < lifeProb) {
    return 'X';
  }
  return '-';
}

Grid::~Grid() {
  for (int i=0; i<numRows; ++i) {
    delete[] data[i];
  }
  delete[] data;
}

void Grid::display() const {
  for (int r=0; r < numRows; ++r) {
    for (int c=0; c < numCols; ++c) {
      std::cout << data[r][c];
    }
    std::cout << std::endl;
  }
}

bool Grid::isValidCoord(int r, int c) const {
  return (r >= 0 and c >= 0 and r < numRows and c < numCols);
}
