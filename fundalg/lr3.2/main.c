#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define XSTR(s) STR(s)
#define STR(s) #s

#define VECTOR_TYPE int
// для смены типа так же поменять -DVECTOR_TYPE в Makefile
// на "<type>"

#define FORMAT_SPECIFIER "%d" // для char " %c"

#define PRINT_SPECIFIER "%d"

#include "actions.h"
#include "vector.h"

VECTOR_TYPE copyFunc(VECTOR_TYPE val) { return val; }
void deleteFunc(VECTOR_TYPE val) { (void)val; }

void print_vector_ui(const char *name, const Vector *v) {
  if (v == NULL) {
    printf("%s: NULL\n", name);
    return;
  }
  printf("%s (Size: %zu, Cap: %zu): [ ", name, v->size, v->capacity);
  for (size_t i = 0; i < v->size; i++) {
    printf(PRINT_SPECIFIER " ", get_at_vector(v, i));
  }
  printf("]\n");
}

void clear_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int main() {
  Vector v1 = create_vector(2, copyFunc, deleteFunc);
  Vector v2 = create_vector(0, copyFunc, deleteFunc);
  Vector *v3 = NULL;

  int choice = 0;
  printf("тест с типом (%s) \n", XSTR(VECTOR_TYPE));

  while (choice != 10) {
    printf("\n");
    print_vector_ui("v1 (main)", &v1);
    print_vector_ui("v2 (copy)", &v2);
    print_vector_ui("v3 (new_copy, heap)", v3);
    printf("\n");

    printf("меню:\n");
    printf(" 1. push_back_vector (в v1)\n");
    printf(" 2. delete_at_vector (из v1)\n");
    printf(" 3. get_at_vector (из v1)\n");
    printf(" 4. copy_vector (v1 -> v2)\n");
    printf(" 5. copy_vector_new (v1 -> v3)\n");
    printf(" 6. vector_resize (для v1)\n");
    printf(" 7. erase_vector (для v1)\n");
    printf(" 8. is_equal_vector (v1 == v2?)\n");
    printf(" 9. delete_vector (для v3)\n");
    printf(" 10. Выход\n");
    printf("Ваш выбор: ");

    if (scanf("%d", &choice) != 1) {
      clear_stdin();
      continue;
    }
    clear_stdin();

    switch (choice) {
    case 1: {
      VECTOR_TYPE val;
      printf("Введите значение (%s): ", FORMAT_SPECIFIER);
      if (scanf(FORMAT_SPECIFIER, &val) != 1) {
        clear_stdin();
        break;
      }
      clear_stdin();
      push_back_vector(&v1, val);
      break;
    }

    case 2: {
      size_t index;
      printf("Введите индекс для удаления: ");
      if (scanf("%zu", &index) != 1) {
        clear_stdin();
        break;
      }
      clear_stdin();
      delete_at_vector(&v1, index);
      break;
    }

    case 3: {
      size_t index;
      printf("введите индекс для получения: ");
      if (scanf("%zu", &index) != 1) {
        clear_stdin();
        break;
      }
      clear_stdin();
      VECTOR_TYPE val = get_at_vector(&v1, index);
      printf("Значение по индексу %zu - " PRINT_SPECIFIER "\n ", index, val);
      break;
    }

    case 4: {
      copy_vector(&v2, &v1);
      printf("v1 скопирован в v2\n");
      break;
    }

    case 5: {
      if (v3 != NULL) {
        printf("сначала нужно удалить v3 (опция 9)\n");
      } else {

        v3 = copy_vector_new(&v1);

        if (v3 == NULL) {
          printf("copy_vector_new вернул NULL\n");
        } else {
          printf("v1 скопирован в v3 (в куче)\n");
        }
      }
      break;
    }

    case 6: {
      size_t cap;
      printf("введите новую вместимость для v1: ");
      if (scanf("%zu", &cap) != 1) {
        clear_stdin();
        break;
      }
      clear_stdin();
      if (vector_resize(&v1, cap) != 0) {
        printf("неудачно\n");
      } else {
        printf("успешно\n");
      }
      break;
    }

    case 7: {
      erase_vector(&v1);
      break;
    }

    case 8: {
      if (is_equal_vector(&v1, &v2)) {
        printf("v1 = v2\n");
      } else {
        printf("v1 != v2\n");
      }
      break;
    }

    case 9: {
      if (v3 == NULL) {
        printf("v3 и так NULL");
      } else {
        delete_vector(v3);
        v3 = NULL;
        printf("v3 удален из кучи\n");
      }
      break;
    }

    case 10: {
      break;
    }

    default:
      break;
    }
  }

  erase_vector(&v1);
  erase_vector(&v2);
  if (v3 != NULL) {
    delete_vector(v3);
  }

  return OK;
}
