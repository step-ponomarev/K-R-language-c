#ifndef MAP_H_
#define MAP_H_

#include "list.h"
#include <stddef.h>

typedef struct Map Map;

// val on stack
typedef struct MapEntry {
  const size_t size;
  const void *val;
} MapEntry;

Map *map_create();
void map_destroy(Map *);

void map_put(Map *, const MapEntry key, const MapEntry value);
void map_get(const Map *, const MapEntry key, void *dest);
char map_contains_key(const Map *, const MapEntry);
char map_remove(Map *, const MapEntry key);
int map_size(const Map *);
List *map_get_keys(const Map *);

#endif
