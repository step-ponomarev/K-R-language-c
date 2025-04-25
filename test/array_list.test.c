#include "../src/lib/asserts.h"
#include "../src/lib/list.h"

void basicAddTest() {
  List *list = list_create(sizeof(int));
  const int count = 3;

  for (int i = 0; i < count; i++) {
    list_add(list, &i);
  }

  assertEquals("Check size after values added", count, list_size(list));

  for (int i = 0; i < count; i++) {
    int get;
    list_get_by_index(list, i, &get);

    assertEquals("Check element", i, get);
  }

  list_destroy(list);
}

void hugeAddTest() {
  List *list = list_create(sizeof(int));
  const int count = 300000;

  for (int i = 0; i < count; i++) {
    list_add(list, &i);
  }

  assertEquals("Check size after values added", count, list_size(list));
  for (int i = 0; i < count; i++) {
    int get;
    list_get_by_index(list, i, &get);

    assertEquals("Check element", i, get);
  }

  list_destroy(list);
}

void addByIndexTest() {
  List *list = list_create(sizeof(int));
  const int count = 13;

  for (int i = 0; i < count; i++) {
    list_add(list, &i);
  }

  int get;
  list_get_by_index(list, 11, &get);
  assertEquals("Get by index", 11, get);

  const int newVal = 44;
  list_add_by_index(list, 11, &newVal);
  list_get_by_index(list, 11, &get);

  assertEquals("Get after added by index", newVal, get);

  list_get_by_index(list, 12, &get);

  assertEquals("Check prev value moved", 11, get);
  assertEquals("Check new size", count + 1, list_size(list));

  list_destroy(list);
}

void removeTest() {
  List *list = list_create(sizeof(int));
  const int count = 12;

  for (int i = 0; i < count; i++) {
    list_add(list, &i);
  }

  list_remove(list, 10);
  assertEquals("Check size", count - 1, list_size(list));

  int get;
  list_get_by_index(list, 10, &get);
  assertEquals("Check element moved", 11, get);
}

void replaceTest() {
  List *list = list_create(sizeof(int));
  const int count = 12;

  for (int i = 0; i < count; i++) {
    list_add(list, &i);
  }

  const int newVal = 11;
  list_replace(list, 10, &newVal);
  assertEquals("Check size", count, list_size(list));

  int get;
  list_get_by_index(list, 9, &get);
  assertEquals("Check prev element", 9, get);

  list_get_by_index(list, 10, &get);
  assertEquals("Check replaced element", 11, get);

  list_get_by_index(list, 11, &get);
  assertEquals("Check next element", 11, get);
}

int main() {
  basicAddTest();
  hugeAddTest();
  addByIndexTest();
  removeTest();
  replaceTest();

  return 0;
}
