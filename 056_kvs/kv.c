#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * fetchStr(size_t len, char * line, size_t startIdx) {
  char * str = malloc(len * sizeof(*str));
  for (size_t j = 0; j < len - 1; j++) {
    str[j] = line[startIdx + j];
  }
  str[len - 1] = '\0';
  return str;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  char * line = NULL;
  size_t sz = 0;
  int num = 0;
  kvarray_t * kvArr = malloc(sizeof(*kvArr));
  kvArr->kvpairArr = NULL;
  ssize_t flag = 0;
  size_t semiIdx = 0;  // index of semicolom
  while ((flag = getline(&line, &sz, f)) >= 0) {
    for (size_t i = 0; line[i] != '\n'; i++) {
      if (line[i] == '=') {
        semiIdx = i;
        break;
      }
    }
    size_t totalLen = 0;
    size_t id = 0;
    while (line[id] != '\n') {
      totalLen++;
      id++;
    }
    char * key = fetchStr(semiIdx + 1, line, 0);
    char * value = fetchStr(totalLen - semiIdx, line, semiIdx + 1);
    kvArr->kvpairArr = realloc(kvArr->kvpairArr, (num + 1) * sizeof(*kvArr->kvpairArr));
    kvArr->kvpairArr[num].key = key;
    kvArr->kvpairArr[num].value = value;
    num++;
  }
  free(line);
  kvArr->length = num;
  int closeRes = 0;
  if ((closeRes = fclose(f)) != 0) {
    fprintf(stderr, "Fail to close the file");
    exit(EXIT_FAILURE);
  }
  return kvArr;
}

void freeKVs(kvarray_t * pairs) {
  int len = pairs->length;
  for (int i = 0; i < len; i++) {
    free(pairs->kvpairArr[i].key);
    free(pairs->kvpairArr[i].value);
  }
  free(pairs->kvpairArr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  int len = pairs->length;
  for (int i = 0; i < len; i++) {
    printf(
        "key = '%s' value = '%s'\n", pairs->kvpairArr[i].key, pairs->kvpairArr[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  char * ret = NULL;
  int len = pairs->length;
  for (int i = 0; i < len; i++) {
    if (strcmp(pairs->kvpairArr[i].key, key) == 0) {
      ret = pairs->kvpairArr[i].value;
    }
  }
  return ret;
}
