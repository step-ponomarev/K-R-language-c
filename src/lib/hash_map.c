#include "hash_map.h"
#include "list.h"
#include "stdlib.h"
#include "string.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE_BYTES 16
#define INITIAL_BUCKET_COUNT 16

struct Map {
  size_t element_count;
  List **buckets;
  size_t bucket_count;
};

typedef struct MapNodeKey {
  // size <= KEY_SIZE_BYTES ? key : adr
  union {
    char key[KEY_SIZE_BYTES];
    void *keyAdr;
  };

  const size_t size;
  const int hash;
} MapNodeKey;

typedef struct MapNodeValue {
  void *val;
  const size_t size;
} MapNodeValue;

typedef struct Node {
  struct MapNodeKey key;
  struct MapNodeValue value;
} Node;

int get_hash(const char val[], const size_t size);
char isKeysEqual(const char *key1, const char *key2, const size_t size);
char findNode(const Map *map, const MapEntry key, Node *dest);
int findNodeIndex(const Map *map, const MapEntry key, List **dest);
void freeNode(Node);

Map *map_create() {
  Map *map = malloc(sizeof(Map));
  map->bucket_count = INITIAL_BUCKET_COUNT;
  map->element_count = 0;
  map->buckets = malloc(sizeof(List *) * INITIAL_BUCKET_COUNT);
  for (int i = 0; i < INITIAL_BUCKET_COUNT; i++) {
    map->buckets[i] = list_create(sizeof(Node));
  }

  return map;
}

void map_destroy(Map *map) {
  for (int i = 0; i < map->bucket_count; i++) {
    List *currBacket = map->buckets[i];
    const int bucketSize = list_size(currBacket);
    for (int i = 0; i < bucketSize; i++) {
      Node node;
      list_get_by_index(currBacket, i, &node);
      freeNode(node);
    }

    list_destroy(map->buckets[i]);
  }

  free(map->buckets);
  free(map);
}

void map_put(Map *map, const MapEntry key, const MapEntry value) {
  const int hash = get_hash(key.val, key.size);

  MapNodeKey nodeKey = {.size = key.size, .hash = hash};
  if (key.size <= KEY_SIZE_BYTES) {
    memcpy(&nodeKey.key, key.val, key.size);
  } else {
    nodeKey.keyAdr = malloc(key.size);
    memcpy(nodeKey.keyAdr, key.val, key.size);
  }

  void *rawVal = malloc(value.size);
  memcpy(rawVal, value.val, value.size);

  const MapNodeValue nodeValue = {.val = rawVal, .size = value.size};
  const Node node = {.key = nodeKey, .value = nodeValue};

  List *bucket;
  const int i = findNodeIndex(map, key, &bucket);
  if (i == -1) {
    bucket = map->buckets[(map->bucket_count - 1) & hash];
    list_add(bucket, &node);
    map->element_count++;
  } else {
    Node oldNode;
    list_get_by_index(bucket, i, &oldNode);
    freeNode(oldNode);

    list_replace(bucket, i, &node);
  }
}

void map_get(const Map *map, const MapEntry key, void *dest) {
  Node node;
  if (!findNode(map, key, &node)) {
    return;
  }

  memcpy(dest, node.value.val, node.value.size);
}

char map_contains_key(const Map *map, const MapEntry key) {
  Node node;
  if (!findNode(map, key, &node)) {
    return 0;
  }

  return 1;
}

char map_remove(Map *map, const MapEntry key) {
  List *bucket;
  const int index = findNodeIndex(map, key, &bucket);
  if (index == -1) {
    return 0;
  }

  list_remove(bucket, index);

  map->element_count--;
  return 1;
}

int map_size(const Map *map) { return map->element_count; }

char findNode(const Map *map, const MapEntry key, Node *dest) {
  List *bucket;

  const int index = findNodeIndex(map, key, &bucket);
  if (index == -1) {
    return 0;
  }

  list_get_by_index(bucket, index, dest);
  return 1;
}

void freeNode(Node node) {
  free(node.value.val);

  if (node.key.size > KEY_SIZE_BYTES) {
    free(node.key.keyAdr);
  }
}

int findNodeIndex(const Map *map, const MapEntry key, List **dest) {
  const int hash = get_hash(key.val, key.size);
  const int bucketIndex = (map->bucket_count - 1) & hash;
  List *bucket = map->buckets[bucketIndex];

  const int bucketSize = list_size(bucket);
  for (int i = 0; i < bucketSize; i++) {
    Node node;
    list_get_by_index(bucket, i, &node);

    if (node.key.hash != hash || node.key.size != key.size) {
      continue;
    }

    if (isKeysEqual(key.size <= KEY_SIZE_BYTES ? node.key.key : node.key.keyAdr,
                    key.val, key.size)) {
      *dest = bucket;
      return i;
    }
  }

  return -1;
}

char isKeysEqual(const char *key1, const char *key2, const size_t size) {
  for (int i = 0; i < size; i++) {
    if (key1[i] != key2[i]) {
      return 0;
    }
  }

  return 1;
}

int get_hash(const char val[], const size_t size) {
  int hash = 5381;

  for (int i = 0; i < size; i++) {
    hash = ((hash << 5) + hash) + val[i];
  }

  return hash;
}
