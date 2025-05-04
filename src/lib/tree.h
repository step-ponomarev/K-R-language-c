#ifndef TREE_H_
#define TREE_H_

#include <stddef.h>

typedef struct TreeNodeValue {
  void *value;
  size_t size;
} TreeNodeValue;

typedef struct TreeNode {
  TreeNodeValue value;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

typedef struct Tree Tree;

Tree *tree_create();
void tree_destroy(Tree *);

void tree_add(Tree *, const void *, const size_t);
void tree_remove(Tree *, const void *, const size_t);
size_t tree_size(const Tree *);

TreeNode *tree_get_root(const Tree *);

#endif
