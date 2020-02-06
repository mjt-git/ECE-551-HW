#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "fail to open the file");
    exit(EXIT_FAILURE);
  }
  char * name = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  char * nameNoNewline = NULL;
  while ((len = getline(&name, &sz, f)) >= 0) {
    nameNoNewline = realloc(nameNoNewline, len * sizeof(*nameNoNewline));
    strncpy(nameNoNewline, name, len - 1);
    nameNoNewline[len - 1] = '\0';
    char * val = lookupValue(kvPairs, nameNoNewline);
    addCount(c, val);
  }
  int close = 0;
  free(nameNoNewline);
  free(name);
  if ((close = fclose(f)) != 0) {
    fprintf(stderr, "fail to close the file");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 4) {
    fprintf(stderr, "The arguments number is wrong");
    exit(EXIT_FAILURE);
  }
  for (int j = 1; j < argc; j++) {
    if (argv[j] == NULL) {
      fprintf(stderr, "argv[%d] is NULL", j);
      exit(EXIT_FAILURE);
    }
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "fail to open the file");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    int close = 0;
    if ((close = fclose(f)) != 0) {
      fprintf(stderr, "fail to close the file");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
