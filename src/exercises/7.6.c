#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 1000

char compare_files(FILE *, FILE *);

int main(const int argc, const char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Expected two file nemes in args\n");
    return 1;
  }

  const char *file_name_1 = argv[1];
  FILE *file1 = fopen(file_name_1, "r");
  if (file1 == NULL) {
    fprintf(stderr, "File '%s' is not found", file_name_1);
    return 1;
  }

  const char *file_name_2 = argv[2];
  FILE *file2 = fopen(file_name_2, "r");
  if (file2 == NULL) {
    fprintf(stderr, "File '%s' is not found", file_name_2);
    return 1;
  }

  if (compare_files(file1, file2)) {
    printf("Files are equal\n");
    return 0;
  }

  char line[MAX_LINE_LEN];
  fgets(line, MAX_LINE_LEN, file1);

  printf("Files are not equal! Different lines:\n");
  printf("%s: %s", file_name_1, line);

  fgets(line, MAX_LINE_LEN, file2);
  printf("%s: %s", file_name_2, line);

  fclose(file1);
  fclose(file2);

  return 0;
}

char compare_files(FILE *f1, FILE *f2) {
  register int ch1;
  register int ch2;
  while ((ch1 = getc(f1)) == (ch2 = getc(f2))) {
    if (ch1 == EOF) {
      return 1;
    }
  }

  ungetc(ch1, f1);
  ungetc(ch2, f2);

  return 0;
}
