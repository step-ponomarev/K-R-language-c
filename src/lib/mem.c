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

// |header:{size, ptr}|.....| - segment
static _header *MEM;

static _header *_cut_segment(_header *, const unsigned);
static _header *_allocate_segment(const unsigned);
static _header *_remove_free_segment(_header *);
static _header *_find_segment(const unsigned);
static _header *_morecore(const unsigned);

void *mem_malloc(const unsigned size) {
  return ((void *)_find_segment(size) + sizeof(_header));
}

void mem_free(void *segment) {
  if (segment == NULL) {
    return;
  }
  // find neither segment
  // merge if available
}

static _header *_find_segment(const unsigned size) {
  const unsigned find_size = sizeof(_header) + size;
  _header *next_segment = MEM;
  while (next_segment != NULL && next_segment->h.s < find_size) {
    next_segment = next_segment->h.next;
  }

  // segment not found
  if (next_segment == NULL) {
    return _morecore(size);
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
  }

  return _cut_segment(next_segment, size);
}

static _header *_remove_free_segment(_header *free_segment) {
  if (free_segment == NULL) {
    return NULL;
  }

  if (MEM == free_segment) {
    MEM = NULL;
    return free_segment;
  }

  if (free_segment->h.prev != NULL) {
    free_segment->h.prev->h.next = free_segment->h.next;
  }

  if (free_segment->h.next != NULL) {
    free_segment->h.next->h.prev = free_segment->h.prev;
  }

  return free_segment;
}

static _header *_cut_segment(_header *segment, const unsigned size) {
  if (segment == NULL || segment->h.s < size + sizeof(_header)) {
    return NULL;
  }

  _header *new_segment = segment + segment->h.s - size;

  segment->h.s -= size + sizeof(_header);

  new_segment->h.s = size;
  new_segment->h.prev = segment;
  new_segment->h.next = segment->h.next;

  return new_segment;
}

static _header *_morecore(const unsigned size) {
  if (MEM == NULL) {
    MEM = _allocate_segment(size);
    return MEM;
  }

  _header *cur = MEM;
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
  segment->h.prev = NULL;
  segment->h.next = NULL;
  segment->h.s = data_size;

  return segment;
}

int main() {
  int *i = mem_malloc(sizeof(int));

  *i = 228;

  printf("%d\n", *i);

  return 0;
}
