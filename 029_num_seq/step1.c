// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  int ret = 4 * x - 3;
  return ret;
}

void testSeq1(int x) {
  int res = seq1(x);
  printf("seq1(%d) = %d\n", x, res);
}

void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int i = low; i < high; i++) {
      printf("%d", seq1(i));
      if (i < high - 1) {
        printf(", ");
      }
    }
    printf("\n");
  }
}

void testSeq1Range(int low, int high) {
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
}

int main(void) {
  testSeq1(0);
  testSeq1(1);
  testSeq1(-1);
  testSeq1(-4);
  testSeq1(5);

  testSeq1Range(0, 0);
  testSeq1Range(-2, 6);
  testSeq1Range(6, -2);
  testSeq1Range(1, 5);
  testSeq1Range(1, 1);

  return 1;
}
