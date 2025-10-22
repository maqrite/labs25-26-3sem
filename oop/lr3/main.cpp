#include <iostream>
#include <limits>
#include <string>
#include <typeinfo>

#include "./includes/Array.hpp"
#include "./includes/Polygon.hpp"

void print_menu();
void add_figure(Array &figures);
void print_all_figures(const Array &figures);
void calculate_total_area(const Array &figures);
void delete_figure(Array &figures);
void clear_cin();

int main() {
  Array figures;
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
  std::cout << "Меню:\n";
  std::cout << "add - добавить фигуру\n";
  std::cout << "print - напечатать все фигуры (центр, площадь, вершины)\n";
  std::cout << "area - вычислить общую площадь всех фигур\n";
  std::cout << "delete - удалить фигуру по индексу\n";
  std::cout << "quit - Выход\n";
  std::cout << "Введите команду: ";
}

void clear_cin() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void add_figure(Array &figures) {
  std::string type;
  std::cout << "введите тип фигуры (t - треугольник, h - 6ти угольник, o - 8ми "
               "угольник)";
  std::cin >> type;

  Figure *new_fig = nullptr;

  int num_vertices = 0;

  if (type == "t") {
    new_fig = new Triangle();
    num_vertices = 3;
  } else if (type == "h") {
    new_fig = new Hexagon();
    num_vertices = 6;
  } else if (type == "o") {
    new_fig = new Octagon();
    num_vertices = 8;
  } else {
    std::cout << "неизвестный тип фигуры\n";
    return;
  }

  std::cout << "Введите " << num_vertices
            << " вершин (в формате 'x y' каждая):\n";
  try {
    std::cin >> *new_fig;

    if (std::cin.fail()) {
      std::cout << "Ошибка ввода координат.\n";
      delete new_fig;
      std::cin.clear();
      clear_cin();
      return;
    }

    figures.push_back(new_fig);
    std::cout << "фигура добавлена\n";
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
    delete new_fig;
  }
}

void print_all_figures(const Array &figures) {
  if (figures.size() == 0) {
    std::cout << "фигур нет";
    return;
  }

  for (size_t i = 0; i < figures.size(); ++i) {
    Figure *fig = figures[i];

    std::cout << "Индекс " << i << "\n";
    std::cout << "Тип " << typeid(*fig).name() << "\n";
    std::cout << "Вершины " << *fig << "\n";
    std::cout << "Центр " << fig->geometricCenter() << "\n";
    std::cout << "Площадь" << static_cast<double>(*fig) << "\n";
  }
}

void calculate_total_area(const Array &figures) {
  double total_area = 0.0;
  for (size_t i = 0; i < figures.size(); ++i) {
    total_area += static_cast<double>(*figures[i]);
  }
  std::cout << "Общая площадь всех фигур в массиве: " << total_area << "\n";
}

void delete_figure(Array &figures) {
  if (figures.size() == 0) {
    std::cout << "Массив пуст\n";
    return;
  }

  size_t index;
  std::cout << "Введите индекс фигуры для удаления от 0 до "
            << figures.size() - 1;

  if (!(std::cin >> index)) {
    std::cout << "Ошибка, введите число\n";
    std::cin.clear();
    clear_cin();
    return;
  }

  try {
    figures.remove(index);
    std::cout << "Фигура по индексу " << index << "Удалена\n";
  } catch (const std::out_of_range &e) {
    std::cout << e.what() << "\n";
  }
}
