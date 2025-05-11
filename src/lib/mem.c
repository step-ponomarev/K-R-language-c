#include "mem.h"
#include "unistd.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>

#define MIN_MEM_BLOCK_SIZE 1024

typedef long _align;

typedef struct _header {
  struct {
    struct _header *prev;
    struct _header *next;
    unsigned s;
  } h;
  _align _;
} _header;

#define HEADER_SIZE sizeof(_header)

// |header:{size, ptr}|.....| - segment
static _header *FREE_MEM;

static void *RAM = NULL;
static size_t ALLOCATED_SIZE;

// TODO: Low segment size problem for requested less than HEADER_SIZE

static _header *_cut_segment(_header *, const unsigned);
static _header *_allocate_segment(const unsigned);
static _header *_remove_free_segment(_header *);
static _header *_find_segment(const unsigned);
static _header *_morecore(const unsigned);

void *mem_malloc(const unsigned size) {
  return ((void *)_find_segment(size) + HEADER_SIZE);
}

void mem_free(void *segment) {
  if (segment == NULL) {
    return;
  }

  _header *segment_header = (_header *)((segment - HEADER_SIZE));
  segment_header->h.next = NULL;
  segment_header->h.prev = NULL;

  if (FREE_MEM == NULL) {
    FREE_MEM = segment_header;
    return;
  }

  _header *cur = FREE_MEM;
  while (cur->h.next != NULL &&
         ((void *)cur->h.next < (void *)segment_header)) {
    cur = cur->h.next;
  }

  // merge with prev and next
  if ((void *)cur + HEADER_SIZE + cur->h.s == segment_header) {
    cur->h.s += HEADER_SIZE + segment_header->h.s;

    if (cur->h.next == (void *)cur + HEADER_SIZE + cur->h.s) {
      _header *tmp = cur->h.next;
      cur->h.next = tmp->h.next;
      if (cur->h.next != NULL) {
        cur->h.next->h.prev = cur;
      }

      cur->h.s += HEADER_SIZE + tmp->h.s;
    }
    return;
  }

  // merg curr and next
  if ((void *)cur->h.next ==
      (void *)segment_header + HEADER_SIZE + segment_header->h.s) {
    segment_header->h.s += cur->h.next->h.s + HEADER_SIZE;
    cur->h.next = NULL;
  }

  segment_header->h.next = cur->h.next;
  if (cur->h.next != NULL) {
    cur->h.next->h.prev = cur;
  }

  segment_header->h.prev = cur;
  cur->h.next = segment_header;
}

static _header *_find_segment(const unsigned size) {
  const unsigned find_size = sizeof(_header) + size;
  _header *next_segment = FREE_MEM;
  while (next_segment != NULL && next_segment->h.s < find_size) {
    next_segment = next_segment->h.next;
  }

  // segment not found
  if (next_segment == NULL) {
    _header *new_seg = _morecore(size);
    if (new_seg->h.s == size) {
      return _remove_free_segment(next_segment);
    }

    return _cut_segment(_morecore(size), size);
  }

  _header *curr = next_segment;
  while (curr != NULL) {
    // perfect fit
    if (curr->h.s == size) {
      return _remove_free_segment(curr);
    }

    if (curr->h.s > next_segment->h.s || curr->h.s < find_size) {
      curr = curr->h.next;
      continue;
    }

    next_segment = curr;
    curr = curr->h.next;
  }

  return _cut_segment(next_segment, size);
}

static _header *_remove_free_segment(_header *free_segment) {
  if (free_segment == NULL) {
    return NULL;
  }

  if (FREE_MEM == free_segment) {
    FREE_MEM = NULL;
    return free_segment;
  }

  if (free_segment->h.prev != NULL) {
    free_segment->h.prev->h.next = free_segment->h.next;
  }

  if (free_segment->h.next != NULL) {
    free_segment->h.next->h.prev = free_segment->h.prev;
  }

  free_segment->h.prev = NULL;
  free_segment->h.next = NULL;

  return free_segment;
}

static _header *_cut_segment(_header *segment, const unsigned size) {
  if (segment == NULL || segment->h.s < size + HEADER_SIZE) {
    return NULL;
  }

  _header *new_segment = (_header *)((void *)segment + segment->h.s - size);
  segment->h.s -= (size + HEADER_SIZE);

  new_segment->h.s = size;
  new_segment->h.prev = NULL;
  new_segment->h.next = NULL;

  return new_segment;
}

static _header *_morecore(const unsigned size) {
  if (FREE_MEM == NULL) {
    FREE_MEM = _allocate_segment(size);
    return FREE_MEM;
  }

  _header *cur = FREE_MEM;
  while (cur->h.next != NULL) {
    cur = cur->h.next;
  }

  _header *new_segment = _allocate_segment(size);
  new_segment->h.prev = cur;
  new_segment->h.next = NULL;

  cur->h.next = new_segment;

  return new_segment;
}

static _header *_allocate_segment(const unsigned size) {
  const unsigned data_size =
      (size >= MIN_MEM_BLOCK_SIZE ? size : MIN_MEM_BLOCK_SIZE);
  const unsigned allocate_size = data_size + sizeof(_header);

  _header *segment = (_header *)sbrk(allocate_size);
  ALLOCATED_SIZE += allocate_size;

  if (RAM == NULL) { // raw
    RAM = (void *)segment;
  }

  segment->h.prev = NULL;
  segment->h.next = NULL;
  segment->h.s = data_size;

  return segment;
}

int main() {
  int *digit = mem_malloc(sizeof(int));

  *digit = 228;

  printf("%d\n", *digit);

  printf("here1\n");
  mem_free(digit);
  printf("here2\n");
  char *c = mem_malloc(sizeof(char) * 12);
  printf("here3\n");
  for (int i = 0; i < 11; i++) {
    c[i] = getchar();
  }
  c[11] = '\0';

  printf("%s %d\n", c, *digit);

  return 0;
}
