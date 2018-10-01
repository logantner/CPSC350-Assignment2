#ifndef _GRID_H_
#define _GRID_H_

#include<fstream>
#include<string>

class Grid {
public:
  Grid() {}
  Grid(std::string);
  Grid(int, int);
  Grid(int, int, float);
  ~Grid();

  // Copy constructor
  Grid(const Grid&);
  // Assignment operator
  Grid& operator = (const Grid&);

  void display() const;
  bool isValidCoord(int, int) const;
  // Getter and setter for matrix data
  char operator ()(int r, int c) const { return data[r][c]; }
  char& operator ()(int r, int c) { return data[r][c]; }

  char get(int r, int c) const { return data[r][c]; }
  // Getters for dimensions
  int getRows() const { return numRows; }
  int getCols() const { return numCols; }

private:
  int numRows;
  int numCols;
  char** data;

  void initializeData();
  void writeDataFromFile(std::ifstream&);
  void writeDataRandomly(float);
  char randomCell(float) const;
};

#endif
