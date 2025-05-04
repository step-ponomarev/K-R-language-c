#include "tree.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Tree {
  TreeNode *root;
  size_t size;
  size_t deep;
};

int add_node(TreeNode *, const void *, const size_t);
TreeNode *create_node(const void *, const size_t);
int compare(const char *, const size_t, const char *, const size_t);
void destroy_node(TreeNode *);

Tree *tree_create() {
  Tree *tree = malloc(sizeof(Tree));
  tree->size = 0;
  tree->deep = 0;

  return tree;
}

void tree_destroy(Tree *tree) {
  destroy_node(tree->root);
  free(tree);
}

void destroy_node(TreeNode *node) {
  if (node == NULL) {
    return;
  }

  destroy_node(node->left);
  destroy_node(node->right);

  free(node->value.value);
  free(node);
}

void tree_add(Tree *tree, const void *val, const size_t size) {
  if (tree->size == 0) {
    tree->root = create_node(val, size);
    tree->size++;
    return;
  }

  TreeNode *root = tree->root;
  const int deep = add_node(root, val, size);
  if (deep == -1) { // already added
    return;
  }

  tree->size++;
  if (deep > tree->deep) {
    tree->deep = deep;
  }

  // TODO: реализовать норм всплытие
  if (tree->size / 2 < deep) {
    const char rotate_right =
        compare(root->value.value, root->value.size, val, size) < 0;

    TreeNode *new_root;
    if (rotate_right) { // right is deeper
      new_root = root->right;
      tree->root->right = new_root->left;
      new_root->left = tree->root;

      tree->root = new_root;
    } else { // left is depere
      new_root = root->left;
      tree->root->left = new_root->right;
      new_root->right = tree->root;

      tree->root = new_root;
    }

    tree->deep--;
  }
}

size_t tree_size(const Tree *t) { return t->size; }

/*
 *
 * Rreturns deep of added node, if exists return -1;
 *
 * */
int add_node(TreeNode *node, const void *curr_val, const size_t size) {
  const size_t compared =
      compare(node->value.value, node->value.size, curr_val, size);

  if (compared == 0) {
    return -1;
  }

  if (compared == -1) {
    if (node->right != NULL) {
      return 1 + add_node(node->right, curr_val, size);
    }

    node->right = create_node(curr_val, size);
    return 1;
  }

  if (node->left != NULL) {
    return 1 + add_node(node->left, curr_val, size);
  }

  node->left = create_node(curr_val, size);
  return 1;
}

TreeNode *tree_get_root(const Tree *tree) { return tree->root; }

TreeNode *create_node(const void *val, const size_t size) {
  TreeNode *node = malloc(sizeof(TreeNode));
  node->value.value = malloc(size);
  memcpy(node->value.value, val, size);
  node->left = NULL;
  node->right = NULL;

  return node;
}

int compare(const char *v1, const size_t s1, const char *v2, const size_t s2) {
  const size_t size = s1 > s2 ? s2 : s1;

  int i = 0;
  while (v1[i] == v2[i] && (i++ < size)) {
  };

  if (i == size && s1 == s2) {
    return 0;
  }

  if (i == size) {
    return s1 > s2 ? 1 : -1;
  }

  return v1[i] < v2[i] ? -1 : 1;
}
