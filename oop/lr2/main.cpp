#include "includes/eleven.hpp"
#include <exception>
#include <ios>
#include <iostream>
#include <ostream>
#include <stdexcept>

int main() {
  try {
    Eleven num1("A5");
    Eleven num2("1A");
    Eleven zero;

    std::cout << "Number1:" << num1.to_string() << std::endl;
    std::cout << "Number2:" << num2.to_string() << std::endl;
    std::cout << "Zero:" << zero.to_string() << std::endl;

    Eleven sum = num1.add(num2);
    std::cout << num1.to_string() << " + " << num2.to_string() << " = "
              << sum.to_string() << std::endl;

    Eleven diff = num1.subtract(num2);
    std::cout << num1.to_string() << " - " << num2.to_string() << " = "
              << diff.to_string() << std::endl;

    std::cout << "original num1 after operations: " << num1.to_string()
              << std::endl;

    Eleven num1_copy = num1.copy();
    std::cout << "Copy of num1: " << num1_copy.to_string() << std::endl;

    std::cout << std::boolalpha;
    std::cout << num1.to_string() << " > " << num2.to_string() << ": "
              << num1.is_greater_than(num2) << std::endl;

    std::cout << num1.to_string() << " < " << num2.to_string() << ": "
              << num1.is_less_than(num2) << std::endl;

    std::cout << num1.to_string() << " == " << num1_copy.to_string() << ": "
              << num1.is_equal_to(num1_copy) << std::endl;

    std::cout << num1.to_string() << " == " << num2.to_string() << ": "
              << num1.is_equal_to(num2) << std::endl;

    std::cout << "\n---test exeptions---\n" << std::endl;

    try {
      Eleven invalid_num("G12");

    } catch (const std::invalid_argument &e) {

      std::cerr << e.what() << std::endl;
    }

    try {
      num2.subtract(num1);

    } catch (const std::logic_error &e) {

      std::cerr << e.what() << std::endl;
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;

    return 1;
  }

  return 0;
}
