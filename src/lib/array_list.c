#include "array_list.h"
#include "stdlib.h"
#include <stddef.h>
#include <string.h>

#define INIT_CAPACITY 16
#define EXPAND_COEF 2

struct List {
  void *head;
  int capacity;
  int size;
  size_t elementSize;
};

List *list_create(size_t elementSize) {
  List *list = malloc(sizeof(List));
  list->head = malloc(elementSize * INIT_CAPACITY);
  list->capacity = INIT_CAPACITY;
  list->size = 0;
  list->elementSize = elementSize;

  return list;
}

void list_destroy(List *list) {
  if (!list) {
    return;
  }

  if (list->head) {
    free(list->head);
  }
}

void list_expand(List *list) {
  list->capacity *= EXPAND_COEF;
  list->head = realloc(list->head, list->capacity * list->elementSize);
}

void list_shrink(List *list) {
  list->capacity /= EXPAND_COEF;
  list->head = realloc(list->head, list->capacity * list->elementSize);
}

void list_add(List *list, const void *element) {
  if (list->size == list->capacity) {
    list_expand(list);
  }

  void *newElementAddr = list->head + (list->size * list->elementSize);
  memcpy(newElementAddr, element, list->elementSize);
  list->size++;
}

char list_add_by_index(List *list, int index, const void *element) {
  if (index >= list->size) {
    return 0;
  }

  if (list->size == list->capacity) {
    list_expand(list);
  }

  void *newElementAddr = list->head + (index * list->elementSize);

  const int delta = list->size - index;
  memcpy(newElementAddr + list->elementSize, newElementAddr,
         delta * list->elementSize);
  memcpy(newElementAddr, element, list->elementSize);
  list->size++;

  return 1;
}

char list_get_by_index(const List *list, const int index, void *dest) {
  if (index >= list->size) {
    return 0;
  }

  const void *newElementAddr = list->head + (index * list->elementSize);
  memcpy(dest, newElementAddr, list->elementSize);

  return 1;
}

char list_remove(List *list, const int index) {
  if (index >= list->size) {
    return 0;
  }

  if (list->size <= (list->capacity / 2)) {
    list_shrink(list);
  }

  void *pos = list->head + (index * list->elementSize);
  const int delta = list->size - index - 1;

  memcpy(pos, pos + list->elementSize, list->elementSize * delta);
  list->size--;

  return 0;
}

char list_replace(List *list, const int index, const void *element) {
  if (index >= list->size) {
    return 0;
  }

  void *elementAddr = list->head + (index * list->elementSize);
  memcpy(elementAddr, element, list->elementSize);

  return 1;
}

int list_size(const List *list) { return list->size; }
