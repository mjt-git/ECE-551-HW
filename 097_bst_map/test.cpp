#include <cstdlib>
#include <iostream>
#include <string>

#include "bstmap.h"

int main() {
  BstMap<int, std::string> * map = new BstMap<int, std::string>();
  map->add(8, "s8");
  map->add(3, "s3");
  map->add(10, "s10");
  map->add(1, "s1");
  map->add(5, "s5");
  map->add(4, "s4");
  map->add(7, "s7");
  map->add(11, "s11");
  map->remove(3);
  map->remove(8);
  map->remove(10);
  map->remove(5);
  // map->remove(5);
  std::cout << map->lookup(4) << "\n";

  // std::cout << map.lookup(1) << "\n";
  map->add(1, "ss1");
  std::cout << map->lookup(1) << "\n";

  BstMap<int, std::string> m2(*map);
  m2.add(20, "s20");
  std::cout << m2.lookup(20) << "\n";
  BstMap<int, std::string> m3 = m2;
  m3.remove(7);
  m3.add(30, "s30");
  std::cout << m3.lookup(30) << "\n";
  std::cout << m3.lookup(7) << "\n";
  delete map;
  return EXIT_SUCCESS;
}
