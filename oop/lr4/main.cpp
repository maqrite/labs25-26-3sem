#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <typeinfo>

#include "./includes/Array.hpp"
#include "./includes/Figure.hpp"
#include "./includes/Polygon.hpp"
#include "includes/Point.hpp"

using T = double;
using FigureT = Figure<T>;
using PointT = Point<T>;
using ArrayT = Array<std::shared_ptr<FigureT>>;

void print_menu();
void add_figure(ArrayT &figures);
void print_all_figures(const ArrayT &figures);
void calculate_total_area(const ArrayT &figures);
void delete_figure(ArrayT &figures);
void clear_cin();
void demo_value_type_array();

int main() {
  demo_value_type_array();

  ArrayT figures;
  std::string command;

  while (1) {
    print_menu();
    std::cin >> command;

    if (command == "add") {
      add_figure(figures);
    } else if (command == "print") {
      print_all_figures(figures);
    } else if (command == "area") {
      calculate_total_area(figures);
    } else if (command == "delete") {
      delete_figure(figures);
    } else if (command == "quit") {
      std::cout << "exit\n";
      break;
    } else {
      std::cout << "unknown command\n";
      clear_cin();
    }
  }

  return 0;
}

void print_menu() {
  std::cout << "add - добавить фигуру\n";
  std::cout << "print - напечатать все фигуры (центр, площадь, вершины)\n";
  std::cout << "area - вычислить общую площадь всех фигур\n";
  std::cout << "delete - удалить фигуру по индексу\n";
  std::cout << "quit - Выход\n";
}

void clear_cin() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void add_figure(ArrayT &figures) {
  std::string type;
  std::cout << "Введите тип фигуры (t - треугольник, s - квадрат, r - "
               "прямоугольник): ";
  std::cin >> type;

  std::shared_ptr<FigureT> new_fig = nullptr;
  int num_vertices = 0;

  if (type == "t") {
    new_fig = std::make_shared<Triangle<T>>();
    num_vertices = 3;
  } else if (type == "s") {
    new_fig = std::make_shared<Square<T>>();
    num_vertices = 4;
  } else if (type == "r") {
    new_fig = std::make_shared<Rectangle<T>>();
    num_vertices = 4;
  } else {
    std::cout << "Неизвестный тип фигуры\n";
    clear_cin();
    return;
  }

  std::cout << "Введите " << num_vertices
            << " вершин (в формате 'x y' каждая):\n";
  try {
    std::cin >> *new_fig;

    if (std::cin.fail()) {
      std::cout << "Ошибка ввода координат.\n";
      std::cin.clear();
      clear_cin();
      return;
    }

    figures.push_back(std::move(new_fig));
    std::cout << "Фигура добавлена\n";
  } catch (const std::exception &e) {
    std::cout << "Исключение: " << e.what() << '\n';
  }
}

void print_all_figures(const ArrayT &figures) {
  if (figures.size() == 0) {
    std::cout << "Фигур нет\n";
    return;
  }

  std::cout << "\n--- Все фигуры (" << figures.size() << ") ---\n";
  for (size_t i = 0; i < figures.size(); ++i) {
    const auto &fig_ptr = figures[i];

    std::cout << "Индекс: " << i << "\n";
    std::cout << "Тип: " << typeid(*fig_ptr).name() << "\n";
    std::cout << "Вершины: " << *fig_ptr << "\n";
    std::cout << "Центр: " << fig_ptr->geometricCenter() << "\n";
    std::cout << "Площадь: " << static_cast<double>(*fig_ptr) << "\n";
  }
}

void calculate_total_area(const ArrayT &figures) {
  double total_area = 0.0;
  for (size_t i = 0; i < figures.size(); ++i) {
    total_area += static_cast<double>(*figures[i]);
  }
  std::cout << "Общая площадь всех фигур в массиве: " << total_area << "\n";
}

void delete_figure(ArrayT &figures) {
  if (figures.size() == 0) {
    std::cout << "Массив пуст\n";
    return;
  }

  size_t index;
  std::cout << "Введите индекс фигуры для удаления от 0 до "
            << (figures.size() - 1) << ": ";

  if (!(std::cin >> index)) {
    std::cout << "Ошибка, введите число\n";
    std::cin.clear();
    clear_cin();
    return;
  }

  try {
    figures.remove(index);
    std::cout << "Фигура по индексу " << index << " удалена\n";
  } catch (const std::out_of_range &e) {
    std::cout << "Ошибка: " << e.what() << "\n";
  }
}

void demo_value_type_array() {
  std::cout << "\nДемонстрация Array<Square<int>>\n";
  Array<Square<int>> square_array;

  Square<int> sq1;
  std::cout << "Создаем Square<int>. Введите 4 вершины (целые числа 'x y'):\n";

  try {
    std::cin >> sq1;
    if (std::cin.fail()) {
      std::cout << "Ошибка ввода. Демонстрация прервана.\n";
      clear_cin();
      return;
    }
    square_array.push_back(sq1);

    Square<int> sq2;
    std::cout << "Введите еще 4 вершины для второго квадрата:\n";
    std::cin >> sq2;
    if (std::cin.fail()) {
      std::cout << "Ошибка ввода. Демонстрация прервана.\n";
      clear_cin();
      return;
    }
    square_array.push_back(std::move(sq2));

    std::cout << "В массиве Array<Square<int>> " << square_array.size()
              << " элемент(а).\n";
    std::cout << "Square[0]: " << square_array[0] << "\n";
    std::cout << "Площадь Square[0]: " << static_cast<double>(square_array[0])
              << "\n";
    std::cout << "Square[1]: " << square_array[1] << "\n";
    std::cout << "Площадь Square[1]: " << static_cast<double>(square_array[1])
              << "\n";

  } catch (const std::exception &e) {
    std::cout << "Ошибка в демонстрации: " << e.what() << "\n";
    clear_cin();
  }
}
