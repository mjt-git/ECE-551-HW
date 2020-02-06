#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream f;
  f.open(fname);
  uint64_t * arr = new uint64_t[257];

  for (int i = 0; i < 257; i++) {
    arr[i] = 0;
  }
  if (f.is_open()) {
    int c;
    while ((c = f.get()) != EOF) {
      // uint64_t val = uint64_t(c);
      arr[c]++;
    }
    arr[256] = 1;
  }
  else {
    fprintf(stderr, "file can't opened!\n");
  }
  f.close();
  return arr;
  /* FILE * f;
  f = fopen(fname, "r");
  int c;
  uint64_t * arr = new uint64_t[257];
  for (int i = 0; i < 257; i++) {
    arr[i] = 0;
  }
  if (f != NULL) {
    while ((c = getc(f)) != EOF) {
      // uint64_t val = uint64_t(c);
      arr[c]++;
    }
    arr[256] = 1;
  }
  else {
    fprintf(stderr, "file can't opened!\n");
  }
  fclose(f);
  return arr;  */
}
