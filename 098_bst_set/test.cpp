#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> * set = new BstSet<int>();
  set->add(8);
  set->add(3);
  set->add(10);
  set->add(1);
  set->add(5);
  set->add(4);
  set->add(7);
  set->add(11);
  set->remove(3);
  set->remove(8);
  set->remove(10);
  set->remove(5);
  // set->remove(5);
  std::cout << set->contains(4) << "\n";

  // std::cout << set.lookup(1) << "\n";
  set->add(1);
  std::cout << set->contains(1) << "\n";

  BstSet<int> m2(*set);
  m2.add(20);
  std::cout << m2.contains(20) << "\n";
  BstSet<int> m3 = m2;
  m3.remove(7);
  m3.add(30);
  std::cout << m3.contains(30) << "\n";
  std::cout << m3.contains(7) << "\n";
  delete set;
  return EXIT_SUCCESS;
}
