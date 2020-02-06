#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void helper(int * array, size_t n, size_t expectedNum) {
  size_t res = maxSeq(array, n);
  if (res != expectedNum) {
    printf("for array = {");
    for (int i = 0; i < n; i++) {
      printf("%d, ", *(array + i));
    }
    printf("}\n");
    printf("the outcome should be %ld, but is %ld\n", expectedNum, res);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[5] = {2, 1, 3, 5, 4};
  int array[0];
  int a[3] = {1, 2, 3};
  int a1[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int a2[4] = {2, 2, 2, 2};
  int a3[6] = {1, 1, 2, 2, 3, 3};

  helper(array, 0, 0);
  helper(array1, 5, 3);
  helper(a, 3, 3);
  helper(a1, 10, 4);

  helper(a2, 4, 1);

  helper(a3, 6, 2);
  int a4[4] = {5, 3, 2, 1};
  helper(a4, 4, 1);
  int a5[4] = {5, -3, 2, 1};
  helper(a5, 4, 2);
  int a6[1] = {5};
  helper(a6, 1, 1);
  int a7[8] = {-5, -3, -4, 0, 2, 5, 3, 5};
  helper(a7, 8, 4);
  int a8[6] = {3, 3, 3, 5, 7, 8};
  helper(a8, 6, 4);

  exit(EXIT_SUCCESS);
}
