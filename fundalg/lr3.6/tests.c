#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "stack.h"

void test_areBracketsPaired() {
  printf("Running tests for: areBracketsPaired...\n");
  assert(areBracketsPaired('(', ')'));
  assert(areBracketsPaired('[', ']'));
  assert(areBracketsPaired('{', '}'));
  assert(areBracketsPaired('<', '>'));

  assert(!areBracketsPaired('(', ']'));
  assert(!areBracketsPaired('{', ')'));
  assert(!areBracketsPaired('a', 'b'));
  printf("Passed.\n");
}

void test_stack_operations() {
  printf("Running tests for: Stack operations...\n");
  node *stack = NULL;

  assert(isEmpty(&stack) == true);
  assert(peek(&stack) == -1);
  assert(pop(&stack) == -1);

  push(&stack, 'a');
  assert(isEmpty(&stack) == false);
  assert(peek(&stack) == 'a');

  push(&stack, 'b');
  assert(peek(&stack) == 'b');

  pop(&stack);
  assert(peek(&stack) == 'a');

  pop(&stack);
  assert(isEmpty(&stack) == true);

  printf("Passed.\n");
}

void test_check_brackets() {
  printf("Running tests for: check_brackets...\n");

  assert(check_brackets("") == OK);
  assert(check_brackets("abc no brackets") == OK);
  assert(check_brackets("()") == OK);
  assert(check_brackets("()[]{}<>") == OK);
  assert(check_brackets("(<[{}]>)") == OK);
  assert(check_brackets("({a} [b] <c> (d))") == OK);
  assert(check_brackets("int main() { return 0; }") == OK);

  assert(check_brackets("(") == INVALID_INPUT);
  assert(check_brackets(")") == INVALID_INPUT);
  assert(check_brackets("([)]") == INVALID_INPUT);
  assert(check_brackets("(]") == INVALID_INPUT);
  assert(check_brackets("())") == INVALID_INPUT);
  assert(check_brackets("{{{") == INVALID_INPUT);
  assert(check_brackets("text <other text] (") == INVALID_INPUT);

  printf("Passed.\n");
}

int main() {
  test_areBracketsPaired();
  test_stack_operations();
  test_check_brackets();

  printf("\nAll internal tests passed successfully!\n");
  return 0;
}
