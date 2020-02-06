#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned res = power(x, y);
  if (res != expected_ans) {
    printf("power(%d, %d) != %d\n", x, y, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 3, 0);
  run_check(2, 3, 8);
  run_check(1, 3, 1);
  run_check(0, 3, 0);
  run_check(1000, 3, 1000000000);
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(4, 0, 1);
  return EXIT_SUCCESS;
}
