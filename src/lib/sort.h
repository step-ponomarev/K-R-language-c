#ifndef SORT_H_
#define SORT_H_

#include <stddef.h>

typedef int Comparator(const void *, const void *);

void qsort(void *, const size_t, const size_t, Comparator *);

#endif
