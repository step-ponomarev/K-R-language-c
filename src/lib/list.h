#ifndef LIST_H_
#define LIST_H_

#include <stddef.h>

typedef struct List List;

List *list_create(size_t);
void list_destroy(List *);

char list_get_by_index(const List *, const int, void *);
char list_remove(List *, const int);
char list_replace(List *, const int, const void *);

void list_add(List *, const void *);
char list_add_by_index(List *, int, const void *);

int list_size(const List *);

#endif // !LIST_H_
