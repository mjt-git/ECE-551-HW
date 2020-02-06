#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int iniHigh = high;
  int max = low;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (mid == iniHigh)
      break;
    int val = f->invoke(mid);
    if (val <= 0) {
      if (mid > max) {
        max = mid;
      }
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  return max;
}
