#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___
#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows() {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r) {
    for (int i = 0; i < r; i++) {
      rows[i].resize(c);
    }
  }
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.numRows) {
    for (int i = 0; i < rhs.numRows; i++) {
      rows[i].resize(rhs.numColumns);
      for (int j = 0; j < rhs.numColumns; j++) {
        rows[i][j] = rhs[i][j];
      }
    }
  }
  ~Matrix() {}
  /*
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    }  */
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<std::vector<T> > temp(rhs.numRows);
      for (int i = 0; i < rhs.numRows; i++) {
        temp[i].resize(rhs.numColumns);
        for (int j = 0; j < rhs.numColumns; j++) {
          temp[i][j] = rhs[i][j];
        }
      }
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = temp;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    //const std::vector<T> & ret = rows[index];
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    //    std::vector<T> & ret = rows[index];
    return rows[index];
  }
  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }
    if (numColumns != rhs.numColumns) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if (rows[i][j] != rhs[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix ret(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ret[i][j] = rows[i][j] + rhs[i][j];
      }
    }
    return ret;
    /*    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        rows[i][j] = rows[i][j] + rhs[i][j];
      }
    }
    return *this;*/
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  char bracket1[2] = {'[', ' '};
  char bracket2[2] = {' ', ']'};
  s.write(bracket1, 2);
  for (int i = 0; i < rhs.getRows(); i++) {
    s << "{";
    for (int j = 0; j < rhs.getColumns(); j++) {
      s << rhs[i][j];
      if (j != rhs.getColumns() - 1) {
        s << ", ";
      }
    }
    if (i != rhs.getRows() - 1) {
      s << "},\n";
    }
    else {
      s << "}";
    }
  }

  s.write(bracket2, 2);
  return s;
}

#endif
