#include "../lib/iolib.h"
#include "../lib/map.h"
#include "../lib/sort.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000
// MAX HEAP было бы очень кстати
void add_word(Map *map, const char *word, const size_t size) {
  char wordcpy[size + 1];
  for (int i = 0; i < size; i++) {
    wordcpy[i] = *word;
    word++;
  }
  wordcpy[size] = '\0';

  const MapEntry key = {.val = (void *)wordcpy, .size = size + 1};
  int count;
  if (map_contains_key(map, key)) {
    map_get(map, key, &count);
  } else {
    count = 0;
  }
  count++;

  const MapEntry value = {.val = &count, .size = sizeof(int)};
  map_put(map, key, value);
}

void add_words(Map *words_to_lines, const char *line) {

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
      add_word(words_to_lines, word_start, i);
    }
  }
}

typedef struct WordWithCount {
  char *word;
  int count;
} WordWithCount;

int compare(WordWithCount l, WordWithCount r) {
  if (l.count == r.count) {
    return 0;
  }

  return l.count < r.count ? -1 : 1;
}

void fill_words(const List *keys, const Map *word_to_count, const size_t size,
                WordWithCount *words) {
  for (int i = 0; i < size; i++) {
    MapEntry key;
    list_get_by_index(keys, i, &key);

    int count;
    const char *word = key.val;

    map_get(word_to_count, key, &count);

    WordWithCount word_with_count = {
        .count = count,
    };

    word_with_count.word = malloc(sizeof(char) * key.size);
    memcpy(word_with_count.word, word, key.size);

    words[i] = word_with_count;
  }
}

int main() {
  Map *word_to_count = map_create();
  int len;
  char line[MAX_LINE_LEN];

  while ((len = readline(line) > 0)) {
    add_words(word_to_count, line);
  }

  List *keys = map_get_keys(word_to_count);
  const size_t word_count = list_size(keys);

  WordWithCount words[word_count];
  fill_words(keys, word_to_count, word_count, words);

  qsort(words, sizeof(WordWithCount), word_count, (Comparator *)&compare);

  for (int i = 0; i < word_count; i++) {
    printf("%d : %s\n", words[i].count, words[i].word);
    free(words[i].word);
  }

  list_destroy(keys);
  map_destroy(word_to_count);

  return 0;
}
