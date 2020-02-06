#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  unsigned ret = 1;
  unsigned curMax = 1;
  for (unsigned i = 0; i < n - 1; i++) {
    if (*(array + i + 1) > *(array + i)) {
      ret++;
      if (ret > curMax) {
        curMax = ret;
      }
    }
    else {
      ret = 1;
    }
  }
  return curMax;
}
