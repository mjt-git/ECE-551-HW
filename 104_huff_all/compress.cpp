#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  std::ifstream f;
  f.open(inFile);
  if (!f.is_open()) {
    std::cerr << "can't open the file!"
              << "\n";
  }
  int c;
  while ((c = f.get()) != EOF) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(c);
    if (it == theMap.end()) {
      std::cerr << "character " << c << "is not in the map"
                << "\n";
    }
    bfw.writeBitString(it->second);
  }
  std::map<unsigned, BitString>::const_iterator eofIt = theMap.find(256);
  bfw.writeBitString(eofIt->second);
  f.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  uint64_t * count = readFrequencies(argv[1]);
  Node * root = buildTree(count);
  BitString b;
  std::map<unsigned int, BitString> theMap;
  root->buildMap(b, theMap);
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete[] count;
  // deleteNode(root);
  delete root;
  return EXIT_SUCCESS;
}
