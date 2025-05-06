#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 1000

char compare_files(FILE *, FILE *);

int main(const int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Expected file nemes in args\n");
    return 1;
  }

  int page = 1;
  for (int i = 1; i < argc; i++) {
    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
      fprintf(stderr, "File '%s' is not found", file_name);
      return 1;
    }

    printf("%30s\n", file_name);

    char line[MAX_LINE_LEN];
    while (fscanf(file, "%[^\n]\n", line) > 0) {
      fputs(line, stdout);
      printf("\n");
    }

    printf("%30d\n", page++);
    fclose(file);
  }

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
