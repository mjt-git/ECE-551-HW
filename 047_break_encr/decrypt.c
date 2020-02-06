#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int decrypt(FILE * f) {
  int c;
  int count[26];

  for (int i = 0; i < 26; i++) {
    count[i] = 0;
  }

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      int num = c - 'a';
      count[num]++;
    }
  }

  int maxId = 0;
  int max = 0;
  for (int j = 0; j < 26; j++) {
    if (count[j] >= max) {
      max = count[j];
      maxId = j;
    }
  }

  return (maxId + 22) % 26;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of Argument!");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open the file");
    return EXIT_FAILURE;
  }
  int key = decrypt(f);
  printf("%d\n", key);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
