#include "IntArray.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index <= numElements - 1);
  const int & ret = data[index];
  return ret;
}

int & IntArray::operator[](int index) {
  assert(index >= 0 && index <= numElements - 1);
  int & ret = data[index];
  return ret;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  bool flag = true;
  if (rhs.numElements != numElements) {
    flag = false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      flag = false;
      break;
    }
  }
  return flag;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (rhs.numElements != numElements) {
    return true;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return true;
    }
  }
  return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  char brace1[1] = {'{'};
  char brace2[1] = {'}'};
  char commaSpace[2] = {',', ' '};
  s.write(brace1, 1);
  int l;
  for (int i = 0; i < rhs.size(); i++) {
    int item = rhs[i];
    char str[16];
    l = snprintf(str, 16, "%d", item);
    if (l >= 0 && l <= 16) {
      s.write(str, strlen(str));
    }
    if (i != rhs.size() - 1) {
      s.write(commaSpace, 2);
    }
  }
  s.write(brace2, 1);
  return s;
}
