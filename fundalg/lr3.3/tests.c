#include "linkedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LIST_TYPE create_test_liver(unsigned int id, const char *surname, int year,
                            double income) {
  LIST_TYPE liver;
  liver.id = id;
  strncpy(liver.surname, surname, MAX_NAME_LEN - 1);
  liver.surname[MAX_NAME_LEN - 1] = '\0';
  strncpy(liver.name, "Test", MAX_NAME_LEN - 1);
  liver.name[MAX_NAME_LEN - 1] = '\0';
  liver.patronymic[0] = '\0';
  liver.dob.day = 1;
  liver.dob.month = 1;
  liver.dob.year = year;
  liver.gender = 'M';
  liver.avgIncome = income;
  return liver;
}

int compare_liver_by_id(const LIST_TYPE *l1, const LIST_TYPE *l2) {
  return l1->id == l2->id;
}

void cleanup_list_and_data(LinkedList *list, LIST_TYPE *data) {
  if (list)
    delete_list(list);
  if (data)
    free(data);
}

void test_basic_list_operations(void) {
  printf("Running tests for: Basic List Operations\n");
  LinkedList list = create_list();
  LIST_TYPE *data1 = NULL;
  LIST_TYPE *data2 = NULL;
  LIST_TYPE *data3 = NULL;
  LIST_TYPE *data_out = NULL;

  LIST_TYPE l1 = create_test_liver(10, "A", 2000, 1000.0);
  LIST_TYPE l2 = create_test_liver(20, "B", 1990, 2000.0);

  push_front_list(&list, &l1);
  assert(list.size == 1);
  data1 = get_at_list(&list, 0);
  assert(compare_liver_by_id(data1, &l1));
  free(data1);

  push_front_list(&list, &l2);
  assert(list.size == 2);
  data2 = get_at_list(&list, 0);
  assert(compare_liver_by_id(data2, &l2));
  free(data2);

  printf("Push Front OK.\n");

  LIST_TYPE l3 = create_test_liver(30, "C", 2010, 3000.0);
  push_back_list(&list, &l3);
  assert(list.size == 3);
  data3 = get_at_list(&list, 2);
  assert(compare_liver_by_id(data3, &l3));
  assert(compare_liver_by_id(list.tail->data, &l3));
  free(data3);

  printf("Push Back OK.\n");

  data_out = pop_back_list(&list);
  assert(compare_liver_by_id(data_out, &l3));
  free(data_out);
  assert(list.size == 2);
  data_out = pop_back_list(&list);
  assert(compare_liver_by_id(data_out, &l1));
  free(data_out);
  assert(list.size == 1);

  printf("Pop Back OK.\n");

  data_out = pop_front_list(&list);
  assert(compare_liver_by_id(data_out, &l2));
  free(data_out);
  assert(list.size == 0);
  assert(pop_front_list(&list) == NULL);

  printf("Pop Front OK.\n");

  push_back_list(&list, &l1);
  push_back_list(&list, &l2);
  insert_at_list(&list, 1, &l3);
  assert(list.size == 3);
  data_out = get_at_list(&list, 1);
  assert(compare_liver_by_id(data_out, &l3));
  free(data_out);

  printf("Insert At OK.\n");

  data_out = delete_at_list(&list, 0);
  assert(compare_liver_by_id(data_out, &l1));
  free(data_out);
  assert(list.size == 2);
  data_out = get_at_list(&list, 0);
  assert(compare_liver_by_id(data_out, &l3));
  free(data_out);

  data_out = delete_at_list(&list, 1);
  assert(compare_liver_by_id(data_out, &l2));
  free(data_out);
  assert(list.size == 1);

  printf("Delete At OK.\n");

  LinkedList list2 = create_list();
  push_back_list(&list2, &l3);
  assert(is_equal_list(&list, &list2));

  LIST_TYPE l4 = create_test_liver(40, "D", 2010, 3000.0);
  push_back_list(&list2, &l4);
  assert(!is_equal_list(&list, &list2));

  printf("Is Equal OK.\n");

  delete_list(&list);
  delete_list(&list2);
  printf("All Basic List Tests Passed.\n\n");
}

void test_stack_interface(void) {
  printf("Running tests for: Stack Interface\n");
  LinkedList stack = create_list();
  LIST_TYPE l1 = create_test_liver(1, "S1", 2000, 100.0);
  LIST_TYPE l2 = create_test_liver(2, "S2", 2000, 200.0);
  LIST_TYPE *data_out = NULL;

  assert(stack.size == 0);
  assert(pop_stack(&stack) == NULL);
  assert(peek_stack(&stack) == NULL);

  push_stack(&stack, &l1);
  assert(stack.size == 1);

  push_stack(&stack, &l2);
  assert(stack.size == 2);

  printf("Push Stack OK.\n");

  data_out = peek_stack(&stack);
  assert(compare_liver_by_id(data_out, &l2));
  free(data_out);
  assert(stack.size == 2);

  printf("Peek Stack OK.\n");

  data_out = pop_stack(&stack);
  assert(compare_liver_by_id(data_out, &l2));
  free(data_out);
  assert(stack.size == 1);

  data_out = pop_stack(&stack);
  assert(compare_liver_by_id(data_out, &l1));
  free(data_out);
  assert(stack.size == 0);

  printf("Pop Stack OK.\n");

  delete_list(&stack);
  printf("All Stack Interface Tests Passed.\n\n");
}

void test_queue_interface(void) {
  printf("Running tests for: Queue Interface\n");
  LinkedList queue = create_list();
  LIST_TYPE l1 = create_test_liver(1, "Q1", 2000, 100.0);
  LIST_TYPE l2 = create_test_liver(2, "Q2", 2000, 200.0);
  LIST_TYPE *data_out = NULL;

  assert(queue.size == 0);
  assert(dequeue(&queue) == NULL);
  assert(peek_queue(&queue) == NULL);

  enqueue(&queue, &l1);
  assert(queue.size == 1);

  enqueue(&queue, &l2);
  assert(queue.size == 2);

  printf("Enqueue OK.\n");

  data_out = peek_queue(&queue);
  assert(compare_liver_by_id(data_out, &l1));
  free(data_out);
  assert(queue.size == 2);

  printf("Peek Queue OK.\n");

  data_out = dequeue(&queue);
  assert(compare_liver_by_id(data_out, &l1));
  free(data_out);
  assert(queue.size == 1);

  data_out = dequeue(&queue);
  assert(compare_liver_by_id(data_out, &l2));
  free(data_out);
  assert(queue.size == 0);

  printf("Dequeue OK.\n");

  delete_list(&queue);
  printf("All Queue Interface Tests Passed.\n\n");
}

int main(void) {
  test_basic_list_operations();
  test_stack_interface();
  test_queue_interface();

  printf("\nAll internal tests completed successfully.\n");
  return 0;
}
