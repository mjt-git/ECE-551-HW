#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->arr = NULL;
  counts->arrSize = 0;
  counts->unknownNum = 0;
  return counts;
}

int existed(counts_t * c, const char * name) {
  for (int i = 0; i < c->arrSize; i++) {
    if (strcmp(c->arr[i].key, name) == 0) {
      return 1;
    }
  }
  return 0;
}

void increCount(counts_t * c, const char * name) {
  for (int i = 0; i < c->arrSize; i++) {
    if (strcmp(c->arr[i].key, name) == 0) {
      c->arr[i].num++;
    }
  }
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknownNum++;
  }
  else if (existed(c, name) == 1) {
    increCount(c, name);
  }
  else {  // the name is new
    c->arrSize++;
    c->arr = realloc(c->arr, (c->arrSize) * sizeof(*(c->arr)));
    c->arr[c->arrSize - 1].key = name;
    c->arr[c->arrSize - 1].num = 1;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  for (int i = 0; i < c->arrSize; i++) {
    fprintf(outFile, "%s: %d\n", c->arr[i].key, c->arr[i].num);
  }
  if (c->unknownNum != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknownNum);
  }
}

void freeCounts(counts_t * c) {
  free(c->arr);
  free(c);
}
