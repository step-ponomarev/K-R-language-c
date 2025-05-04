#include "../src/lib/tree.h"
#include "../src/lib/asserts.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void test_added_one_value_several_time() {
  Tree *tree = tree_create();

  const int val = 212;
  for (int i = 0; i < 100; i++) {
    tree_add(tree, &val, sizeof(int));
  }

  assertEquals("Check size of tree", 1, tree_size(tree));
  tree_destroy(tree);
}

int main() {
  test_added_one_value_several_time();
  return 0;
}
