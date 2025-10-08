#include "includes/eleven.hpp"

int main() {
  try {
    std::cout << "--- Testing String Constructor & Basic Operations ---"
              << std::endl;
    Eleven num1("A5");
    Eleven num2("1A");
    Eleven zero;

    std::cout << "Number 1 (from string \"A5\"): " << num1.to_string()
              << std::endl;
    std::cout << "Number 2 (from string \"1A\"): " << num2.to_string()
              << std::endl;
    std::cout << "Zero (from default constructor): " << zero.to_string()
              << std::endl;

    std::cout << "\n--- Testing New Constructors ---" << std::endl;

    Eleven fill_num(4, 10);
    std::cout << "From Eleven(4, 10): " << fill_num.to_string() << std::endl;

    Eleven list_num = {5, 10};
    std::cout << "From Eleven{5, 10}: " << list_num.to_string() << std::endl;

    std::cout << "Is num1 (\"A5\") equal to list_num ({5, 10})? "
              << std::boolalpha << num1.is_equal_to(list_num) << std::endl;

    std::cout << "\n--- Testing Arithmetic & Comparisons ---" << std::endl;

    Eleven sum = num1.add(num2);
    std::cout << num1.to_string() << " + " << num2.to_string() << " = "
              << sum.to_string() << std::endl;

    Eleven diff = num1.subtract(num2);
    std::cout << num1.to_string() << " - " << num2.to_string() << " = "
              << diff.to_string() << std::endl;

    Eleven num1_copy = num1.copy();
    std::cout << "Copy of num1: " << num1_copy.to_string() << std::endl;

    std::cout << num1.to_string() << " > " << num2.to_string() << ": "
              << num1.is_greater_than(num2) << std::endl;
    std::cout << num1.to_string() << " < " << num2.to_string() << ": "
              << num1.is_less_than(num2) << std::endl;
    std::cout << num1.to_string() << " == " << num1_copy.to_string() << ": "
              << num1.is_equal_to(num1_copy) << std::endl;

    std::cout << "\n--- Testing Exceptions ---" << std::endl;

    try {
      std::cout << "Trying to create Eleven(\"G12\")... ";
      Eleven invalid_num("G12");
    } catch (const std::invalid_argument &e) {
      std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }

    try {
      std::cout << "Trying to do num2.subtract(num1)... ";
      num2.subtract(num1);
    } catch (const std::logic_error &e) {
      std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }

    try {
      std::cout << "Trying to create Eleven(2, 11)... ";
      Eleven invalid_fill(2, 11);
    } catch (const std::invalid_argument &e) {
      std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }

    try {
      std::cout << "Trying to create Eleven({1, 12})... ";
      Eleven invalid_list = {1, 12};
    } catch (const std::invalid_argument &e) {
      std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }

  } catch (const std::exception &e) {
    std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
