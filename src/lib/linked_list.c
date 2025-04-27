#include "linked_list.h"
#include "list.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct List {
  Node *head;
  Node *tail;
  size_t size;
  size_t element_size;
};

struct Node {
  Node *prev;
  Node *next;
  void *val;
};

void freeNodes(Node *);
void freeNode(Node *);
Node *find_node_by_index(const List *, const int);

List *list_create(const size_t element_size) {
  List *list = malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->element_size = element_size;
  list->size = 0;

  return list;
}

void list_destroy(List *list) {
  if (list->head) {
    freeNodes(list->head);
  }

  free(list);
}

void list_add(List *list, const void *elem) {
  Node *newNode = malloc(sizeof(Node));
  newNode->val = malloc(list->element_size);
  memcpy(newNode->val, elem, list->element_size);

  if (list->size == 0) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
  }

  list->size++;
}

void list_remove_head(List *list, void *dest) {
  if (list->size == 0) {
    return;
  }

  memcpy(dest, list->head->val, list->element_size);

  Node *prevHead = list->head;
  if (prevHead == list->tail) {
    list->tail = NULL;
    list->head = NULL;
  } else {
    list->head = prevHead->next;
    list->head->prev = NULL;
  }
  freeNode(prevHead);

  list->size--;
}

void list_remove_tail(List *list, void *dest) {
  if (list->size == 0) {
    return;
  }

  memcpy(dest, list->tail->val, list->element_size);

  Node *prevTail = list->tail;
  if (prevTail == list->head) {
    list->tail = NULL;
    list->head = NULL;
  } else {
    list->tail = prevTail->prev;
    list->head->next = NULL;
  }
  freeNode(prevTail);

  list->size--;
}

char list_get_by_index(const List *list, const int i, void *dest) {
  const Node *node = find_node_by_index(list, i);
  if (!node) {
    return 0;
  }

  memcpy(dest, node->val, list->element_size);

  return 1;
}

char list_remove(List *list, const int i) {
  Node *node = find_node_by_index(list, i);
  if (!node) {
    return 0;
  }

  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    if (node->prev) {
      node->prev->next = node->next;
    }

    if (node->next) {
      node->next->prev = node->prev;
    }
  }
  freeNode(node);

  list->size--;
  return 1;
}

char list_replace(List *list, const int i, const void *elem) {
  Node *node = find_node_by_index(list, i);
  if (!node) {
    return 0;
  }

  memcpy(node->val, elem, list->element_size);
  return 1;
}

char list_add_by_index(List *list, int i, const void *elem) {
  if (i == list->size) {
    list_add(list, elem);
    return 1;
  }

  Node *node = find_node_by_index(list, i);
  if (!node) {
    return 0;
  }

  Node *newNode = malloc(sizeof(Node));
  newNode->prev = node->prev;
  newNode->next = node;

  newNode->val = malloc(list->element_size);
  memcpy(newNode->val, elem, list->element_size);

  if (node->prev) {
    node->prev->next = newNode;
  } else {
    list->head = newNode;
  }

  list->size++;

  return 1;
}

int list_size(const List *list) { return list->size; }

Node *find_node_by_index(const List *list, const int i) {
  if (i >= list->size) {
    return NULL;
  }

  const char startFromEnd = i > list->size / 2;
  Node *curr = startFromEnd ? list->tail : list->head;
  int startI = startFromEnd ? list->size - 1 : 0;
  while (startI != i) {
    curr = startFromEnd ? curr->prev : curr->next;
    startI = startFromEnd ? startI - 1 : startI + 1;
  }

  return curr;
}

void freeNodes(Node *node) {
  if (!node) {
    return;
  }

  freeNodes(node->next);
  freeNode(node);
}

void freeNode(Node *node) {
  if (!node) {
    return;
  }

  free(node->val);
  free(node);
}
