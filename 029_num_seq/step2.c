// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  if ((2 - x) % 4 == 0) {
    return 2 * x;
  }
  else {
    return x * x + 3 * x + 1;
  }
}

void testSeq2(int x) {
  int res = seq2(x);
  printf("seq2(%d) = %d\n", x, res);
}

int sumSeq2(int low, int high) {
  int sum = 0;
  for (int i = low; i < high; i++) {
    sum += seq2(i);
  }
  return sum;
}

void testSumSeq2(int low, int high) {
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
}

int main(void) {
  testSeq2(0);
  testSeq2(1);
  testSeq2(2);
  testSeq2(-3);
  testSeq2(-4);
  testSeq2(10);
  testSeq2(13);

  testSumSeq2(0, 2);
  testSumSeq2(3, 6);
  testSumSeq2(-3, 5);
  testSumSeq2(9, 7);
  testSumSeq2(5, 5);

  return 1;
}
