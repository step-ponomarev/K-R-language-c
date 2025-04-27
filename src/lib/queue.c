#include "queue.h"
#include "linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 16
#define EXPAND_COEF 2

struct Queue {
  List *list;
  size_t element_size;
};

Queue *queue_create(size_t element_size) {
  Queue *queue = malloc(sizeof(Queue));
  queue->list = list_create(element_size);
  queue->element_size = element_size;

  return queue;
}

void queue_destroy(Queue *queue) {
  list_destroy(queue->list);
  free(queue);
}

void queue_poll(const Queue *queue, void *dest) {
  list_remove_head(queue->list, dest);
}

void queue_add(const Queue *queue, const void *elem) {
  list_add(queue->list, elem);
}

void queue_add_at_start(const Queue *queue, const void *elem) {
  list_add_by_index(queue->list, 0, elem);
}

size_t queue_size(const Queue *queue) { return list_size(queue->list); }
