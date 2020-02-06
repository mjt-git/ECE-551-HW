#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class linearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg + 1; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int n = log(high - low) / log(2) + 1;
  /*
  if (f->invoke(low) > 0 || f->invoke(high) < 0) {
    n = 1;
  }
  else {
    n = log(high - low) / log(2) + 1;
    } */
  CountedIntFn * c = new CountedIntFn(n, f, mesg);
  int result = binarySearchForZero(c, low, high);
  assert(result == expected_ans);
}

int main() {
  SinFunction * sin = new SinFunction();
  check(sin, 0, 150000, 52359, "test sinfunction");
  linearFunction * linear = new linearFunction();
  check(linear, -3, 4, -1, "test linear normal");
  check(linear, 2, 4, 2, "test linear all positive");
  check(linear, -9, -3, -4, "test linear all negative");
  check(linear, 5, 5, 5, "test linear all positive and low==high");
  return EXIT_SUCCESS;
}
