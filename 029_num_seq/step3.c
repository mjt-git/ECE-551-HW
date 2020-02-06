// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return x * y + 2 * y - 3 * x;
}

void testSeq3(int x, int y) {
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int num = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        num++;
      }
    }
  }
  return num;
}

void testCount(int xLow, int xHi, int yLow, int yHi) {
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));
}

int main(void) {
  testSeq3(0, 0);
  testSeq3(2, 3);
  testSeq3(3, 8);
  testSeq3(-1, 0);
  testSeq3(0, 9);
  testSeq3(8, 0);
  testSeq3(-3, -10);

  testCount(0, 2, 0, 3);
  testCount(3, 2, 0, 3);
  testCount(0, 2, 9, 3);
  testCount(4, 6, -4, -3);
  testCount(-4, -3, 2, 4);

  return 1;
}
