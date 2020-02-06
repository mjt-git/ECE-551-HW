#include <assert.h>

#include <iostream>

#include "il.h"

void testList(void) {
  IntList llast = IntList();
  IntList l1 = IntList();
  IntList l2 = IntList();
  IntList l4 = IntList();

  l1.addFront(111);
  l1.addBack(2);
  assert(l1[0] == 111);
  l1.remove(111);
  assert(l1[0] == 2);

  l2.addFront(22);
  l1 = l2;
  assert(l1[0] == 22);

  IntList ltemp(l1);
  assert(ltemp[0] == 22);
  assert(l1.find(22) == 0);
  l4.addBack(23);
  l1[0] = l4[0];
  assert(l1[0] == 23);
  l1.~IntList();
  assert(llast.getSize() == 0);
}

int main() {
  testList();
  IntList ldel = IntList();
  ldel.~IntList();

  IntList l1 = IntList();

  return EXIT_SUCCESS;
}
