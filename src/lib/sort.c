#include "sort.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(void *, const size_t, const size_t, const size_t);
void _qsort(void *, const size_t, int, int, Comparator *);

void qsort(void *base, const size_t elem_size, const size_t size,
           Comparator *comp) {
  _qsort(base, elem_size, 0, size - 1, comp);
}

void _qsort(void *base, size_t elem_size, int left, int right,
            Comparator *comp) {
  if (left >= right) {
    return;
  }

  swap(base, elem_size, left, (left + right) >> 1);
  int last = left;

  for (int i = left + 1; i <= right; i++) {
    if ((*comp)(base + (i * elem_size), base + (left * elem_size)) < 0) {
      swap(base, elem_size, ++last, i);
    }
  }

  swap(base, elem_size, left, last);
  _qsort(base, elem_size, left, last - 1, comp);
  _qsort(base, elem_size, last + 1, right, comp);
}

void swap(void *arr, const size_t elem_size, const size_t i1, const size_t i2) {
  if (i1 == i2) {
    return;
  }

  // TODO: for high elem_size use memcpy
  char *a = (char *)arr + elem_size * i1;
  char *b = (char *)arr + elem_size * i2;
  for (size_t i = 0; i < elem_size; ++i) {
    char tmp = a[i];
    a[i] = b[i];
    b[i] = tmp;
  }
}
