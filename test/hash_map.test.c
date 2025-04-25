#include "../src/lib/asserts.h"
#include "../src/lib/map.h"
#include "string.h"

void basicPutTest() {
  Map *sut = map_create();

  const MapEntry key = {.size = 5, .val = "1234"};
  const MapEntry val = {.size = 5, .val = "4321"};
  map_put(sut, key, val);

  assertEquals("Check map size", 1, map_size(sut));
  assertEquals("Check map contains added key", 1, map_contains_key(sut, key));

  char res[val.size];
  map_get(sut, key, &res);

  assertEquals("Check added value", val.val, res);

  map_destroy(sut);
}

void basicReplaceTest() {
  Map *sut = map_create();

  const MapEntry key = {.size = 5, .val = "1234"};
  const MapEntry val = {.size = 5, .val = "4321"};
  map_put(sut, key, val);

  const MapEntry valToReplace = {.size = 9, .val = "No value"};
  map_put(sut, key, valToReplace);

  char res[valToReplace.size];
  map_get(sut, key, &res);

  assertEquals("Check replcaed value", valToReplace.val, res);
  assertEquals("Check map size", 1, map_size(sut));

  map_destroy(sut);
}

void basicRemoveTest() {
  Map *sut = map_create();

  const MapEntry key = {.size = 5, .val = "1234"};
  const MapEntry val = {.size = 5, .val = "4321"};
  map_put(sut, key, val);

  assertEquals("Check map size", 1, map_size(sut));

  map_remove(sut, key);
  assertEquals("Check map size", 0, map_size(sut));

  map_destroy(sut);
}

int main() {
  basicPutTest();
  basicReplaceTest();
  basicRemoveTest();

  return 0;
}
