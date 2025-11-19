#include "includes/PmrStack.h"
#include "includes/Resource.hpp"
#include <iostream>
#include <string>
#include <vector>

struct ComplexData {
  int id;
  std::string name;

  ComplexData(int i, std::string n) : id(i), name(std::move(n)) {
    std::cout << "\t[ComplexData]: Создан объект ID=" << id << std::endl;
  }

  ~ComplexData() {
    std::cout << "\t[ComplexData]: Удален объект ID=" << id << std::endl;
  }

  friend std::ostream &operator<<(std::ostream &os, const ComplexData &cd) {
    os << "ID: " << cd.id << ", Name: \"" << cd.name << "\"";
    return os;
  }
};

void demo_int_stack(Resource &resource) {
  PmrStack<int> int_stack(&resource);

  int a, b, c, d;

  std::cout << "введите 3 элемента (int) для добавления в стек" << std::endl;
  std::cin >> a >> b >> c;

  std::cout << "1. Push элементов\n";
  int_stack.push(a);
  int_stack.push(b);
  int_stack.push(c);

  std::cout << "2. Top и Pop (демонстрация переиспользования)\n";
  std::cout << "Top: " << int_stack.top() << std::endl;
  int_stack.pop();
  std::cout << "new Top: " << int_stack.top() << std::endl;

  int_stack.push(99);

  std::cout << "3. Итерация\n";
  std::cout << "Содержимое стека (Top -> Bottom): ";
  for (int x : int_stack) {
    std::cout << x << " ";
  }
  std::cout << "\n";

  std::cout << "4. Выход из области видимости: int_stack уничтожается\n";
}

void demo_complex_stack(Resource &resource) {
  PmrStack<ComplexData> complex_stack(&resource);

  std::cout << "1. Push сложных объектов (Конструкторы вызываются\n";
  complex_stack.push(101, "Object_A");
  complex_stack.push(102, "Object_B");

  std::cout << "2. Top и Pop\n";
  std::cout << "Top: " << complex_stack.top() << std::endl;
  complex_stack.pop();

  std::cout << "3. Push нового объекта (Переиспользование)\n";
  complex_stack.push(103, "Object_C");

  std::cout << "4. Итерация\n";
  std::cout << "Содержимое стека:\n";
  for (const auto &item : complex_stack) {
    std::cout << " -> " << item << "\n";
  }

  std::cout << "5. Выход из области видимости: complex_stack уничтожается\n";
}

int main() {
  Resource resource;

  demo_int_stack(resource);

  demo_complex_stack(resource);

  return 0;
}
