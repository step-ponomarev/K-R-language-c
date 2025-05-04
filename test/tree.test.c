#include "../src/lib/tree.h"
#include "../src/lib/asserts.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void tree_print(TreeNode *node) {
  if (node == NULL) {
    return;
  }

  int val;
  memcpy(&val, node->value.value, sizeof(int));
  printf("%d", val);

  printf("\n");
  printf("left: ");
  tree_print(node->left);

  printf("\t");
  printf("right: ");
  tree_print(node->right);
}

void test_added_one_value_several_time() {
  Tree *tree = tree_create();

  const int val = 212;
  for (int i = 0; i < 10; i++) {
    tree_add(tree, &i, sizeof(int));
  }
  tree_print(tree_get_root(tree));

  assertEquals("Check size of tree", 1, tree_size(tree));
  tree_destroy(tree);
}

int main() {
  test_added_one_value_several_time();
  return 0;
}
