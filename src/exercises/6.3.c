#include "../lib/iolib.h"
#include "../lib/list.h"
#include "../lib/map.h"
#include "../lib/tree.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 1000

void add_word(Map *map, const char *word, const size_t size,
              const size_t line_number) {
  char wordcpy[size + 1];
  for (int i = 0; i < size; i++) {
    wordcpy[i] = *word;
    word++;
  }
  wordcpy[size] = '\0';

  const MapEntry key = {.val = (void *)wordcpy, .size = size + 1};

  Tree *numbers;
  if (map_contains_key(map, key)) {
    map_get(map, key, &numbers);
  } else {
    numbers = tree_create();
  }

  tree_add(numbers, &line_number, sizeof(size_t));

  const MapEntry value = {.val = &numbers, .size = sizeof(Tree *)};
  map_put(map, key, value);
}

void add_words(Map *words_to_lines, const char *line,
               const size_t line_number) {

  while (*line != '\0') {
    size_t i = 0;
    while (*line != '\0' && isspace(*line)) {
      line++;
    }

    const char *word_start = line;
    while (*line != '\0' && !isspace(*line)) {
      i++;
      line++;
    }

    if (i > 0) {
      add_word(words_to_lines, word_start, i, line_number);
    }
  }
}

void print_lines(const TreeNode *node) {
  if (node == NULL) {
    return;
  }

  print_lines(node->left);

  size_t line;
  memcpy(&line, node->value.value, sizeof(size_t));
  printf("%d, ", line);
  print_lines(node->right);
}

int main() {
  Map *word_to_line_numbers = map_create();

  size_t line_number = 1;
  int len;
  char line[MAX_LINE_LEN];

  while ((len = readline(line) > 0)) {
    add_words(word_to_line_numbers, line, line_number++);
  }

  List *keys = map_get_keys(word_to_line_numbers);
  for (int i = 0; i < list_size(keys); i++) {
    MapEntry key;
    list_get_by_index(keys, i, &key);

    const char *word = key.val;
    Tree *lines;
    map_get(word_to_line_numbers, key, &lines);

    printf("Word '%s' found on lines: ", word);
    print_lines(tree_get_root(lines));
    printf("\b\b\n");
  }

  list_destroy(keys);
  map_destroy(word_to_line_numbers);
  return 0;
}
