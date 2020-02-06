#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printStdin(void) {
  size_t n = 0;
  ssize_t isEnd = 0;
  char * line = NULL;
  size_t count = 0;
  char ** data = NULL;
  while ((isEnd = getline(&line, &n, stdin)) >= 0) {
    data = realloc(data, (count + 1) * sizeof(*data));
    data[count] = line;
    line = NULL;
    count++;
  }
  sortData(data, count);
  for (size_t j = 0; j < count; j++) {
    printf("%s", data[j]);
    free(data[j]);
  }
  free(data);
}

int main(int argc, char ** argv) {
  if (argc < 1) {
    fprintf(stderr, "Wrong argument number!");
    return EXIT_FAILURE;
  }

  if (argc == 1) {
    printStdin();
  }

  else {
    for (int i = 1; i < argc; i++) {
      char ** data = NULL;
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Could not open the file[i]!");
        return EXIT_FAILURE;
      }

      char * line = NULL;
      size_t n = 0;
      ssize_t isEnd = 0;
      size_t count = 0;
      while ((isEnd = getline(&line, &n, f)) >= 0) {
        data = realloc(data, (count + 1) * sizeof(*data));
        data[count] = line;
        line = NULL;
        count++;
      }
      free(line);
      sortData(data, count);
      for (size_t j = 0; j < count; j++) {
        printf("%s", data[j]);
        free(data[j]);
      }
      free(data);
      if (fclose(f) != 0) {
        fprintf(stderr, "Could not close the file[i]!");
        return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
