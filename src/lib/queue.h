#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>

typedef struct Queue Queue;

Queue *queue_create(const size_t element_size);
void queue_destroy(Queue *);

void queue_add(const Queue *, const void *);
void queue_add_at_start(const Queue *, const void *);
void queue_poll(const Queue *, void *);

size_t queue_size(const Queue *);
char queue_is_empty(const Queue *);

#endif
