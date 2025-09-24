#include "function.hpp"

int countVowels(const string &str) {
  int counter = 0;

  for (int i = 0; i < str.length(); ++i) {
    char ch = str[i];

    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
      counter++;
    }
  }

  return counter;
}
