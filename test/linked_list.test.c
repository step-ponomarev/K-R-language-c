#include "../src/lib/linked_list.h"
#include "../src/lib/asserts.h"
#include <stdio.h>

void testGetByIndex() {
  List *list = list_create(sizeof(int));

  const int expected = 122;
  list_add(list, &expected);
  assertEquals("Test size after addition", 1, list_size(list));

  int actual;
  list_get_by_index(list, 0, &actual);

  assertEquals("Test get by index", expected, actual);
  assertEquals("Test size after get", 1, list_size(list));

  list_destroy(list);
}

void testRemoveHead() {
  List *list = list_create(sizeof(int));

  const int expected = 122;
  list_add(list, &expected);

  int actual;
  list_remove_head(list, &actual);

  assertEquals("Test remove head", expected, actual);
  assertEquals("Test size after remove head", 0, list_size(list));

  list_destroy(list);
}

void testRemoveTail() {
  List *list = list_create(sizeof(int));

  const int expected = 122;
  list_add(list, &expected);

  int actual;
  list_remove_tail(list, &actual);

  assertEquals("Test remove tail", expected, actual);
  assertEquals("Test size after remove tail", 0, list_size(list));

  list_destroy(list);
}

void testRemoveHeadMoreData() {
  List *list = list_create(sizeof(int));

  int i = 0;
  while (i < 5) {
    list_add_by_index(list, 0, &i);
    i++;
  }

  char corrct = 1;
  while (list_size(list) > 0) {
    int val;
    list_remove_head(list, &val);
    corrct &= (val == --i);
  }

  assertEquals("Test data is correct after several head removal", 1, corrct);
  list_destroy(list);
}

void testRemoveTailMoreData() {
  List *list = list_create(sizeof(int));

  int i = 0;
  while (i < 5) {
    list_add_by_index(list, i, &i);
    i++;
  }

  char corrct = 1;
  while (list_size(list) > 0) {
    int val;
    list_remove_tail(list, &val);
    corrct &= (val == --i);
  }

  assertEquals("Test data is correct after several tail removal", 1, corrct);
  list_destroy(list);
}

void testHugeDataOperations() {
  List *list = list_create(sizeof(int));

  const int added = 200000;
  for (int i = 0; i < added; i++) {
    list_add(list, &i);
  }

  assertEquals("Test huge added", added, list_size(list));

  char equals = 1;
  for (int i = 0; i < added; i += 10) {
    int val;
    list_get_by_index(list, i, &val);
    equals = equals && (val == i);
  }
  assertEquals("Test data equals", 1, equals);

  const int newVal = -1;
  list_replace(list, 12, &newVal);

  int res;
  list_get_by_index(list, 12, &res);

  assertEquals("Test replace", newVal, res);

  list_remove(list, 12);
  list_get_by_index(list, 12, &res);
  assertEquals("Test remove N", 13, res);

  list_destroy(list);
}

int main() {
  testGetByIndex();
  testRemoveHead();
  testRemoveTail();
  testRemoveHeadMoreData();
  testRemoveTailMoreData();
  testHugeDataOperations();

  return 0;
}
