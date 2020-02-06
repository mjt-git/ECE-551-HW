#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void printMatrix(char matrix[][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

void rotate(char matrix[][10]) {
  char newMatrix[10][10];

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      newMatrix[i][j] = ' ';
    }
  }

  for (int i = 0; i < 10; i++) {    // i: column
    for (int j = 9; j >= 0; j--) {  // j: row
      newMatrix[i][9 - j] = matrix[j][i];
    }
  }
  printMatrix(newMatrix);
}

int main(int argc, char ** argv) {
  if (argc != 2) {  // check arg number
    fprintf(stderr, "Wrong argument number!");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {  // check if file is NULL
    fprintf(stderr, "File does not exist!");
    return EXIT_FAILURE;
  }

  char matrix[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = ' ';
    }
  }
  int c = 0;
  int i = 0;
  int j = 0;
  int num = 0;
  while ((c = fgetc(f)) != EOF) {
    num++;

    if (num > 110) {
      fprintf(stderr, "too long!");
      return EXIT_FAILURE;
    }

    if (c == '\n' && num % 11 != 0) {
      fprintf(stderr, "Should not be an '\n'!");
      return EXIT_FAILURE;
    }

    if (num % 11 == 0 && c != '\n') {
      fprintf(stderr, "Should be an '\n'!");
      return EXIT_FAILURE;
    }

    if (c > 127 || c < -128) {
      fprintf(stderr, "Unrecognizable char!");
      return EXIT_FAILURE;
    }

    if (c == '\n') {
      if (j != 10) {
        fprintf(stderr, "Wrong number of column!");
        return EXIT_FAILURE;
      }
      i++;
      j = 0;
      continue;
    }
    matrix[i][j] = c;
    j++;
  }
  if (i != 10) {
    fprintf(stderr, "Wrong number of row!");
    return EXIT_FAILURE;
  }
  /*
  if (num != 110) {
    fprintf(stderr, "Wrong number of row!");
    return EXIT_FAILURE;
    }  */

  if (num != 110) {
    fprintf(stderr, "too short!");
    return EXIT_FAILURE;
  }

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close files");
    return EXIT_FAILURE;
  }

  rotate(matrix);
  return EXIT_SUCCESS;
}
