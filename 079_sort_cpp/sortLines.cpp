#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void ptinfsort(std::vector<std::string> vec) {
  std::sort(vec.begin(), vec.end());
  std::vector<std::string>::iterator it = vec.begin();
  while (it != vec.end()) {
    std::cout << *it << "\n";
    ++it;
  }
}

int main(int argc, char ** argv) {
  std::vector<std::string> vec;
  std::string tempstr;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::ifstream f(argv[i]);
      if (!f) {
        fprintf(stderr, "file open error");
        exit(EXIT_FAILURE);
      }
      if (f.is_open()) {
        while (std::getline(f, tempstr)) {
          vec.push_back(tempstr);
        }
      }
      ptinfsort(vec);
      vec.clear();
    }
  }
  else {
    if (std::cin.good()) {
      while (!std::cin.eof()) {
        std::getline(std::cin, tempstr);
        vec.push_back(tempstr);
      }
      ptinfsort(vec);
      vec.clear();
    }
    else {
      fprintf(stderr, "stdin read error");
      exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}
