#include "../compiler/tokenizer.h"
#include "../lib/char_utils.h"
#include "../lib/list.h"
#include "../lib/stack.h"
#include "../lib/tree.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 100
#define DEFAULT_COMPARE_LEN 6

char *get_str(const TreeNode *node, int compare_val) {
  if (node == NULL) {
    return "\0";
  }

  return substring(node->value.value, 0, compare_val);
}

void fill_stack(Stack *stack, TreeNode *node) {
  if (node == NULL) {
    return;
  }

  fill_stack(stack, node->right);

  Token curr;
  memcpy(&curr, node->value.value, sizeof(Token));
  stack_add(stack, &curr);

  fill_stack(stack, node->left);
}

int main(int argc, char *argv[]) {
  const int comp_val = argc == 1 ? DEFAULT_COMPARE_LEN : atoi(argv[1]);

  List *tokens = read_tokens();
  const size_t token_amount = list_size(tokens);

  Tree *sorted_identefiers = tree_create();
  for (int i = 0; i < token_amount; i++) {
    Token token;
    list_get_by_index(tokens, i, &token);

    if (token.type != IDENTEFIER) {
      continue;
    }

    tree_add(sorted_identefiers, token.val, token.size);
  }

  Stack *stack = create_stack(sizeof(Token));
  fill_stack(stack, tree_get_root(sorted_identefiers));

  while (!is_stack_empty(stack)) {
    Token token;
    stack_pop(stack, &token);
    printf("%s\n", token.val);
  }

  destroy_stack(stack);
  tree_destroy(sorted_identefiers);
  list_destroy(tokens);

  return 0;
}
