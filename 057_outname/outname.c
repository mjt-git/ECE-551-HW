#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  int num = 0;
  for (int i = 0; inputName[i] != '\0'; i++) {
    num++;
  }

  char * ret = malloc((num + 8) * sizeof(*ret));

  //   char * ret = malloc((num + 8) * sizeof(*ret));
  strncpy(ret, inputName, num);
  ret[num] = '\0';
  const char * suffix = ".counts";
  // strncpy(ret + num, suffix, 8);
  strcat(ret, suffix);
  return ret;
}
